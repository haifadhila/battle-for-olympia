// ADT MAP
#include "unit.h"
#include "unitList.h"
#include "building.h"
#include "buildingList.h"
#include "./pcolor/pcolor.h"
#include "player.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "./Point/point.h"
#include "moveStack.h"


Building getBuilding(Map M, Point P){
// Mengambil object building pada Map pada Point P (x jadi kolom, y jadi baris)
    return M.MapTable[P.Y][P.X].building;
}

Unit getUnit(Map M, Point P){
// Mengambil object unit pada Map pada Point P (x jadi kolom, y jadi baris)
    return M.MapTable[P.Y][P.X].unit;
}

int generateRandNum(int min_num, int max_num){
  return (rand() % (max_num + 1 - min_num) + min_num);
}

void createMap(Map *M,int row,int column){
// Inisialisasi semua building dan unit dengan KOSONG
  (M)->row = row;
  (M)->column = column;
  for (int i=0; i<=row-1; i++){
    for (int j=0; j<=column-1; j++){
      (M)->MapTable[i][j].building.type = KOSONG; //Kosong gaada building
      (M)->MapTable[i][j].unit.type = KOSONG; //Kosong gaada unit
    }
  }
}

void kingToList(King K, UnitList *U){
// Menambahkan King ke list Unit
  address P = (address) malloc(1* sizeof(ElmtUnitList));
  UnitInfo(P) = K;
  if (IsEmptyUL(*U)){
    FirstUL(*U) = P;
    NextUL(P) = FirstUL(*U);
  }
}

