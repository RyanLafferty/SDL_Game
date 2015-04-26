//
//  input.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-17.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

#include "game.h"

/*
 Desc: Get's input from the keyboard and updates player position.
 Args: A pointer to the size and position of the player (SDL_Rect).
 Ret: An integer (1 on exit, 0 otherwise).
 */
int getInput(SDL_Rect * clip, SDL_Renderer * ren, player * p)
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if(e.type == SDL_QUIT)
        {
            return 0;
        }
    }
    
    /*TODO: add key pressed and key released later*/
    const Uint8 * currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_UP])
    {
        if(clip->y - (1 * SPEED) >= 0)
        {
            clip->y = (clip->y - (1 * SPEED));
        }
        else
        {
            clip->y = SCREEN_HEIGHT + (clip->y - (1 * SPEED));
        }
    }
    else if(currentKeyStates[SDL_SCANCODE_DOWN])
    {
        clip->y = (clip->y + (1 * SPEED)) % SCREEN_HEIGHT;
    }
    else if(currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if(clip->x - (1 * SPEED) >= 0)
        {
            clip->x = (clip->x - (1 * SPEED));
        }
        else
        {
            clip->x = SCREEN_WIDTH + (clip->x - (1 * SPEED));
        }
    }
    else if(currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        clip->x = (clip->x + (1 * SPEED)) % SCREEN_WIDTH;
    }
    else if(currentKeyStates[SDL_SCANCODE_SPACE])
    {
        if(p->b == NULL)
        {
            //printf("init bullet");
            p->b = initBullet(ren, p);
        }
        else
        {
            //printf("adding bullet");
            bullet * nav;
            nav = p->b;
            while(nav->next != NULL)
            {
                nav = nav->next;
            }
            nav->next = initBullet(ren, p);
        }
    }
    else
    {
    }

    return 1;
}