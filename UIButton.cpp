#include <string>

#include "SDL.h"

#include "InputHandler.h"
#include "MouseHandler.h"
#include "SDLUtility.h"
#include "TextInput.h"
#include "UIButton.h"
#include "UIElements.h"

//Initialize rendering area, mouse handler area, text displayed on the button, the size of the text
//on the button and if the text is centered.  If the button is part of another UI Element, centering
//the text may be handled by that element rather than the button itself.
//buttonarea is the area the button will be rendered to and the active area for mouse events.
//text is a UTF8 string.
//fontsize is the size of the font.
//istextcentered denotes if the text is centered in the button or left justified.
UIButton::UIButton(SDL_Rect buttonarea, std::string text, int fontsize, bool istextcentered)
{
	absolutecoordinatesrect_ = buttonarea;
	buttontext_.Init(fontsize);
	buttontext_.CreateTextureFromText(text);
	centertext_ = istextcentered;
	donotresetarea_ = true;
	mousefunction_.Init(absolutecoordinatesrect_);
	InputHandler::AddMouseHandler(&mousefunction_);
}

UIButton::~UIButton()
{
	InputHandler::RemoveMouseHandler(&mousefunction_);
}

int UIButton::GetMouseEvent()
{
	return mousefunction_.GetEvent();
}

SDL_Rect UIButton::GetButtonArea()
{
	return absolutecoordinatesrect_;
}

TextInput *UIButton::GetText()
{
	return &buttontext_;
}

bool UIButton::IsTextCentered()
{
	return centertext_;
}

//Change the text displayed by the button.
//text is a UTF8 string.
void UIButton::SetButtonText(std::string text)
{
	buttontext_.CreateTextureFromText(text);
}

//Alter the area of the button on screen.  This alter the coordinates and
//size of the rendering area and the mouse handler.
void UIButton::SetButtonArea(SDL_Rect newarea)
{
	absolutecoordinatesrect_ = newarea;
	mousefunction_.SetMouseArea(newarea);
}

//Change the coordinates of the button.  This effect the rendering area
//and the mouse handler.
void UIButton::SetButtonCoordinates(int x, int y)
{
	absolutecoordinatesrect_.x = x;
	absolutecoordinatesrect_.y = y;

	SDL_Rect mouserect = mousefunction_.GetMouseArea();
	mousefunction_.SetMouseArea(SDL_Rect{ x, y, mouserect.w, mouserect.h });
}

//Activate mouse function for the button.  Do not call if the mouse is already
//active for the button.
void UIButton::SetMouseHandler()
{
	InputHandler::AddMouseHandler(&mousefunction_);
}

//Deactivate mouse function for the button.
void UIButton::RemoveMouseHandler()
{
	InputHandler::RemoveMouseHandler(&mousefunction_);
}
