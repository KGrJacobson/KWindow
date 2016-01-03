#ifndef MOUSE_HANDLER
#define MOUSE_HANDLER

#include "SDL.h"

#include "DebugText.h"
#include "SDLUtility.h"

enum mousestate
{
	NO_MOUSE_STATE = -1,
	MOUSEOVER,
	LEFT_BUTTON_DOWN,
	LEFT_BUTTON_UP,
	RIGHT_BUTTON_DOWN,
	RIGHT_BUTTON_UP
};

class MouseHandler {
public:
	void Init(SDL_Rect initialmousearea);
	void SetEvent(int eventtype);
	int GetEvent();
	void SetMouseArea(SDL_Rect newmousearea);
	SDL_Rect GetMouseArea();
	void ShowMouseArea(SDL_Color setcolor);
	int GetTicks();
	void ResetMouseEvents();
private:
	int mouseevent_;
	bool isdown_;
	int ticks_;
	SDL_Rect mousearea_;
};

#endif //MOUSE_HANDLER