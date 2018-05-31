#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#else
#error "Unrecognized configuration!"
#endif

#include "GameController.h"
#include <iostream>
#include "Updates.h"
#include "Client.h"
#include "Server.h"

int main() {
	GameController gm;
	gm.run();
	return EXIT_SUCCESS;
}




