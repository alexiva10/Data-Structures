#include<stdio.h>
#include<mm_malloc.h>
#include<string.h>
typedef struct Minge Minge;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Minge {
    char* brand;
    int pret;
};

struct Nod {
    Nod* next;
    Minge info;
};

struct HashTable {
    Nod** vector;
    int nrElemente;
};

Minge initMinge(char* brand, int pret) {
    Minge minge;
    minge.pret = pret;
    minge.brand = (char*)malloc(sizeof(char)*strlen(brand)+1);
    strcpy(minge.brand, brand);
    return minge;
}

void afisareMinge(Minge minge) {
    printf("Mingea de la %s costa %d lei", minge.brand, minge.pret);
}

HashTable initHashTable(int nrElemente) {
    HashTable ht;
    ht.nrElemente = nrElemente;
    ht.vector = (Nod**)malloc(sizeof(Nod*)*nrElemente);
    for(int i=0;i<nrElemente;i++)
    {
        ht.vector[i] = NULL;
    }
    return ht;
}

int functieHT(char* brand, int nrElemente) {
    return(strlen(brand)%nrElemente);
}

void inserareLaSfarsit(Nod** cap, Minge minge) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = minge;
    nou->next = NULL;
    if(*cap) {
        Nod* aux = *cap;
        while(aux) {
            aux = aux->next;
        }
        aux->next = nou;
    } else {
        (*cap) = nou;
    }
}

void inserareHT(Minge minge, HashTable ht) {
    if(ht.nrElemente>0)
    {
        int poz = functieHT(minge.brand, ht.nrElemente);
        if(poz>=0 && poz<ht.nrElemente)
            inserareLaSfarsit(&(ht.vector[poz]), minge);
    }
}

void afisareHT(HashTable ht) {
    for(int i=0;i<=ht.nrElemente;i++) {
        if(ht.vector[i]!=NULL) {
            Nod* aux = ht.vector[i];
            while(aux){
                printf("Pozitie %d:\n", i);
                afisareMinge(aux->info);
                aux = aux->next;
            }
        } else {
            printf("Pozitia %d este goala", i);
        }
    }
}

int main() 
{
    HashTable ht = initHashTable(4);
    Minge Adidas = initMinge("Adidas", 50);
    Minge Nike = initMinge("Nike", 60);
    Minge Puma = initMinge("Puma", 75);
    inserareHT(Adidas, ht);
    inserareHT(Nike, ht);
    inserareHT(Puma, ht);
    afisareHT(ht);
    return 0;

}
