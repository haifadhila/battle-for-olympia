/* File : stacklist.h */
#ifndef _MOVESTACK_H
#define _MOVESTACK_H

#include "boolean.h"
#include "./Point/point.h"
#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* Stack dengan representasi berkait dengan pointer */
typedef struct tElmtStack * MoveAddress;
typedef struct tElmtStack {
	Point Info;
	MoveAddress Next;
} ElmtStack;

/* Type stack dengan ciri TOP : */
typedef struct {
	MoveAddress TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Selektor */
#define Top(S) (S).TOP
#define InfoTop(S) (S).TOP->Info
#define NextMove(P) (P)->Next
#define MoveInfo(P) (P)->Info

/* Prototype manajemen memori */
void AlokasiMove (MoveAddress *P, Point X);

void DealokasiMove (MoveAddress P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsEmptyStack (Stack S);
/* Mengirim true jika Stack kosong: TOP(S) = Nil */

void CreateStack (Stack * S);
/* I.S. sembarang */
/* F.S. Membuat sebuah stack S yang kosong */

void PushMove (Stack * S, Point Po);
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */

void PopMove (Stack * S, Point * Po);
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

#endif
