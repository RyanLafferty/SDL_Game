//
//  bullet.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-18.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

#include "game.h"

/*
 Desc: Creates and initializes the bullet.
 Args: A pointer to the game renderer (SDL_Renderer).
 Ret: A pointer to the bullet created on success and NULL on failure.
 */
bullet * initBullet(SDL_Renderer * ren, player * p)
{
    bullet * b;
    SDL_Surface * bImg;
    
    b = NULL;
    
    b = malloc(sizeof(bullet)*1);
    if(b == NULL)
    {
        printf("Error: Failed to allocate player memory.\n");
        return NULL;
    }
    
    b->ticks = 0;
    b->clipIMG = NULL;
    b->clipSP = NULL;
    b->tex = NULL;
    b->next = NULL;
    
    //set clips
    b->clipSP = malloc(sizeof(SDL_Rect) * 1);
    if(b->clipSP == NULL)
    {
        printf("Error: Failed to allocate clipsSP memory.\n");
        free(b);
        return NULL;
    }
    
    //Size and position clippings for texture
    b->clipSP->h = 10;
    b->clipSP->w = 10;
    b->clipSP->x = (p->clipSP->x + p->clipSP->w + 1);
    b->clipSP->y = (p->clipSP->y + (p->clipSP->h / 2) - 5);
    
    
    //load texture for bullet (ball image is a place holder)
    bImg = IMG_Load("ball.bmp");
    b->tex = SDL_CreateTextureFromSurface(ren, bImg);
    if(b->tex == NULL)
    {
        printf("texture load error: %s\n", SDL_GetError());
        free(b->clipSP);
        free(b);
        return NULL;
    }
    SDL_FreeSurface(bImg);
    
    return b;
}

/*
 Desc: Free's memory associated with the bullet.
 Args: A pointer to the bullet.
 Ret: Nothing.
 */
void destroyBullet(bullet * b)
{
    if(b->tex != NULL)
    {
        SDL_DestroyTexture(b->tex);
    }
    if(b->clipIMG != NULL)
    {
        free(b->clipIMG);
    }
    if(b->clipSP != NULL)
    {
        free(b->clipSP);
    }
    
    free(b);
}

/*
 Desc: Free's memory associated with the bullets.
 Args: A pointer to the bullets.
 Ret: Nothing.
 */
void destroyBullets(bullet * b)
{
    bullet * temp;
    
    temp = NULL;
    
    if(b == NULL)
    {
        return;
    }
    
    while(b->next != NULL)
    {
        if(b != NULL)
        {
            temp = b;
            b = b->next;
            destroyBullet(temp);
        }
    }
    if(b != NULL)
    {
        destroyBullet(b);
    }
}