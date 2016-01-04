#ifndef UI_Elements
#define UI_Elements

#include <string>
#include <vector>

#include "SDL.h"

#include "SDLUtility.h"
#include "ShortenedText.h"
#include "TextInput.h"
#include "UIButton.h"
#include "UIMenu.h"

static std::vector<SDL_Color> standardcolorvector_;
static std::vector<std::vector<SDL_Color>*> colorlayouts_;
static std::vector<SDL_Color> *currentcolorlayout_;

//Only one of each of these UI Elements can be shown at a time.
namespace Global_UI_Element
{
	static UIMenu *currentmenu_ = NULL;
	static ShortenenedText *hovertext_ = NULL;
}

class UIElements 
{
public:
	static const int STANDARD_UI_FONT_SIZE = 10;

	static const int STANDARD_TINY_BUTTON_WIDTH = 20;
	static const int STANDARD_TINY_BUTTON_HEIGHT = 20;

	static const int STANDARD_MENU_WIDTH = 75;
	static const int STANDARD_MENU_HEIGHT = 20;
	
	static const int STANDARD_TAB_WIDTH = 100;
	static const int STANDARD_TAB_HEIGHT = 20;

	enum Standard_Colors
	{
		BLACK,						//23,20,18
		WHITE,						//235,246,247

		//The Yellow-Red Series of traditional Japanese colors
		WALNUT_DYED,
		SUMAC_DYED,
		RICH_GARDENIA,
		RED_OCHRE_COLOR,
		POLISHED_BROWN,
		STYLISH_PERSIMMON,
		DAYLILY_COLORED,
		RED_BRONZE,
		LEGAL_DYE,
		AMBER,
		DECAYING_LEAVES,
		CLOVE_DYED,
		BRUSHWOOD_DYED,
		WEATHERED_BAMBOO,
		OCHRE,
		YELLOW_TEA,
		CATTAIL_COLOR,
		SCORCHED_BROWN,
		WASHEDOUT_PERSIMMON,
		SAWTOOTH_OAK,
		GREEN_TEA,
		PALE_PERSIMMON,
		PLUM_DYED,
		CLOVE_BROWN,
		LOQUAT_BROWN,
		PALE_INCENSE,
		GOLDEN_BROWN,
		FOX,
		ALOEWOOD_COLOR,
		WHITE_TEA_COLOR,
		GOLDEN_GREY_BAMBOO,
		BROWN_OF_FLATTERY,

		//The Violet Series of traditional Japanese colors
		WISTERIA_PURPLE,			//135,95,154
		TATARIAN_ASTER,				//151,110,154
		BLUE_VIOLET,				//43,32,40
		THIN_COLOR,					//168,124,160
		VIOLET,						//91,50,86
		DARK_RED,					//35,25,30
		RED_WISTERIA,				//187,119,150
		DOVE_FEATHER_GREY,			//117,93,91
		VINE_GRAPE,					//109,43,80
		TREE_PEONY,					//164,52,93
		FAKE_PURPLE,				//67,36,42
		SAPPANWOOD,					//126,38,57
		VANISHING_RED_MOUSE,		//68,49,46
		BELLFLOWER,					//93,63,106
		DISAPPEARING_PURPLE,		//63,49,58
		DEEP_PURPLE,				//58,36,59
		HALF_COLOR,					//141,96,140
		PURPLE,						//79,40,75
		IRIS_COLOR,					//118,53,104
		RABBIT_EAR_IRIS,			//73,30,60
		GRAPE_MOUSE,				//99,66,75
		WISTERIA_AND_BURNT_BAMBOO,	//77,59,60
		PLUM_PURPLE,				//143,65,85
		PURPLE_KITE,				//81,44,49
		MULBERRY_DYE				//89,41,44
	};

	enum Standard_Alpha_Values {
		TRANSPARENT_COLOR = 50,
		SEMITRANSPARENT_COLOR = 150,
		SOLID_COLOR = 255
	};

	enum Standard_UI_Element_Colors {
		BACKGROUND_COLOR,
		DEMO_SCREEN_COLOR,
		INPUT_SCREEN_COLOR,
		TEXT_COLOR,
		OUTLINED_BOX_COLOR,
		BUTTON_BACKGROUND_COLOR,
		BUTTON_UNPRESSED_COLOR,
		BUTTON_PRESSED_COLOR,
		TINY_BUTTON_BACKGROUND_COLOR,
		TINY_BUTTON_UNPRESSED_COLOR,
		TINY_BUTTON_PRESSED_COLOR,
		CONTEXT_MENU_ELEMENT_PRESSED_COLOR,
		TAB_BACKGROUND_COLOR,
		TAB_SELECTED_COLOR,
		TAB_PRESSED_COLOR,
		CAPTION_CONTAINER_COLOR,
		CAPTION_CONTAINER_SELECTED_COLOR,
		CAPTION_CONTAINER_DRAWN_CAPTION_COLOR,
		TEXT_INPUT_BOX,
		CONTEXT_MENU_BACKGROUND_COLOR,
		HOVER_TEXT_BACKGROUND_COLOR
	};

	enum UI_Color_Layouts {
		VIOLET_LAYOUT,
		YELLOW_RED_LAYOUT
	};

	static void Init();
	static void CloseLayouts();
	static void SetColorLayout(int colorlayout);
	static SDL_Color GetSDLColor(int color, int alphavalue);
	static SDL_Color GetUIElementColor(int uielement, int alphavalue);
	static SDL_Color InvertColor(SDL_Color color);
	static void SetMenu(UIMenu *contextmenu, int *x, int *y);
	static void SetHoverText(ShortenenedText *text);
	static UIMenu *GetMenu();
	static ShortenenedText *GetHoverText();
	static void ShowUIHoverText(TextInput *text);
	static void ShowUIButton(UIButton *button);
	static void ShowUITinyButton(UIButton *button);
	static void ShowUITab(UIButton *button, bool isselected);
	static void ShowUIContextMenu(UIButton *button);
};

#endif //UI_Elements