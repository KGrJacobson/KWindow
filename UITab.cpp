#include <list>

#include "SDL.h"

#include "DebugText.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "UITab.h"
#include "UIElements.h"
#include "UIButton.h"

//Initalize the rendering area, MouseHandler area, text displayed on the tab, the tab position in its list,
//and the context menu for the tab.
UITab::UITab(SDL_Rect tabarea, std::string text, int tabnumber, UIMenu *contextmenu)
{
	tabnumber_ = tabnumber;
	tabarea_ = tabarea;
	tabbutton_ = new UIButton(tabarea, text, UIElements::STANDARD_UI_FONT_SIZE, false);
	closebutton_ = new UIButton(SDL_Rect{ tabarea.x + tabarea.w - 20, tabarea.y, 20, UIElements::STANDARD_TAB_HEIGHT }, "X", UIElements::STANDARD_UI_FONT_SIZE, true);
	SetContextMenu(contextmenu);
}

UITab::~UITab()
{
	delete tabbutton_;
	tabbutton_ = NULL;
	delete closebutton_;
	closebutton_ = NULL;
	delete contextmenu_;
	contextmenu_ = NULL;
}

//Renders the tab on screen and returns a return code if necessary.
//Return codes details are listed in the enum in the UITab header file.
//isselected denotes if the tab is currently active.
int UITab::ShowTab(bool isselected)
{
	int returncode = NO_RETURN_VALUE;

	UIElements::ShowUITab(tabbutton_, isselected);

	if (SDLUtility::IsMouseActive(tabarea_) == true)
		UIElements::ShowUITinyButton(closebutton_);

	switch (tabbutton_->GetMouseEvent())
	{
	case LEFT_BUTTON_DOWN:
		returncode = MOVE_TAB;
		break;
	case LEFT_BUTTON_UP:
		returncode = SELECT_TAB;
		break;
	case RIGHT_BUTTON_UP:
		returncode = OPEN_CONTEXT_MENU;
		break;
	}

	if (closebutton_->GetMouseEvent() == LEFT_BUTTON_UP)
		returncode = CLOSE_TAB;

	if (contextmenu_->GetButtonPress() != UIMenu::NO_CONTEXT_MENU_BUTTONS_PRESSED)
		returncode = CHECK_CONTEXT_MENU;

	return returncode;
}

//Alter the rendering area and MouseHandler area for the tab.
void UITab::SetTabArea(SDL_Rect newarea)
{
	tabarea_ = newarea;
	tabbutton_->SetButtonArea(newarea);
	closebutton_->SetButtonCoordinates(tabarea_.x + tabarea_.w - 20, tabarea_.y);
}

void UITab::SetContextMenu(UIMenu *newmenu)
{
	contextmenu_ = newmenu;
}

void UITab::SetTabNumber(int number)
{
	tabnumber_ = number;
}

int UITab::GetTabNumber()
{
	return tabnumber_;
}

SDL_Rect UITab::GetTabArea()
{
	return tabarea_;
}

//Return the text texture of the tab.  This is used to rename
//the tab with KeyboardEntry.
TextInput *UITab::GetTabText()
{
	return tabbutton_->GetText();
}

int UITab::GetContextMenuAction()
{
	return contextmenu_->GetButtonPress();
}

//Return the context menu of the tab.  This is used to open
//the context menu for this tab.
UIMenu *UITab::GetContextMenu()
{
	return contextmenu_;
}
