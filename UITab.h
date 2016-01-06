#ifndef UI_TAB
#define UI_TAB
#include <list>

#include "SDL.h"

#include "MouseHandler.h"
#include "TextInput.h"
#include "UIButton.h"
#include "UIMenu.h"

//The UITab is very similar to a UI Button, but has functionality specific to existing in a TabBar.
//UITab is functional, but unfinished due to the current lack of a TabBar tab handling class.
class UITab {
public:
	enum UI_Tab_Return_Values
	{
		NO_RETURN_VALUE,
		CLOSE_TAB,
		SELECT_TAB,
		MOVE_TAB,
		OPEN_CONTEXT_MENU,
		CHECK_CONTEXT_MENU
	};

	UITab(SDL_Rect tabarea, std::string text, int tabnumber, UIMenu *contextmenu);
	~UITab();
	int ShowTab(bool isselected);
	void SetTabArea(SDL_Rect newarea);
	void SetContextMenu(UIMenu *newmenu);
	void SetTabNumber(int tabnumber);
	int GetTabNumber();
	SDL_Rect GetTabArea();
	TextInput *GetTabText();
	int GetContextMenuAction();
	UIMenu *GetContextMenu();
private:
	int tabnumber_;
	SDL_Rect tabarea_;
	UIButton *tabbutton_;
	UIButton *closebutton_;
	UIMenu *contextmenu_;
};

#endif //UI_TAB