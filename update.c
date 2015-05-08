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
void update(player * p, enemy1 * e, SDL_Renderer * ren)
{
    enemy1 * prev = NULL;
    int enemyCount = 0;
    
    if(p->invTicks >= 0)
    {
        p->invTicks++;
    }
    
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
                //e->clipSP->x = SCREEN_WIDTH + (e->clipSP->x - ENEMY_SPEED);
                e->dead = 1;
            }
        }
        
        if(e != NULL && e->next != NULL)
        {
            prev = e;
            e = e->next;
        }
        else if(e == NULL)
        {
            e = NULL;
        }
        else
        {
            if(enemyCount <= 3)
            {
                e->next = initEnemy1(ren);
            }
            e = NULL;
        }
        enemyCount++;
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
    enemy1 * prev = NULL;
    enemy1 * head = e;
    
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
                    //printf("enemy collision\n");
                    if(e == head)
                    {
                        if(e->next == NULL)
                        {
                            e->dead = 1;
                            e = NULL;
                        }
                        else
                        {
                            e->dead = 1;
                        }
                    }
                    else
                    {
                        e->dead = 1;
                    }
                }
                
                if(e != NULL && e->next != NULL)
                {
                    prev = e;
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
            if((p->clipSP->x + p->clipSP->w) >= (e->clipSP->x)
               && (p->clipSP->x + p->clipSP->w) <= (e->clipSP->x + e->clipSP->w)
               && (p->clipSP->y + (p->clipSP->h / 2)) >= (e->clipSP->y)
               && (p->clipSP->y + (p->clipSP->h / 2)) <= (e->clipSP->y + (e->clipSP->h)))
            {
                if(p->invTicks >= (FPS*1.35))
                {
                    p->invTicks = -1;
                }
                
                if(p->invTicks >= 0)
                {
                    p->invTicks++;
                }
                else
                {
                    p->health -= 10;
                    p->invTicks = 0;
                }
                
                return;
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