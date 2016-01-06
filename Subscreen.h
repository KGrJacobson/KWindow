#ifndef SUBSCREEN
#define SUBSCREEN

#include "SDL.h"

#include "MouseHandler.h"

//Subscreen is a template that defines necessary functions a subscreen handled by the ScreenHandler
//must contain.
class Subscreen {
public:
	virtual int Show() = 0;
};

#endif //SUBSCREEN