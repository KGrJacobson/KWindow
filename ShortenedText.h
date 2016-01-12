#ifndef SHORTENED_TEXT
#define SHORTENED_TEXT
#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "TextInput.h"

//A subclass of TextInput that creates a rendering of text that can fit in a given
//width.  A preview of the full text is shown when the mouse is hovering over the
//area the text is rendered to.
class ShortenenedText : public TextInput
{
public:
	ShortenenedText();
	~ShortenenedText();
	void SetArea(SDL_Rect textarea);
	void SetMouseActive();
	void CreateFittedText(std::string text);
	void CreateQuickFittedText(std::string text);
	int GetMouseEvent();
	void Show();
	void ShowFullHoverText();
	std::string GetFullText();
private:
	int maxtextwidth_;
	MouseHandler *mousefunction_;
	bool isshortened_;
	TextInput fulltext_;
};

#endif //SHORTENED_TEXT