#include <list>
#include <string>

#include "DebugText.h"
#include "SDLUtility.h"

//A message appears in the upper left corner of the screen with additional messages appearing below the previous
//and will remain until ClearMessages is called or 30 total messages are reached.
//debugmessage is a UTF8 string
void DebugText::CreateMessage(std::string debugmessage)
{
	if (messagelist.size() > 30)
		messagelist.clear();

	TextInput *newmessage = new TextInput;
	newmessage->Init(12);
	newmessage->CreateTextureFromText(debugmessage);

	messagelist.push_back(newmessage);
}

//Deletes all debug messages
void DebugText::ClearMessages()
{
	messagelist.clear();
}

//Show the messages on screen.  The only use of this function should be in the Main file at the end
//of the rendering loop.
void DebugText::PostMessages()
{
	int nexth = 0;

	for (std::list<TextInput*>::iterator it = messagelist.begin(); it != messagelist.end(); it++)
	{
		SDLUtility::PostText(*it, 0, nexth);

		nexth = nexth + (*it)->GetHeight();
	}
}
