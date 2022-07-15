#include <stdio.h>
#include <mm_malloc.h>
#include <string.h>
typedef struct Fruct Fruct;
typedef struct Nod Nod;

struct Fruct {
    char* nume;
    float pret;
};

struct Nod {
    Nod* next;
    Fruct info;
};

Fruct initFruct(char* nume, float pret) {
    Fruct fruct;
    fruct.pret = pret;
    fruct.nume = (char*)malloc(sizeof(char)*strlen(nume)+1);
    strcpy(fruct.nume, nume);
    return fruct;
}

void afisareFruct(Fruct fruct) {
    printf("%s - cu pret %.2f per bucata\n", fruct.nume, fruct.pret);
}
 
void inserareLaInceput(Nod** cap, Fruct fruct) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = fruct;
    nou->next = *cap;
    *cap = nou;
}

void inserareLaFinal(Nod** cap, Fruct fruct) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = fruct;
    Nod* aux = *cap;
    while((aux)->next) {
        aux = (aux)->next;
    }
    (aux)->next = nou;
    nou->next = NULL;
}

void afisareLista(Nod* cap) {
    while(cap) {
        afisareFruct(cap->info);
        cap = cap->next;
    }
    printf("------");
}

void dezalocareMemorie(Nod** cap) {
    while(*cap)
    {
        free((*cap)->info.nume);
        Nod* aux = *cap;
        (*cap) = (*cap)->next;
        free(aux);
    }
    printf("\nA dezalocat\n");
}

int main()
{
    Nod* cap = NULL;
    inserareLaInceput(&cap, initFruct("Mar", 1.23));
    inserareLaInceput(&cap, initFruct("Para", 0.93));
    inserareLaInceput(&cap, initFruct("Banana", 1.92));
    inserareLaInceput(&cap, initFruct("Gutuie", 1.05));
    inserareLaFinal(&cap, initFruct("Strugure", 0.04));
    inserareLaFinal(&cap, initFruct("Ananas", 4.05));
    afisareLista(cap);
    dezalocareMemorie(&cap);
    afisareLista(cap);

    return 0;
}