void initMap(Map *M, Player *P1, Player *P2){
// Inisialisasi Map awal dan segala macam awalan game:
// Castle, Tower, King, Village dengan lokasi tertentu

  Point KingTower1, CSouth1, CNorth1, CEast1, CWest1;
  Point KingTower2, CSouth2, CNorth2, CEast2, CWest2;
  Building CS2, CN2, CE2, CW2, T1;
  Building CS1, CN1, CE1, CW1, T2; //CS = Castle South, CW = castle west, dsb
  King K1,K2;
  int ID1,ID2;

  CSouth1.X = 1;                CSouth1.Y = (M)->row-1;
  CSouth2.X = (M)->column-2;    CSouth2.Y = 2;

  CNorth1.X = 1;                CNorth1.Y = (M)->row-3;
  CNorth2.X = (M)->column-2;    CNorth2.Y = 0;

  CEast1.X = 0;                 CEast1.Y = (M)->row-2;
  CEast2.X = (M)->column-3;     CEast2.Y = 1;

  CWest1.X = 2;                 CWest1.Y = (M)->row-2;
  CWest2.X = (M)->column-1;     CWest2.Y = 1;

  KingTower1.X = 1;               KingTower1.Y = (M)->row-2;  // King tower player 1 di kiri bawah
  KingTower2.X = (M)->column-2;   KingTower2.Y = 1;  //King tower player 2 di kanan atas

  ID1 = getID(*P1);
  ID2 = getID(*P2);

  //INISIALISASI KING DAN KING TOWER
  initKing(&K1);
  K1.playerID = ID1;
  K1.location = KingTower1;
  PushMove(&(K1.stackMovement),K1.location);
  initKing(&K2);
  K2.playerID = ID2;
  K2.location = KingTower2;
  PushMove(&(K2.stackMovement),K2.location);

  CreateEmptyUL(&(P1)->unitList);
  CreateEmptyUL(&(P2)->unitList);
  kingToList(K1,&(P1)->unitList);
  kingToList(K2,&(P2)->unitList);

  T1 = createTower(ID1,KingTower1);
  AddBuilding(&((P1)->buildingList),T1);
  T2 = createTower(ID2,KingTower2);
  AddBuilding(&((P2)->buildingList),T2);

  (M)->MapTable[KingTower1.Y][KingTower1.X].building = T1; //Masukin ke lokasi map
  (M)->MapTable[KingTower1.Y][KingTower1.X].unit = K1;
  (M)->MapTable[KingTower2.Y][KingTower2.X].building = T2;
  (M)->MapTable[KingTower2.Y][KingTower2.X].unit = K2;

  //INISIALISASI CASTLE PLAYER 1
  CS1 = createCastle(ID1,CSouth1);
  (M)->MapTable[CSouth1.Y][CSouth1.X].building = CS1;
  AddBuilding(&((P1)->buildingList),CS1);

  CN1 = createCastle(ID1,CNorth1);
  (M)->MapTable[CNorth1.Y][CNorth1.X].building = CN1;
  AddBuilding (&((P1)->buildingList),CN1);

  CE1 = createCastle(ID1,CEast1);
  (M)->MapTable[CEast1.Y][CEast1.X].building = CE1;
  AddBuilding (&((P1)->buildingList),CE1);

  CW1 = createCastle(ID1,CWest1);
  (M)->MapTable[CWest1.Y][CWest1.X].building = CW1;
  AddBuilding(&((P1)->buildingList),CW1);

  //INISIALISASI CASTLE PLAYER 2
  CS2 = createCastle(ID2,CSouth2);
  (M)->MapTable[CSouth2.Y][CSouth2.X].building = CS2;
  AddBuilding (&((P2)->buildingList),CS2);

  CN2 = createCastle(ID2,CNorth2);
  (M)->MapTable[CNorth2.Y][CNorth2.X].building = CN2;
  AddBuilding (&((P2)->buildingList),CN2);

  CE2 = createCastle(ID2,CEast2);
  (M)->MapTable[CEast2.Y][CEast2.X].building = CE2;
  AddBuilding (&((P2)->buildingList),CE2);

  CW2 = createCastle(ID2,CWest2);
  (M)->MapTable[CWest2.Y][CWest2.X].building = CW2;
  AddBuilding (&((P2)->buildingList),CW2);

  //INISIALISASI VILLAGE RANDOM -- BELUM
  Point Pv;
  int VperBaris, idxKolV;
  Building Vil;

  time_t t;
  srand((unsigned) time(&t));

  CreateEmptyBL(&((M)->villageList));
  for (int i=0; i<=(M)->row-1; i++){
    VperBaris = generateRandNum(0,2);
    for (int p=0; p<VperBaris; p++){
      if ((i>=0)&&(i<=2))
        idxKolV = generateRandNum(0,(M)->column-4);
      else if ((i>=(M)->row-4)&&(i<=(M)->row-1))
        idxKolV = generateRandNum(3,(M)->column-1);
      else
        idxKolV = generateRandNum(0,(M)->column-1);
      Pv.X = idxKolV;
      Pv.Y = i;
      Vil = createVillage(0,Pv);
      AddBuilding(&((M)->villageList),Vil);
    }
  }

  (P1)-> currentUnit = (FirstUL((P1)-> unitList));
  (P2)-> currentUnit = (FirstUL((P2)->unitList));
}

