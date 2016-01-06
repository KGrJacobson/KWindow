#include <algorithm>
#include <list>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "SDLUtility.h"
#include "TextInput.h"
#include "UIElements.h"

TextInput::TextInput()
{
	texture_ = NULL;
	font_ = NULL;
	currenttext_ = "";
	isfinal_ = false;
}

TextInput::~TextInput()
{
	DestroyTexture();
	font_ = NULL;
}

//Reset texture and load font
int TextInput::Init(int fontsize)
{
	DestroyTexture();
	font_ = SDLUtility::GetFont(fontsize);

	return 0;
}

//Creates high quality texture from given text.  This text is considered "final" for KeyboardEntry purposes and
//will remove the texture from KeyboardEntry unpon being called.
void TextInput::CreateTextureFromText(std::string text)
{
	if (text == "")
	{
		DestroyTexture();
	}
	else
	{
		if (currenttext_ != text)
		{
			SDL_Surface *textsurface;

			textsurface = TTF_RenderUTF8_Blended(font_, text.c_str(), UIElements::GetUIElementColor(UIElements::TEXT_COLOR, UIElements::SOLID_COLOR));
			texture_ = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);

			imageheight_ = textsurface->h;
			imagewidth_ = textsurface->w;

			SDL_FreeSurface(textsurface);
			currenttext_ = text;
		}
	}

	isfinal_ = true;
}

//Creates low quality texture from given text.  This text is not considered "final" for KeyboardEntry purposes.
void TextInput::CreateQuickTextureFromText(std::string text)
{
	if (text == "")
	{
		DestroyTexture();
	}
	else
	{
		if (currenttext_ != text)
		{
			SDL_Surface *textsurface;

			textsurface = TTF_RenderUTF8_Solid(font_, text.c_str(), UIElements::GetUIElementColor(UIElements::TEXT_COLOR, UIElements::SOLID_COLOR));
			texture_ = SDL_CreateTextureFromSurface(SDLUtility::GetRenderer(), textsurface);

			imageheight_ = textsurface->h;
			imagewidth_ = textsurface->w;

			SDL_FreeSurface(textsurface);
			currenttext_ = text;
		}
	}

	isfinal_ = false;
}

SDL_Texture *TextInput::GetTexture()
{
	return texture_;
}

int TextInput::GetWidth()
{
	return imagewidth_;
}

int TextInput::GetHeight()
{
	return imageheight_;
}

std::string TextInput::GetCurrentText()
{
	return currenttext_;
}

//Returns true if CreateTextureFromText is called and false if CreateQuickTextureFromText
//is called.
bool TextInput::GetFinal()
{
	return isfinal_;
}

void TextInput::DestroyTexture()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		imagewidth_ = 0;
		imageheight_ = 0;
		currenttext_ = "";
	}
}

int TextInput::TextWidth(std::string text)
{
	int widthoftext;
	TTF_SizeUTF8(font_, text.c_str(), &widthoftext, NULL);

	return widthoftext;
}

//Text height is consistent based on the font size chosen.
int TextInput::TextHeight()
{
	return TTF_FontHeight(font_);
}

