#include <stdio.h>
#include <string.h>
#include "grafKeuangan.h"

AddressNode newPriorityNode(PrioStruct p)
/*Mengembalikan alamat dari alokasi struktur Graph*/
{
    AddressNode np = (AddressNode)malloc(sizeof(NodePriority));
    if (np != NULL)
    {
        np->prio = p;
        np->next = NULL;
    }
    return np;
}

void createGraph(Graf *G)
/*Membuat Graf kosong, Graf kosong ditandai dengan elemen pertamanya kosong/bernilai NULL*/
{
    FIRSTNODE(*G) = NULL;
}

boolean isGraphEmpty(Graf G)
/*Mengembalikan true jika Graf Kosong*/
{
    return (FIRSTNODE(G) == NULL);
}

void addPriorityNode(Graf *G)
/*Menambahkan alokasi PriorityNode baru pada Graf*/
{
    if (isGraphEmpty(*G))
    {
        PrioStruct p;
        CreateList(&p.bobot);
        printf("Input priority tag : ");
        scanf("%s", p.priorityTag);
        AddressNode np = newPriorityNode(p);
        FIRSTNODE(*G) = np;
    }
    else
    {
        PrioStruct p;
        CreateList(&p.bobot);
        printf("Input priority tag : ");
        scanf("%s", p.priorityTag);
        AddressNode np = newPriorityNode(p);
        AddressNode gr = FIRSTNODE(*G);
        while (gr->next != NULL)
        {
            gr = gr->next;
        }
        gr->next = np;
    }
}

AddressNode getGraph(Graf G, int index)
{
    AddressNode g = G;
    int i = 0;
    while (g != NULL && i != index)
    {
        g = g->next;
    }
    return g;
}

void printPriorityTag(Graf G, int Index)
/*Menambahkan alokasi PriorityNode baru pada Graf*/
{
    AddressNode g = G;
    int i = 0;
    while (g != NULL && i != Index)
    {
        g = g->next;
        i++;
    }
    printf("%s\n", g->prio.priorityTag);
}

void addDecision(Graf *G, int index)
/*Menambahkan decision pada isi struktur prioritas, basically insertLast buat struktur List bobot*/
{
    AddressNode gr = FIRSTNODE(*G);
    int i = 0, val;
    while (gr != NULL && i != index)
    {
        gr = gr->next;
        i++;
    }
    if (i != index)
    {
        printf("Masukkan index yang valid!\n");
    }
    else
    {
        printf("Input bobot : ");
        scanf("%d", &val);
        insertLast(&gr->prio.bobot, val);
    }
}

int getPengeluaranMin(Graf G)
/*Mengembalikan pengeluaran minimum dari graf keuangan*/
{
    AddressNode g = G;
    int accu = 0, index = 0;
    while (g != NULL)
    {
        accu += getMin(g->prio.bobot);
        g = g->next;
    }
    return accu;
}

void printMinDecisions(Graf G)
/*Menampilkan keputusan-keputusan yang harus diambil agar meminimalisir pengeluaran*/
{
    AddressNode g = G;
    printf("Berikut adalah keputusan-keputusan yang perlu diambil untuk meminimalisasi pengeluaran Anda :\n");
    while (g != NULL)
    {
        printf("%s, ", getDecisionTag(g->prio.bobot, indexOf(g->prio.bobot, getMin(g->prio.bobot))));
        printf("harga : %d\n", getMin(g->prio.bobot));
        g = g->next;
    }
    printf("%d selamat mengirit~ :D", getPengeluaranMin(G));
}