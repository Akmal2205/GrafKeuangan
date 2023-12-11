#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listlinier.h"

Address newNode(ElType val)
{
    Address p = (Address)malloc(sizeof(Node));

    if (p != NULL)
    {
        p->info = val;
        p->next = NULL;
        printf("Input decision tag: ");
        scanf("%s", p->decisionTag);
    }
    return p;
}

/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

typedef Address List;

#define IDX_UNDEF (-1)
#define FIRST(l) (l)

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong */
{
    return (FIRST(l) == NULL);
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    int i = 0;
    Address p = l;
    while (i < idx && l != NULL)
    {
        p = p->next;
        i++;
    }
    return p->info;
}

char *getDecisionTag(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    int i = 0;
    Address p = l;
    while (i < idx && l != NULL)
    {
        p = p->next;
        i++;
    }
    return p->decisionTag;
}

void setElmt(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
    int i = 0;
    Address p = *l;
    while (i < idx)
    {
        i++;
        p = p->next;
    }
    p->info = val;
}

int indexOf(List l, ElType val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
    Address p = l;
    boolean found = false;
    int idx = 0;
    while (p != NULL && found == false)
    {
        if (p->info == val)
        {
            found = true;
        }
        else
        {
            idx++;
            p = p->next;
        }
    }
    if (found)
    {
        return idx;
    }
    else
    {
        return IDX_UNDEF;
    }
}

int getMin(List l)
/*I.S. l berisi elemen unik*/
/*Mengembalikan nilai minimum dari sebuah list*/
{
    Address lr = l;
    int min = getElmt(lr, 0);
    while (lr != NULL)
    {
        if (lr->info <= min)
        {
            min = lr->info;
        }
        lr = lr->next;
    }
    return min;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p = newNode(val);
    if (p != NULL)
    {
        p->next = *l;
        *l = p;
    }
}

void insertLast(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (isEmpty(*l))
    {
        insertFirst(l, val);
    }
    else
    {
        Address p = newNode(val);
        if (p != NULL)
        {
            Address last = *l;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = p;
        }
    }
}

void insertAt(List *l, ElType val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (idx == 0)
    {
        insertFirst(l, val);
    }
    else
    {
        Address p = newNode(val);
        Address loc = *l;
        if (p != NULL)
        {
            int i = 0;
            while (i < idx - 1)
            {
                loc = loc->next;
                i++;
            }
            p->next = loc->next;
            loc->next = p;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p = *l;
    *val = INFO(p);
    *l = NEXT(p);
    free(p);
}
void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
    if (FIRST(*l)->next == NULL)
    {
        deleteFirst(l, val);
    }
    else
    {
        Address p = *l;
        while (NEXT(NEXT(p)) != NULL)
        {
            p = p->next;
        }
        *val = NEXT(p)->info;
        free(p->next);
        p->next = NULL;
    }
}

void deleteAt(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if (idx == 0)
    {
        deleteFirst(l, val);
    }
    else
    {
        int i = 0;
        Address loc = *l, p;
        while (i < idx - 1)
        {
            i++;
            loc = loc->next;
        }
        p = loc->next;
        *val = p->info;
        loc->next = p->next;
        free(p);
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    if (!isEmpty(l))
    {
        Address p = l;
        printf("[");
        printf("%d", FIRST(p)->info);
        p = p->next;
        while (p != NULL)
        {
            printf(",%d", p->info);
            p = p->next;
        }
        printf("]");
    }
    else
    {
        printf("[]");
    }
}

int length(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int length = 0;
    Address p = l;
    while (p != NULL)
    {
        length++;
        p = p->next;
    }
    return length;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2)
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    if (isEmpty(l1) && isEmpty(l2))
    {
        List l3;
        CreateList(&l3);
        return l3;
    }
    else
    {
        List l3;
        CreateList(&l3);
        Address p1 = l1, p2 = l2;
        while (p1 != NULL)
        {
            insertLast(&l3, p1->info);
            p1 = p1->next;
        }
        while (p2 != NULL)
        {
            insertLast(&l3, p2->info);
            p2 = p2->next;
        }
        return l3;
    }
}