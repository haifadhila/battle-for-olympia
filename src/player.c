#include "player.h"
#include "unitList.h"


void initPlayer(Player *P, int ID){
  UnitList UL;
  BuildingList BL;
  CreateEmptyUL(&UL);
  CreateEmptyBL(&BL);

  (P)-> gold = START_GOLD;
  (P)-> ID = ID;
  (P)-> unitList = UL;
  (P)-> buildingList = BL;
  (P)-> income = 0;
  (P)-> upkeep = 0;
};

void updateUpkeep(Player *P){
  UnitList UL= (P)->unitList;
  int units = countUnit(UL);
  (P)->upkeep = units * UNIT_COST;
}

void updateIncome(Player *P){
  BuildingList BL = (P)->buildingList;
  buildingAddress buildingAddr = FirstBL(BL);
  int countVillage = 0;

  if (!IsEmptyBL(BL)){
    buildingAddr = NextBL(buildingAddr);
    while(buildingAddr != FirstBL(BL)){
      if (BuildingInfo(buildingAddr).type == VILLAGE){
        countVillage++;
      }
      buildingAddr = NextBL(buildingAddr);
    }
  }

  (P)->income = countVillage*VILLAGE_INCOME;
}

void updateIncomeUpkeep(Player *P){
  updateIncome(P);
  updateUpkeep(P);
}

void updateCurrentUnit(Player *P){
  UnitList UL = (P)->unitList;

    (P)-> currentUnit = FirstUL(UL);

}

void updatePlayerTurn(Player *P){
  updateIncomeUpkeep(P);
  updateCurrentUnit(P);
  increaseGold(P,(P)->income);
  if (canPayUpkeep(*P)){
    decreaseGold(P,(P)->upkeep);
  }
}

boolean canPayUpkeep(Player P){
  return P.gold > P.upkeep;
};

void updatePlayer(Player *P){
  updateIncomeUpkeep(P);
}

int getID(Player P){
    return P.ID;
}

UnitList getUnitList(Player P){
    return P.unitList;
}

BuildingList getBuildingList(Player P){
    return P.buildingList;
}

int getIncome(Player P){
    return P.income;
}

int getUpkeep(Player P){
    return P.upkeep;
}

int getGold(Player P){
    return P.gold;
}
// set gold ke amount tertentu

void setGold(Player *P, int amount){
    P->gold = amount;
};
// set gold ke amount tertentu

void increaseGold(Player *P, int amount){
    P->gold += amount;
};
// tambah gold beberapa amount tertentu

void decreaseGold(Player *P, int amount){
    P->gold -= amount;
};
// kurangi gold beberapa amount tertentu
