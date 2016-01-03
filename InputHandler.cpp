#include <list>

#include "SDL.h"

#include "UIMenu.h"
#include "DebugText.h"
#include "InputHandler.h"
#include "KeyboardEntry.h"
#include "MouseHandler.h"
#include "ShortenedText.h"
#include "TextInput.h"
#include "UIElements.h"

void InputHandler::CloseInputs()
{
	delete Input_Handler_Inputs::keyboardentry_;
	Input_Handler_Inputs::keyboardentry_ = NULL;
	
	Input_Handler_Inputs::mousetoevaluate_ = NULL;
	Input_Handler_Inputs::previousmousevent_ = NULL;
	Input_Handler_Inputs::currentmouseevent_ = NULL;

	Input_Handler_Inputs::mouselist_.clear();
}

void InputHandler::AddMouseHandler(MouseHandler *mousehandler)
{
	Input_Handler_Inputs::mouselist_.push_back(mousehandler);
}

void InputHandler::RemoveMouseHandler(MouseHandler *mousehandler)
{
	Input_Handler_Inputs::mouselist_.remove(mousehandler);
}

int InputHandler::HandleEvents(const SDL_Event &e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		Input_Handler_Inputs::ismousedown_ = true;
		Input_Handler_Inputs::mouseevent_ = e.button.button;

		if (Global_UI_Element::currentmenu_ != NULL)
		{
			if (SDLUtility::IsMouseActive(Global_UI_Element::currentmenu_->GetMenuArea()) == false)
				UIElements::SetMenu(NULL, NULL, NULL);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		Input_Handler_Inputs::ismousedown_ = false;
		Input_Handler_Inputs::mouseevent_ = e.button.button;
		break;
	}

	switch (e.type)
	{
	case SDL_KEYUP:
		Input_Handler_Inputs::keyboardentry_->KeyUpInput(e);
		break;
	case SDL_KEYDOWN:
		switch (Input_Handler_Inputs::keyboardentry_->KeyDownInput(e))
		{
		case KeyboardEntry::DELETE_CAPTIONS:
			return KeyboardEntry::DELETE_CAPTIONS;
		case KeyboardEntry::SET_TEXT_ENGLISH:
			return KeyboardEntry::SET_TEXT_ENGLISH;
		case KeyboardEntry::SET_TEXT_JAPANESE:
			return KeyboardEntry::SET_TEXT_JAPANESE;
		case KeyboardEntry::TEXT_FINALIZED:
			return KeyboardEntry::TEXT_FINALIZED;
		}
		break;
	}

	return KeyboardEntry::NO_MACRO;
}

void InputHandler::CheckMouseHandlers()
{
	Input_Handler_Inputs::previousmousevent_ = Input_Handler_Inputs::currentmouseevent_;
	Input_Handler_Inputs::currentmouseevent_ = NULL;

	for (std::list<MouseHandler*>::iterator it = Input_Handler_Inputs::mouselist_.begin(); it != Input_Handler_Inputs::mouselist_.end(); ++it)
	{
		if (SDLUtility::IsMouseActive((*it)->GetMouseArea()) == true)
		{
			Input_Handler_Inputs::currentmouseevent_ = (*it);
		}
	}

	if (Input_Handler_Inputs::previousmousevent_ != NULL && Input_Handler_Inputs::previousmousevent_ != Input_Handler_Inputs::currentmouseevent_)
	{
		if (Input_Handler_Inputs::ismousedown_ == true)
			Input_Handler_Inputs::currentmouseevent_ = Input_Handler_Inputs::previousmousevent_;
		else
			Input_Handler_Inputs::previousmousevent_->ResetMouseEvents();
	}

	if (Input_Handler_Inputs::currentmouseevent_ != NULL)
	{
		Input_Handler_Inputs::currentmouseevent_->SetEvent(GetCurrentMouseState(Input_Handler_Inputs::mouseevent_, Input_Handler_Inputs::ismousedown_));
	}

	if (Input_Handler_Inputs::ismousedown_ != true)
		Input_Handler_Inputs::mouseevent_ = MOUSEOVER;
}

void InputHandler::SetKeyboardEntryTexture(TextInput *textinput)
{
	Input_Handler_Inputs::keyboardentry_->SetTexture(textinput);
}

bool InputHandler::IsKeyboardEntryNull()
{
	if (Input_Handler_Inputs::keyboardentry_->GetTexture() == NULL)
		return true;

	return false;
}

int InputHandler::GetCurrentMouseState(int mouseevent_, bool isdown)
{
	if (mouseevent_ == MOUSEOVER)
		return MOUSEOVER;

	if (isdown == true)
	{
		if (mouseevent_ == SDL_BUTTON_LEFT)
		{
			return LEFT_BUTTON_DOWN;
		}
		else
		{
			if (mouseevent_ == SDL_BUTTON_RIGHT)
				return RIGHT_BUTTON_DOWN;
		}
	}
	else
	{
		if (mouseevent_ == SDL_BUTTON_LEFT)
		{
			return LEFT_BUTTON_UP;
		}
		else
		{
			if (mouseevent_ == SDL_BUTTON_RIGHT)
				return RIGHT_BUTTON_UP;
		}
	}

	return NO_MOUSE_STATE;
}