#include "unit.h"

void initKing(King *K){
  int currentHealth = KING_MAX_HEALTH;
  Point P;
  P.X = 0;
  P.Y = 0;
    K->type = KING_TYPE;
    K->maxHealth = currentHealth;
    K->attackType = MELEE;
    K->health = currentHealth;
    K->location = P;
    K->attackPoint = KING_ATTACK_POINTS;
    K->movementPoint = KING_MOVEMENT_POINT;
    K->price = KING_PRICE;
    K->hasAttacked = true;
    CreateStack(&(*K).stackMovement);
}

void initArcher(Archer *A) {
  int currentHealth = ARCHER_MAX_HEALTH;
    A->maxHealth = currentHealth;
    A->type = ARCHER_TYPE;
    A->health = currentHealth;
    A->attackType = RANGED;
    A->attackPoint = ARCHER_ATTACK_POINTS;
    A->movementPoint = ARCHER_MOVEMENT_POINT;
    A->price = ARCHER_PRICE;
    A->hasAttacked = true;
    CreateStack(&(*A).stackMovement);
}

void initSwordsman(Swordsman *S){
    int currentHealth = SWORDSMAN_MAX_HEALTH;
    S->maxHealth = currentHealth;
    S->type = SWORDSMAN_TYPE;
    S->health = currentHealth;
    S->attackPoint = SWORDSMAN_ATTACK_POINTS;
    S->movementPoint = SWORDSMAN_MOVEMENT_POINT;
    S->attackType = MELEE;
    S->price = SWORDSMAN_PRICE;
    S->hasAttacked = true;
    CreateStack(&(*S).stackMovement);
}

void initMage(Mage *M){
    int currentHealth = MAGE_MAX_HEALTH;
    M->maxHealth = currentHealth;
    M->type = MAGE_TYPE;
    M->health = currentHealth;
    M->attackPoint = MAGE_ATTACK_POINTS;
    M->movementPoint = MAGE_MOVEMENT_POINT;
    M->attackType = RANGED;
    M->price = MAGE_PRICE;
    M->hasAttacked = true;
    CreateStack(&(*M).stackMovement);
}

Point getUnitLocation(Unit U){
    Point P;
    P = U.location;
    return P;
}

int getHealth(Unit U){
    return U.health;
}

int getPrice(Unit U){
    return U.price;
}

int getMovementPoint(Unit U){
    return U.movementPoint;
}

boolean canAttack(Unit U){
    return !U.hasAttacked;
}

void setHealth(Unit*U, int amount){
    U->health=amount;
}

void increaseHealth(Unit *U, int amount){
  printf("ada\n" );
    U->health+=amount;
}

void decreaseHealth(Unit *U, int amount){
    U->health-=amount;
}

void setPrice(Unit *U, int amount){
    U->price=amount;
}

void setMovementPoint(Unit *U,int amount){
    U->movementPoint=amount;
}

void decreaseMovementPoint(Unit *U){
    U->movementPoint-=1;
}

void setHasAttacked(Unit *U,boolean hasAttacked){
    U->movementPoint=hasAttacked;
}
