#include <string>
#include <vector>

#include "SDL.h"

#include "TextInput.h"
#include "SDLUtility.h"
#include "ShortenedText.h"
#include "UIButton.h"
#include "UIElements.h"

//Init creates the vectors used for preset RBG colors and preset
//colors for each of the window layout elements.  See the UIElements
//header file for more information on the contents of the vectors.
void UIElements::Init()
{
	standardcolorvector_ = std::vector<SDL_Color>{
		SDL_Color{ 23, 20, 18, 255 },		//BLACK
		SDL_Color{ 235, 246, 247, 255 },	//WHITE
		SDL_Color{ 159, 116, 98, 255 },		//WALNUT_DYED
		SDL_Color{ 89, 43, 31, 255 },		//SUMAC_DYED
		SDL_Color{ 245, 127, 79, 255 },		//RICH_GARDENIA
		SDL_Color{ 159, 82, 51, 255 },		//RED_OCHRE_COLOR
		SDL_Color{ 152, 85, 56, 255 },		//POLISHED_BROWN
		SDL_Color{ 255, 162, 107, 255 },	//STYLISH_PERSIMMON
		SDL_Color{ 255, 137, 54, 255 },		//DAYLILY_COLORED
		SDL_Color{ 251, 129, 54, 255 },		//RED_BRONZE
		SDL_Color{ 46, 33, 27, 255 },		//LEGAL_DYE
		SDL_Color{ 202, 105, 36, 255 },		//AMBER
		SDL_Color{ 213, 120, 53, 255 },		//DECAYING_LEAVES
		SDL_Color{ 169, 98, 50, 255 },		//CLOVE_DYED
		SDL_Color{ 140, 89, 57, 255 },		//BRUSHWOOD_DYED
		SDL_Color{ 89, 58, 39, 255 },		//WEATHERED_BAMBOO
		SDL_Color{ 190, 127, 81, 255 },		//OCHRE
		SDL_Color{ 183, 112, 45, 255 },		//YELLOW_TEA
		SDL_Color{ 182, 73, 37, 255 },		//CATTAIL_COLOR
		SDL_Color{ 53, 31, 25, 255 },		//SCORCHED_BROWN
		SDL_Color{ 236, 130, 84, 255 },		//WASHEDOUT_PERSIMMON
		SDL_Color{ 236, 149, 108, 255 },	//SAWTOOTH_OAK
		SDL_Color{ 130, 75, 53, 255 },		//GREEN_TEA
		SDL_Color{ 252, 164, 116, 255 },	//PALE_PERSIMMON
		SDL_Color{ 250, 146, 88, 255 },		//PLUM_DYED
		SDL_Color{ 143, 88, 60, 255 },		//CLOVE_BROWN
		SDL_Color{ 171, 97, 52, 255 },		//LOQUAT_BROWN
		SDL_Color{ 255, 165, 101, 255 },	//PALE_INCENSE
		SDL_Color{ 198, 107, 39, 255 },		//GOLDEN_BROWN
		SDL_Color{ 152, 86, 41, 255 },		//FOX
		SDL_Color{ 106, 67, 45, 255 },		//ALOEWOOD_COLOR
		SDL_Color{ 196, 142, 105, 255 },	//WHITE_TEA_COLOR
		SDL_Color{ 125, 78, 45, 255 },		//GOLDEN_GREY_BAMBOO
		SDL_Color{ 107, 68, 35, 255 },		//BROWN_OF_FLATTERY
		SDL_Color{ 135, 95, 154, 255 },		//WISTERIA_PURPLE
		SDL_Color{ 151, 110, 154, 255 },	//TATARIAN_ASTER
		SDL_Color{ 43, 32, 40, 255 },		//BLUE_VIOLET
		SDL_Color{ 168, 124, 160, 255 },	//THIN_COLOR
		SDL_Color{ 91, 50, 86, 255 },		//VIOLET
		SDL_Color{ 35, 25, 30, 255 },		//DARK_RED
		SDL_Color{ 187, 119, 150, 255 },	//RED_WISTERIA
		SDL_Color{ 117, 93, 91, 255 },		//DOVE_FEATHER_GREY
		SDL_Color{ 109, 43, 80, 255 },		//VINE_GRAPE
		SDL_Color{ 164, 52, 93, 255 },		//TREE_PEONY
		SDL_Color{ 67, 36, 42, 255 },		//FAKE_PURPLE
		SDL_Color{ 126, 38, 57, 255 },		//SAPPANWOOD
		SDL_Color{ 68, 49, 46, 255 },		//VANISHING_RED_MOUSE
		SDL_Color{ 93, 63, 106, 255 },		//BELLFLOWER
		SDL_Color{ 63, 49, 58, 255 },		//DISAPPEARING_PURPLE
		SDL_Color{ 58, 36, 59, 255 },		//DEEP_PURPLE
		SDL_Color{ 141, 96, 140, 255 },		//HALF_COLOR
		SDL_Color{ 79, 40, 75, 255 },		//PURPLE
		SDL_Color{ 118, 53, 104, 255 },		//IRIS_COLOR
		SDL_Color{ 73, 30, 60, 255 },		//RABBIT_EAR_IRIS
		SDL_Color{ 99, 66, 75, 255 },		//GRAPE_MOUSE
		SDL_Color{ 77, 59, 60, 255 },		//WISTERIA_AND_BURNT_BAMBOO
		SDL_Color{ 143, 65, 85, 255 },		//PLUM_PURPLE
		SDL_Color{ 81, 44, 49, 255 },		//PURPLE_KITE
		SDL_Color{ 89, 41, 44, 255 }		//MULBERRY_DYE
	};
		
	colorlayouts_ = std::vector<std::vector<SDL_Color>*>{
		new std::vector<SDL_Color>{				//VIOLET_LAYOUT
			standardcolorvector_[VIOLET],				//BACKGROUND_COLOR
			standardcolorvector_[BLACK],				//DEMO_SCREEN_COLOR
			standardcolorvector_[BLACK],				//INPUT_SCREEN_COLOR
			standardcolorvector_[WHITE],				//TEXT_COLOR
			standardcolorvector_[BLACK],				//OUTLINED_BOX_COLOR
			standardcolorvector_[RABBIT_EAR_IRIS],		//BUTTON_BACKGROUND_COLOR
			standardcolorvector_[IRIS_COLOR],			//BUTTON_UNPRESSED_COLOR
			standardcolorvector_[BELLFLOWER],			//BUTTON_PRESSED_COLOR
			standardcolorvector_[DISAPPEARING_PURPLE],	//TINY_BUTTON_BACKGROUND_COLOR
			standardcolorvector_[MULBERRY_DYE],			//TINY_BUTTON_UNPRESSED_COLOR
			standardcolorvector_[DARK_RED],				//TINY_BUTTON_PRESSED_COLOR
			standardcolorvector_[HALF_COLOR],			//CONTEXT_MENU_ELEMENT_PRESSED_COLOR
			standardcolorvector_[FAKE_PURPLE],			//TAB_BACKGROUND_COLOR
			standardcolorvector_[PLUM_PURPLE],			//TAB_SELECTED_COLOR
			standardcolorvector_[VINE_GRAPE],			//TAB_PRESSED_COLOR
			standardcolorvector_[SAPPANWOOD],			//CAPTION_CONTAINER_COLOR
			standardcolorvector_[WHITE],				//CAPTION_CONTAINER_SELECTED_COLOR
			standardcolorvector_[RED_WISTERIA],			//CAPTION_CONTAINER_DRAWN_CAPTION_COLOR
			standardcolorvector_[DARK_RED],				//TEXT_INPUT_BOX
			standardcolorvector_[RABBIT_EAR_IRIS],		//CONTEXT_MENU_BACKGROUND_COLOR
			standardcolorvector_[PLUM_PURPLE]			//HOVER_TEXT_BACKGROUND_COLOR
		},

		new std::vector<SDL_Color>{				//YELLOW_RED_LAYOUT
			standardcolorvector_[RED_OCHRE_COLOR],		//BACKGROUND_COLOR
			standardcolorvector_[BLACK],				//DEMO_SCREEN_COLOR
			standardcolorvector_[BLACK],				//INPUT_SCREEN_COLOR
			standardcolorvector_[WHITE],				//TEXT_COLOR
			standardcolorvector_[BLACK],				//OUTLINED_BOX_COLOR
			standardcolorvector_[SUMAC_DYED],			//BUTTON_BACKGROUND_COLOR
			standardcolorvector_[CLOVE_BROWN],			//BUTTON_UNPRESSED_COLOR
			standardcolorvector_[WEATHERED_BAMBOO],		//BUTTON_PRESSED_COLOR
			standardcolorvector_[ALOEWOOD_COLOR],		//TINY_BUTTON_BACKGROUND_COLOR
			standardcolorvector_[GOLDEN_BROWN],			//TINY_BUTTON_UNPRESSED_COLOR
			standardcolorvector_[SCORCHED_BROWN],		//TINY_BUTTON_PRESSED_COLOR
			standardcolorvector_[STYLISH_PERSIMMON],	//CONTEXT_MENU_ELEMENT_PRESSED_COLOR
			standardcolorvector_[CLOVE_DYED],			//TAB_BACKGROUND_COLOR
			standardcolorvector_[PALE_PERSIMMON],		//TAB_SELECTED_COLOR
			standardcolorvector_[WASHEDOUT_PERSIMMON],	//TAB_PRESSED_COLOR
			standardcolorvector_[DAYLILY_COLORED],		//CAPTION_CONTAINER_COLOR
			standardcolorvector_[WHITE],				//CAPTION_CONTAINER_SELECTED_COLOR
			standardcolorvector_[RICH_GARDENIA],		//CAPTION_CONTAINER_DRAWN_CAPTION_COLOR
			standardcolorvector_[LEGAL_DYE],			//TEXT_INPUT_BOX
			standardcolorvector_[SUMAC_DYED],			//CONTEXT_MENU_BACKGROUND_COLOR
			standardcolorvector_[BRUSHWOOD_DYED]		//HOVER_TEXT_BACKGROUND_COLOR
		}
	};

	currentcolorlayout_ = colorlayouts_[VIOLET_LAYOUT];
}

