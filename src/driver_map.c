#include "playerQueue.h"
#include "buildingList.h"
#include "unitList.h"
#include "map.h"
#include "gameplay.h"

int main(){
  Player P1,P2;
  Map M;
  Building B;
  Unit U;
  Point P;
  Queue Q;
  int row,col;

  printf("Masukkan koordinat peta: ");
  scanf("%d %d",&row,&col);

  createMap(&M, row, col);

  CreateEmpty(&Q);

  initPlayer(&P1,PLAYER1);
  initPlayer(&P2,PLAYER2);

  initMap(&M,&P1,&P2);

  Add(&Q,P1);
  Add(&Q,P2);

  updateMap(&M,Q);

  printMap(M,Q);

  P.X = 1;
  P.Y = row-2;

  B = getBuilding(M, P);
  U = getUnit(M,P);

  printf("\n");
  printf("Tipe building di (1,2): %d\n", B.type);
  printf("Tipe unit di (1,2): %d\n", U.type);
}
