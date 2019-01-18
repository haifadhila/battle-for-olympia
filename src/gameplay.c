#include "gameplay.h"
#include "command_list.h"
#include "printformat.h"
#include "map.h"
#include "player.h"
#include <string.h>


void printHelp(){
  printf("\n\n-------------------HELP-------------------\n");
  printf("MOVE                  : Move selected unit \n");
  printf("RECRUIT               : Recruit a unit \n");
  printf("UNDO                  : Undo the latest unit movement\n");
  printf("CHANGE_UNIT           : Change selected unit \n");
  printf("NEXT_UNIT             : Change to the next unit\n");
  printf("ATTACK                : Attack nearby enemy \n");
  printf("INFO                  : Show the selected location information\n");
  printf("END_TURN              : End the turn \n");
}

int checkKing(Player P){
  int check=0;
  address uAdr = FirstUL(P.unitList);
  if (uAdr != Nil){
    // uAdr = NextUL(uAdr);
    if (UnitInfo(uAdr).type==KING_TYPE){
      check = 1;
    }
    else {
      while (uAdr != FirstUL(P.unitList)) {
        if (UnitInfo(uAdr).type==KING_TYPE){
          check = 1;
        }
        uAdr = NextUL(uAdr);
      }
    }
  }
  else {
    return 0;
  }
  return check;
}


void checkWinner(Queue *Q){
  int is_king1_ada = 0;
  int is_king2_ada = 0;
  Player P1;
  Player P2;
  is_king1_ada = checkKing(InfoHead(*Q));
  Del(Q,&P1);
  is_king2_ada = checkKing(InfoHead(*Q));
  Del(Q,&P2);
  if (is_king1_ada){
    Add(Q,P1);
  }
  if (is_king2_ada){
    Add(Q,P2);
  }

}

void updateTurn(Queue *Q, Map *M){
  Player P;
  updatePlayerTurn(&InfoHead(*Q));
  resetUnitState(InfoHead(*Q).unitList);
  whiteMageHealing (*M,&InfoHead(*Q));
  Del(Q,&P);
  updatePlayerTurn(&InfoHead(*Q));
  resetUnitState(InfoHead(*Q).unitList);
  whiteMageHealing (*M,&InfoHead(*Q));
  Add(Q,P);
}

void makeTurnQueue(Queue *Q, Map *M){
  Player P1;
  Player P2;
  CreateEmpty(Q);
  initPlayer(&P1,PLAYER1);
  initPlayer(&P2,PLAYER2);
  initMap(M,&P1,&P2);
  Add(Q,P1);
  Add(Q,P2);
  updateMap(M,*Q);
}


void newGame(Queue *Q, Map *M)
{
  int col,row;
  do {
      printf("Masukkan Ukuran Peta (Minimum 8x8)\n");
      printf("Jumlah Baris : ");
      scanf("%d", &row);
      printf("Jumlah Kolom : ");
      scanf("%d", &col);
    if ((row < 8) || (col < 8)){
      printf("Masukan Salah! Input minimum 8x8.\n");
    }
} while ((row < 8) || (col < 8));
  createMap(M, row, col);
  makeTurnQueue(Q,M);
  clearScreen();
  printf("\n");
  printMap(*M,*Q);
}


void playTurn(Queue *Q, Map *M)
{
  updatePlayer(&InfoHead(*Q));
  char input[200];
  printPlayerInfo(Q);
  printf("Your input : ");
  scanf("%s",input);
  getCommand(Q,M,input);

  printMap(*M,*Q);
  checkWinner(Q);
}

void getCommand(Queue *Q,Map *M, char *input)
// minta command
// lakukan aksi sesuai dengan command list
{

  if (!strcmp(input,"RECRUIT")){
    Recruit(&InfoHead(*Q), *M);
    updateMap(M,*Q);
    printMap(*M,*Q);
    playTurn(Q,M);
    // clearScreen();
  }
  else if (!strcmp(input, "UNDO")){
    Undo(&InfoHead(*Q));
    // clearScreen();
  }
  else if (!strcmp(input,"CHANGE_UNIT")){
    clearScreen();
    printMap(*M,*Q);
    ChangeUnit(&InfoHead(*Q));
  }
  else if (!strcmp(input,"ATTACK")){
    if (canAttack(UnitInfo(InfoHead(*Q).currentUnit))){
      Attack(*M,&InfoHead(*Q),&InfoTail(*Q));
    }
    else {
      printf("This unit cannot attack this turn.\n" );
      playTurn(Q,M);
    }
  }
  else if (!strcmp(input,"INFO")){
    clearScreen();
    updateMap(M,*Q);
    printMap(*M,*Q);
    InfoCell(*M,InfoHead(*Q),InfoTail(*Q));
    playTurn(Q,M);
  }
  else if (!strcmp(input, "END_TURN")){
    clearScreen();
    nextTurn(Q,M);
  }
  else if (!strcmp(input, "MOVE")){
    clearScreen();
    Move(Q,&InfoHead(*Q),M);
  }
  else if (!strcmp(input, "NEXT_UNIT")){
    clearScreen();
    NextUnit(&InfoHead(*Q));
  }
  else if (!strcmp(input, "HELP")){
    clearScreen();
    printMap(*M,*Q);
    printHelp();
    playTurn(Q,M);
  }
  else {
    clearScreen();
    printf("\n");printMap(*M,*Q);
    printf("\nWrong input. Please try again.\n" );
    playTurn(Q,M);
  }
  printf("\n" );
  updateMap(M,*Q);

}

void nextTurn(Queue *Q, Map *M)
// //ganti ke player selanjutnya
// // update map setelah command-command dilakukan
// // (Optional) check unit mage, temen-temen yang adjacent healthnya nambah
// // update uang player
{
  updateTurn(Q,M);
  updateMap(M,*Q);
}