void UIElements::CloseLayouts()
{
	colorlayouts_.clear();
}

//Set a new color layout based on the enum provided.  See the UIElements
//header file for UI_Color_Layouts to see the possible layouts.
void UIElements::SetColorLayout(int colorlayout)
{
	currentcolorlayout_ = colorlayouts_[colorlayout];
}

//Returns the RGBA color based on the enums provided.  Enums are from the 
//Standard_Colors and Standard_Alpha_Values listed in the UIElements
//header file.
SDL_Color UIElements::GetSDLColor(int color, int alphavalue)
{
	SDL_Color colortoreturn = standardcolorvector_[color];
	colortoreturn.a = alphavalue;

	return colortoreturn;
}

//Returns the RGBA color based on the enums provided.  Enums are from the 
//Standard_UI_Element_Colors and Standard_Alpha_Values listed in the UIElements
//header file.  The UI Elements Colors are specific to the current layout set.
SDL_Color UIElements::GetUIElementColor(int uielement, int alphavalue)
{
	SDL_Color colortoreturn = currentcolorlayout_->at(uielement);
	colortoreturn.a = alphavalue;

	return colortoreturn;
}

SDL_Color UIElements::InvertColor(SDL_Color color) {
	SDL_Color colortoreturn = color;
	colortoreturn.r += 127;
	colortoreturn.g += 127;
	colortoreturn.b += 127;

	return colortoreturn;
}

