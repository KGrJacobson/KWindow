#ifndef NETWORK_UTILITY
#define NETWORK_UTILITY
#include <string>

#include "SDL_net.h"

#include "DebugText.h"

class NetworkUtility
{
public:
	static bool Init();
	static void Close();
};

#endif //NETWORK_UTILITY