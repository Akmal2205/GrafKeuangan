#ifndef grafKeuangan_H
#define grafKeuangan_H

#include <stdlib.h>
#include "boolean.h"
#include "listlinier.c"

typedef struct np *AddressNode;
typedef struct prio
{
    List bobot;
    char priorityTag[100];
} PrioStruct;

typedef struct np
{
    PrioStruct prio;
    AddressNode next;
} NodePriority;

typedef AddressNode Graf;
#define FIRSTNODE(G) (G)

AddressNode newPriorityNode(PrioStruct p);
/*Mengembalikan alamat dari alokasi struktur Graph*/

void createGraph(Graf *G);
/*Membuat Graf kosong, Graf kosong ditandai dengan elemen pertamanya kosong/bernilai NULL*/

boolean isGraphEmpty(Graf G);
/*Mengembalikan true jika Graf Kosong*/

void addPriorityNode(Graf *G);
/*Menambahkan alokasi PriorityNode baru pada Graf*/

void printPriorityTag(Graf G, int Index);
/*Menambahkan alokasi PriorityNode baru pada Graf*/

void addDecision(Graf *G, int index);
/*Menambahkan decision pada isi struktur prioritas, basically insertLast buat struktur List bobot*/

int getPengeluaranMin(Graf G);
/*Mengembalikan nilai bobot minimum dari list bobot*/

void printMinDecisions(Graf G);
/*Menampilkan keputusan-keputusan yang harus diambil agar meminimalisir pengeluaran*/

#endif