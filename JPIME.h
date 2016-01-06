#ifndef JAPANESE_IME
#define JAPANESE_IME
#include <string>
#include <unordered_map>
#include <vector>

#include "DebugText.h"

class Japanese_IME
{
public:
	//Kanji_Menu is a list of flags to use with the whichlist argument of the GetKanji function.
	//Each enum corresponds to one of the hash map class members.
	enum Kanji_Menu
	{
		ONYOMI,
		KUNYOMI,
		NAME
	};

	void Init();
	std::vector<std::string> GetKanji(std::string kana, int whichlist);
private:
	std::unordered_map<std::string, std::vector<std::string>> kanjionmap_;
	std::unordered_map<std::string, std::vector<std::string>> kanjikunmap_;
	std::unordered_map<std::string, std::vector<std::string>> kanjinamemap_;
};

#endif //JAPANESE_IME