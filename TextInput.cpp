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
	TTF_CloseFont(font_);
	font_ = NULL;
}

int TextInput::Init(std::string ttffilepath, int fontsize)
{
	DestroyTexture();

	font_ = TTF_OpenFont(ttffilepath.c_str(), fontsize);
	if (font_ == NULL)
	{
		printf("Failed to load font SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

	return 0;
}

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

int TextInput::TextHeight()
{
	return TTF_FontHeight(font_);
}