void updateMap(Map *M, Queue Q){
// update Map sesuai dengan posisi-posisi yang masing-masing player punya
// cek ke list unitnya player masing-masing posisinya, dan assign ke Map
  buildingAddress Pb1, Pb2, Pvil;
  Player P1;
  Player P2;
  Del(&Q,&P1);
  Del(&Q,&P2);
  address Pu1, Pu2;
  int Xp,Yp;
  BuildingList VillageList;
  VillageList = (M)->villageList;
  createMap(M,(M)->row,(M)->column);

  // UPDATE BUILDING PLAYER 1
  Pb1 = FirstBL(P1.buildingList);
  Xp = BuildingInfo(Pb1).location.X;
  Yp = BuildingInfo(Pb1).location.Y;
  (M)->MapTable[Yp][Xp].building = BuildingInfo(Pb1);
  Pb1 = NextBL(Pb1);

  while (Pb1!=FirstBL(P1.buildingList)){
    Xp = BuildingInfo(Pb1).location.X;
    Yp = BuildingInfo(Pb1).location.Y;
    (M)->MapTable[Yp][Xp].building = BuildingInfo(Pb1);
    Pb1 = NextBL(Pb1);
  }

  // UPDATE BUILDING PLAYER 2
  Pb2 = FirstBL(P2.buildingList);
  Xp = BuildingInfo(Pb2).location.X;
  Yp = BuildingInfo(Pb2).location.Y;
  (M)->MapTable[Yp][Xp].building = BuildingInfo(Pb2);
  Pb2 = NextBL(Pb2);

  while (Pb2!=FirstBL(P2.buildingList)){
    Xp = BuildingInfo(Pb2).location.X;
    Yp = BuildingInfo(Pb2).location.Y;
    (M)->MapTable[Yp][Xp].building = BuildingInfo(Pb2);
    Pb2 = NextBL(Pb2);
  }

  // UPDATE UNIT PLAYER 1
  Pu1 = FirstUL(P1.unitList);
  if (Pu1!=Nil){
   Xp = UnitInfo(Pu1).location.X;
   Yp = UnitInfo(Pu1).location.Y;
  (M)->MapTable[Yp][Xp].unit = UnitInfo(Pu1);

  Pu1= NextUL(Pu1);

  while (Pu1!=FirstUL(P1.unitList)){
    Xp = UnitInfo(Pu1).location.X;
    Yp = UnitInfo(Pu1).location.Y;
    (M)->MapTable[Yp][Xp].unit = UnitInfo(Pu1);
    Pu1 = NextUL(Pu1);
  }
}

  // UPDATE UNIT PLAYER 2
  Pu2 = FirstUL(P2.unitList);
  if (Pu2!=Nil){
   Xp = UnitInfo(Pu2).location.X;
   Yp = UnitInfo(Pu2).location.Y;
  (M)->MapTable[Yp][Xp].unit = UnitInfo(Pu2);
  Pu2 = NextUL(Pu2);

  while (Pu2!=FirstUL(P2.unitList)){
    Xp = UnitInfo(Pu2).location.X;
    Yp = UnitInfo(Pu2).location.Y;
    (M)->MapTable[Yp][Xp].unit = UnitInfo(Pu2);
    Pu2 = NextUL(Pu2);
  }

}

  // UPDATE UNOWNED VILLAGE
  Pvil = FirstBL(VillageList);
  Xp = BuildingInfo(Pvil).location.X;
  Yp = BuildingInfo(Pvil).location.Y;
  (M)->MapTable[Yp][Xp].building = BuildingInfo(Pvil);

  Pvil = NextBL(Pvil);

  while (Pvil!=FirstBL(VillageList)){
    Xp = BuildingInfo(Pvil).location.X;
    Yp = BuildingInfo(Pvil).location.Y;
    (M)->MapTable[Yp][Xp].building = BuildingInfo(Pvil);
    Pvil = NextBL(Pvil);
  }
}

void makeHorizontalBorder(Map M){
/* Membuat border horizontal pada peta */
  printf("  ");
  for (int i=0; i<=((M.column)*4); i++){
    printf("*");
  }
}

