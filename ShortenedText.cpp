#include <string>

#include "SDL.h"

#include "InputHandler.h"
#include "SDLUtility.h"
#include "ShortenedText.h"
#include "TextInput.h"
#include "UIElements.h"

ShortenenedText::ShortenenedText()
{
	maxtextwidth_ = 0;
	mousefunction_ = new MouseHandler();
	mousefunction_->Init(SDL_Rect{ 0, 0, 0, 0 });
	
	fulltext_.Init("meiryo.ttc", UIElements::STANDARD_UI_FONT_SIZE);
}

ShortenenedText::~ShortenenedText()
{
	InputHandler::RemoveMouseHandler(mousefunction_);
	delete mousefunction_;
	mousefunction_ = NULL;
	isshortened_ = false;
}

void ShortenenedText::SetArea(SDL_Rect textarea)
{
	mousefunction_->SetMouseArea(textarea);

	if (textarea.w != maxtextwidth_)
	{
		maxtextwidth_ = textarea.w;
		CreateFittedText(GetCurrentText());
	}
}

void ShortenenedText::SetMouseActive()
{
	InputHandler::AddMouseHandler(mousefunction_);
}

void ShortenenedText::CreateFittedText(std::string text)
{
	fulltext_.CreateTextureFromText(text);

	int textwidth = TextWidth(text);

	std::string showtext;
	if (textwidth > maxtextwidth_)
	{
		double proportiontoshow = static_cast<double>(maxtextwidth_) / static_cast<double>(textwidth);
		showtext = text.substr(0, static_cast<int>(text.length() * proportiontoshow));
		if (showtext.length() >= 3)
		{
			showtext = showtext.substr(0, showtext.length() - 3);
			showtext = showtext + "...";
		}

		CreateTextureFromText(showtext);
		isshortened_ = true;
	}
	else
	{
		showtext = text;
		CreateTextureFromText(showtext);		
	}

	SDL_Rect currentmousearea = mousefunction_->GetMouseArea();
	mousefunction_->SetMouseArea(SDL_Rect{ currentmousearea.x, currentmousearea.y, TextWidth(showtext), TextHeight() });
}

int ShortenenedText::GetMouseEvent()
{
	return mousefunction_->GetEvent();
}

void ShortenenedText::Show()
{
	SDL_Rect textarea = mousefunction_->GetMouseArea();

	SDLUtility::PostText(this, textarea.x, textarea.y);
}

void ShortenenedText::ShowFullHoverText()
{
	UIElements::ShowUIHoverText(&fulltext_);
}
