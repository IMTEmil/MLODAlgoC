#ifndef _PROJET_H_
#define _PROJET_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

#define MENU_CHOICE_FONT_SIZE 50
#define SNARE_COUNT 30
#define SQUARE_SIZE 31

typedef enum GAMESTATE
{
    GS_MENU,

    GS_NORMAL,

    GS_SENEQUE,

    GS_SNARE

} GAMESTATE;

typedef struct
{
    Texture2D SenequeHeadImage;

    bool isCitation;

    int indexCitation;

    int LastCitationFrame;

} GAME_SENEQUE;

typedef enum 
{
    SNARE_START,

    SNARE_LOADING,

    SNARE_CHARGED

} SNARE_STATE;

typedef struct Snare
{
    Vector2 position;

    Vector2 size;

    bool active;

    Color color;

    SNARE_STATE state;

    unsigned int nSeconds;

} Snare;

typedef Snare Element;

struct cellule_s {
	Element val;
	struct cellule_s* suiv;
};

typedef struct cellule_s Cellule;

typedef Cellule* Liste;

Liste InitProjetAddOn(GAME_SENEQUE *gameSeneque, Liste snares);
void CloseProjetAddOn(GAME_SENEQUE *gameSeneque, Liste snares);

void IfCollisionSendCitation(GAME_SENEQUE *GameSeneque, int currentFrameNumber);
void displayCitationForSeconds(GAME_SENEQUE *GameSeneque, int seconds, int currentFrame);
void DrawSenequeHead(GAME_SENEQUE *GameSeneque, Vector2 SnakeHeadPosition);

Liste UpdateSnares(Liste snares, unsigned int waitForNext, unsigned int lifeSpanSnare, Vector2 fruitPosition);
void DrawSnares(Liste snares);
bool SnareAlreadyAtPosition(Liste snares, Vector2 position);
bool SnareCollision(Liste snares, Vector2 position);

bool estVide(Liste l);
Liste creer(Element v);
Liste ajoutTete(Element v, Liste l);
void detruire(Liste l);
Liste ajoutFin(Element v, Liste l);
Liste retirePremierElement(Liste l);

#endif /*_PROJET_H_*/