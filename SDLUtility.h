#ifndef SDLUTILITY
#define SDLUTILITY

#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Image.h"
#include "TextInput.h"

static SDL_Window *window;
static SDL_Renderer *renderer;

static TTF_Font *tenptfont;
static TTF_Font *twelveptfont;
static TTF_Font *sixteenptfont;
static TTF_Font *thirtytwoptfont;;

const static int SCREENW = 1500;
const static int SCREENH = 750;

//An area that is dependent on another areas coordinates.  Each variable in the struct
//is a percentage of the destination rectangle, listed in ".00" form.  For example, if
//the rectangle is half the size of the destination rectangle, w would be ".5".
struct RelativeRect {
	double x;
	double y;
	double w;
	double h;
};

//A number of functions that provide a layer of abstraction between SDL.  Most are related
//to rendering basic shapes, text or images.
class SDLUtility {
public:
	static int Init();
	static void Close();
	static SDL_Renderer *GetRenderer();
	static TTF_Font *GetFont(int fontsize);
	static int GetScreenWidth();
	static int GetScreenHeight();
	static SDL_Rect GetAbsoluteRect(RelativeRect relativerect, SDL_Rect destrect);
	static void ClearScreen();
	static void UpdateScreen();
	static void PostImage(Image *img, int x, int y);
	static void PostText(TextInput *text, int x, int y);
	static void PostTexture(SDL_Texture *texture, int x, int y);
	static void PostImage(Image *img, int x, int y, SDL_Rect sourcerect);
	static void CreateSquare(SDL_Rect rect, SDL_Color color);
	static void CreateBorderedRect(SDL_Rect rect, SDL_Color bordercolor, SDL_Color innercolor);
	static bool IsMouseActive(SDL_Rect mousecheckarea);
};

#endif //SDLUTILITY