#include<stdio.h>
#include<mm_malloc.h>
#include<string.h>
#include<stdlib.h>
typedef struct Carte Carte;
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

struct Nod {
    Carte info;
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

Carte citireCarte(FILE* streamFisier) {
    Carte carte;
    if(streamFisier != NULL) {
        //1,"De la 0 la 1", "Peter Thiel", 2, 192, 8.6, 2013, 4, v
        char buffer[100];
        fgets(buffer, 3, streamFisier);
        carte.id = atoi(buffer);
        fgets(buffer, 19, streamFisier);
        char* sir = strtok(buffer, "\n");
        carte.nume = (char*)malloc(sizeof(char)*(strlen(sir)+1));
        strcpy(carte.nume, sir);
        fgets(buffer, 14, streamFisier);
        carte.autor = (char*)malloc(sizeof(char)*(strlen(sir)+1));
        strcpy(carte.autor, sir);
        fgets(buffer, 3, streamFisier);
        carte.gen = atoi(buffer);
        fgets(buffer, 5, streamFisier);
        carte.nrPagini = atoi(buffer);
        fgets(buffer, 6, streamFisier);
        carte.notaCritic = atof(buffer);
        fgets(buffer, 6, streamFisier);
        carte.anAparitie = atol(buffer);
        fgets(buffer, 3, streamFisier);
        carte.nrRecenzii = atoi(buffer);
    }
    return carte;
}

/*Carte* citireVectorCarti(FILE* streamfisier, int* nrCarti) {
    if(streamfisier != NULL) {
        char buffer[10];
        fgets(buffer, 3, streamfisier);
        *nrCarti = atoi(buffer);
        Carte* vectorCarti = (Carte*)malloc(sizeof(Carte)*(*nrCarti));
        for(int i=0; i<(*nrCarti);i++)
            vectorCarti[i] = citireCarte(streamfisier);
        return vectorCarti;
    }
}*/

void afisareCarte(Carte carte) {
    printf("%d. '%s' de %s are %d pagini, aparuta in %ld este o carte din categoria: %d \n    Nota criticului este %.2f, pe site are %d recenzii: ", carte.id, carte.nume, carte.autor, carte.nrPagini, carte.anAparitie,carte.gen, carte.notaCritic, carte.nrRecenzii);
    for(int i=0; i<carte.nrRecenzii-1; i++) {
        printf("%d, ", carte.noteSite[i]);
    }
    printf("%d", carte.noteSite[carte.nrRecenzii-1]);
    printf("\n");
}

void inserareLaInceput(Carte c, LD* lista) { // este transmisa prin adresa (de aici o steluta) si nu mai e nevoie de prima deoarece retine adresa la nivel de lista
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = c; // copiem informatia utila
    nou->prev = NULL;
    nou->next = lista->prim;
    if(lista->prim) {
        lista->prim->prev = nou; // am facut legatura dubla - ca prim sa pointeze catre nodul nou (pe care il inseram primul)
        lista->prim = nou;
    } else { //nodul nou va fi si prim si ultim
        lista->prim = nou;
        lista->ultim = nou;
    }
}

void traversareLista(LD lista) {
    Nod* aux = lista.prim;
    while(aux!=NULL) {
        afisareCarte(aux->info);
        aux = aux->next;
    }
    printf("\n");
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

void cautamCaracter(LD lista, char* nume) {
    Nod* aux = lista.prim;
    while(aux && strcmp(aux->info.autor, nume)){
        aux = aux->next;
    }
    afisareCarte(aux->info);
}

void stergereNod(LD lista, char* nume) {
    Nod* aux = lista.prim;
    while(aux && strcmp(aux->info.autor, nume)){
        aux = aux->next;
    }
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
}



int main()
{
    LD lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    int v[] = {3,4,5,6};
    int v1[] = {7,8,6,7,9,6};
    int v3[] = {8, 10};
    inserareLaInceput(initCarte(1,"De la 0 la 1", "Peter Thiel", 2, 192, 8.6, 2013, 4, v), &lista);
    inserareLaInceput(initCarte(2,"Sapiens", "Harrari", 6, 345, 8.8, 2011, 6, v1), &lista);
    inserareLaInceput(initCarte(3,"Cum merge lumea", "Chomsky", 2, 410, 9.1, 2000, 2, v3), &lista);
    inserareLaInceput(initCarte(4,"Why we sleep", "Matthew Walker", 3, 278, 8.1, 2015, 4, v1), &lista);
    inserareLaInceput(initCarte(5,"Dune", "Frank Herbert", 5, 501, 9.3, 1965, 2, v3), &lista);
    traversareLista(lista);
    printf("\n");
    cautamCaracter(lista, "Chomsky");
    stergereNod(lista, "Chomsky");
    printf("\n");
    traversareLista(lista);
    FILE* f = fopen("carti.txt", "r");
    Carte cart1 = citireCarte(f);
    cart1.noteSite = v;
    afisareCarte(cart1);

    return 0;
}