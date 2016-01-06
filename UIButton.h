#ifndef UI_BUTTON
#define UI_BUTTON

#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "SDLUtility.h"
#include "TextInput.h"

//UIButton defines a mouse sensitive area that works exactly like the classic UI Element.  This class
//works very similarly to a MouseHandler object, but has an associated text texture and can be rendered
//easily with various functions in UI Elements.
class UIButton 
{
public:
	UIButton(SDL_Rect buttonarea, std::string text, int fontsize, bool istextcentered);
	~UIButton();
	int GetMouseEvent();
	SDL_Rect GetButtonArea();
	TextInput *GetText();
	bool IsTextCentered();
	void SetButtonText(std::string text);
	void SetButtonArea(SDL_Rect destrect);
	void SetButtonCoordinates(int x, int y);
	void SetMouseHandler();
	void RemoveMouseHandler();
private:
	SDL_Rect absolutecoordinatesrect_;
	TextInput buttontext_;
	MouseHandler mousefunction_;
	bool centertext_;
	bool donotresetarea_;
};

#endif //UI_BUTTON