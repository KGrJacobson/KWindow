#ifndef JAPANESE_IME
#define JAPANESE_IME
#include <string>
#include <unordered_map>
#include <vector>

#include "DebugText.h"

class Japanese_IME
{
public:
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