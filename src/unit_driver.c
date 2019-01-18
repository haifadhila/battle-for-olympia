#include <stdio.h>
#include "unit.h"
#include "unitList.h"


int main() {
  Unit U1;
  Unit U2;
  Unit U3;
  int price;
  int health;
  int movementPoint;
  Point position;
  address UA;
  UnitList UL;

  initKing(&U1);
  initArcher(&U2);
  initSwordsman(&U3);

  price = getPrice(U1);
  health = getHealth(U1);
  movementPoint = getMovementPoint(U1);
  position = getUnitLocation(U1);

  printf("%d %d %d %d %d\n",price, health, movementPoint, position.X, position.Y );
  CreateEmptyUL(&UL);
  AddKing(&UL);
  AddArcher(&UL);
  AddSwordsman(&UL);
  AddMage(&UL);

  PrintULInfo(UL);
  UA = FirstUL(UL);
  DeleteUnit(&UL,UA);
  PrintULInfo(UL);


  return 0;
}
