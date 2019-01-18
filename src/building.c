#include "building.h"


Building createVillage(int playerID, Point Location){
  Building V;
  V.playerID = 0;
  V.type = VILLAGE;
  // V.color = "X";
  V.location = Location;
  return V;
};

Point getBuildingLocation(Building B){
  return B.location;
};

int getBuildingPlayerID(Building B){
  return B.playerID;
};
int getBuildingType(Building B){
  return B.type;
};

// Buat castle
Building createCastle(int playerID, Point Location){
    Building C;
    C.playerID = playerID;
    C.type = CASTLE;
    C.location = Location;
    // C.color = 'X';
    return C;
};
Building createTower(int playerID, Point Location){
  Building T;
  T.playerID = playerID;
  T.type = TOWER;
  T.location = Location;
  // T.color = 'X';
  return T;
};

void DeleteBuilding(Building *B){
  B->type=KOSONG;
};
void setPlayerID(Building *B, int playerID){
    B->playerID = playerID;
};
void setLocation(Building *B, Point location){
    B->location = location;
};