//Set the current Menu to the one provided.  Only one bar menu
//or context menu can be set at a time in the program.
//menu is the menu to be shown.
//x, y are the coordinates to set the menu at.  If passed null
//  values, the menu is placed on the mouse cursor.
void UIElements::SetMenu(UIMenu *menu, int *x, int *y)
{
	if (Global_UI_Element::currentmenu_ != NULL)
		Global_UI_Element::currentmenu_->ResetMenu();

	if (menu != NULL)
	{

		Global_UI_Element::currentmenu_ = menu;

		if (x != NULL && y != NULL)
		{
			Global_UI_Element::currentmenu_->SetXY((*x), (*y));
		}
		else
		{
			int mousex, mousey;
			SDL_GetMouseState(&mousex, &mousey);
			Global_UI_Element::currentmenu_->SetXY(mousex, mousey);
		}
	}
	else
	{
		Global_UI_Element::currentmenu_ = menu;
	}
}

//Set the hovertext to be the one provided in the argument.  Only
//one hovertext may be active at any time.
//text is the hovertext to show.  Null is a possible value for this
//argument.
void UIElements::SetHoverText(ShortenenedText *text)
{
	Global_UI_Element::hovertext_ = text;
}

UIMenu *UIElements::GetMenu()
{
	return Global_UI_Element::currentmenu_;
}

ShortenenedText *UIElements::GetHoverText()
{
	return Global_UI_Element::hovertext_;
}

//Display the current hovertext.  Hovertext exists in the Global_UI_Element
//namespace in the UIElements header file.
void UIElements::ShowUIHoverText(TextInput *text)
{
	int x = -1;
	int	y = -1;
	SDL_GetMouseState(&x, &y);

	int textwidth = text->GetWidth();
	int textheight = text->GetHeight();

	SDL_Rect textbackground{ x, y, textwidth + 4, textheight + 4 };
	SDLUtility::CreateBorderedRect(textbackground, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(HOVER_TEXT_BACKGROUND_COLOR, SOLID_COLOR));
	SDLUtility::PostText(text, x + 2, y + 2);
}

