#include<stdio.h>
#include<mm_malloc.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct Lista Lista;

struct Carte {
    char* nume;
    int pg;
};

struct Nod {
    Carte info;
    Nod* prev;
    Nod* next;
};

struct Lista {
    Nod* prim;
    Nod* ultim;
};

Carte initCarte(char* nume, int pg) {
    Carte carte;
    carte.pg = pg;
    carte.nume = (char*)malloc(sizeof(char)*(strlen(nume)+1));
    strcpy(carte.nume, nume);
    return carte;
}

void afisCarte(Carte carte) {
    printf("Cartea '%s' are %d pagini\n", carte.nume, carte.pg);
}

void inserareLaInceput(Lista* lista, Carte carte) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = carte;
    nou->next = lista->prim;
    nou->prev = NULL;
    if(lista->prim) {
        lista->prim->prev = nou;
        lista->prim = nou;
    } else {
        lista->prim = nou;
        lista->ultim = nou;
    }
}

void inserareLaFinal(Lista* lista, Carte carte) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = carte;
    nou->next = NULL;
    nou->prev = lista->ultim;
    if(lista->ultim) {
        lista->ultim->next = nou;
        lista->ultim = nou;
    } else {
        lista->ultim = nou;
        lista->prim = nou;
    }
}

void afisareLista(Lista lista) {
    Nod* cap = lista.prim;
    while(cap) {
        afisCarte((cap)->info);
        cap = (cap)->next;
    }
    printf("----\n");
}

void dezalocareLista(Nod** prim, Nod** ultim) {
    if(*ultim == NULL)
        return;
    Nod* aux = *prim;
    while(aux->next!=NULL) {
        aux = aux->next;
        free(aux->prev);
    }
    free(aux);
    *prim = NULL;
    *ultim = NULL;

    printf("A dezalocat\n");
}

int main()
{   
    Lista lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    inserareLaInceput(&lista, initCarte("Inteligenta emotionala", 350));
    inserareLaInceput(&lista, initCarte("Avutia natiunilor", 295));
    inserareLaInceput(&lista, initCarte("Bambi", 130));
    afisareLista(lista);
    dezalocareLista(&lista.prim, &lista.ultim);

    Lista lista2;
    lista2.prim = NULL;
    lista2.ultim = NULL;
    inserareLaFinal(&lista2, initCarte("Fram, ursul polar", 350));
    inserareLaFinal(&lista2, initCarte("Harry Potter", 295));
    inserareLaFinal(&lista2, initCarte("Narnia", 130));
    afisareLista(lista2);
    dezalocareLista(&lista2.prim, &lista2.ultim);

    return 0;
}