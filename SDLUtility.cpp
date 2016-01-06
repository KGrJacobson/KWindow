#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "DebugText.h"
#include "InputHandler.h"
#include "JPIME.h"
#include "NetworkUtility.h"
#include "SDLUtility.h"
#include "UIElements.h"

//Initialize SDL and create window/renderer/font.  Returns 0 if successful and -1 otherwise.
int SDLUtility::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	window = SDL_CreateWindow("OBS Captioning System",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREENW, SCREENH, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	int pngflag = IMG_INIT_PNG;
	if (!(IMG_Init(pngflag)))
	{
		std::cout << "could not initialize IMG PNG" << '\n';
		return -1;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "could not initialize TTF" << '\n';
		return -1;
	}
	else
	{
		std::string fontfilepath = "meiryo.ttc";

		tenptfont = TTF_OpenFont(fontfilepath.c_str(), 10);
		twelveptfont = TTF_OpenFont(fontfilepath.c_str(), 12);
		sixteenptfont = TTF_OpenFont(fontfilepath.c_str(), 16);
		thirtytwoptfont = TTF_OpenFont(fontfilepath.c_str(), 32);

		if (tenptfont == NULL || twelveptfont == NULL || sixteenptfont == NULL || thirtytwoptfont == NULL)
		{
			printf("Failed to load font SDL_ttf Error: %s\n", TTF_GetError());
			return -1;
		}
	}

	if (window == NULL || renderer == NULL)
	{
		std::cout << "could not create window/renderer" << '\n';
		return -1;
	}

	if (NetworkUtility::Init() == false)
	{
		return -1;
	}

	UIElements::Init();
	InputHandler::Init();

	return 0;
}

void SDLUtility::Close()
{
	UIElements::CloseLayouts();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	TTF_Quit(); 
	IMG_Quit();
	NetworkUtility::Close();
	SDL_Quit();
}

SDL_Renderer *SDLUtility::GetRenderer()
{
	return renderer;
}

//return a pointer to the TTF font based on the fontsize argument.  10pt font
//is the default.
TTF_Font *SDLUtility::GetFont(int fontsize)
{
	switch (fontsize)
	{
	case 10:
		return tenptfont;
	case 12:
		return twelveptfont;
	case 16:
		return sixteenptfont;
	case 32:
		return thirtytwoptfont;
	}

	return tenptfont;
}

int SDLUtility::GetScreenWidth()
{
	return SCREENW;
}

int SDLUtility::GetScreenHeight()
{
	return SCREENH;
}

//Returns a SDL_Rect containing the absolute coordinates and width/height of the rectangle based
//on the destination rectangle (destrect) provided.  This is for areas that do not have a definite
//position on screen and are position based on another rectangle.  See RelativeRect in SDLUtility
//header for more information.
SDL_Rect SDLUtility::GetAbsoluteRect(RelativeRect relativerect, SDL_Rect destrect)
{
	SDL_Rect absolutecoordinatesrect {
		static_cast<int>(destrect.x + (relativerect.x * static_cast<double>(destrect.w))),
		static_cast<int>(destrect.y + (relativerect.y * static_cast<double>(destrect.h))),
		static_cast<int>(relativerect.w * static_cast<double>(destrect.w)),
		static_cast<int>(relativerect.h * static_cast<double>(destrect.h))
	};

	return absolutecoordinatesrect;
}

void SDLUtility::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void SDLUtility::UpdateScreen()
{
	SDL_Color drawcolor = UIElements::GetUIElementColor(UIElements::BACKGROUND_COLOR, UIElements::SOLID_COLOR);

	SDL_SetRenderDrawColor(renderer, drawcolor.r, drawcolor.g, drawcolor.b, drawcolor.a);

	SDL_RenderPresent(renderer);
}

//Render an Image object as an image on the screen.  This PostImage stretchs the image
//to completely cover the screen.
void SDLUtility::PostImage(Image *img, int x, int y)
{
	SDL_Rect destrect{ x, y, img->GetWidth(), img->GetHeight() };

	SDL_RenderCopy(renderer, img->GetTexture(), NULL, &destrect);
}

//Render a TextInput object as text on screen at x, y coordinates.
void SDLUtility::PostText(TextInput *text, int x, int y)
{
	SDL_Rect destrect{ x, y, text->GetWidth(), text->GetHeight() };

	SDL_RenderCopy(renderer, text->GetTexture(), NULL, &destrect);
}

void SDLUtility::PostTexture(SDL_Texture *texure, int x, int y)
{
	SDL_RenderCopy(renderer, texure, NULL, NULL);
}

//Render an Image object as an image on the screen.  This PostImage does not stretch
//the image and just posts it "as is".
//sourcerect is the SDL_Rect representing the area of the image.
void SDLUtility::PostImage(Image *img, int x, int y, SDL_Rect sourcerect)
{
	SDL_Rect destrect{ x, y, sourcerect.w, sourcerect.h };

	SDL_RenderCopy(renderer, img->GetTexture(), &sourcerect, &destrect);
}

//Render a colored rectangle on screen.
//rect is the area of the rectangle to render.
//color is the RBGA value of the rectangle.
void SDLUtility::CreateSquare(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect(renderer, &rect);
}

//Render a colored rectangle with a border on screen.
//rect is the area of the rectangle to render.
//bordercolor is the RBGA value of the border.
//innercolor is the RBGA value of the rectangle.
void SDLUtility::CreateBorderedRect(SDL_Rect rect, SDL_Color bordercolor, SDL_Color innercolor)
{
	SDL_SetRenderDrawColor(renderer, innercolor.r, innercolor.g, innercolor.b, innercolor.a);
	SDL_RenderFillRect(renderer, &rect);
	
	SDL_SetRenderDrawColor(renderer, bordercolor.r, bordercolor.g, bordercolor.b, bordercolor.a);
	SDL_RenderDrawRect(renderer, &rect);
}

//Returns true if the mouse is within the area provided.
//mousecheckarea is the area to check the mouse in.
bool SDLUtility::IsMouseActive(SDL_Rect mousecheckarea)
{
	int mousex = -1;
	int mousey = -1;
	SDL_GetMouseState(&mousex, &mousey);

	if (mousex >= mousecheckarea.x && mousey >= mousecheckarea.y &&
		mousex <= mousecheckarea.x + mousecheckarea.w && mousey <= mousecheckarea.y + mousecheckarea.h)
	{
		return true;
	}

	return false;
}
