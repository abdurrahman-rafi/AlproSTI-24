#include <stdio.h>
#include "MegaDuel.h"

void runMegaDuel(LabTrack *L){
    // MegaNimons left = L->contents[0];
    // MegaNimons right = L->contents[1];
    // int indright = 1;
    // printf("\n");
    // while(length(*L) != 1){
    //    printf("== DUEL ROUND ==\n");
    //    printf("Duel: %s (%.1d) vs %s (%.1d)\n", left.name, left.powerLevel, right.name, right.powerLevel);
    //    MegaNimons winner = (left.powerLevel > right.powerLevel) ? left : right;
    //    MegaNimons loser = (left.powerLevel > right.powerLevel) ? right : left;

    //    printf("Winner: %s\n\n",winner.powerLevel);
    // }
    
    while(length(*L) != 1){
        printf("\n");
        MegaNimons left = L->contents[0];
        MegaNimons right = L->contents[1];
        printf("== DUEL ROUND ==\n");
        duelOnce(left, right);
        left = resolveDuel(left,right);
        L->contents[0] = left;
        printf("\n");

        MegaNimons temp;
        deleteAt(L, 1, &temp);
        
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