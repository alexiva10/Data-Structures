#include <stdio.h>
#include <mm_malloc.h>
#include <string.h>
typedef struct Carte Carte;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Nod Nod;
typedef struct LD LD;

enum gen {Poezie = 1, Economie = 2, Psihologie = 3, romanPolitist = 4, SF = 5, Istorie = 6};

struct Carte {
    int id;
    char* nume; // numele cartii
    char* autor;
    enum gen gen; // genul cartii
    int nrPagini;
    float notaCritic;
    long anAparitie;
    int nrRecenzii;
    int* noteSite;
};

struct NodPrincipal {
    Carte info;
    NodPrincipal* next;
    NodSecundar* vecin;
};

struct NodSecundar {
    NodPrincipal* info;
    NodSecundar* next;
};

struct Nod {
    int info;
    Nod* next;
    Nod* prev;
};

struct LD {
    Nod* prim;
    Nod* ultim;
};

Carte initCarte(int id, char* nume,char* autor, enum gen gen, int nrPagini, float notaCritic, long anAparitie, int nrRecenzii, int* notaSite) {
    Carte carte;
    carte.id = id;
    carte.gen = gen;
    carte.nrPagini = nrPagini;
    carte.notaCritic = notaCritic;
    carte.anAparitie = anAparitie;
    carte.nume = (char*)malloc(sizeof(char)*(strlen(nume)+1));
    strcpy(carte.nume, nume);
    carte.autor = (char*)malloc(sizeof(char)*(strlen(autor)+1));
    strcpy(carte.autor, autor);
    carte.nrRecenzii = nrRecenzii;
    carte.noteSite = (int*)malloc(sizeof(int)*nrRecenzii);
    for(int i=0;i<carte.nrRecenzii;i++) {
        carte.noteSite[i] = notaSite[i];
    }
    return carte;
}

void afisareCarte(Carte carte) {
    printf("%d. '%s' de %s are %d pagini, aparuta in %ld este o carte din categoria: %d \n    Nota criticului este %.2f, pe site are %d recenzii: ", carte.id, carte.nume, carte.autor, carte.nrPagini, carte.anAparitie,carte.gen, carte.notaCritic, carte.nrRecenzii);
    for(int i=0; i<carte.nrRecenzii-1; i++) {
        printf("%d, ", carte.noteSite[i]);
    }
    printf("%d", carte.noteSite[carte.nrRecenzii-1]);
    printf("\n");
}

void push(int id, LD* lista) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = id;
    nou->prev = NULL;
    nou->next = lista->prim;
    if(lista->prim) {
        lista->prim->prev = nou;
        lista->prim = nou;
    } else {
        lista->prim = nou;
        lista->ultim = nou;
    }
}

int pop(LD* lista) {
    int id = -1;
    if(lista->prim) {
        id = lista->prim->info;
        Nod* aux = lista->prim;
        lista->prim = lista->prim->next;
        if(lista->prim == NULL) {
            lista->ultim = NULL;
        }
        free(aux);
    }
    return id;
}

void put(int id, LD* lista) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = id;
    nou->prev = lista->ultim;
    nou->next = NULL;
    if(lista->ultim) {
        lista->ultim->next = nou;
        lista->ultim = nou;
    } else {
        lista->ultim = nou;
        lista->prim = nou;
    }
}

int nrNoduri(NodPrincipal* graf) {
    int k = 0;
    while(graf) {
        k++;
        graf = graf->next;
    }
    return k;
}

void InserareLaFinal(NodPrincipal** cap, Carte carte) {
    NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
    nou->info = carte;
    nou->next = NULL;
    nou->vecin = NULL;
    if(*cap) {
        NodPrincipal* aux = *cap;
        while(aux->next) {
            aux = aux->next;
        }
        aux->next = nou;
    } else {
        *cap = nou;
    }
}

