#include <math.h>
#include <stdio.h>
#include "boolean.h"
#include "point.h"
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (float X, float Y){
	Point P;
	Absis(P)=X;
	Ordinat(P)=Y;

	return P;
};
/* Membentuk sebuah Point dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPoint (Point * P){
	float X, Y;

	scanf("%f %f",&X,&Y);

	*P = MakePoint(X,Y);
};
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   Point P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
void TulisPoint (Point P){
	printf("(%.2f,%.2f)",Absis(P),Ordinat(P));
};
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ (Point P1, Point P2){

	return ((Absis(P1)==Absis(P2))&&(Ordinat(P1)==Ordinat(P2)));

};
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean NEQ (Point P1, Point P2){
	return (!EQ(P1,P2));
};
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (Point P){
	return ((Absis(P)==0)&&(Ordinat(P)==0));
};
/* Menghasilkan true jika P adalah titik origin */
boolean IsOnSbX (Point P){
	return (Ordinat(P)==0);
};
/* Menghasilkan true jika P terletak Pada sumbu X */
boolean IsOnSbY (Point P){
	return (Absis(P)==0);
};
/* Menghasilkan true jika P terletak pada sumbu Y */
int Kuadran (Point P){

	if ((Absis(P)>0)&&(Ordinat(P)>0)){
		return 1;
	}
	else if ((Absis(P)<0)&&(Ordinat(P)>0)){
		return 2;
	}
	else if ((Absis(P)<0)&&(Ordinat(P)<0)){
		return 3;
	}
	else if ((Absis(P)>0)&&(Ordinat(P)<0)){
		return 4;
	}

};
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX (Point P){

	return MakePoint((Absis(P)+1),(Ordinat(P)));

};
/* Mengirim salinan P dengan absis ditambah satu */
Point NextY (Point P){

	return MakePoint((Absis(P)),(Ordinat(P)+1));
};
/* Mengirim salinan P dengan ordinat ditambah satu */
Point PlusDelta (Point P, float deltaX, float deltaY){

	return MakePoint((Absis(P)+deltaX),(Ordinat(P)+deltaY));

};
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
Point MirrorOf (Point P, boolean SbX){
	float xMirrored;
	float yMirrored;

	if (SbX){
		xMirrored = Absis(P)*(-1);
		return MakePoint(xMirrored,Ordinat(P));
	}
	else {
		yMirrored = Ordinat(P)*(-1);
		return MakePoint(Absis(P),yMirrored);
	}
};

/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
float Jarak0 (Point P){
	return (sqrt((Absis(P)*Absis(P))+(Ordinat(P)*Ordinat(P))));
};
/* Menghitung jarak P ke (0,0) */
float Panjang (Point P1, Point P2){
	return (sqrt((Absis(P1)-Absis(P2))*(Absis(P1)-Absis(P2))+(Ordinat(P1)-Ordinat(P2))*(Ordinat(P1)-Ordinat(P2))));
};
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */
void Geser (Point *P, float deltaX, float deltaY){
	*P = PlusDelta(*P,deltaX,deltaY);
};
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void GeserKeSbX (Point *P){
	*P = MakePoint(Absis(*P),0);
};
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void GeserKeSbY (Point *P){
	*P = MakePoint(0,Ordinat(*P));
};
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
void Mirror (Point *P, boolean SbX){
	*P = MirrorOf(*P, SbX);
};
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
void Putar (Point *P, float Sudut){
	float xRotated;
	float yRotated;

	double angleRad;
	angleRad = Sudut * (M_PI/180);

	xRotated = (Absis(*P)*cos(angleRad))-(Ordinat(*P)*sin(angleRad));
	yRotated = (Absis(*P)*sin(angleRad))-((Ordinat(*P)*cos(angleRad)));

	*P = MakePoint(xRotated,yRotated);
};
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
