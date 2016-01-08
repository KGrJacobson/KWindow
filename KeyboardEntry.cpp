#include <string>
#include <unordered_map>

#include "SDL.h"

#include "DebugText.h"
#include "KeyboardEntry.h"
#include "JPIME.h"
#include "TextInput.h"
#include "UIButton.h"
#include "UIElements.h"
#include "UIMenu.h"

//Initialize class members and create the kanji dropdown menu kanjimenu_.
KeyboardEntry::KeyboardEntry()
{
	isshift_ = false;
	isctrl_ = false;
	currentime_ = ENGLISH;
	currenttext_ = "";
	tempstring_ = "";
	nexttempchar_ = "";

	kanjimenu_.push_back(new UIMenu(UIElements::STANDARD_TINY_BUTTON_WIDTH * 2, UIElements::STANDARD_TINY_BUTTON_HEIGHT, 16));  //Onyomi
	kanjimenu_.push_back(new UIMenu(UIElements::STANDARD_TINY_BUTTON_WIDTH * 2, UIElements::STANDARD_TINY_BUTTON_HEIGHT, 16));  //Kunyomi
	kanjimenu_.push_back(new UIMenu(UIElements::STANDARD_TINY_BUTTON_WIDTH * 2, UIElements::STANDARD_TINY_BUTTON_HEIGHT, 16));  //Names

	menux_ = 0;
	menuy_ = 0;

	jpime_.Init();
	CloseMenu();

	hiraganamap_ = std::unordered_map<std::string, std::string>({
		//Syllabograms ending in 'a'
		{ "a",  u8"あ" },
		{ "ka",  u8"か" },
		{ "sa",  u8"さ" },
		{ "ta",  u8"た" },
		{ u8"んa",  u8"な" },
		{ "ha",  u8"は" },
		{ "ma",  u8"ま" },
		{ "ya",  u8"や" },
		{ "ra",  u8"ら" },
		{ "wa",  u8"わ" },
		{ "kya",  u8"きゃ" },
		{ "sha",  u8"しゃ" },
		{ "cha",  u8"ちゃ" },
		{ u8"んya",  u8"にゃ" },
		{ "hya",  u8"ひゃ" },
		{ "mya",  u8"みゃ" },
		{ "rya",  u8"りゃ" },
		{ "ga",  u8"が" },
		{ "za",  u8"ざ" },
		{ "da",  u8"だ" },
		{ "ba",  u8"ば" },
		{ "pa",  u8"ぱ" },
		{ "gya",  u8"ぎゃ" },
		{ "ja",  u8"じゃ" },
		{ "dya",  u8"ぢゃ" },
		{ "bya",  u8"びゃ" },
		{ "pya",  u8"ぴゃ" },

		//Syllabograms ending in 'i'
		{ "i",  u8"い" },
		{ "ki",  u8"き" },
		{ u8"んi",  u8"に" },
		{ "hi",  u8"ひ" },
		{ "mi",  u8"み" },
		{ "ri",  u8"り" },
		{ "wi",  u8"ゐ" },
		{ "shi",  u8"し" },
		{ "chi",  u8"ち" },
		{ "gi",  u8"ぎ" },
		{ "di",  u8"ぢ" },
		{ "bi",  u8"び" },
		{ "pi",  u8"ぴ" },
		{ "ji",  u8"じ" },
		
		//Syllabograms ending in 'u'
		{ "u",  u8"う" },
		{ "ku",  u8"く" },
		{ "su",  u8"す" },
		{ "tsu",  u8"つ" },
		{ u8"んu",  u8"ぬ" },
		{ "fu",  u8"ふ" },
		{ "mu",  u8"む" },
		{ "yu",  u8"ゆ" },
		{ "ru",  u8"る" },
		{ "kyu",  u8"きゅ" },
		{ "shu",  u8"しゅ" },
		{ "chu",  u8"ちゅ" },
		{ u8"んyu",  u8"にゅ" },
		{ "hyu",  u8"ひゅ" },
		{ "myu",  u8"みゅ" },
		{ "ryu",  u8"りゅ" },
		{ "gu",  u8"ぐ" },
		{ "zu",  u8"ず" },
		{ "du",  u8"づ" },
		{ "bu",  u8"ぶ" },
		{ "pu",  u8"ぷ" },
		{ "gyu",  u8"ぎゅ" },
		{ "ju",  u8"じゅ" },
		{ "byu",  u8"びゅ" },
		{ "pyu",  u8"ぴゅ" },

		//Syllabograms ending in 'e'
		{ "e",  u8"え" },
		{ "ke",  u8"け" },
		{ "se",  u8"せ" },
		{ "te",  u8"て" },
		{ u8"んe",  u8"ね" },
		{ "he",  u8"へ" },
		{ "me",  u8"め" },
		{ "re",  u8"れ" },
		{ "we",  u8"ゑ" },
		{ "ge",  u8"げ" },
		{ "ze",  u8"ぜ" },
		{ "de",  u8"で" },
		{ "be",  u8"べ" },
		{ "pe",  u8"ぺ" },

		//Syllabograms ending in 'o'
		{ "o",  u8"お" },
		{ "ko",  u8"こ" },
		{ "so",  u8"そ" },
		{ "to",  u8"と" },
		{ u8"んo",  u8"の" },
		{ "ho",  u8"ほ" },
		{ "mo",  u8"も" },
		{ "yo",  u8"よ" },
		{ "ro",  u8"ろ" },
		{ "wo",  u8"を" },
		{ "kyo",  u8"きょ" },
		{ "sho",  u8"しょ" },
		{ "cho",  u8"ちょ" },
		{ u8"んyo",  u8"にょ" },
		{ "hyo",  u8"ひょ" },
		{ "myo",  u8"みょ" },
		{ "ryo",  u8"りょ" },
		{ "go",  u8"ご" },
		{ "zo",  u8"ぞ" },
		{ "do",  u8"ど" },
		{ "bo",  u8"ぼ" },
		{ "po",  u8"ぽ" },
		{ "gyo",  u8"ぎょ" },
		{ "jo",  u8"じょ" },
		{ "byo",  u8"びょ" },
		{ "pyo",  u8"ぴょ" }
	});
}

