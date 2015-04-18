//
//  update.c
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
void update(player * p, enemy1 * e)
{
    enemyCollisions(p, e);
    playerCollisions(p, e);
    
    while(e != NULL)
    {
        if(e->clipSP != NULL && e->tex != NULL)
        {
            if((e->clipSP->x - ENEMY_SPEED) >= 0)
            {
                e->clipSP->x -= ENEMY_SPEED;
            }
            else
            {
                e->clipSP->x = SCREEN_WIDTH + (e->clipSP->x - ENEMY_SPEED);
            }
            
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
}

/*
 Desc:
 Args:
 Ret:
 */
void enemyCollisions(player * p, enemy1 * e)
{
    bullet * nav = p->b;
    
    while(nav != NULL)
    {
        while(e != NULL)
        {
            if(e->clipSP != NULL)
            {
                //printf("a\n");
                if((nav->clipSP->x + nav->clipSP->w) >= (e->clipSP->x)
                   && (nav->clipSP->x + nav->clipSP->w) <= (e->clipSP->x + e->clipSP->w)
                   && (nav->clipSP->y + (nav->clipSP->h / 2)) >= (e->clipSP->y)
                   && (nav->clipSP->y + (nav->clipSP->h / 2)) <= (e->clipSP->y + (e->clipSP->h)))
                {
                    printf("enemy collision\n");
                    //figure out what to do on collision
                }
                
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
        nav = nav->next;
    }
}

/*
 Desc:
 Args:
 Ret:
 */
void playerCollisions(player * p, enemy1 * e)
{
    while(e != NULL)
    {
        if(e->clipSP != NULL)
        {
            //printf("a\n");
            if((p->clipSP->x + p->clipSP->w) >= (e->clipSP->x)
               && (p->clipSP->x + p->clipSP->w) <= (e->clipSP->x + e->clipSP->w)
               && (p->clipSP->y + (p->clipSP->h / 2)) >= (e->clipSP->y)
               && (p->clipSP->y + (p->clipSP->h / 2)) <= (e->clipSP->y + (e->clipSP->h)))
            {
                printf("collision\n");
                //figure out what to do on collision
            }
            
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
    
}