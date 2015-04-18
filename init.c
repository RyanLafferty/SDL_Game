//
//  init.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-17.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

#include "game.h"

int initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //TODO: figure out how to init more img types
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image JPG could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        SDL_Quit();
        return 1;
    }
    
    return 0;
}