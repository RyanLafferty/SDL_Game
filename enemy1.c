//
//  enemy1.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-17.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

#include "game.h"

/*
 Desc: Creates and initializes the enemy1.
 Args: A pointer to the game renderer (SDL_Renderer).
 Ret: A pointer to the enemy1 created on success and NULL on failure.
 */
enemy1 * initEnemy1(SDL_Renderer * ren)
{
    enemy1 * e;
    SDL_Surface * eImg;
    
    e = NULL;
    
    e = malloc(sizeof(enemy1)*1);
    if(e == NULL)
    {
        printf("Error: Failed to allocate player memory.\n");
        return NULL;
    }
    
    e->health = 100;
    e->dead = 0;
    e->clipIMG = NULL;
    e->clipSP = NULL;
    e->tex = NULL;
    e->next = NULL;
    
    //set clips
    e->clipSP = malloc(sizeof(SDL_Rect) * 1);
    if(e->clipSP == NULL)
    {
        printf("Error: Failed to allocate clipsSP memory.\n");
        free(e);
        return NULL;
    }
    
    //Size and position clippings for texture
    e->clipSP->h = 75;
    e->clipSP->w = 50;
    e->clipSP->x = SCREEN_WIDTH - 50;
    e->clipSP->y = rand() % (SCREEN_HEIGHT);
    
    
    //load texture for player (arrow image is a place holder)
    eImg = IMG_Load("left.png");
    e->tex = SDL_CreateTextureFromSurface(ren, eImg);
    if(e->tex == NULL)
    {
        printf("texture load error: %s\n", SDL_GetError());
        free(e->clipSP);
        free(e);
        return NULL;
    }
    SDL_FreeSurface(eImg);
    
    return e;
}

/*
 Desc: Free's memory associated with the enemy1.
 Args: A pointer to the enemy1.
 Ret: Nothing.
 */
void destroyEnemy1(enemy1 * e)
{
    if(e == NULL)
    {
        return;
    }
    
    if(e->tex != NULL)
    {
        SDL_DestroyTexture(e->tex);
    }
    if(e->clipIMG != NULL)
    {
        free(e->clipIMG);
    }
    if(e->clipSP != NULL)
    {
        free(e->clipSP);
    }
    
    free(e);
}

/*
 Desc: Free's memory associated with the enemy1s.
 Args: A pointer to the enemy1s.
 Ret: Nothing.
 */
void destroyEnemies(enemy1 * e)
{
    enemy1 * temp;
    
    temp = NULL;
    
    if(e == NULL)
    {
        return;
    }
    
    while(e->next != NULL)
    {
        if(e != NULL)
        {
            temp = e;
            e = e->next;
            destroyEnemy1(temp);
        }
    }
    if(e != NULL)
    {
        destroyEnemy1(e);
    }
}