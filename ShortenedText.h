#ifndef SHORTENED_TEXT
#define SHORTENED_TEXT
#include <string>

#include "SDL.h"

#include "MouseHandler.h"
#include "TextInput.h"

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
private:
	int maxtextwidth_;
	MouseHandler *mousefunction_;
	bool isshortened_;
	TextInput fulltext_;
};

#endif //SHORTENED_TEXT