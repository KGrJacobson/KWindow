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

	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
	{
		(*it)->RemoveMouseHandler();
	}
}

void UIMenu::AddListItem(UIButton *newitem)
{
	optionlist_.push_back(newitem);
	newitem->RemoveMouseHandler();
}

void UIMenu::SetXY(int x, int y)
{
	int nextx = x;
	int nexty = y;
	int numberofelements = 0;

	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
	{
		if (numberofelements >= STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN)
		{
			nextx = nextx + STANDARD_CONTEXT_MENU_WIDTH;
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
		(optionlist_.size() < STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) ? STANDARD_CONTEXT_MENU_WIDTH : 1 + static_cast<int>(static_cast<double>(optionlist_.size()) / STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN ) * STANDARD_CONTEXT_MENU_WIDTH,
		(optionlist_.size() < STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN) ? nexty - y : STANDARD_CONTEXT_MENU_HEIGHT * STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN
	};
}

void UIMenu::ShowMenu()
{
	int currentbutton = 0;
	for (std::vector<UIButton*>::iterator it = optionlist_.begin(); it != optionlist_.end(); ++it)
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
