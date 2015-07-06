// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Main.cpp
  *  @brief  Vstupni bod programu.
  */

#include "RetroSpaceGame.h"

/**
 * Vstupni bod programu.
 * Vytvori instanci tridy RetroSpaceGame, ktera spusti celou aplikaci.
 * @param argc Pocet parametru prikazove radky.
 * @param argv Hodnoty parametru prikazove radky.
 * @return Navratovy kod.
 */
int main(int argc, char *argv[])
{
    RetroSpace::RetroSpaceGame *retroSpaceGame = new RetroSpace::RetroSpaceGame();
    int retCode = retroSpaceGame->Run(argc, argv);

    delete retroSpaceGame;

    return retCode;
}

/**
 * \mainpage Retrospektivni hra pro dva hrace s vesmirnou tematikou
 * 
 * \section intro_sec Uvod
 *
 * Bakalarska prace, FIT VUT Brno 2011.
 * 
 *
 * @date 18.5.2011
 * @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
 * 
 */