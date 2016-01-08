#ifndef UI_MENU
#define UI_MENU

#include <vector>

#include "SDL.h"

#include "MouseHandler.h"
#include "UIButton.h"

//UIMenu defines a Menu UI Element that includes standard menu bars, context menus and dropdown menus.
//This class is about to go through a revamp.
class UIMenu
{
public:
	static const int STANDARD_CONTEXT_MENU_HEIGHT = 20;
	static const int STANDARD_CONTEXT_MENU_WIDTH = 200;
	static const int STANDARD_CONTEXT_MENU_NUMBER_OF_ELEMENTS_IN_COLUMN = 17;
	static const int NO_CONTEXT_MENU_BUTTONS_PRESSED = -1;

	UIMenu(int menuwidth, int menuheight, int fontsize);
	~UIMenu();
	int GetButtonPress();
	void ResetMenu();
	void SetSizeOfMenu(int sizeofmenu);
	void RenameMenuIndex(int indexnumber, std::string newname);
	void SetXY(int x, int y);
	void ShowMenu(int numberofelementstoshow);
	SDL_Rect GetMenuArea();
	void RemoveMouseHandler();
private:
	MouseHandler *mainmenuarea_;
	MouseHandler *additionalmenuarea_;
	std::vector<TextInput> optiontext_;
	int menuwidth_;
	int menuheight_;
	int fontsize_;
	int buttonpressed_;
};

#endif //UI_MENU