/* File : jam.c */ 
/* Body prototype type jam */ 
#include "boolean.h"
#include <stdio.h>
#include "jam.h"
/* BODY Prototype */
/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */


/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
boolean IsJAMValid (int H, int M, int S){
	return ((H>=0) && (H<=23))&&((M>=0) && (M<=59))&&((S>=0) && (S<=59));
};

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS){
	JAM J;
	//Algoritma//
	Hour(J) = HH;
	Minute(J) = MM;
	Second(J) = SS;
	
	return J;
};
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J){
	int HH, MM, SS;
	
	do{ 
		scanf("%d %d %d",&HH,&MM,&SS);
		if (!(IsJAMValid(HH,MM,SS))){
			printf("Jam tidak valid\n");
		}
	} while(!(IsJAMValid(HH,MM,SS)));
		
	*J = MakeJAM(HH,MM,SS);
};
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
   
void TulisJAM (JAM J){
	printf("%02d:%02d:%02d",Hour(J),Minute(J),Second(J));
};
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */

long JAMToDetik (JAM J){
	long result;
	
	result=((Hour(J)*3600)+(Minute(J)*60)+Second(J));
	
	return result;
};
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */

JAM DetikToJAM (long N){
	long N1;	//Hour left in 1 day
	int HH,MM,DD;
	JAM J;
	N1 = N%86400;
	HH= N1/3600;
	MM= N1%3600/60;
	DD= N1%3600%60;
	
	J = MakeJAM(HH,MM,DD);
	
	return J;
}; 
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2){
	return (JAMToDetik(J1)==JAMToDetik(J2));
};
/* Mengirimkan true jika J1=J2, false jika tidak */
boolean JNEQ (JAM J1, JAM J2){
	return (!JEQ(J1,J2));
};
/* Mengirimkan true jika J1 tidak sama dengan J2 */
boolean JLT (JAM J1, JAM J2){
	return (JAMToDetik(J1)<JAMToDetik(J2));
};
/* Mengirimkan true jika J1<J2, false jika tidak */
boolean JGT (JAM J1, JAM J2){
	return (JAMToDetik(J1)>JAMToDetik(J2));
};
/* Mengirimkan true jika J1>J2, false jika tidak */
/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J){
	
	long nextOneSecond;

	nextOneSecond=JAMToDetik(J)+1;
	
	return DetikToJAM(nextOneSecond);
};
/* Mengirim 1 detik setelah J dalam bentuk JAM */
JAM NextNDetik (JAM J, int N){
	
	long nextNSecond;

	nextNSecond=JAMToDetik(J)+N;
	
	return DetikToJAM(nextNSecond);
};
/* Mengirim N detik setelah J dalam bentuk JAM */
JAM PrevDetik (JAM J){
	long prevOneSecond;
	if (JAMToDetik(J)==0){
		return MakeJAM(23,59,59);
	}
	else {
		prevOneSecond=JAMToDetik(J)-1;
	}
	
	return DetikToJAM(prevOneSecond);
};
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
JAM PrevNDetik (JAM J, int N){
	long prevNSecond;
	if (JAMToDetik(J)-N<0){
		prevNSecond=JAMToDetik(J)-N+86400;
	}
	else {
		prevNSecond=JAMToDetik(J)-N;
	}
	
	return DetikToJAM(prevNSecond);
};

/* Mengirim N detik sebelum J dalam bentuk JAM */
/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh){
	long diff;
	if (JAMToDetik(JAw)>JAMToDetik(JAkh)){
		diff=JAMToDetik(JAkh)-JAMToDetik(JAw)+86400;
	}
	else {
		diff=JAMToDetik(JAkh)-JAMToDetik(JAw);
	}
	return diff;
	
};
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
