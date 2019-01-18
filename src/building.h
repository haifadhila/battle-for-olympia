#ifndef BUILDING_H
#define BUILDING_H

#include "unit.h"
#include "./Point/point.h"

#define KOSONG 0
#define VILLAGE 1
#define CASTLE 2
#define TOWER 3

#define VILLAGE_INCOME 10

typedef struct Building{
    int type;
    Point location;
    int playerID;
} Building;


// Buat village
Building createVillage(int playerID, Point Location);
Point getBuildingLocation(Building B);
int getBuildingPlayerID(Building B);
int getBuildingType(Building B);
// Buat castle
Building createCastle(int playerID, Point Location);
Building createTower(int playerID, Point Location);
void DeleteBuilding(Building *B);
void setPlayerID(Building *B, int playerID);
void setLocation(Building *B, Point location);



#endif
