#ifndef TEXT_INPUT
#define TEXT_INPUT

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

//TextInput creates a texture of a string of text provided.  This class does not provide the area the
//text will be rendered to, just the texture itself.
class TextInput
{
public:
	TextInput();
	~TextInput();
	int Init(int fontsize);
	void CreateTextureFromText(std::string text);
	void CreateQuickTextureFromText(std::string text);
	SDL_Texture *GetTexture();
	int GetWidth();
	int GetHeight();
	std::string GetCurrentText();
	bool GetFinal();
	void DestroyTexture();
	int TextWidth(std::string text);
	int TextHeight();
private:
	SDL_Texture *texture_;
	TTF_Font *font_;
	std::string currenttext_;
	int imagewidth_;
	int imageheight_;
	bool isfinal_;
};

#endif //TEXT_INPUT