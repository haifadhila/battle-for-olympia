#include "unitList.h"
#include "printformat.h"
#include <stdio.h>


int main() {
  UnitList UL;
  Queue Q;
  Unit U ;
  initArcher(&U);

  printLogo();
  clearScreen();
  printUnitbyType(U);
  printPlayerInfo(&Q);
  printUnitInfo(UL);
  return 0;
}
