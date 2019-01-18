#include <stdio.h>
#include "building.h"
#include "buildingList.h"


int main() {
  BuildingList BL;
  buildingAddress bA = Nil;
  Point P;
  P.X = 1;
  P.Y = 1;
  Building B1 = createTower(1,P);
  Building B2 = createVillage(1,P);
  Building B3 = createCastle(1,P);

  setPlayerID(&B1,2);
  setLocation(&B1,P);

  CreateEmptyBL(&BL);
  AddBuilding(&BL,B1);
  AddBuilding(&BL,B2);
  AddBuilding(&BL,B3);

  PrintBLInfo(BL);
  RemoveBuilding(&BL,bA);

  PrintBLInfo(BL);

  return 0;
}
