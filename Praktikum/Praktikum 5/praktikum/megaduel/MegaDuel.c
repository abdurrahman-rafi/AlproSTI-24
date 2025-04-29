#include <stdio.h>
#include "MegaNimons.h"


void runMegaDuel(LabTrack *L){
    while(L->nEff > 1){
        printf("\n== DUEL ROUND ==\n");
        duelOnce(L->contents[0], L->contents[1]);

        MegaNimons winner = resolveDuel(L->contents[0], L->contents[1]);
        if(winner.id == L->contents[0].id){
            MegaNimons temp;
            deleteAt(L, indexOf(*L, L->contents[1].id), &temp);
        }else{
            MegaNimons temp;
            deleteAt(L, indexOf(*L, L->contents[0].id), &temp);
        }
    }

    printf("\n== The Champion: %s ==\n", L->contents[0].name);
}