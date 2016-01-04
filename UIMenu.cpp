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

void UIMenu::ResetMenu()
{
	buttonpressed_ = NO_CONTEXT_MENU_BUTTONS_PRESSED;
	menuarea_ = SDL_Rect{ 0, 0, 0, 0 };

	RemoveMouseHandler();
}

void UIMenu::AddListItem(UIButton *newitem)
{
	optionlist_.push_back(newitem);
	newitem->RemoveMouseHandler();
}

void UIMenu::RenameListItem(int button, std::string newname)
{
	optionlist_[button]->SetButtonText(newname);
}

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

void UIMenu::ResizeList(unsigned int size)
{
	if (size > optionlist_.size())
	{
		int numberofnewelements = size - optionlist_.size();

		for (int newelement = 0; newelement < numberofnewelements; ++newelement)
		{
			optionlist_.push_back(new UIButton(optionlist_[0]->GetButtonArea(), "", true));
		}
	}
}

void UIMenu::RemoveMouseHandler()
{
	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.begin(); ++it)
	{
		(*it)->RemoveMouseHandler();
	}
}

void UIMenu::AddMouseHandler(int numberofelementstoshow)
{
	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != ((numberofelementstoshow == -1) ? optionlist_.end() : optionlist_.begin() + numberofelementstoshow); ++it)
	{
		(*it)->SetMouseHandler();
	}
}
