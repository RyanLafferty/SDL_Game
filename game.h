//
//  game.h
//  sdlGame
//
//  Created by Lafferty on 2015-04-17.
//  Copyright (c) 2015 Lafferty. All rights reserved.
//

/*Comment format*/
/*
 Desc:
 Args:
 Ret:
*/

#ifndef sdlGame_game_h
#define sdlGame_game_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60
#define SPEED 3
#define ENEMY_SPEED 4
#define BULLET_SPEED 25

/*
 Desc:
 Args:
 Ret:
 */
typedef struct bullet
{
    int ticks;
    SDL_Rect * clipSP;
    SDL_Rect * clipIMG;
    SDL_Texture * tex;
    struct bullet * next;
}bullet;

/*
 Desc:
 Args:
 Ret:
 */
typedef struct player
{
    int health;
    int invTicks;
    SDL_Rect * clipSP;
    SDL_Rect * clipIMG;
    SDL_Texture * tex;
    bullet * b;
}player;

/*
 Desc:
 Args:
 Ret:
 */
typedef struct enemy1
{
    int health;
    int dead;
    SDL_Rect * clipSP;
    SDL_Rect * clipIMG;
    SDL_Texture * tex;
    struct enemy1 * next;
}enemy1;

//init
int initSDL();

//clean
void quit();
void clean(player * p, enemy1 * e);

//input
int getInput(SDL_Rect * clip, SDL_Renderer * ren, player * p);

//update
void update(player * p, enemy1 * e, SDL_Renderer * ren);
void enemyCollisions(player * p, enemy1 * e);
void playerCollisions(player * p, enemy1 * e);


//render
void displayTextures(SDL_Renderer * ren, player * p, enemy1 * e);

//player
player * initPlayer(SDL_Renderer * ren);
void destroyPlayer(player * p);

//enemy1
enemy1 * initEnemy1(SDL_Renderer * ren);
void destroyEnemy1(enemy1 * e);
void destroyEnemies(enemy1 * e);

//bullet
bullet * initBullet(SDL_Renderer * ren, player * p);
void destroyBullet(bullet * b);
void destroyBullets(bullet * b);
void addBullet(SDL_Renderer * ren, bullet *** bul, player * p);

#endif
