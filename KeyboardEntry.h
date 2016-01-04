#ifndef KEYBOARD_ENTRY
#define KEYBOARD_ENTRY

#include <string>
#include <unordered_map>
#include <vector>

#include "JPIME.h"
#include "TextInput.h"
#include "UIMenu.h"

class KeyboardEntry
{
public:
	enum Key_Macro_Return_Code
	{
		NO_MACRO,
		DELETE_CAPTIONS,
		SET_TEXT_ENGLISH,
		SET_TEXT_JAPANESE,
		TEXT_FINALIZED,
		CREATE_KANJI_TABLE
	};

	enum Key_IME
	{
		ENGLISH,
		JAPANESE
	};

	KeyboardEntry();
	~KeyboardEntry();
	void InsertCharacter(char character);
	void InsertString(std::string string);
	void DeleteCharacter();
	void SetTexture(TextInput *text, int textx, int textlowesty);
	void SetShift(bool isdown);
	void SetCTRL(bool isdown);
	void FinalizeCurrentText();
	int KeyDownInput(const SDL_Event &e);
	char KeyDownInputEnglish(const SDL_Event &e);
	void KeyDownInputJapaneseHiragana(const SDL_Event &e);
	void KeyDownInputJapaneseKatakana(const SDL_Event &e);
	void CreateKanjiFindMenu(std::string kana);
	void ShowMenu();
	void KeyUpInput(const SDL_Event &e);
	TextInput *GetTexture();
private:
	TextInput *currenttexttexture_;
	std::string currenttext_;
	std::string tempstring_;
	std::string nexttempchar_;
	bool isshift_;
	bool isctrl_;
	int currentime_;
	Japanese_IME jpime_;
	std::unordered_map<std::string, std::string> hiraganamap_;
	std::unordered_map<std::string, std::string> katakanamap_;
	std::vector<UIMenu> kanjimenu_;
	int menux_;
	int menuy_;
	bool ismenuactive_;
};

#endif //KEYBOARD_ENTRY