#include <stdio.h>
#include "grafKeuangan.c"

int main()
{
    Graf G;
    createGraph(&G);
    addPriorityNode(&G);
    addPriorityNode(&G);
    addPriorityNode(&G);
    // addPriorityNode(&G);
    printf("Priority ");
    printPriorityTag(G, 0);
    addDecision(&G, 0);
    addDecision(&G, 0);
    addDecision(&G, 0);
    // printf("%d", getElmt(getGraph(G, 0)->prio.bobot, 0));
    // printf("%d", getElmt(getGraph(G, 0)->prio.bobot, 1));
    printf("Priority ");
    printPriorityTag(G, 1);
    addDecision(&G, 1);
    addDecision(&G, 1);
    addDecision(&G, 1);
    printf("Priority ");
    printPriorityTag(G, 2);
    addDecision(&G, 2);
    printMinDecisions(G);
}