#ifndef _GAMEPLAY_H
#define _GAMEPLAY_H

#include "unitList.h"
#include "playerQueue.h"
#include "buildingList.h"
#include "map.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

void updateTurn(Queue *Q,Map *M);

void makeTurnQueue(Queue *Q,Map *M);

void newGame(Queue *Q, Map *M);

void playTurn(Queue *Q, Map *M);

void getCommand(Queue *Q,Map *M, char *input);

void nextTurn(Queue *Q,Map *M);

#endif
