#include "buildingList.h"
#include "boolean.h"

boolean IsEmptyBL (BuildingList L){
  return (FirstBL(L)==Nil);
};
/* Mengirim true jika BuildingList kosong. Lihat definisi di atas. */

/****************** PEMBUATAN BuildingList KOSONG ******************/
void CreateEmptyBL (BuildingList *L){
	FirstBL(*L) = Nil;
};
/* I.S. L sembarang             */
/* F.S. Terbentuk BuildingList kosong. Lihat definisi di atas. */
buildingAddress CreateBuilding(Building B){
	buildingAddress P = (buildingAddress) malloc(1* sizeof(ElmtBuildingList));
	if (P!=Nil){
		BuildingInfo(P)=B;
		NextBL(P) = Nil;
	    return P;
	 }
	 else {
	    return P;
	  }
}
/****************** Manajemen Memori ******************/
/* Mengirimkan buildingAddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka buildingAddress tidak nil, dan misalnya */
/* menghasilkan P, maka BuildingInfo(P)=X, NextBL(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiBL (buildingAddress P){
  free(P);
};
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan DealokasiBL/pengembalian buildingAddress P */

/****************** PENCARIAN SEBUAH ELEMEN BuildingList ******************/

/* Mencari apakah ada elemen BuildingList dengan BuildingInfo(P)= X */
/* Jika ada, mengirimkan buildingAddress elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/

void AddBuilding (BuildingList *L,Building B){
  buildingAddress PIterate;
  buildingAddress PInsert;

  PInsert = CreateBuilding(B);

  PIterate = FirstBL(*L);

  if (PInsert!=Nil){
    if (PIterate!=Nil){
      while (NextBL(PIterate)!=FirstBL(*L)) {
        PIterate = NextBL(PIterate);
      }
      NextBL(PInsert) = FirstBL(*L);
      NextBL(PIterate) = PInsert;
    }
    else {
      FirstBL(*L) = PInsert;
      NextBL(PInsert) = FirstBL(*L);
    }
  }
};
/* I.S. BuildingList L tidak kosong  */
/* F.S. Elemen pertama BuildingList dihapus: nilai BuildingInfo disimpan pada X */
/*      dan alamat elemen pertama di-DealokasiBL */
buildingAddress getBuildingAddressByLocation(BuildingList L, Point P){
  buildingAddress BA = FirstBL(L);
  Point location = BuildingInfo(BA).location;

  if (!IsEmptyBL(L)){
    BA = NextBL(BA);
    while (!(location.X == P.X && location.Y == P.Y) && BA!=FirstBL(L)){
      BA = NextBL(BA);
      location = BuildingInfo(BA).location;
    }
    return BA;
  }
  else {
    return Nil;
  }
}


/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void RemoveBuilding(BuildingList *L, buildingAddress P){
  buildingAddress PIterate;
  buildingAddress PRec;

  PIterate = FirstBL(*L);
  PRec = Nil;

  if (PIterate==P){
    if (NextBL(PIterate) == FirstBL(*L)){
      FirstBL(*L) = Nil;
    }
    else {
      while (NextBL(PIterate)!=FirstBL(*L)) {
        PIterate = NextBL(PIterate);
      }
      DealokasiBL(FirstBL(*L));
      FirstBL(*L) = NextBL(FirstBL(*L));
      NextBL(PIterate) = FirstBL(*L);
    }
  }
  else{
    PRec = PIterate;
    PIterate = NextBL(PIterate);

    while ( (PIterate!=FirstBL(*L)) && (PIterate!=P)) {
      PRec = PIterate;
      PIterate = NextBL(PIterate);
    }

    if (PIterate!=FirstBL(*L)){
      NextBL(PRec) = NextBL(NextBL(PRec));
      DealokasiBL(P);
    }
  }

};
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
void PrintBLInfo (BuildingList L){
  buildingAddress PIterate;
  PIterate = FirstBL(L);

  printf("[");
    if (!IsEmptyBL(L)){
      printf("%d",BuildingInfo(PIterate).type);
      if (NextBL(PIterate)!=FirstBL(L)){
        printf(",");
      }
      PIterate = NextBL(PIterate);

      while (PIterate != FirstBL(L)) {
        printf("%d",BuildingInfo(PIterate).type);
        if (NextBL(PIterate)!=FirstBL(L)){
          printf(",");
        }
        PIterate = NextBL(PIterate);
      }
    }

  printf("]");
};
/* I.S. BuildingList mungkin kosong */
/* F.S. Jika BuildingList tidak kosong, iai BuildingList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika BuildingList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
