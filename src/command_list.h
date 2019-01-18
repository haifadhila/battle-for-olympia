#ifndef command_list_H
#define command_list_H

#include "player.h"
#include "unit.h"
#include "unitList.h"
#include "building.h"
#include "buildingList.h"
#include "map.h"
#include "./Point/point.h"
#include "moveStack.h"


int countMove (Point P1, Point P2);
// menghitung banyaknya move yang dilakukan untuk berpindah dari P1 ke P2

void Move(Queue*Q, Player *P, Map *M);
// Tampilkan kemungkinan jalan yang mungkin (baca spek)
// Unit bergerak ke lokasi yang ditempuh
// apabila merupakan village, village jadi milik player tersebut ()

void ChangeUnit(Player *P);
// Menambah unit baru yang hanya bisa dilakukan oleh King
// dan hanya bisa dilakukan di Castle yang kosong
void Recruit(Player *P, Map M);

void Undo(Player *P);

void NextUnit(Player *P);

void Attack (Map M, Player *P1, Player *P2);

void InfoCell(Map M, Player P1, Player P2);

void whiteMageHealing(Map M, Player *PL);
// void EndTurn(Player P);*/

#endif