KeyboardEntry::~KeyboardEntry()
{
	if (currenttexttexture_ != NULL)
	{
		FinalizeCurrentText();
		currenttexttexture_ = NULL;
	}

	currenttext_ = "";
	tempstring_ = "";
	nexttempchar_ = "";
}

//Add a character to the currenttext_ string and create a new texture from it.
void KeyboardEntry::InsertCharacter(char character)
{
	if (character >= 'a' && character <= 'z' && isshift_ == true)
	{
		currenttext_ = currenttext_ + static_cast<char>(character - 32);
	}
	else
	{
		if (isshift_ == true)
		{
			switch (character)
			{
			case '0':
				currenttext_ = currenttext_ + ')';
				break;
			case '1':
				currenttext_ = currenttext_ + '!';
				break;
			case '2':
				currenttext_ = currenttext_ + '@';
				break;
			case '3':
				currenttext_ = currenttext_ + '#';
				break;
			case '4':
				currenttext_ = currenttext_ + '$';
				break;
			case '5':
				currenttext_ = currenttext_ + '%';
				break;
			case '6':
				currenttext_ = currenttext_ + '^';
				break;
			case '7':
				currenttext_ = currenttext_ + '&';
				break;
			case '8':
				currenttext_ = currenttext_ + '*';
				break;
			case '9':
				currenttext_ = currenttext_ + '(';
				break;
			case '/':
				currenttext_ = currenttext_ + '?';
				break;
			}
		}
		else
		{
			currenttext_ = currenttext_ + character;
		}
	}

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

//Add a string to the currenttext_ string and create a new texture from it.  The InsertCharacter counterpart is for user
//input from a keyboard, while this function is intended for larger strings such as those from the clipboard.
void KeyboardEntry::InsertString(std::string string)
{
	currenttext_ = currenttext_ + string;

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

//Delete the last character of currenttext_.  Mainly used when the user presses the backspace button.
void KeyboardEntry::DeleteCharacter()
{
	if (currenttext_ != "")
	{
		//if ()
		//	currenttext_ = currenttext_.substr(0, currenttext_.length() - 3);
		//else
			currenttext_.pop_back();
	}

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

//Adds a new texture for keyboard input and finalizes the current texture if possible.
//text is the text texture to receive user input.  Any text contained in the text is immediately deleted as well as the
//  texture itself.  It is possible to pass null so no keyboard input is received.
//textx is the x value of the destination rectangle for the text texture.  This is used to place the kanji dropdown menu in
//  Japanese IME mode.
//textlowesty is the y value of the lowest height (y + height) of the destination rectangle for the text texture.  
//  This is used to place the kanji dropdown menu in Japanese IME mode.
void KeyboardEntry::SetTexture(TextInput *text, int textx, int textlowesty)
{
	menux_ = textx;
	menuy_ = textlowesty;

	FinalizeCurrentText();

	currenttexttexture_ = text;
	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateQuickTextureFromText("|");
}

void KeyboardEntry::SetShift(bool isdown)
{
	isshift_ = isdown;
}

void KeyboardEntry::SetCTRL(bool isdown)
{
	isctrl_ = isdown;
}

//Create a high quality rendering of currenttext_ and reset the input variables.
void KeyboardEntry::FinalizeCurrentText()
{
	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateTextureFromText(currenttext_);

	currenttext_ = "";
	tempstring_ = "";
	CloseMenu();
}

//Add the character represented by current user key press as dictated by the IME to currenttext_.
//Returned is a key macro if one has been accessed.
//e is the global SDL event list.
int KeyboardEntry::KeyDownInput(const SDL_Event &e)
{
	char chartoadd = 0;

	if (isctrl_ != true)
	{
		switch (currentime_)
		{
		case ENGLISH:
			chartoadd = KeyDownInputEnglish(e);

			if (chartoadd != 0)
				InsertCharacter(chartoadd);
			break;
		case JAPANESE:
			if (isshift_ == false)
				KeyDownInputJapaneseHiragana(e);
			else
				KeyDownInputJapaneseKatakana(e);

			if (currenttexttexture_ != NULL)
				if (tempstring_ == "" && nexttempchar_ == "")
					currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
				else
					currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
			break;
		}

		switch (e.key.keysym.sym)
		{
		case SDLK_PERIOD:
			InsertCharacter('.');
			break;
		case SDLK_SLASH:
			InsertCharacter('/');
			break;
		case SDLK_0:
			InsertCharacter('0');
			break;
		case SDLK_1:
			InsertCharacter('1');
			break;
		case SDLK_2:
			InsertCharacter('2');
			break;
		case SDLK_3:
			InsertCharacter('3');
			break;
		case SDLK_4:
			InsertCharacter('4');
			break;
		case SDLK_5:
			InsertCharacter('5');
			break;
		case SDLK_6:
			InsertCharacter('6');
			break;
		case SDLK_7:
			InsertCharacter('7');
			break;
		case SDLK_8:
			InsertCharacter('8');
			break;
		case SDLK_9:
			InsertCharacter('9');
			break;
		case SDLK_LSHIFT:
			SetShift(true);
			break;
		case SDLK_RSHIFT:
			SetShift(true);
			break;
		case SDLK_LCTRL:
			SetCTRL(true);
			break;
		case SDLK_RCTRL:
			SetCTRL(true);
			break;
		}
	}
	else
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			return DELETE_CAPTIONS;
			break;
		case SDLK_e:
			currentime_ = ENGLISH;
			tempstring_ = "";
			return SET_TEXT_ENGLISH;
			break;
		case SDLK_j:
			currentime_ = JAPANESE;
			return SET_TEXT_JAPANESE;
			break;
		case SDLK_v:
			currenttext_ = currenttext_ + SDL_GetClipboardText();
			if (currenttexttexture_ != NULL)
				currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
			break;
		case SDLK_RETURN:
			return TEXT_FINALIZED;
			break;
		case SDLK_KP_ENTER:
			return TEXT_FINALIZED;
			break;
		}
	}

	return NO_MACRO;
}

//Return the character that represents the key pressed on the keyboard for the English IME.
char KeyboardEntry::KeyDownInputEnglish(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_SPACE:
		InsertCharacter(' ');
		break;
	case SDLK_BACKSPACE:
		DeleteCharacter();
		return 0;
	case SDLK_a:
		return 'a';
	case SDLK_b:
		return 'b';
	case SDLK_c:
		return 'c';
	case SDLK_d:
		return 'd';
	case SDLK_e:
		return 'e';
	case SDLK_f:
		return 'f';
	case SDLK_g:
		return 'g';
	case SDLK_h:
		return 'h';
	case SDLK_i:
		return 'i';
	case SDLK_j:
		return 'j';
	case SDLK_k:
		return 'k';
	case SDLK_l:
		return 'l';
	case SDLK_m:
		return 'm';
	case SDLK_n:
		return 'n';
	case SDLK_o:
		return 'o';
	case SDLK_p:
		return 'p';
	case SDLK_q:
		return 'q';
	case SDLK_r:
		return 'r';
	case SDLK_s:
		return 's';
	case SDLK_t:
		return 't';
	case SDLK_u:
		return 'u';
	case SDLK_v:
		return 'v';
	case SDLK_w:
		return 'w';
	case SDLK_x:
		return 'x';
	case SDLK_y:
		return 'y';
	case SDLK_z:
		return 'z';
	}

	return 0;
}

