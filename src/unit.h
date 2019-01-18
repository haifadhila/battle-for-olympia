// Feel free to add necessary function/methods
// ADT Unit
// Berisi type basic sebuah unit
#ifndef UNIT_H
#define UNIT_H

#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"
#include "moveStack.h"
#include <string.h>
#include "./Point/point.h"

#define KING_TYPE 1
#define ARCHER_TYPE 2
#define SWORDSMAN_TYPE 3
#define MAGE_TYPE 4

#define UNIT_COST 5

#define RANGED 1
#define MELEE -1

// KING STATS
#define KING_MAX_HEALTH 500
#define KING_ATTACK_POINTS  10
#define KING_PRICE  0
#define KING_MOVEMENT_POINT 1

// ARCHER STATS
#define ARCHER_MAX_HEALTH  200
#define ARCHER_ATTACK_POINTS  20
#define ARCHER_PRICE  20
#define ARCHER_MOVEMENT_POINT 2

// SWORDSMAN STATS
#define SWORDSMAN_MAX_HEALTH  300
#define SWORDSMAN_ATTACK_POINTS  20
#define SWORDSMAN_PRICE  30
#define SWORDSMAN_MOVEMENT_POINT 3

// (OPTIONAL) MAGE
#define MAGE_MAX_HEALTH  100
#define MAGE_ATTACK_POINTS  20
#define MAGE_PRICE  35
#define MAGE_MOVEMENT_POINT 1

typedef struct Unit{
    int type;
    Point location;
    int maxHealth;
    int health;
    int price;
    int attackPoint;
    int movementPoint;
    int attackType;
    int playerID;
    Stack stackMovement;
    boolean hasAttacked;
} Unit;



typedef struct Unit King;
typedef struct Unit Archer;
typedef struct Unit Swordsman;
typedef struct Unit Mage;


void initKing(King *K);

void initArcher(Archer *A);

void initSwordsman(Swordsman *S);

void initMage(Mage *M);

Point getUnitLocation(Unit U);

int getHealth(Unit U);

int getPrice(Unit U);

int getMovementPoint(Unit U);

boolean canAttack(Unit U);

void setHealth(Unit*U, int amount);

void increaseHealth(Unit *U, int amount);

void decreaseHealth(Unit *U, int amount);

void setPrice(Unit *U, int amount);

void setMovementPoint(Unit *U,int amount);

void decreaseMovementPoint(Unit *U);

void setHasAttacked(Unit *U,boolean hasAttacked);

#endif
