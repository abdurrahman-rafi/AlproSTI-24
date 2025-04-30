#include <stdio.h>
#include "hashmap.h"

void CreateEmpty(HashMap *h){
    h->Count = Nil;
    for(int i = 0; i<MaxEl; i++){
        h->Elements[i].key = Undefined;
        h->Elements[i].value = Undefined;
    }
}

address Hash(keytype K){
    address al;
    al = K % MaxEl;
    return al;
}

int Value(HashMap h, keytype key){
    return h.Elements[Hash(key)].value;
}

void Insert(HashMap *h, keytype key, valuetype value){
    address i = Hash(key);
    //Collision
    while (h->Elements[i].key != Undefined && h->Elements[i].key != key){
        i = (i+1) % MaxEl;
    }

    if (h->Elements[i].key == Undefined) {
        h->Count++;
    }

    h->Elements[i].key = key;
    h->Elements[i].value = value;
}

void printHashMap(HashMap h){
    for(int i = 0; i<MaxEl; i++){
        printf("%d:\n", i);
        printf("  Key: %d\n", h.Elements[i].key);
        printf("  Value: %d\n", h.Elements[i].value);
    }
}