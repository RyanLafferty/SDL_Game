//
//  main.c
//  sdlGame
//
//  Created by Lafferty on 2015-04-16.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//
//TODO: Test memory leaks
//TODO: figure out how to copy resources to executable
//TODO: get sprites
//TODO: Documentation

#include "game.h"

int main(int argc, const char * argv[])
{
    int succ;
    int running;
    Uint32 timer;
    player * p;
    enemy1 * enemies;
    enemy1 * nav;
    enemy1 * temp;
    enemy1 * temp2;
    enemy1 * prev;
    bullet * bullets;
    
    succ = 0;
    running = 1;
    timer = 0;
    p = NULL;
    enemies = NULL;
    nav = NULL;
    temp = NULL;
    temp2 = NULL;
    prev = NULL;
    bullets = NULL;
    
    succ = initSDL();
    if(succ == 1)
    {
        return 1;
    }
    
    SDL_Window * win = NULL;
    win = SDL_CreateWindow("My Window", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(win == NULL)
    {
        printf("Window init Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer * ren = NULL;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == NULL)
    {
        printf("Renerer init error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    p = initPlayer(ren);
    if(p == NULL)
    {
        printf("Error: Player was not created.\n");
        //TODO: call cleanup and quit sdl
        return 1;
    }
    
    enemies = initEnemy1(ren);
    if(enemies == NULL)
    {
        printf("Error: Enemy was not created.\n");
        //TODO: determine how to handle error.
        return 1;
    }
    
    p->health = 9999;
    
    while(running == 1)
    {
        timer = SDL_GetTicks();

        //get input
        running = getInput(p->clipSP, ren, p);
        
        //update
        update(p, enemies, ren);
        
        if(enemies->dead == 1)
        {
            //running = 0;
            destroyEnemy1(enemies);
            enemies = initEnemy1(ren);
            if(enemies == NULL)
            {
                printf("Error: Could not create enemies!\n");
                return 0;
            }
        }
        else
        {
            nav = enemies;
            while(nav != NULL && nav->next != NULL)
            {
                if(nav->dead == 1)
                {
                    if(nav == enemies)
                    {
                        if(nav->next == NULL)
                        {
                            destroyEnemy1(enemies);
                            enemies = initEnemy1(ren);
                            nav->next = NULL;
                            nav = enemies;
                        }
                        else
                        {
                            temp = enemies;
                            temp2 = nav->next;
                            destroyEnemy1(enemies);
                            enemies = temp2;
                            nav = enemies;
                        }
                    }
                    else
                    {
                        temp = nav;
                        temp2 = nav->next;
                        nav = nav->next;
                        destroyEnemy1(temp);
                        prev->next = nav;
                    }
                }
                
                prev = nav;
                nav = nav->next;
            }
            
            if(nav!= NULL && nav->dead == 1)
            {
                if(nav == enemies)
                {
                    if(nav->next == NULL)
                    {
                        destroyEnemy1(enemies);
                        enemies = initEnemy1(ren);
                        nav->next = NULL;
                        nav = NULL;
                        break;
                    }
                    else
                    {
                        temp = enemies;
                        temp2 = nav->next;
                        nav = nav->next;
                        destroyEnemy1(enemies);
                        enemies = temp2;
                    }
                }
                else
                {
                    temp = nav;
                    temp2 = nav->next;
                    nav = nav->next;
                    destroyEnemy1(temp);
                    prev->next = nav;
                }
            }
        }
        
        if(p->health <= 0)
        {
            running = 0;
        }

        //render
        displayTextures(ren, p, enemies);

        //frame cap
        if((SDL_GetTicks() - timer) < (1000 / FPS))
        {
            SDL_Delay((1000 / FPS) - (SDL_GetTicks() - timer));
        }
    }
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    clean(p, enemies);
    
    return 0;
    
}
