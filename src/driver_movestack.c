#include "./Point/point.h"
#include "moveStack.h"
#include <stdio.h>


int main () {

	//KAMUS
	Point Poa, Pob;
	Stack S;

	//ALGORITMA
	(Poa).X=1;
	(Poa).Y=2;
	(Pob).X=3;
	(Pob).Y=5;
	CreateStack(&S);
	PushMove(&S, Poa);
	printf("Push berhasil.\n");
	PopMove(&S, &Pob);
	printf("Pop berhasil. X poa= %d, Y poa= %d\n", (Pob).X, (Pob).Y);

	return 0;
}