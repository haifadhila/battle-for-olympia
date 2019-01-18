/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "boolean.h"
#include "mesinkar.h"
#include "mesinlogo.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
    {
        /* Algoritma */
        while ((CC == BLANK) && (CC != MARK)) {
            ADV();
        } /* CC != BLANK or CC = MARK */
}

void STARTKATA()
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
    {
         /* Algoritma*/
        START();
        IgnoreBlank();
        if (CC == MARK)
             EndKata = true;
        else /* CC != MARK */ {
            EndKata = false;
            SalinKata();
        }
    }

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
   {
    /* Algoritma*/
    IgnoreBlank();
    if (CC == MARK)
        EndKata = true;
    else /* CC != MARK */
        SalinKata();
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    /* Kamus Lokal */
    int i = 1; /* inisialisasi */

    /* Algoritma*/
    for (;;) {
        CKata.TabKata[i] = CC;
        ADV();
        if ((CC == MARK) || (CC == BLANK) || (i>=NMax))
            break;
        else
            i++;
    } /* CC = MARK or CC = BLANK */
    IgnoreBlank();
 CKata.Length = i;

}

void TulisKata (Kata K)
{
/* Prosedur untuk menuliskan kata ke layar */
  int i;
  for (i=1; i<=K.Length; i++) {
    printf("%c",K.TabKata[i]);
  }
}


boolean IsKataSama (Kata K1, Kata K2)
// Mengecek apakah Kata K1 dan K2 sama (length dan semua hurufnya sama)
{
  boolean sama=true;
  int i=1;

    //algoritma
    if (K1.Length== K2.Length) {
      while ((i<=K1.Length) && sama) {
        if (K1.TabKata[i]==K2.TabKata[i]) {
          i++;
        } else
          sama=false;
      }
      return sama;
    }
    else
        return false;
}

void TulisLogo() {
// Memanggil semua prosedur untuk membaca file logo lalu menuliskannya ke layar.
  Kata Tikom;
  int i;

  STARTKATA();
  if(!EndKata) {
    while (!EndKata) {
      IgnoreBlank();
      TulisKata(CKata);
      ADVKATA();
    }
    printf("\n");
    printf("\n");
  }
}
