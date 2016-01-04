#ifndef INPUT_HANDLER
#define INPUT_HANDLER
#include <list>

#include "SDL.h"

#include "UIMenu.h"
#include "KeyboardEntry.h"
#include "MouseHandler.h"
#include "ShortenedText.h"
#include "TextInput.h"

//Input_Handler_Inputs holds global values that are either limited to a single instance at a time
//(Mouse Handler variables) or a single instance for the entire program (keyboard entry, mouse event, etc.).
namespace Input_Handler_Inputs
{
	static MouseHandler *mousetoevaluate_ = NULL;
	static MouseHandler *previousmousevent_ = NULL;
	static MouseHandler *currentmouseevent_ = NULL;
	static int mouseevent_ = NO_MOUSE_STATE;
	static bool ismousedown_ = false;
	static std::list<MouseHandler*> mouselist_;
	static KeyboardEntry *keyboardentry_ = NULL;
}


class InputHandler
{
public:
	static void Init();
	static void CloseInputs();
	static void AddMouseHandler(MouseHandler *mousehandler);
	static void RemoveMouseHandler(MouseHandler *mousehandler);
	static void CheckMouseHandlers();
	static int HandleEvents(const SDL_Event &e);
	static void SetKeyboardEntryTexture(TextInput *textinput, int textx, int textlowesty);
	static bool IsKeyboardEntryNull();
	static int GetCurrentMouseState(int mouseevent_, bool isdown);
	static void ShowKeyboardInputMenu();
};

#endif //INPUT_HANDLER