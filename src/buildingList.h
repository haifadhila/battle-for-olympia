/* File : BuildingListsirkuler.h */
/* ADT BuildingList Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */
/* Representasi berkait dengan buildingAddress adalah pointer */
/* BuildingInfotype adalah integer */

#ifndef BUILDINGLIST_H
#define BUILDINGLIST_H

#include "boolean.h"
#include "building.h"

#define Nil NULL

typedef struct tElmtBuildingList *buildingAddress;
typedef struct tElmtBuildingList {
	Building info;
	buildingAddress next;
} ElmtBuildingList;

typedef struct {
	buildingAddress first;
} BuildingList;

/* Definisi BuildingList : */
/* BuildingList kosong : FirstBL(L) = Nil */
/* Setiap elemen dengan buildingAddress P dapat diacu BuildingInfo(P), NextBL(P) */
/* Elemen terakhir BuildingList: jika buildingAddressnya Last, maka NextBL(Last)=FirstBL(L) */

#define BuildingInfo(P) (P)->info
#define NextBL(P) (P)->next
#define FirstBL(L) ((L).first)

/* PROTOTYPE */
/****************** TEST BuildingList KOSONG ******************/
boolean IsEmptyBL (BuildingList L);
/* Mengirim true jika BuildingList kosong. Lihat definisi di atas. */

/****************** PEMBUATAN BuildingList KOSONG ******************/
void CreateEmptyBL (BuildingList *L);
/* I.S. L sembarang             */
/* F.S. Terbentuk BuildingList kosong. Lihat definisi di atas. */
buildingAddress CreateBuilding(Building B);
/****************** Manajemen Memori ******************/
/* Mengirimkan buildingAddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka buildingAddress tidak nil, dan misalnya */
/* menghasilkan P, maka BuildingInfo(P)=X, NextBL(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiBL (buildingAddress P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan DealokasiBL/pengembalian buildingAddress P */

/****************** PENCARIAN SEBUAH ELEMEN BuildingList ******************/

/* Mencari apakah ada elemen BuildingList dengan BuildingInfo(P)= X */
/* Jika ada, mengirimkan buildingAddress elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/

void AddBuilding (BuildingList *L,Building B);
/* I.S. BuildingList L tidak kosong  */
/* F.S. Elemen pertama BuildingList dihapus: nilai BuildingInfo disimpan pada X */
/*      dan alamat elemen pertama di-DealokasiBL */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void RemoveBuilding(BuildingList *L, buildingAddress P);
/****************** PROSES SEMUA ELEMEN BuildingList ******************/
/* I.S. BuildingList mungkin kosong */
/* F.S. Jika BuildingList tidak kosong, iai BuildingList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika BuildingList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
/* I.S. Sembarang */
/* F.S. Jika ada elemen BuildingList berbuildingAddress P, dengan BuildingInfo(P)=X  */
/* Maka P dihapus dari BuildingList dan di-DealokasiBL */
/* Jika tidak ada elemen BuildingList dengan BuildingInfo(P)=X, maka BuildingList tetap */
/* BuildingList mungkin menjadi kosong karena penghapusan */

/****************** PROSES SEMUA ELEMEN BuildingList ******************/
void PrintBLInfo (BuildingList L);
/* I.S. BuildingList mungkin kosong */
/* F.S. Jika BuildingList tidak kosong, iai BuildingList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika BuildingList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

buildingAddress getBuildingAddressByLocation(BuildingList L,Point P);

#endif
