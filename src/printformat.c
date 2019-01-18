#include "printformat.h"

void printLogo(){
  printf("\n");
  printf("\n");
  printf("    ██████╗ █████╗██████████████████╗    ███████╗    ███████╗██████╗██████╗\n " );
  printf("    ██╔══████╔══██╚══██╔══╚══██╔══██║    ██╔════╝    ██╔════██╔═══████╔══██╗\n " );
  printf("    ██████╔███████║  ██║     ██║  ██║    █████╗      █████╗ ██║   ████████╔╝\n " );
  printf("    ██╔══████╔══██║  ██║     ██║  ██║    ██╔══╝      ██╔══╝ ██║   ████╔══██╗\n " );
  printf("    ██████╔██║  ██║  ██║     ██║  ██████████████╗    ██║    ╚██████╔██║  ██║\n " );
  printf("    ╚═════╝╚═╝  ╚═╝  ╚═╝     ╚═╝  ╚══════╚══════╝    ╚═╝     ╚═════╝╚═╝  ╚═╝\n " );
  printf("                                                                        \n " );
  printf("                ██████╗██╗ ██╗   █████╗   █████████╗██╗█████╗\n " );
  printf("               ██╔═══████║ ╚██╗ ██╔████╗ ██████╔══██████╔══██╗\n " );
  printf("               ██║   ████║  ╚████╔╝██╔████╔████████╔█████████║\n " );
  printf("               ██║   ████║   ╚██╔╝ ██║╚██╔╝████╔═══╝████╔══██║\n " );
  printf("               ╚██████╔█████████║  ██║ ╚═╝ ████║    ████║  ██║\n " );
  printf("               ╚═════╝╚══════╚═╝  ╚═╝     ╚═╚═╝    ╚═╚═╝  ╚═╝\n " );
  printf("\n" );
}

void clearScreen(){
  #ifdef _WIN32
    system("cls");
  #endif
  #ifdef __unix__
    system("clear");
  #endif
}

void printCanAttack(Unit U){
  if (canAttack(U)){
    printf("YES");
  }
  else{
    printf("NO");
  }
}

void printUnitbyType(Unit U){
  if (U.type==KING_TYPE){
    printf("KING");
  }
  else if (U.type == ARCHER_TYPE){
    printf("ARCHER");
  }
  else if (U.type == SWORDSMAN_TYPE){
    printf("SWORDSMAN");
  }
  else if (U.type == MAGE_TYPE){
    printf("MAGE" );
  }
}

void printAttackType(Unit U){
  if (U.attackType == MELEE){
    printf("MELEE");
  }
  else if (U.attackType==RANGED) {
    printf("RANGED");
  }
};

void printPlayerInfo(Queue *Q){
  Player currPlayer = InfoHead(*Q);
  Unit currentUnit = UnitInfo(currPlayer.currentUnit);

  Point position = getUnitLocation(currentUnit);
  printf("\n" );
  printf("Player %d's Turn\n",currPlayer.ID);
  printf("Cash : %dG",currPlayer.gold);
  printf(" | Income : %dG",currPlayer.income);
  printf(" | Upkeep : %dG",currPlayer.upkeep);
  printf("\n");

  printf("Unit : ");
  printUnitbyType(currentUnit);
  printf(" (%d,%d)",position.X,position.Y);
  printf(" | Health : ");
  printf("%d",currentUnit.health );
  printf(" | " );
  printAttackType(currentUnit);
  printf(" | Movement Point : ");
  printf("%d",currentUnit.movementPoint );
  printf(" | Can Attack : ");
  printCanAttack(currentUnit);

  printf("\n");
}


void printUnitFormat(Unit U){
  printUnitbyType(U);
  printf(" (%d,%d)",U.location.X,U.location.Y);
  printf(" | " );
  printAttackType(U);
  printf(" | Health : ");
  printf("%d",U.health );
  printf(" | Movement Point : ");
  printf("%d",U.movementPoint );
  printf(" | Can Attack : ");
  printCanAttack(U);
}

void printUnitInfo(UnitList L){
  address P = FirstUL(L);
  int idx = 0;
  if (!IsEmptyUL(L)){
    idx++;
    printf("%d. ",idx);printUnitFormat(UnitInfo(P));printf("\n" );
    P = NextUL(P);
    while (P!=FirstUL(L)) {
      idx++;
      printf("%d. ",idx);printUnitFormat(UnitInfo(P));printf("\n" );
      P = NextUL(P);
    }
  }
}