void InserareLaFinalListaSecundara(NodSecundar** capSecund, NodPrincipal* informatie) {
    NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
    nou->info = informatie;
    nou->next = NULL;
    if(*capSecund) {
        NodSecundar* aux = *capSecund;
        while(aux->next) {
            aux = aux->next;
        }
        aux->next = nou;
    } else {
        *capSecund = nou;
    }
}

void afisareLista(NodPrincipal* cap) {
    while(cap) {
        printf("Nod: %d, carte: %s, de: %s\n", cap->info.id, cap->info.nume, cap->info.autor);
        NodSecundar* aux = cap->vecin;
        while(aux) {
            printf("Vecin: %d, carte: %s, de: %s\n", aux->info->info.id, aux->info->info.nume, aux->info->info.autor);
            aux = aux->next;
        }
        cap = cap->next;
        printf("\n");
    }
}

NodPrincipal* cautareDupaId(NodPrincipal* nod, int id) {
    while(nod!=NULL && nod->info.id != id) {
        nod = nod->next;
    }
    return nod;
}

void inserareVecini(NodPrincipal* nod, int id1, int id2) {
    NodPrincipal* nodCautat1 = cautareDupaId(nod, id1);
    NodPrincipal* nodCautat2 = cautareDupaId(nod, id2);
    if(nodCautat1 && nodCautat2) {
        InserareLaFinalListaSecundara(&nodCautat1->vecin, nodCautat2);
        InserareLaFinalListaSecundara(&nodCautat2->vecin, nodCautat1);
    }
}


void stergereVecinDupaId(NodSecundar** vec, int id) {
    while(*vec) {
        if((*vec)->next->info->info.id == id) {
            (*vec)->next = (*vec)->next->next;
        } else {
            *vec = (*vec)->next;
        }
    }
}

void stergereVeciniBun(NodSecundar** vec) {
    while(*vec) {
        NodSecundar* aux = *vec;
        *vec = (*vec)->next;
        free(aux);
    }
}

void stergereNodGrafDupaId(NodPrincipal** nod, int id) {
    while((*nod)) {
        if((*nod)->info.id == id) {
            stergereVeciniBun(&(*nod)->vecin);
            NodPrincipal* aux = *nod;
            *nod = (*nod)->next;
            free(aux);
        } else {
            stergereVecinDupaId(&(*nod)->vecin, id);
            *nod = (*nod)->next;
        }
    }
}

void stergereGraf(NodPrincipal** nod) {
    while(*nod) {
        stergereVeciniBun(&(*nod)->vecin);
        free((*nod)->info.autor);
        free((*nod)->info.noteSite);
        free((*nod)->info.nume);
        NodPrincipal* aux = *nod;
        *nod = (*nod)->next;
        free(aux);
    }
    printf("A dezalocat");
}

int main()
{
    NodPrincipal* cap = NULL;
    int v[] = {3,4,5,6};
    int v1[] = {7,8,6,7,9,6};
    int v3[] = {8, 10};
    InserareLaFinal(&cap, initCarte(1,"De la 0 la 1", "Peter Thiel", 2, 192, 8.6, 2013, 4, v));
    InserareLaFinal(&cap, initCarte(2,"Sapiens", "Harrari", 6, 345, 8.8, 2011, 6, v1));
    InserareLaFinal(&cap, initCarte(3,"Cum merge lumea", "Chomsky", 2, 410, 9.1, 2000, 2, v3));
    InserareLaFinal(&cap, initCarte(4,"Why we sleep", "Matthew Walker", 3, 278, 8.1, 2015, 4, v1));
    InserareLaFinal(&cap, initCarte(5,"Dune", "Frank Herbert", 5, 501, 9.3, 1965, 2, v3));
    inserareVecini(cap, 1, 3);
    inserareVecini(cap, 1, 4);
    inserareVecini(cap, 1, 5);
    inserareVecini(cap, 2, 5);
    afisareLista(cap);
    printf("-------\n");
    stergereGraf(&cap);
    // stergereNodGrafDupaId(&cap, 5);
    afisareLista(cap);
    return 0;
}
