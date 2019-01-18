#include <stdio.h>
#include "point.h"
#include "boolean.h"

void printBoolResult(boolean bool){
	
	if (bool){
		printf("TRUE\n");
	}
	else {
		printf("FALSE\n");
	}
}

int main(){
	POINT P1,P2;
	
	//Baca
	BacaPOINT(&P1);
	BacaPOINT(&P2);
	
	//Tulis 
	TulisPOINT(P1);printf("\n");
	TulisPOINT(P2);printf("\n");
	
	//Predikat
	printBoolResult(IsOrigin(P1));
	printBoolResult(IsOnSbX(P1));
	printBoolResult(IsOnSbY(P1));
	
	
	
	
	//Other functions
	printf("%.2f",Jarak0(P1));printf("\n");
	printf("%.2f",Panjang(P1,P2));printf("\n");
	
	
	printf("%d",Kuadran(P1));printf("\n");
	TulisPOINT(NextX(P1));printf("\n");
	TulisPOINT(NextY(P1));printf("\n");
	Geser(&P1,10,-10);
	TulisPOINT(P1);printf("\n");
	Mirror(&P1,false);
	TulisPOINT(P1);printf("\n");
	Putar(&P1,90);
	TulisPOINT(P1);printf("\n");
	

	
	
	
}