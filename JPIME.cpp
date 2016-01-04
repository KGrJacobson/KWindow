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
		{ u8"����", { u8"��", u8"��" } },
		{ u8"����", { u8"��", u8"��", u8"��", u8"��", u8"��" } },

		//u
		//e
		{ u8"��", { u8"��", u8"��", u8"��", u8"�q", u8"��", u8"�G", u8"��", u8"�b", u8"��", u8"��", u8"��", u8"�d", u8"�a", u8"�G", u8"�c" } },

		//o
		//k
		{ u8"����", { u8"��", u8"��", u8"�J", u8"��", u8"�E", u8"��", u8"��", u8"�C", u8"�K", u8"��", u8"��", u8"�X", u8"�G", u8"��", u8"�|", u8"��", u8"��", u8"�F",
			u8"�B", u8"��", u8"��", u8"��", u8"��", u8"�D", u8"��", u8"��", u8"��", u8"�H", u8"�O", u8"�w", u8"�@", u8"��", u8"�M", u8"�W", u8"�I", u8"��", u8"��" } },
		{ u8"����", { u8"��", u8"��", u8"��", u8"��", u8"�J", u8"��", u8"��", u8"��", u8"��", u8"��", u8"�k", u8"��", u8"��" } },

		//g
		//s
		//z
		//j
		{ u8"���イ", { u8"�\", u8"�d", u8"�Z", u8"�]", u8"�[", u8"�a", u8"�e", u8"�_", u8"�c", u8"�E", u8"�b", u8"�`" } },
		{ u8"����", { u8"��", u8"��" } },
		{ u8"����", { u8"�l", u8"�_", u8"�w", u8"�s", u8"�b", u8"��", u8"�m", u8"�q", u8"�D", u8"�C", u8"�t", u8"�n", u8"��", u8"�v", u8"�r", u8"�`", u8"�p" } },

		//t
		{ u8"����", { u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��",
			u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"�O", u8"��" } },

		//d
		{ u8"����", { u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"�T", u8"�L", u8"��", u8"��" } },

		//c
		//n
		{ u8"�ɂ�", { u8"��" } },
		{ u8"�ɂ�", { u8"�l", u8"�F", u8"�C", u8"�m", u8"�D", u8"�E", u8"�n", u8"��", u8"�`", u8"�p" } },
		{ u8"�˂�", { u8"�N", u8"�O", u8"�R", u8"�R", u8"��", u8"�S", u8"��", u8"��", u8"��", u8"�Q" } }

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
		{ u8"��",{ u8"��" } },
		{ u8"����" ,{ u8"��" } },

		//g
		//s
		//z
		//j
		//t
		{ u8"��",{ u8"�l" } },

		//c
		//d
		//n
		//h
		{ u8"��",{ u8"��" } },
		{ u8"�Ђ�",{ u8"��", u8"�l" } },

		//b
		{ u8"��",{ u8"��" } },

		//p
		//m
		//y
		//r
		{ u8"��",{ u8"�l" } }

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