void printMap(Map M, Queue Q){
// print map sesuai dengan spek
// kalau building.type == KOSONG// , print spasi
// Menggunakan warna
  int ID1,ID2;
  int i,j;
  Point P;

  Player P1;
  Player P2;
  Del(&Q,&P1);
  Del(&Q,&P2);

  ID1 = PLAYER1;
  ID2 = PLAYER2;

  printf("  ");
  for (P.X=0; P.X<=M.column-1; P.X++){
    if (P.X < 10)
      printf("  %d ",P.X);
    else
      printf("  %d",P.X);
  }
  printf("\n");

  for (P.Y=0; P.Y<=M.row-1; P.Y++){
    makeHorizontalBorder(M); //Print border tiap ganti baris
    printf("\n");

/***LOOPING PRINT 3X KARENA TIAP KOLOM PUNYA 3 BARIS****/

printf("  ");
for (P.X=0; P.X<=M.column-1; P.X++){
  if (M.MapTable[P.Y][P.X].building.type == 0)
    printf("*   ");
  else if (M.MapTable[P.Y][P.X].building.type == 1){
    printf("* ");
    if (M.MapTable[P.Y][P.X].building.playerID==ID1)
      print_red('V');
    else if (M.MapTable[P.Y][P.X].building.playerID==ID2)
      print_blue('V');
    else printf("V");
    printf(" ");
  }
  else if (M.MapTable[P.Y][P.X].building.type == 2){
    printf("* ");
    if (M.MapTable[P.Y][P.X].building.playerID==ID1)
      print_red('C');
    else if (M.MapTable[P.Y][P.X].building.playerID==ID2)
      print_blue('C');
    printf(" ");
  }
  else if (M.MapTable[P.Y][P.X].building.type == 3){
    printf("* ");
    if (M.MapTable[P.Y][P.X].building.playerID==ID1)
      print_red('T');
    else if (M.MapTable[P.Y][P.X].building.playerID==ID2)
      print_blue('T');
    printf(" ");
  }
} printf("*\n");

//PRINT SEBARIS KEDUA YANG DAPAT BERISI UNIT
if (P.Y<10)
  printf("%d ",P.Y);
else
    printf("%d",P.Y);
for (P.X=0; P.X<=M.column-1; P.X++){
  if (M.MapTable[P.Y][P.X].unit.type == 0){
    printf("*   ");
  }
  else if (M.MapTable[P.Y][P.X].unit.type == 1){
    printf("* ");
    if (M.MapTable[P.Y][P.X].unit.playerID==ID1){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('K');
      }

      else {

        print_red('K');
      }

    }
    else if (M.MapTable[P.Y][P.X].unit.playerID==ID2){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('K');
      }
      else {

        print_blue('K');
      }
    }

    printf(" ");
  }
  else if (M.MapTable[P.Y][P.X].unit.type == 2){
    printf("* ");
    if (M.MapTable[P.Y][P.X].unit.playerID==ID1){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('A');
      }
      else {
        print_red('A');
      }
    }
    else if (M.MapTable[P.Y][P.X].unit.playerID==ID2){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('A');
      }
      else {
        print_blue('A');
      }
    }
    printf(" ");
  }
  else if (M.MapTable[P.Y][P.X].unit.type == 3){
    printf("* ");
    if (M.MapTable[P.Y][P.X].unit.playerID==ID1){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('S');
      }
      else {
        print_red('S');
      }
    }
    else if (M.MapTable[P.Y][P.X].unit.playerID==ID2){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('S');
      }
      else {

        print_blue('S');
      }
    }
    printf(" ");
  }
  else if (M.MapTable[P.Y][P.X].unit.type == 4){
    printf("* ");
    if (M.MapTable[P.Y][P.X].unit.playerID==ID1){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('w');
      }
      else {
        print_red('w');
      }
    }
    else if (M.MapTable[P.Y][P.X].unit.playerID==ID2){
      if ( UnitInfo(P1.currentUnit).location.X == P.X && UnitInfo(P1.currentUnit).location.Y == P.Y ){
        print_green('w');
      }
      else{

        print_blue('w');
      }
    }
    else printf("w");
    printf(" ");
  }
  else if (M.MapTable[P.Y][P.X].unit.type == 5){
    printf("* ");
    print_yellow('#');
    printf(" ");
    }
  } printf("*\n");

  //PRINT SEBARIS KETIGA YANG TIDAK ADA ISINYA
  printf("  ");
  for (P.X=0; P.X<=M.column-1; P.X++){
    printf("*   ");
    } printf("*\n");
  }
  makeHorizontalBorder(M);
}
