#include <string>
#include <unordered_map>
#include <vector>

#include "DebugText.h"
#include "JPIME.h"

void Japanese_IME::Init()
{
	kanjionmap_ = std::unordered_map < std::string, std::vector<std::string>>({
		//a
		//i
		{ u8"‚¢‚¿", { u8"ˆê", u8"ˆë" } },
		{ u8"‚¢‚Â", { u8"ˆê", u8"ˆí", u8"‰³", u8"ˆë", u8"ˆì" } },

		//u
		//e
		{ u8"‚¦", { u8"‰ï", u8"‰ñ", u8"‰æ", u8"‰q", u8"‰ó", u8"ŠG", u8"ˆË", u8"Œb", u8"ˆß", u8"–ç", u8"‰ù", u8"Œd", u8"œa", u8"ŒG", u8"˜c" } },

		//o
		//k
		{ u8"‚©‚¢", { u8"‰ï", u8"‰ñ", u8"ŠJ", u8"‰ü", u8"ŠE", u8"‰ğ", u8"‰æ", u8"ŠC", u8"ŠK", u8"‰î", u8"‰ó", u8"ŠX", u8"ŠG", u8"“Í", u8"Š|", u8"‰ú", u8"‰õ", u8"ŠF",
			u8"ŠB", u8"‰÷", u8"‰ù", u8"‰û", u8"‰ö", u8"ŠD", u8"Š ", u8"‰ò", u8"ä", u8"ŠH", u8"•O", u8"w", u8"Š@", u8"Š¡", u8"ŠM", u8"ŠW", u8"ŠI", u8"˜ñ", u8"ø" } },
		{ u8"‚±‚­", { u8"‘", u8"", u8"‰Â", u8"Î", u8"’J", u8"•", u8"", u8"", u8"“", u8"’", u8"Šk", u8"”", u8"ˆ½" } },

		//g
		//s
		//z
		//j
		{ u8"‚¶‚ã‚¤", { u8"\", u8"d", u8"Z", u8"]", u8"[", u8"a", u8"e", u8"_", u8"c", u8"E", u8"b", u8"`" } },
		{ u8"‚¶‚Â", { u8"“ú", u8"À" } },
		{ u8"‚¶‚ñ", { u8"l", u8"_", u8"w", u8"s", u8"b", u8"’¾", u8"m", u8"q", u8"”D", u8"’C", u8"t", u8"n", u8"–«", u8"v", u8"r", u8"‰`", u8"p" } },

		//t
		{ u8"‚½‚¢", { u8"‘å", u8"‘Î", u8"‘ã", u8"‘Ì", u8"—ˆ", u8"‘ä", u8"‘Ô", u8"‘Ò", u8"‘Ş", u8"‘¾", u8"‘à", u8"‘Ñ", u8"‘ß", u8"‘Ö", u8"‘İ", u8"‘Ø", u8"‘Ü", u8"‘×",
			u8"‘Ï", u8"“Ö", u8"‘Ó", u8"‘Ù", u8"‘Í", u8"’ò", u8"‘á", u8"‘ç", u8"‘Õ", u8"‰O", u8"’ú" } },

		//d
		{ u8"‚¾‚¢", { u8"‘å", u8"“à", u8"‘ã", u8"‘è", u8"‘æ", u8"’ñ", u8"‘ä", u8"“Ş", u8"‘Ü", u8"’í", u8"”T", u8"‰L", u8"‘ç", u8"’î" } },

		//c
		//n
		{ u8"‚É‚¿", { u8"“ú" } },
		{ u8"‚É‚ñ", { u8"l", u8"”F", u8"”C", u8"m", u8"”D", u8"”E", u8"n", u8"–«", u8"‰`", u8"p" } },
		{ u8"‚Ë‚ñ", { u8"”N", u8"”O", u8"‘R", u8"”R", u8"‰", u8"”S", u8"–«", u8"“í", u8"ˆ¼", u8"”Q" } }

		//h
		//b
		//p
		//m
		//y
		//r
		//w
	});

	kanjikunmap_ = std::unordered_map < std::string, std::vector<std::string>>({
		//a
		//i
		//e
		//u
		//o
		//k
		{ u8"‚©",{ u8"“ú" } },
		{ u8"‚­‚É" ,{ u8"‘" } },

		//g
		//s
		//z
		//j
		//t
		{ u8"‚Æ",{ u8"l" } },

		//c
		//d
		//n
		//h
		{ u8"‚Ğ",{ u8"“ú" } },
		{ u8"‚Ğ‚Æ",{ u8"ˆê", u8"l" } },

		//b
		{ u8"‚Ñ",{ u8"“ú" } },

		//p
		//m
		//y
		//r
		{ u8"‚è",{ u8"l" } }

		//w
	});

	kanjinamemap_ = std::unordered_map < std::string, std::vector<std::string>>({
		//a
		//i
		//e
		//u
		//o
		//k
		//g
		//s
		//z
		//j
		//t
		//c
		//d
		//n
		//h
		//b
		//p
		//m
		//y
		//r
		//w
	});

	/*
	{ u8"", { u8"", } },
	*/
}

std::vector<std::string> Japanese_IME::GetKanji(std::string kana, int whichlist)
{
	switch (whichlist)
	{
	case ONYOMI:
		return kanjionmap_[kana];
	case KUNYOMI:
		return kanjikunmap_[kana];
	case NAME:
		return kanjinamemap_[kana];
	}

	return kanjionmap_[kana];
}
