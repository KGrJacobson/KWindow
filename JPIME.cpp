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
		{ u8"いち", { u8"一", u8"壱" } },
		{ u8"いつ", { u8"一", u8"逸", u8"乙", u8"壱", u8"溢" } },

		//u
		//e
		{ u8"え", { u8"会", u8"回", u8"画", u8"衛", u8"壊", u8"絵", u8"依", u8"恵", u8"衣", u8"也", u8"懐", u8"慧", u8"彗", u8"隈", u8"歪" } },

		//o
		//k
		{ u8"かい", { u8"会", u8"回", u8"開", u8"改", u8"界", u8"解", u8"画", u8"海", u8"階", u8"介", u8"壊", u8"街", u8"絵", u8"届", u8"掛", u8"戒", u8"快", u8"皆",
			u8"械", u8"悔", u8"懐", u8"拐", u8"怪", u8"灰", u8"刈", u8"塊", u8"堺", u8"芥", u8"桧", u8"檜", u8"魁", u8"苅", u8"凱", u8"蓋", u8"蟹", u8"偕", u8"鮭" } },
		{ u8"こく", { u8"国", u8"告", u8"可", u8"石", u8"谷", u8"黒", u8"刻", u8"克", u8"酷", u8"穀", u8"殻", u8"鵠", u8"或" } },

		//g
		//s
		//z
		//j
		{ u8"じゅう", { u8"十", u8"重", u8"住", u8"従", u8"充", u8"渋", u8"銃", u8"柔", u8"縦", u8"拾", u8"獣", u8"汁" } },
		{ u8"じつ", { u8"日", u8"実" } },
		{ u8"じん", { u8"人", u8"神", u8"陣", u8"尽", u8"臣", u8"沈", u8"仁", u8"尋", u8"妊", u8"辰", u8"腎", u8"刃", u8"稔", u8"迅", u8"甚", u8"荏", u8"壬" } },

		//t
		{ u8"たい", { u8"大", u8"対", u8"代", u8"体", u8"来", u8"台", u8"態", u8"待", u8"退", u8"太", u8"隊", u8"帯", u8"逮", u8"替", u8"貸", u8"滞", u8"袋", u8"泰",
			u8"耐", u8"敦", u8"怠", u8"胎", u8"堆", u8"梯", u8"黛", u8"醍", u8"戴", u8"碓", u8"諦" } },

		//d
		{ u8"だい", { u8"大", u8"内", u8"代", u8"題", u8"第", u8"提", u8"台", u8"奈", u8"袋", u8"弟", u8"乃", u8"鵜", u8"醍", u8"悌" } },

		//c
		//n
		{ u8"にち", { u8"日" } },
		{ u8"にん", { u8"人", u8"認", u8"任", u8"仁", u8"妊", u8"忍", u8"刃", u8"稔", u8"荏", u8"壬" } },
		{ u8"ねん", { u8"年", u8"念", u8"然", u8"燃", u8"縁", u8"粘", u8"稔", u8"楠", u8"鮎", u8"撚" } }

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
		{ u8"か",{ u8"日" } },
		{ u8"くに" ,{ u8"国" } },

		//g
		//s
		//z
		//j
		//t
		{ u8"と",{ u8"人" } },

		//c
		//d
		//n
		//h
		{ u8"ひ",{ u8"日" } },
		{ u8"ひと",{ u8"一", u8"人" } },

		//b
		{ u8"び",{ u8"日" } },

		//p
		//m
		//y
		//r
		{ u8"り",{ u8"人" } }

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
