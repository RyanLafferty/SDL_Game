//
//  clean.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-17.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

#include "game.h"

/*
 Desc: Called upon program exit to exit systems.
 Args: None.
 Ret: Nothing.
 */
void quit()
{
    IMG_Quit();
    SDL_Quit();
}

/*
 Desc: Called upon to cleanup memory used up by the game.
 Args:
 Ret: Nothing.
 */
void clean(player * p, enemy1 * e)
{
    destroyPlayer(p);
    destroyEnemies(e);
}