#ifndef PRINTFORMAT_H
#define PRINTFORMAT_H

#include <stdio.h>
#include "unit.h"
#include "playerQueue.h"
#include <stdlib.h>

void printLogo();

void clearScreen();

void printUnitbyType(Unit U);

void printPlayerInfo(Queue *Q);

void printUnitInfo(UnitList L);
#endif
