// #include "building.h"
#include "playerQueue.h"
#include "buildingList.h"
#include "printformat.h"
#include "unitList.h"
#include "map.h"
#include "gameplay.h"
#include "mesinlogo.h"
#include "mesinkar.h"

int main() {

  Queue Q;
  Map M;
  clearScreen();
  TulisLogo();
  newGame(&Q,&M);
  while (NbElmt(Q) == 2) {
    printf("%d\n",NbElmt(Q) );
    playTurn(&Q,&M);
  }
  clearScreen();
  printf("\n====================================================\n" );
  printf("         Player %d won the game!\n", (InfoHead(Q).ID));
  printf("\n====================================================\n" );


  return 0;
}
