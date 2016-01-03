#ifndef SUBSCREEN
#define SUBSCREEN

#include "SDL.h"

#include "MouseHandler.h"

class Subscreen {
public:
	virtual int Show() = 0;
};

#endif //SUBSCREEN