#include<stdio.h>
#include<mm_malloc.h>
#include<string.h>
typedef struct Carte Carte;
typedef struct Nod Nod;

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

struct Nod {
    Carte info;
    Nod* dr;
    Nod* st;
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

void inserare(Nod** rad, Carte carte) {
    if((*rad) == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = carte;
        nou->dr = nou->st = NULL;
        *rad = nou;
    } else {
        if(carte.id > (*rad)->info.id) {
            inserare(&(*rad)->dr, carte);
        } else {
            inserare(&(*rad)->st, carte);
        }
    }
}

void stergereNodNeterminal(Nod** rad, Nod** nod) { // cautam nodul cel mai din dreapta din subarborele stang
    if((*rad)->dr) {
        stergereNodNeterminal(&(*rad)->dr, &(*nod));
    } else {
        (*nod)->info = (*rad)->info;
        Nod* aux = *rad;
        (*rad) = (*rad)->st;
        free(aux);
    }
}

void stergereNod(Nod** rad, int id) {
    if(*rad) {
        if((*rad)->info.id == id) {
            if((*rad)->st == NULL && (*rad)->dr == NULL) {
                free((*rad));
                *rad = NULL;
            } else {
                if((*rad)->dr == NULL) {
                    Nod* aux = *rad;
                    (*rad) = (*rad)->st;
                    free(aux);
                } else {
                    if((*rad)->st == NULL) {
                    Nod* aux = *rad;
                    (*rad) = (*rad)->dr;
                    free(aux);
                    } else stergereNodNeterminal(&(*rad)->st, &(*rad));
                }
            }
        } else {
            if((*rad)->info.id > id)  {
                stergereNod(&(*rad)->st, id);
            } else stergereNod(&(*rad)->dr, id);
        }
    } else printf("Nu exista nod cu id-ul selectat");
}

void afisarePreordine(Nod* rad) { // RSD
    if(rad) {
        afisareCarte(rad->info);
        afisarePreordine(rad->st);
        afisarePreordine(rad->dr);
    }
}


int main ()
{
    int v[] = {3,4,5,6};
    int v1[] = {7,8,6,7,9,6};
    int v3[] = {8, 10};
    Nod* rad = NULL;
    /* afisareCarte(initCarte(1,"De la 0 la 1", "Peter Thiel", 2, 192, 8.6, 2013, 4, v));
    afisareCarte(initCarte(2,"Sapiens", "Harrari", 6, 345, 8.8, 2011, 6, v1));
    afisareCarte(initCarte(3,"Cum merge lumea", "Chomsky", 2, 410, 9.1, 2000, 2, v3));
    afisareCarte(initCarte(4,"Why we sleep", "Matthew Walker", 3, 278, 8.1, 2015, 4, v1));
    afisareCarte(initCarte(5,"Dune", "Frank Herbert", 5, 501, 9.3, 1965, 2, v3)); */
    inserare(&rad, initCarte(1,"De la 0 la 1", "Peter Thiel", 2, 192, 8.6, 2013, 4, v));
    inserare(&rad, initCarte(2,"Sapiens", "Harrari", 6, 345, 8.8, 2011, 6, v1));
    inserare(&rad, initCarte(3,"Cum merge lumea", "Chomsky", 2, 410, 9.1, 2000, 2, v3));
    inserare(&rad, initCarte(4,"Why we sleep", "Matthew Walker", 3, 278, 8.1, 2015, 4, v1));
    inserare(&rad, initCarte(5,"Dune", "Frank Herbert", 5, 501, 9.3, 1965, 2, v3));
    afisarePreordine(rad);
    printf("\n");
    stergereNod(&rad, 4);
    printf("\n");
    afisarePreordine(rad);
}
