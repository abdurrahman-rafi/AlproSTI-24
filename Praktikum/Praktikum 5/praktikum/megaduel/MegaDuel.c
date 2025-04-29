#include <stdio.h>
#include "MegaDuel.h"

void runMegaDuel(LabTrack *L){
    while(L->nEff > 1){
        print("\n== DUEL ROUND ==\n");
        duelOnce(L->contents[0], L->contents[1]);

        MegaNimons winner = resolveDuel(L->contents[0], L->contents[1]);
        if(winner.id == L->contents[0].id){
            MegaNimons temp;
            deleteAt(&L, indexOf(*L, L->contents[1].id), &temp);
        }
    }

    printf("\n== The Champion: %s ==\n", L->contents[0]);
}

/* Output:
 *   <endline>
 *   == DUEL ROUND ==
 *   Duel: Kevzilla (800.0) vs Melatron (780.0)
 *   Winner: Kevzilla
 *   <endline>
 *   == DUEL ROUND ==
 *   Duel: Kevzilla (800.0) vs Bobzilla (850.0)
 *   Winner: Bobzilla
 *   <endline>
 *   == The Champion: Bobzilla ==
 */