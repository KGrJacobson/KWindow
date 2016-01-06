#include "SDL.h"

#include "MouseHandler.h"
#include "SDLUtility.h"

void MouseHandler::Init(SDL_Rect initialmousearea)
{
	SetMouseArea(initialmousearea);
	ticks_ = 0;
	mouseevent_ = NO_MOUSE_STATE;
}

void MouseHandler::SetEvent(int eventtype)
{
	mouseevent_ = eventtype;
}

int MouseHandler::GetEvent()
{
	return mouseevent_;
}

void MouseHandler::SetMouseArea(SDL_Rect newmousearea)
{
	mousearea_ = newmousearea;
}

SDL_Rect MouseHandler::GetMouseArea()
{
	return mousearea_;
}

void MouseHandler::ShowMouseArea(SDL_Color setcolor)
{
	SDLUtility::CreateSquare(mousearea_, setcolor);
}

void MouseHandler::ResetMouseEvents()
{
	mouseevent_ = NO_MOUSE_STATE;
	ticks_ = 0;
}
