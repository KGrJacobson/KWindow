#include <algorithm>
#include <string>
#include <vector>

#include "SDL.h"

#include "UIMenu.h"
#include "InputHandler.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "UIButton.h"
#include "UIElements.h"

UIMenu::UIMenu(int menuwidth, int menuheight, int fontsize)
{
	menuwidth_ = menuwidth;
	menuheight_ = menuheight;
	fontsize_ = fontsize;

	mainmenuarea_ = new MouseHandler();
	additionalmenuarea_ = NULL;

	ResetMenu();
}

UIMenu::~UIMenu()
{
	delete mainmenuarea_;
	mainmenuarea_ = NULL;
	delete additionalmenuarea_;
	additionalmenuarea_ = NULL;
}

int UIMenu::GetButtonPress()
{
	return buttonpressed_;
}

//Remove the menu area, reset the button events, and remove the mouse function
//from the menu.
void UIMenu::ResetMenu()
{
	buttonpressed_ = NO_CONTEXT_MENU_BUTTONS_PRESSED;
	RemoveMouseHandler();
}

void UIMenu::SetSizeOfMenu(int sizeofmenu)
{
	if (sizeofmenu <= STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN)
	{
		mainmenuarea_->SetMouseArea(SDL_Rect{ 0, 0, menuwidth_, menuheight_ * sizeofmenu });
		InputHandler::RemoveMouseHandler(mainmenuarea_);

		if (additionalmenuarea_ != NULL)
		{
			delete additionalmenuarea_;
			additionalmenuarea_ = NULL;
		}
	}
	else
	{
		mainmenuarea_->SetMouseArea(SDL_Rect{ 
			0, 
			0, 
			menuwidth_ * (sizeofmenu / STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN),
			menuheight_ * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN 
		});
		InputHandler::RemoveMouseHandler(mainmenuarea_);

		if (additionalmenuarea_ == NULL)
			additionalmenuarea_ = new MouseHandler();
	
		additionalmenuarea_->SetMouseArea(SDL_Rect{
			0,
			0,
			menuwidth_,
			menuheight_ * (sizeofmenu % STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN)
		});
		InputHandler::RemoveMouseHandler(additionalmenuarea_);
	}

	for (int elements = optiontext_.size(); elements < sizeofmenu; ++elements)
	{
		TextInput newtext;
		newtext.Init(fontsize_);
		optiontext_.push_back(newtext);
	}
}

void UIMenu::RenameMenuIndex(int indexnumber, std::string newname)
{
	optiontext_[indexnumber].CreateTextureFromText(newname);
}


//SetXY sets the rendering area of the button to exist on the screen
//and sets the MouseHandler of each button active.  Always call ResetMenu
//or RemoveMouseHandler before calling this function a second time.
void UIMenu::SetXY(int x, int y)
{
	SDL_Rect currentmousearea = mainmenuarea_->GetMouseArea();
	mainmenuarea_->SetMouseArea(SDL_Rect{ x, y, currentmousearea.w, currentmousearea.h });
	InputHandler::AddMouseHandler(mainmenuarea_);

	if (additionalmenuarea_ != NULL)
	{
		currentmousearea = additionalmenuarea_->GetMouseArea();
		additionalmenuarea_->SetMouseArea(SDL_Rect{ x + mainmenuarea_->GetMouseArea().w, y, currentmousearea.w, currentmousearea.h } );
		InputHandler::AddMouseHandler(additionalmenuarea_);
	}
}

//Render the menu on screen
//numberofelementstoshow is the number of buttons to display on the menu
//  use -1 to display all the buttons.
void UIMenu::ShowMenu(int numberofelementstoshow)
{
	SDLUtility::CreateSquare(mainmenuarea_->GetMouseArea(), UIElements::GetUIElementColor(UIElements::CONTEXT_MENU_BACKGROUND_COLOR, UIElements::SOLID_COLOR));
	if (numberofelementstoshow > STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN && numberofelementstoshow % STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN != 0)
		SDLUtility::CreateSquare(additionalmenuarea_->GetMouseArea(), UIElements::GetUIElementColor(UIElements::CONTEXT_MENU_BACKGROUND_COLOR, UIElements::SOLID_COLOR));
	
	int selectedelement = -1;
	int mousex = -1;
	int mousey = -1;
	SDL_GetMouseState(&mousex, &mousey);
	switch (mainmenuarea_->GetEvent())
	{
	case MOUSEOVER:
		mousex = mousex - mainmenuarea_->GetMouseArea().x;
		mousey = mousey - mainmenuarea_->GetMouseArea().y;
		selectedelement = (mousey / menuheight_) + ((mousex / menuwidth_) * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN);
		break;
	case LEFT_BUTTON_UP:
		mousex = mousex - mainmenuarea_->GetMouseArea().x;
		mousey = mousey - mainmenuarea_->GetMouseArea().y;
		buttonpressed_ = (mousey / menuheight_) + ((mousex / menuwidth_) * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN);
		break;
	}

	if (additionalmenuarea_ != NULL && additionalmenuarea_->GetEvent() != NO_MOUSE_STATE)
	{
		switch (additionalmenuarea_->GetEvent())
		{
		case MOUSEOVER:
			mousex = mousex - additionalmenuarea_->GetMouseArea().x;
			mousey = mousey - additionalmenuarea_->GetMouseArea().y;
			selectedelement = ((mousey / menuheight_) + ((mousex / menuwidth_) * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN)) + ((mainmenuarea_->GetMouseArea().w / menuwidth_) * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN);
			break;
		case LEFT_BUTTON_UP:
			mousex = mousex - additionalmenuarea_->GetMouseArea().x;
			mousey = mousey - additionalmenuarea_->GetMouseArea().y;
			buttonpressed_ = ((mousey / menuheight_) + ((mousex / menuwidth_) * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN)) + ((mainmenuarea_->GetMouseArea().w / menuwidth_) * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN);
			break;
		}
	}

	for (int currentelement = 0; currentelement < ((numberofelementstoshow == -1) ? optiontext_.size() : numberofelementstoshow); ++currentelement)
	{
		if (currentelement == selectedelement)
		{
			SDLUtility::CreateSquare(
				SDL_Rect{ 
					mainmenuarea_->GetMouseArea().x + ((currentelement / STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) * menuwidth_),
					mainmenuarea_->GetMouseArea().y + ((currentelement % STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) * menuheight_),
					menuwidth_,
					menuheight_
				}, 
				UIElements::GetUIElementColor(UIElements::CONTEXT_MENU_ELEMENT_PRESSED_COLOR, UIElements::SOLID_COLOR));
		}

		SDLUtility::PostText(
			&optiontext_[currentelement], 
			mainmenuarea_->GetMouseArea().x + ((currentelement / STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) * menuwidth_),
			mainmenuarea_->GetMouseArea().y + ((currentelement % STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) * menuheight_)
			);
	}
}

SDL_Rect UIMenu::GetMenuArea()
{
	if (additionalmenuarea_ != NULL)
	{
		SDL_Rect mainarea = mainmenuarea_->GetMouseArea();
		SDL_Rect addarea = additionalmenuarea_->GetMouseArea();

		return SDL_Rect{ mainarea.x, mainarea.y, mainarea.w + addarea.w, mainarea.h };
	}

	return mainmenuarea_->GetMouseArea();
}

//Deactivate mouse functionality for the menu.
void UIMenu::RemoveMouseHandler()
{
	InputHandler::RemoveMouseHandler(mainmenuarea_);

	if (additionalmenuarea_ != NULL)
	{
		InputHandler::RemoveMouseHandler(additionalmenuarea_);
	}
}
