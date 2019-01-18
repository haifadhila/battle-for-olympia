// Feel free to add necessary function/methods
/* File : UnitListsirkuler.h */
/* ADT UnitList Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */
/* Representasi berkait dengan address adalah pointer */
/* UnitInfotype adalah integer */

#ifndef UNITLIST_H
#define UNITLIST_H

#include "boolean.h"
#include "unit.h"

#define Nil NULL

typedef struct tElmtUnitList *address;
typedef struct tElmtUnitList {
	Unit info;
	address next;
} ElmtUnitList;

typedef struct {
	address First;
} UnitList;

/* Definisi UnitList : */
/* UnitList kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu UnitInfo(P), Next(P) */
/* Elemen terakhir UnitList: jika addressnya Last, maka Next(Last)=First(L) */

#define UnitInfo(P) (P)->info
#define NextUL(P) (P)->next
#define FirstUL(L) ((L).First)

/* PROTOTYPE */
/* PROTOTYPE */
/****************** TEST UnitList KOSONG ******************/
boolean IsEmptyUL (UnitList L);
/* Mengirim true jika UnitList kosong. Lihat definisi di atas. */

/****************** PEMBUATAN UnitList KOSONG ******************/
void CreateEmptyUL (UnitList *L);
/* I.S. L sembarang             */
/* F.S. Terbentuk UnitList kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/

// Terbentuk address yang beratribut King
address CreateKing();
// Terbentuk address yang beratribut Archer
address CreateArcher();

// Terbentuk address yang beratribut Mage
address CreateMage();
// Terbentuk address yang beratribut Swordsman
address CreateSwordsman();
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka UnitInfo(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiUL (address P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan DealokasiUL/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN UnitList ******************/

/* Mencari apakah ada elemen UnitList dengan UnitInfo(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */


/*** PENAMBAHAN ELEMEN ***/
// Menambah King ke belakang list,
// [King,Archer] -> [King,Archer,King]
void AddKing(UnitList *L);

// Menambah Archer ke belakang list,
// [King,Archer] -> [King,Archer,Archer]
void AddArcher (UnitList *L);

// Menambah Swordsman ke belakang list,
// [King,Archer] -> [King,Archer,Swordsman]
void AddSwordsman (UnitList *L);

// Menambah Mage ke belakang list,
// [King,Archer] -> [King,Archer,Mage]
void AddMage (UnitList *L);
/* I.S. UnitList L tidak kosong  */
/* F.S. Elemen pertama UnitList dihapus: nilai UnitInfo disimpan pada X */
/*      dan alamat elemen pertama di-DealokasiUL */
int countUnit(UnitList L);

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DeleteUnit(UnitList *L, address P);
/****************** PROSES SEMUA ELEMEN UnitList ******************/
/* I.S. UnitList mungkin kosong */
/* F.S. Jika UnitList tidak kosong, iai UnitList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika UnitList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
/* I.S. Sembarang */
/* F.S. Jika ada elemen UnitList beraddress P, dengan UnitInfo(P)=X  */
/* Maka P dihapus dari UnitList dan di-DealokasiUL */
/* Jika tidak ada elemen UnitList dengan UnitInfo(P)=X, maka UnitList tetap */
/* UnitList mungkin menjadi kosong karena penghapusan */

/****************** PROSES SEMUA ELEMEN UnitList ******************/
void PrintULInfo (UnitList L);
/* I.S. UnitList mungkin kosong */
/* F.S. Jika UnitList tidak kosong, iai UnitList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika UnitList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

void resetUnitState (UnitList L);

#endif
