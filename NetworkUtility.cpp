#include "SDL_net.h"

#include "NetworkUtility.h"

bool NetworkUtility::Init()
{
	if (SDLNet_Init() == 0)
		return true;

	return false;
}

void NetworkUtility::Close()
{
	SDLNet_Quit();
}
