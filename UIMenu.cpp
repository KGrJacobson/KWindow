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

UIMenu::UIMenu()
{
	ResetMenu();
}

UIMenu::~UIMenu()
{
	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.begin(); ++it)
	{
		delete (*it);
	}

	optionlist_.clear();
	ResetMenu();
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
	menuarea_ = SDL_Rect{ 0, 0, 0, 0 };

	RemoveMouseHandler();
}

//Add a new button to the menu.
//newitem is the button to add.  The button should be dynamically
//  allocated and deletion is handled by the menu.
void UIMenu::AddListItem(UIButton *newitem)
{
	optionlist_.push_back(newitem);
	newitem->RemoveMouseHandler();
}

//Alter the text of a button based on the string provided.
//button is the index of the button to be changed.
//newname is a UTF8 string.
void UIMenu::RenameListItem(int button, std::string newname)
{
	optionlist_[button]->SetButtonText(newname);
}

//SetXY sets the rendering area of the button to exist on the screen
//and sets the MouseHandler of each button active.  Always call ResetMenu
//or RemoveMouseHandler before calling this function a second time.
void UIMenu::SetXY(int x, int y)
{
	int nextx = x;
	int nexty = y;
	int menuelementwidth = optionlist_[0]->GetButtonArea().w;
	int numberofelements = 0;

	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
	{
		if (numberofelements >= STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN)
		{
			nextx = nextx + menuelementwidth;
			nexty = y;
			numberofelements = 0;
		}

		(*it)->SetButtonCoordinates(nextx, nexty);
		nexty = nexty + STANDARD_CONTEXT_MENU_HEIGHT;

		(*it)->SetMouseHandler();

		++numberofelements;
	}

	menuarea_ = SDL_Rect{
		x,
		y,
		(optionlist_.size() < STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) ? menuelementwidth : 1 + static_cast<int>(static_cast<double>(optionlist_.size()) / STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN ) * menuelementwidth,
		(optionlist_.size() < STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) ? nexty - y : STANDARD_CONTEXT_MENU_HEIGHT * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN
	};
}

//Render the menu on screen
//numberofelementstoshow is the number of buttons to display on the menu
//  use -1 to display all the buttons.
void UIMenu::ShowMenu(int numberofelementstoshow)
{
	int currentbutton = 0;
	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != ((numberofelementstoshow == -1) ? optionlist_.end() : optionlist_.begin() + numberofelementstoshow); ++it)
	{
		UIElements::ShowUIContextMenu((*it));

		if ((*it)->GetMouseEvent() == LEFT_BUTTON_UP)
		{
			buttonpressed_ = currentbutton;
		}

		++currentbutton;
	}
}

SDL_Rect UIMenu::GetMenuArea()
{
	return menuarea_;
}

//Create a number of new buttons for the menu based on the argument provided.
//New buttons have their size based on the first button of the menu and are initialized
//with no text.  This function does not delete buttons if the size is smaller than the 
//current size.
//size is the minimum amount of buttons the list should have.
//fontsize is the size of the font for new buttons.
void UIMenu::ResizeList(unsigned int size, int fontsize)
{
	if (size > optionlist_.size())
	{
		int numberofnewelements = size - optionlist_.size();

		for (int newelement = 0; newelement < numberofnewelements; ++newelement)
		{
			optionlist_.push_back(new UIButton(optionlist_[0]->GetButtonArea(), "", fontsize, true));
		}
	}
}

//Deactivate mouse functionality for the menu.
void UIMenu::RemoveMouseHandler()
{
	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
	{
		(*it)->RemoveMouseHandler();
	}
}
