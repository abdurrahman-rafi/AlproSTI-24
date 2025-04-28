#include <stdio.h>
#include "keranjangpisang.h"

int main(){
    //Mock data
    KeranjangPisang Bananas;
    readKeranjang(&Bananas);
    printKeranjang(Bananas);
    
    printf("\nADD function\n");
    ElType val1, val2, val3;
    IdxType id;
    printf("First, insertat, lastinsert, insertat id: ");
    scanf("%d %d %d %d", &val1, &val2, &val3, &id);
    insertFirst(&Bananas, val1);
    insertAt(&Bananas, val2, id);
    insertLast(&Bananas,val3);
    printKeranjang(Bananas);

    printf("\nDELETE FUNCTION\n");
    ElType del1, del2, del3;
    printf("Deleting previously added nums\n");
    deleteAt(&Bananas, &del2, id);
    deleteFirst(&Bananas,&del1);
    deleteLast(&Bananas, &del3);
    printf("Deleted elements are: %d %d %d\n", del1, del2, del3);
    printKeranjang(Bananas);

}