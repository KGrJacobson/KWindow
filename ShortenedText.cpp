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
	
	fulltext_.Init(UIElements::STANDARD_UI_FONT_SIZE);
}

ShortenenedText::~ShortenenedText()
{
	InputHandler::RemoveMouseHandler(mousefunction_);
	delete mousefunction_;
	mousefunction_ = NULL;
	isshortened_ = false;
}

//Set the area in which the text is to be rendered.  Having the area set
//will provide the width necessary to determine where to shorten the text.
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

//Create a string of text that will fit in the width provided by SetArea.  SetArea
//must be called before this, or an error will occur.
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

//Render the text on screen. SetArea and CreateFittedText must be called before
//the texture is rendered to avoid error.
void ShortenenedText::Show()
{
	SDL_Rect textarea = mousefunction_->GetMouseArea();

	SDLUtility::PostText(this, textarea.x, textarea.y);
}

void ShortenenedText::ShowFullHoverText()
{
	UIElements::ShowUIHoverText(&fulltext_);
}

std::string ShortenenedText::GetFullText()
{
	return fulltext_.GetCurrentText();
}
