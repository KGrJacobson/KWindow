#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "DebugText.h"
#include "NetworkUtility.h"
#include "SDLUtility.h"
#include "UIElements.h"

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

int SDLUtility::GetScreenWidth()
{
	return SCREENW;
}

int SDLUtility::GetScreenHeight()
{
	return SCREENH;
}

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

void SDLUtility::PostImage(Image *img, int x, int y)
{
	SDL_Rect destrect{ x, y, img->GetWidth(), img->GetHeight() };

	SDL_RenderCopy(renderer, img->GetTexture(), NULL, &destrect);
}

void SDLUtility::PostText(TextInput *text, int x, int y)
{
	SDL_Rect destrect{ x, y, text->GetWidth(), text->GetHeight() };

	SDL_RenderCopy(renderer, text->GetTexture(), NULL, &destrect);
}

void SDLUtility::PostTexture(SDL_Texture *texure, int x, int y)
{
	SDL_RenderCopy(renderer, texure, NULL, NULL);
}

void SDLUtility::PostImage(Image *img, int x, int y, SDL_Rect sourcerect)
{
	SDL_Rect destrect{ x, y, sourcerect.w, sourcerect.h };

	SDL_RenderCopy(renderer, img->GetTexture(), &sourcerect, &destrect);
}

void SDLUtility::CreateSquare(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect(renderer, &rect);
}

void SDLUtility::CreateBorderedRect(SDL_Rect rect, SDL_Color bordercolor, SDL_Color innercolor)
{
	SDL_SetRenderDrawColor(renderer, innercolor.r, innercolor.g, innercolor.b, innercolor.a);
	SDL_RenderFillRect(renderer, &rect);
	
	SDL_SetRenderDrawColor(renderer, bordercolor.r, bordercolor.g, bordercolor.b, bordercolor.a);
	SDL_RenderDrawRect(renderer, &rect);
}

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