//Render a UIButton on screen.
void UIElements::ShowUIButton(UIButton *button)
{
	SDL_Rect showrect = button->GetButtonArea();
	SDLUtility::CreateSquare(showrect, GetUIElementColor(BUTTON_BACKGROUND_COLOR, SOLID_COLOR));

	SDL_Rect innerrect{
		showrect.x + 4,
		showrect.y + 2,
		showrect.w - 8,
		showrect.h - 4
	};

	if (button->GetMouseEvent() == LEFT_BUTTON_DOWN)
	{
		SDLUtility::CreateBorderedRect(innerrect, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(BUTTON_PRESSED_COLOR, SOLID_COLOR));
	}
	else
	{
		SDLUtility::CreateBorderedRect(innerrect, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(BUTTON_UNPRESSED_COLOR, SOLID_COLOR));
	}

	if (button->IsTextCentered() == false)
	{
		SDLUtility::PostText(button->GetText(), 
			(showrect.x + 4) + 5, 
			(showrect.y + 2) + static_cast<int>((showrect.h - 4 - button->GetText()->GetHeight()) * .5)
			);
	}
	else
	{
		SDLUtility::PostText(button->GetText(),
			innerrect.x + static_cast<int>((innerrect.w - button->GetText()->GetWidth()) * .5),
			innerrect.y + static_cast<int>((innerrect.h - button->GetText()->GetHeight()) * .5)
			);
	}
}

//Render a UIButton as a tiny button on screen similar in size to the close
//buttons in standard windows.  Most "Tiny Buttons" will only have one character
//of text to render.
void UIElements::ShowUITinyButton(UIButton *button)
{
	SDL_Rect showrect = button->GetButtonArea();
	SDLUtility::CreateSquare(showrect, GetUIElementColor(TINY_BUTTON_BACKGROUND_COLOR, SOLID_COLOR));

	SDL_Rect innerrect{
		showrect.x + 2,
		showrect.y + 2,
		showrect.w - 4,
		showrect.h - 4
	};

	if (button->GetMouseEvent() == LEFT_BUTTON_DOWN)
	{
		SDLUtility::CreateBorderedRect(innerrect, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(TINY_BUTTON_PRESSED_COLOR, SOLID_COLOR));
	}
	else
	{
		SDLUtility::CreateBorderedRect(innerrect, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(TINY_BUTTON_UNPRESSED_COLOR, SOLID_COLOR));
	}

	SDLUtility::PostText(button->GetText(),
		innerrect.x + static_cast<int>((innerrect.w - button->GetText()->GetWidth()) * .5),
		innerrect.y + static_cast<int>((innerrect.h - button->GetText()->GetHeight()) * .5)
		);
}

//Render a UIButton as a tab on screen.
void UIElements::ShowUITab(UIButton *button, bool isselected)
{
	SDL_Rect showrect = button->GetButtonArea();

	if (button->GetMouseEvent() == LEFT_BUTTON_DOWN)
	{
		SDLUtility::CreateBorderedRect(showrect, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(TAB_PRESSED_COLOR, SOLID_COLOR));
	}
	else
	{
		if (isselected == true)
			SDLUtility::CreateBorderedRect(showrect, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(TAB_SELECTED_COLOR, SOLID_COLOR));
		else
			SDLUtility::CreateBorderedRect(showrect, GetUIElementColor(OUTLINED_BOX_COLOR, SOLID_COLOR), GetUIElementColor(TAB_BACKGROUND_COLOR, SOLID_COLOR));
	}

	SDLUtility::PostText(button->GetText(),
		showrect.x + 5,
		showrect.y + static_cast<int>((showrect.h - button->GetText()->GetHeight()) * .5)
		);
}

//Render a UIButton as a member of a menu on screen.
void UIElements::ShowUIContextMenu(UIButton *button)
{
	SDL_Rect showrect = button->GetButtonArea();

	if (button->GetMouseEvent() == LEFT_BUTTON_DOWN)
	{
		SDLUtility::CreateSquare(showrect, GetUIElementColor(CONTEXT_MENU_ELEMENT_PRESSED_COLOR, SOLID_COLOR));
	}
	else
	{
		SDLUtility::CreateSquare(showrect, GetUIElementColor(CONTEXT_MENU_BACKGROUND_COLOR, SOLID_COLOR));
	}

	SDLUtility::PostText(button->GetText(),
		showrect.x + 5,
		showrect.y + static_cast<int>((showrect.h - button->GetText()->GetHeight()) * .5)
		);
}
