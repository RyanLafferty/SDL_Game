//
//  player.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-17.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

#include "game.h"

/*
 Desc: Creates and initializes the player.
 Args: A pointer to the game renderer (SDL_Renderer).
 Ret: A pointer to the player created on success and NULL on failure.
*/
player * initPlayer(SDL_Renderer * ren)
{
    player * p;
    SDL_Surface * pImg;
    
    p = NULL;
    
    p = malloc(sizeof(player)*1);
    if(p == NULL)
    {
        printf("Error: Failed to allocate player memory.\n");
        return NULL;
    }
    
    p->health = 100;
    p->clipIMG = NULL;
    p->clipSP = NULL;
    p->tex = NULL;
    p->b = NULL;
    
    //set clips
    p->clipSP = malloc(sizeof(SDL_Rect) * 1);
    if(p->clipSP == NULL)
    {
        printf("Error: Failed to allocate clipsSP memory.\n");
        free(p);
        return NULL;
    }
    
    //Size and position clippings for texture
    p->clipSP->h = 25;
    p->clipSP->w = 25;
    p->clipSP->x = 0;
    p->clipSP->y = (SCREEN_HEIGHT / 2);
    
    
    //load texture for player (ball image is a place holder)
    pImg = IMG_Load("ball.bmp");
    p->tex = SDL_CreateTextureFromSurface(ren, pImg);
    if(p->tex == NULL)
    {
        printf("texture load error: %s\n", SDL_GetError());
        free(p->clipSP);
        free(p);
        return NULL;
    }
    SDL_FreeSurface(pImg);
    
    return p;
}

/*
 Desc: Free's memory associated with the player.
 Args: A pointer to the player.
 Ret: Nothing.
*/
void destroyPlayer(player * p)
{
    if(p->b != NULL)
    {
        destroyBullets(p->b);
    }
    if(p->tex != NULL)
    {
        SDL_DestroyTexture(p->tex);
    }
    if(p->clipIMG != NULL)
    {
        free(p->clipIMG);
    }
    if(p->clipSP != NULL)
    {
        free(p->clipSP);
    }
    
    free(p);
}
