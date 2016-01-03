#ifndef DEBUG_TEXT
#define DEBUG_TEXT

#include <list>
#include <string>

#include "TextInput.h"

static std::list<TextInput*> messagelist;

//DebugText allows strings of text to be posted in the upper left corner of the screen at any time
//for debugging purposes.  This class cannot be instantiated and should only be used for debugging.
//A maximum of 30 messages can be on screen before the entire list of messages is cleared.
class DebugText
{
public:
	static void CreateMessage(std::string debugmessage);
	static void ClearMessages();
	static void PostMessages();
};

#endif //DEBUG_TEXT