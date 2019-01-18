#include <stdio.h>
#include "boolean.h"
#include "jam.h"


void printBoolResult(boolean bool){
	
	if (bool){
		printf("TRUE\n");
	}
	else {
		printf("FALSE\n");
	}
}

int main(){
	JAM J1;
	JAM J2;
	//Baca
	BacaJAM(&J1);
	BacaJAM(&J2);
	
	//Tulis
	TulisJAM(J1);printf("\n");
	TulisJAM(J2);printf("\n");
	
	printf("%d\n",JAMToDetik(J1));
	TulisJAM(DetikToJAM(JAMToDetik(J1)));printf("\n");
	
	//Predikat
	printBoolResult(JEQ(J1,J2));	
	printBoolResult(JNEQ(J1,J2));
	printBoolResult(JLT(J1,J2));
	printBoolResult(JGT(J1,J2));
	
	//Other functions
	TulisJAM(NextDetik(J1));printf("\n");
	TulisJAM(NextNDetik(J1,60));printf("\n");
	TulisJAM(PrevDetik(J1));printf("\n");
	TulisJAM(PrevNDetik(J1,60));printf("\n");
	
	printf("%d",Durasi(J1,J2));	
}