//Determine if the last key pressed can be transformed into the proper Japanese hiragana or add the current key
//pressed to the "on deck" string nexttempchar_ and/or tempstring_ to be potentially processed in
//the next key press.  Pressing Enter or Return while in Japanese IME mode will add the tempstring_
//and nexttempchar_ to currenttext_.
void KeyboardEntry::KeyDownInputJapaneseHiragana(const SDL_Event &e)
{
	if (ismenuactive_ == true)
		CloseMenu();

	switch (e.key.keysym.sym)
	{
	case SDLK_a:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			tempstring_ = tempstring_ + hiraganamap_[nexttempchar_ + 'a'];
			nexttempchar_ = "";
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + hiraganamap_["a"];
			nexttempchar_ = "";
		}
		break;
	case SDLK_b:
		if (std::string("b").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "b";
			}
			else
			{
				if (nexttempchar_ == "b")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "b";
		}
		break;
	case SDLK_c:
		if (std::string("c").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "c";
			}
			else
			{
				if (nexttempchar_ == "c")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "c";
		}
		break;
	case SDLK_d:
		if (std::string("d").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "d";
			}
			else
			{
				if (nexttempchar_ == "d")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "d";
		}
		break;
	case SDLK_e:
		if ((std::string("s h b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			tempstring_ = tempstring_ + hiraganamap_[nexttempchar_ + 'e'];
			nexttempchar_ = "";
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + hiraganamap_["e"];
			nexttempchar_ = "";
		}
		break;
	case SDLK_f:
		if (std::string("f").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "f";
			}
			else
			{
				if (nexttempchar_ == "f")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "f";
		}
		break;
	case SDLK_g:
		if (std::string("g").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "g";
			}
			else
			{
				if (nexttempchar_ == "g")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "g";
		}
		break;
	case SDLK_h:
		if (std::string("csh").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "h";
			}
			else
			{
				if (nexttempchar_ == "s")
				{
					nexttempchar_ = "sh";
				}
				else
				{
					if (nexttempchar_ == "c")
					{
						nexttempchar_ = "ch";
					}
					else
					{
						if (nexttempchar_ == "h" && nexttempchar_ != "sh" && nexttempchar_ != "ch")
						{
							tempstring_ = tempstring_ + u8"っ";
						}
					}
				}
			}
		}
		break;
	case SDLK_i:
		if ((std::string("sh ch b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			tempstring_ = tempstring_ + hiraganamap_[nexttempchar_ + 'i'];
			nexttempchar_ = "";
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + hiraganamap_["i"];
			nexttempchar_ = "";
		}
		break;
	case SDLK_j:
		if (std::string("j").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "j";
			}
			else
			{
				if (nexttempchar_ == "j")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "j";
		}
		break;
	case SDLK_k:
		if (std::string("k").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "k";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "k";
		}
		break;
	case SDLK_m:
		if (std::string("m").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "m";
			}
			else
			{
				if (nexttempchar_ == "m")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "m";
		}
		break;
	case SDLK_n:
		if (std::string(u8"ん").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = u8"ん";
			}
			else
			{
				if (nexttempchar_ == u8"ん")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = u8"ん";
		}
		break;
	case SDLK_o:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			tempstring_ = tempstring_ + hiraganamap_[nexttempchar_ + 'o'];
			nexttempchar_ = "";
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + hiraganamap_["o"];
			nexttempchar_ = "";
		}
		break;
	case SDLK_p:
		if (std::string("p").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "p";
			}
			else
			{
				if (nexttempchar_ == "p")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "p";
		}
		break;
	case SDLK_r:
		if (std::string("r").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "r";
			}
			else
			{
				if (nexttempchar_ == "r")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "r";
		}
		break;
	case SDLK_s:
		if (std::string("ts").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "s";
			}
			else
			{
				if (nexttempchar_ == "s" && nexttempchar_ != "ts")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
				else
				{
					if (nexttempchar_ == "t")
					{
						nexttempchar_ = "ts";
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "s";
		}
		break;
	case SDLK_t:
		if (std::string("t").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "t";
			}
			else
			{
				if (nexttempchar_ == "t")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "t";
		}
		break;
	case SDLK_u:
		if ((std::string("sh ch hy by d gy j ky my py ry ts w z f").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			tempstring_ = tempstring_ + hiraganamap_[nexttempchar_ + 'u'];
			nexttempchar_ = "";
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + hiraganamap_["u"];
			nexttempchar_ = "";
		}
		break;
	case SDLK_w:
		if (std::string("w").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "w";
			}
			else
			{
				if (nexttempchar_ == "w")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "w";
		}
		break;
	case SDLK_y:
		if (std::string("k h m r g b p").find(nexttempchar_) != std::string::npos || std::string(u8"ん").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "y";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					nexttempchar_ = "ky";
				}
				else
				{
					if (nexttempchar_ == u8"ん")
					{
						nexttempchar_ = u8"んy";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							nexttempchar_ = "hy";
						}
						else
						{
							if (nexttempchar_ == "m")
							{
								nexttempchar_ = "my";
							}
							else
							{
								if (nexttempchar_ == "m")
								{
									nexttempchar_ = "my";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										nexttempchar_ = "gy";
									}
									else
									{
										if (nexttempchar_ == "b")
										{
											nexttempchar_ = "by";
										}
										else
										{
											if (nexttempchar_ == "p")
											{
												nexttempchar_ = "py";
											}
											else
											{
												if (nexttempchar_ == "r")
												{
													nexttempchar_ = "ry";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "y";
		}
		break;
	case SDLK_z:
		if (std::string("z").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "z";
			}
			else
			{
				if (nexttempchar_ == "z")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "z";
		}
		break;
	case SDLK_MINUS:
		tempstring_ = tempstring_ + nexttempchar_ + u8"ー";
		nexttempchar_ = "";
		break;
	case SDLK_BACKSPACE:
		if (nexttempchar_ != "")
		{
				nexttempchar_.pop_back();
		}
		else
		{
			if (tempstring_ != "")
			{
				tempstring_.pop_back();
			}
			else
			{
				DeleteCharacter();
			}
		}
		break;
	case SDLK_RETURN:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	case SDLK_KP_ENTER:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	case SDLK_TAB:
		if (tempstring_ != "" || nexttempchar_ != "")
		{
			CreateKanjiFindMenu(tempstring_ + nexttempchar_);
			ismenuactive_ = true;
		}
		break;
	}
}

//Determine if the last key pressed can be transformed into the proper Japanese katakana or add the current key
//pressed to the "on deck" string nexttempchar_ and/or tempstring_ to be potentially processed in
//the next key press.  Pressing Enter or Return while in Japanese IME mode will add the tempstring_
//and nexttempchar_ to currenttext_.
void KeyboardEntry::KeyDownInputJapaneseKatakana(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_a:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"シャ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"チャ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"サ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"ハ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"バ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"ダ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"ガ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"ジャ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"カ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"マ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"パ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ラ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"タ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"ワ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"ヤ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"ザ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ン")
																			{
																				tempstring_ = tempstring_ + u8"ナ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"ヒャ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"キャ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"ミャ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"リャ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"ンy")
																								{
																									tempstring_ = tempstring_ + u8"ニャ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"ギャ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"ビャ";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"ピャ";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"ア";
			nexttempchar_ = "";
		}
		break;
	case SDLK_b:
		if (std::string("b").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "b";
			}
			else
			{
				if (nexttempchar_ == "b")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "b";
		}
		break;
	case SDLK_c:
		if (std::string("c").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "c";
			}
			else
			{
				if (nexttempchar_ == "c")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "c";
		}
		break;
	case SDLK_d:
		if (std::string("d").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "d";
			}
			else
			{
				if (nexttempchar_ == "d")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "d";
		}
		break;
	case SDLK_e:
		if ((std::string("s h b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "s")
			{
				tempstring_ = tempstring_ + u8"セ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"ヘ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"ベ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"デ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"ゲ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"ケ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"メ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"ペ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"レ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"テ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ヱ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"ゼ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ン")
															{
																tempstring_ = tempstring_ + u8"ネ";
																nexttempchar_ = "";
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"エ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_f:
		if (std::string("f").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "f";
			}
			else
			{
				if (nexttempchar_ == "f")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "f";
		}
		break;
	case SDLK_g:
		if (std::string("g").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "g";
			}
			else
			{
				if (nexttempchar_ == "g")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "g";
		}
		break;
	case SDLK_h:
		if (std::string("csh").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "h";
			}
			else
			{
				if (nexttempchar_ == "s")
				{
					nexttempchar_ = "sh";
				}
				else
				{
					if (nexttempchar_ == "c")
					{
						nexttempchar_ = "ch";
					}
					else
					{
						if (nexttempchar_ == "h" && nexttempchar_ != "sh" && nexttempchar_ != "ch")
						{
							tempstring_ = tempstring_ + u8"ッ";
						}
					}
				}
			}
		}
		break;
	case SDLK_i:
		if ((std::string("sh ch b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"シ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"ヒ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"ビ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"ヂ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"ギ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"キ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"ミ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"ピ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"リ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"チ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ヰ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"ジ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ン")
															{
																tempstring_ = tempstring_ + u8"ニ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "ch")
																{
																	tempstring_ = tempstring_ + u8"チ";
																	nexttempchar_ = "";
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"イ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_j:
		if (std::string("j").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "j";
			}
			else
			{
				if (nexttempchar_ == "j")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "j";
		}
		break;
	case SDLK_k:
		if (std::string("k").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "k";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "k";
		}
		break;
	case SDLK_m:
		if (std::string("m").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "m";
			}
			else
			{
				if (nexttempchar_ == "m")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "m";
		}
		break;
	case SDLK_n:
		if (std::string(u8"ン").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = u8"ン";
			}
			else
			{
				if (nexttempchar_ == u8"ン")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = u8"ン";
		}
		break;
	case SDLK_o:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"ショ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"チョ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"ソ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"ホ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ボ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"ド";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"ゴ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"ジョ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"コ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"モ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"ポ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ロ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"ト";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"ヲ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"ヨ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"ゾ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ン")
																			{
																				tempstring_ = tempstring_ + u8"ノ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"ヒョ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"キョ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"ミョ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"リョ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"ンy")
																								{
																									tempstring_ = tempstring_ + u8"ニョ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"ギョ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"ビョ";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"ピョ";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"オ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_p:
		if (std::string("p").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "p";
			}
			else
			{
				if (nexttempchar_ == "p")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "p";
		}
		break;
	case SDLK_r:
		if (std::string("r").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "r";
			}
			else
			{
				if (nexttempchar_ == "r")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "r";
		}
		break;
	case SDLK_s:
		if (std::string("ts").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "s";
			}
			else
			{
				if (nexttempchar_ == "s" && nexttempchar_ != "ts")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
				else
				{
					if (nexttempchar_ == "t")
					{
						nexttempchar_ = "ts";
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "s";
		}
		break;
	case SDLK_t:
		if (std::string("t").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "t";
			}
			else
			{
				if (nexttempchar_ == "t")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "t";
		}
		break;
	case SDLK_u:
		if ((std::string("sh ch hy by d gy j ky my py ry ts w z f").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"シュ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"チュ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"ス";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "f")
						{
							tempstring_ = tempstring_ + u8"フ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ブ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"ヅ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"グ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"ジュ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"ク";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"ム";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"プ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ル";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "ts")
															{
																tempstring_ = tempstring_ + u8"ツ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "y")
																{
																	tempstring_ = tempstring_ + u8"ユ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "z")
																	{
																		tempstring_ = tempstring_ + u8"ズ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == u8"ン")
																		{
																			tempstring_ = tempstring_ + u8"ヌ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == "hy")
																			{
																				tempstring_ = tempstring_ + u8"ヒュ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "ky")
																				{
																					tempstring_ = tempstring_ + u8"キュ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "my")
																					{
																						tempstring_ = tempstring_ + u8"ミュ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "ry")
																						{
																							tempstring_ = tempstring_ + u8"リュ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == u8"ンy")
																							{
																								tempstring_ = tempstring_ + u8"ニュ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == "gy")
																								{
																									tempstring_ = tempstring_ + u8"ギュ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "by")
																									{
																										tempstring_ = tempstring_ + u8"ビュ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "py")
																										{
																											tempstring_ = tempstring_ + u8"ピュ";
																											nexttempchar_ = "";
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"ウ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_w:
		if (std::string("w").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "w";
			}
			else
			{
				if (nexttempchar_ == "w")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "w";
		}
		break;
	case SDLK_y:
		if (std::string("k h m r g b p").find(nexttempchar_) != std::string::npos || std::string(u8"ン").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "y";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					nexttempchar_ = "ky";
				}
				else
				{
					if (nexttempchar_ == u8"ン")
					{
						nexttempchar_ = u8"ンy";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							nexttempchar_ = "hy";
						}
						else
						{
							if (nexttempchar_ == "m")
							{
								nexttempchar_ = "my";
							}
							else
							{
								if (nexttempchar_ == "m")
								{
									nexttempchar_ = "my";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										nexttempchar_ = "gy";
									}
									else
									{
										if (nexttempchar_ == "b")
										{
											nexttempchar_ = "by";
										}
										else
										{
											if (nexttempchar_ == "p")
											{
												nexttempchar_ = "py";
											}
											else
											{
												if (nexttempchar_ == "r")
												{
													nexttempchar_ = "ry";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "y";
		}
		break;
	case SDLK_z:
		if (std::string("z").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "z";
			}
			else
			{
				if (nexttempchar_ == "z")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "z";
		}
		break;
	case SDLK_MINUS:
		tempstring_ = tempstring_ + nexttempchar_ + u8"ー";
		nexttempchar_ = "";
		break;
	case SDLK_BACKSPACE:
		if (nexttempchar_ != "")
		{
			nexttempchar_.pop_back();
		}
		else
		{
			if (tempstring_ != "")
			{
				tempstring_.pop_back();
			}
			else
			{
				DeleteCharacter();
			}
		}
		break;
	case SDLK_RETURN:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	case SDLK_KP_ENTER:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	}
}

//Pressing tab while entering hiragana will pull up a dropdown menu showing all possible kanji that
//is represented by the kana entered.  The kana used is the combined combined tempstring_ and nexttempchar_
//and is represented in the text by the left and right square brackets around the text ([ and ] characters).
//kana is the combined tempstring_ and nexttempchar_.
void KeyboardEntry::CreateKanjiFindMenu(std::string kana)
{
	SDL_Rect currentmenuarea;

	std::vector<std::string> onlist = jpime_.GetKanji(kana, Japanese_IME::ONYOMI);
	std::vector<std::string> kunlist = jpime_.GetKanji(kana, Japanese_IME::KUNYOMI);
	std::vector<std::string> namelist = jpime_.GetKanji(kana, Japanese_IME::NAME);

	kanjimenu_[Japanese_IME::ONYOMI]->SetSizeOfMenu(onlist.size());
	kanjimenu_[Japanese_IME::KUNYOMI]->SetSizeOfMenu(kunlist.size());
	kanjimenu_[Japanese_IME::NAME]->SetSizeOfMenu(namelist.size());

	for (int onelement = 0; onelement != onlist.size(); ++onelement)
	{
		kanjimenu_[Japanese_IME::ONYOMI]->RenameMenuIndex(onelement, onlist[onelement]);
	}

	kanjimenu_[Japanese_IME::ONYOMI]->SetXY(menux_, menuy_);
	currentmenuarea = kanjimenu_[Japanese_IME::ONYOMI]->GetMenuArea();

	for (int kunelement = 0; kunelement != kunlist.size(); ++kunelement)
	{
		kanjimenu_[Japanese_IME::KUNYOMI]->RenameMenuIndex(kunelement, kunlist[kunelement]);
	}

	kanjimenu_[Japanese_IME::KUNYOMI]->SetXY(currentmenuarea.x + currentmenuarea.w, menuy_);
	currentmenuarea = kanjimenu_[Japanese_IME::KUNYOMI]->GetMenuArea();

	kanjimenu_[Japanese_IME::NAME]->SetXY(currentmenuarea.x + currentmenuarea.w, menuy_);
}

//Show the dropdown kanji menu if it is active and add the kanji to the text if the user has
//selected a button.
void KeyboardEntry::ShowMenu()
{
	bool closemenu = false;

	if (ismenuactive_ == true)
	{
		std::vector<std::string> onlist = jpime_.GetKanji(tempstring_ + nexttempchar_, Japanese_IME::ONYOMI);
		std::vector<std::string> kunlist = jpime_.GetKanji(tempstring_ + nexttempchar_, Japanese_IME::KUNYOMI);
		std::vector<std::string> namelist = jpime_.GetKanji(tempstring_ + nexttempchar_, Japanese_IME::NAME);

		if (kanjimenu_[Japanese_IME::ONYOMI]->GetButtonPress() != -1)
		{
			tempstring_ = "";
			nexttempchar_ = "";
			InsertString(onlist[kanjimenu_[Japanese_IME::ONYOMI]->GetButtonPress()]);
			closemenu = true;
		}
		
		if (kanjimenu_[Japanese_IME::KUNYOMI]->GetButtonPress() != -1)
		{
			tempstring_ = "";
			nexttempchar_ = "";
			InsertString(kunlist[kanjimenu_[Japanese_IME::KUNYOMI]->GetButtonPress()]);
			closemenu = true;
		}
		
		if (kanjimenu_[Japanese_IME::NAME]->GetButtonPress() != -1)
		{
			tempstring_ = "";
			nexttempchar_ = "";
			InsertString(namelist[kanjimenu_[Japanese_IME::NAME]->GetButtonPress()]);
			closemenu = true;
		}

		if (onlist.size() != 0)
		{
			kanjimenu_[Japanese_IME::ONYOMI]->ShowMenu(onlist.size());
		}

		if (kunlist.size() != 0)
		{	
			kanjimenu_[Japanese_IME::KUNYOMI]->ShowMenu(kunlist.size());
		}

		if (namelist.size() != 0)
		{
			kanjimenu_[Japanese_IME::NAME]->ShowMenu(namelist.size());
		}
	}

	if (closemenu == true)
		CloseMenu();
}

void KeyboardEntry::CloseMenu()
{
	kanjimenu_[Japanese_IME::ONYOMI]->ResetMenu();
	kanjimenu_[Japanese_IME::KUNYOMI]->ResetMenu();
	kanjimenu_[Japanese_IME::NAME]->ResetMenu();
	ismenuactive_ = false;
}

//Reset shift/CTRL macros if the user releases the shift/CTRL button.
//e is the global SDL Event list.
void KeyboardEntry::KeyUpInput(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LSHIFT:
		SetShift(false);
		break;
	case SDLK_RSHIFT:
		SetShift(false);
		break;
	case SDLK_LCTRL:
		SetCTRL(false);
		break;
	case SDLK_RCTRL:
		SetCTRL(false);
		break;
	}
}

TextInput *KeyboardEntry::GetTexture()
{
	return currenttexttexture_;
}
