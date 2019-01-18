#include "unitList.h"

/****************** TEST UnitList KOSONG ******************/
boolean IsEmptyUL (UnitList L){
  return (FirstUL(L)==Nil);
};
/* Mengirim true jika UnitList kosong. Lihat definisi di atas. */

/****************** PEMBUATAN UnitList KOSONG ******************/
void CreateEmptyUL (UnitList *L){
 FirstUL(*L) = Nil;
};
/* I.S. L sembarang             */
/* F.S. Terbentuk UnitList kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/

// Terbentuk address yang beratribut King
address CreateKing(){
    address P = (address) malloc(1* sizeof(ElmtUnitList));

	if (P!=Nil){
		initKing(&UnitInfo(P));
		NextUL(P) = Nil;
	    return P;
	 }
	 else {
	    return P;
	  }
}

// Terbentuk address yang beratribut Archer
address CreateArcher(){
    address U = (address) malloc(1* sizeof(ElmtUnitList));

	if (U!=Nil){
		initArcher(&UnitInfo(U));
		NextUL(U) = Nil;
	    return U;
	 }
	 else {
	    return U;
	  }
}

// Terbentuk address yang beratribut Mage
address CreateMage(){
    address U = (address) malloc(1* sizeof(ElmtUnitList));
	if (U!=Nil){
		initMage(&UnitInfo(U));
		NextUL(U) = Nil;
		return U;
	 }
	 else {
		return U;
	  }
	return U;
}

// Terbentuk address yang beratribut Swordsman
address CreateSwordsman(){
    address U = (address) malloc(1* sizeof(ElmtUnitList));
    initSwordsman(&UnitInfo(U));
	if (U!=Nil){
		initSwordsman(&UnitInfo(U));
		NextUL(U) = Nil;
	    return U;
	 }
	 else {
	    return U;
	  }
    return U;
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka UnitInfo(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiUL (address P){
  free(P);
};
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
void AddKing(UnitList *L){
  address PIterate;
  address PAdd;

  PAdd = CreateKing();

  PIterate = FirstUL(*L);

	if (PAdd!=Nil){
	  if (PIterate!=Nil){
	    while (NextUL(PIterate)!=FirstUL(*L)) {
	      PIterate = NextUL(PIterate);
	    }
	    NextUL(PAdd) = FirstUL(*L);
	    NextUL(PIterate) = PAdd;
	  }
	  else {
	    FirstUL(*L) = PAdd;
	    NextUL(PAdd) = FirstUL(*L);
	  }
	}
};

// Menambah Archer ke belakang list,
// [King,Archer] -> [King,Archer,Archer]
void AddArcher (UnitList *L){
  address PIterate;
  address PAdd;

  PAdd = CreateArcher();

  PIterate = FirstUL(*L);
	if (PAdd!=Nil){
	  if (PIterate!=Nil){
	    while (NextUL(PIterate)!=FirstUL(*L)) {
	      PIterate = NextUL(PIterate);
	    }
	    NextUL(PAdd) = FirstUL(*L);
	    NextUL(PIterate) = PAdd;
	  }
	  else {
	    FirstUL(*L) = PAdd;
	    NextUL(PAdd) = FirstUL(*L);
	  }
	}
};

// Menambah Swordsman ke belakang list,
// [King,Archer] -> [King,Archer,Swordsman]
void AddSwordsman (UnitList *L){
  address PIterate;
  address PAdd;

  PAdd = CreateSwordsman();

  PIterate = FirstUL(*L);

  if (PAdd!=Nil){
    if (PIterate!=Nil){
      while (NextUL(PIterate)!=FirstUL(*L)) {
        PIterate = NextUL(PIterate);
      }
      NextUL(PAdd) = FirstUL(*L);
      NextUL(PIterate) = PAdd;
    }
    else {
      FirstUL(*L) = PAdd;
      NextUL(PAdd) =FirstUL(*L);
    }
  }
};

// Menambah Mage ke belakang list,
// [King,Archer] -> [King,Archer,Mage]
void AddMage (UnitList *L){
  address PIterate;
  address PAdd;

  PAdd = CreateMage();

  PIterate = FirstUL(*L);

  if (PAdd!=Nil){
    if (PIterate!=Nil){
      while (NextUL(PIterate)!=FirstUL(*L)) {
        PIterate = NextUL(PIterate);
      }
      NextUL(PAdd) = FirstUL(*L);
      NextUL(PIterate) = PAdd;
    }
    else {
      FirstUL(*L) = PAdd;
      NextUL(PAdd) =FirstUL(*L);
    }
  }
};
/* I.S. UnitList L tidak kosong  */
/* F.S. Elemen pertama UnitList dihapus: nilai UnitInfo disimpan pada X */
/*      dan alamat elemen pertama di-DealokasiUL */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DeleteUnit(UnitList *L, address P){
  address PIterate;
  address PRec;

  PIterate = FirstUL(*L);
  PRec = Nil;

  if (PIterate==P){
    if (NextUL(PIterate) == FirstUL(*L)){
      FirstUL(*L) = Nil;
    }
    else {
      while (NextUL(PIterate)!=FirstUL(*L)) {
        PIterate = NextUL(PIterate);
      }
      DealokasiUL(FirstUL(*L));
      FirstUL(*L) = NextUL(FirstUL(*L));
      NextUL(PIterate) = FirstUL(*L);
    }
  }
  else{
    PRec = PIterate;
    PIterate = NextUL(PIterate);

    while ( (PIterate!=FirstUL(*L)) && (PIterate!=P)) {
      PRec = PIterate;
      PIterate = NextUL(PIterate);
    }

    if (PIterate!=FirstUL(*L)){
      NextUL(PRec) = NextUL(NextUL(PRec));
      DealokasiUL(PIterate);
    }
  }

};
int countUnit(UnitList L){
  address P = FirstUL(L);
  int count=0;
  if (!IsEmptyUL(L)){
    count++;
    P = NextUL(P);
    while (P!=FirstUL(L)) {
      count++;
      P = NextUL(P);
    }
  }
  return count;

};

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
void PrintULInfo (UnitList L){
  address PIterate;
  PIterate = FirstUL(L);

  printf("[");
    if (!IsEmptyUL(L)){
      printf("%d",UnitInfo(PIterate).type);
      if (NextUL(PIterate)!=FirstUL(L)){
        printf(",");
      }
      PIterate = NextUL(PIterate);

      while (PIterate != FirstUL(L)) {
        printf("%d",UnitInfo(PIterate).type);
        if (NextUL(PIterate)!=FirstUL(L)){
          printf(",");
        }
        PIterate = NextUL(PIterate);
      }
    }

  printf("]");
};

void resetUMovementPoint(address U){
  if (UnitInfo(U).type == KING_TYPE){
    UnitInfo(U).movementPoint = KING_MOVEMENT_POINT;
  }
  else if (UnitInfo(U).type == ARCHER_TYPE){
    UnitInfo(U).movementPoint = ARCHER_MOVEMENT_POINT;
  }
  else if (UnitInfo(U).type == SWORDSMAN_TYPE){
    UnitInfo(U).movementPoint = SWORDSMAN_MOVEMENT_POINT;
  }
  else if (UnitInfo(U).type == MAGE_TYPE){
    UnitInfo(U).movementPoint = MAGE_MOVEMENT_POINT;
  }

  UnitInfo(U).hasAttacked = false;
}

void resetUnitState (UnitList L){
  address U = FirstUL(L);

  if (!IsEmptyUL(L)){
    resetUMovementPoint(U);
    U = NextUL(U);
    while (U!= FirstUL(L)) {
      resetUMovementPoint(U);
      U = NextUL(U);
    }
  }

};
/* I.S. UnitList mungkin kosong */
/* F.S. Jika UnitList tidak kosong, iai UnitList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika UnitList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
