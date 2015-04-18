//
//  render.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-17.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

#include "game.h"

/*
 Desc:
 Args:
 Ret:
 */
void displayTextures(SDL_Renderer * ren, player * p, enemy1 * e)
{
    //clear renderer
    SDL_RenderClear(ren);
    
    //Render player texture
    //renderer, texture, image clip, size/location clip
    SDL_RenderCopy(ren, p->tex, NULL, p->clipSP);
    
    while(e != NULL)
    {
        if(e->clipSP != NULL && e->tex != NULL)
        {
            //Render player texture
            //renderer, texture, image clip, size/location clip
            SDL_RenderCopy(ren, e->tex, NULL, e->clipSP);
            if(e->next != NULL)
            {
                e = e->next;
            }
            else
            {
                e = NULL;
            }
        }
    }
    
    bullet * nav = p->b;
    bullet * prev = NULL;
    bullet * temp = NULL;
    while(nav != NULL)
    {
        if(nav->clipSP != NULL && nav->tex != NULL)
        {
            //Render player texture
            //renderer, texture, image clip, size/location clip
            nav->clipSP->x = nav->clipSP->x + BULLET_SPEED;
            SDL_RenderCopy(ren, nav->tex, NULL, nav->clipSP);
            nav->ticks++;
            if(nav->next != NULL)
            {
                nav = nav->next;
            }
            else
            {
                nav = NULL;
            }
        }
    }
    
    nav = p->b;
    int head = 0;
    
    while(nav != NULL)
    {
        if(nav->ticks >= 5)
        {
            if(nav == p->b)
            {
                temp = nav;
                nav = nav->next;
                destroyBullet(temp);
                p->b = nav;
                head = 1;
            }
            else
            {
                prev->next = nav->next;
                destroyBullet(nav);
            }
        }
        if(head == 0)
        {
            prev = nav;
            nav = nav->next;
        }
        head = 0;
    }
    
    
    //Update screen
    SDL_RenderPresent(ren);
}