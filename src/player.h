// Feel free to add necessary function/methods
#ifndef player_H
 #define player_H

#include "unitList.h"
#include "buildingList.h"
#include "boolean.h"

#define PLAYER1 1
#define PLAYER2 2

#define START_GOLD 100

typedef struct Player{
    UnitList unitList;
    BuildingList buildingList;
    address currentUnit;
    int gold;
    int ID;
    int income;
    int upkeep;
} Player;

void initPlayer(Player *P, int ID);

void updatePlayerTurn(Player *P);

void updateCurrentUnit(Player *P);

void updatePlayer(Player *P);

int getID(Player P);

UnitList getUnitList(Player P);

BuildingList getBuildingList(Player P);

boolean canPayUpkeep(Player P);

int getIncome(Player P);

int getUpkeep(Player P);

int getGold(Player P);
// set gold ke amount tertentu

void setGold(Player *P, int amount);
// set gold ke amount tertentu

void increaseGold(Player *P, int amount);
// tambah gold beberapa amount tertentu

void decreaseGold(Player *P, int amount);
// kurangi gold beberapa amount tertentu

#endif
