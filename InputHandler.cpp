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

void InputHandler::Init()
{
	Input_Handler_Inputs::keyboardentry_ = new KeyboardEntry();
}

void InputHandler::CloseInputs()
{
	delete Input_Handler_Inputs::keyboardentry_;
	Input_Handler_Inputs::keyboardentry_ = NULL;
	
	Input_Handler_Inputs::mousetoevaluate_ = NULL;
	Input_Handler_Inputs::previousmousevent_ = NULL;
	Input_Handler_Inputs::currentmouseevent_ = NULL;

	Input_Handler_Inputs::mouselist_.clear();
}

//Create a new mouse sensitive area by adding a MouseHandler to the InputHandler list.
//mousehandler is a pointer to an existing MouseHandler.  Do not add more than one of the same
//handler to the list at a time.  Only the current mouse event flag is altered by being in the list.  
//Deleting the object the pointer is associated with without removing it from the list will cause the
//program to crash.  Freeing the handler from memory, adjusting the area covered by the handler,
//removing the handler from the list, etc. must be managed by the object that initialy created the pointer.
void InputHandler::AddMouseHandler(MouseHandler *mousehandler)
{
	Input_Handler_Inputs::mouselist_.push_back(mousehandler);
}

//Remove mousehandler from the InputHandler list.
//mousehandler may not be in the list when the function is called without causing error.
void InputHandler::RemoveMouseHandler(MouseHandler *mousehandler)
{
	Input_Handler_Inputs::mouselist_.remove(mousehandler);
}

//HandleEvents alters class members to reflect new changes in user inputs.  Returned is
//an enum Key_Macro_Return_Code from KeyboardEntry denoting if a key macro has been pressed.
//Actual implementation of the key macro must be handled elsewhere.
//e is the global SDL_Event list.
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

//CheckMouseHandlers iterates through the list of active MouseHandlers and alters its mouse state enum depending on
//current user input (as handled in InputHandler::HandleEvents).  If the previous handler is different from the current,
//the previous handler is reset.
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

//Set a text texture (TextInput) object as the current recipient of keyboard input.  The previous texture held
//by the TextInput is erased and will be replaced by user input as handled in KeyboardEntry.
//textinput is a pointer to the text that is to be changed.
//textx is the x coordinate that textinput will be placed.  This is used for the kanji dropdown menu in the
//  Japanese IME mode.
//textlowesty is the y coordinate underneath where textinput will be place (y + height of the destination rectangle
//  of textinput)  This is used for the kanji dropdown menu in the Japanese IME mode.
void InputHandler::SetKeyboardEntryTexture(TextInput *textinput, int textx, int textlowesty)
{
	Input_Handler_Inputs::keyboardentry_->SetTexture(textinput, textx, textlowesty);
}

//IsKeyboardEntryNull is used if there is a default texture to be altered by KeyboardEntry input that is always active
//unless the window is not focused or a different texture needs to be altered.
bool InputHandler::IsKeyboardEntryNull()
{
	if (Input_Handler_Inputs::keyboardentry_->GetTexture() == NULL)
		return true;

	return false;
}

//Changes SDL mouse input flags to ones usable by MouseHandler.
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

//Show the kanji dropdown menu if it is active.
void InputHandler::ShowKeyboardInputMenu()
{
	Input_Handler_Inputs::keyboardentry_->ShowMenu();
}
