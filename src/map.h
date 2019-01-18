#ifndef map_H
#define map_H

#include "unit.h"
#include "unitList.h"
#include "building.h"
#include "buildingList.h"
#include "playerQueue.h"
#include "./pcolor/pcolor.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "./Point/point.h"
#include "moveStack.h"

#define KOSONG 0
#define MAX_MAP_ROW 50
#define MAX_MAP_COLUMN 50

typedef struct MapElement{
    Building building;
    Unit unit;
} MapElement;

typedef struct Map{
    BuildingList villageList;
    MapElement MapTable[MAX_MAP_ROW][MAX_MAP_COLUMN];
    int row;
    int column;
} Map;

Building getBuilding(Map M, Point P);
// Mengambil object building pada Map pada Point P (x jadi kolom, y jadi baris)

Unit getUnit(Map M, Point P);
// Mengambil object unit pada Map pada Point P (x jadi kolom, y jadi baris)

int generateRandNum(int max_num, int min_num);

void createMap(Map *M,int row,int column);
// Inisialisasi semua building dan unit dengan KOSONG

void initMap(Map *M, Player *P1, Player *P2);
// Inisialisasi Map awal dan segala macam awalan game:
// castle,King
// parameter fungsi nyesuain aja

void updateMap(Map *M, Queue Q);
// update Map sesuai dengan posisi-posisi yang masing-masing player punya
// cek ke list unitnya player masing-masing posisinya, dan assign ke Map

void makeHorizontalBorder();
/* Membuat border horizontal pada peta */

void printMap(Map M, Queue Q);
// print map sesuai dengan spek
// kalau building.type == KOSONG// , print spasi aja
// jangan lupa pakai warna

#endif
