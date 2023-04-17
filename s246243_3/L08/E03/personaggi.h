#ifndef PERSONAGGI_H_INCLUDED
#define PERSONAGGI_H_INCLUDED
#include "inventario.h"

typedef struct {

Oggetti* vetteq[8];
int inUso;

}tabEquip_t;

typedef struct{

char codice[7];
char nome[51];
char classe[51];
Stat_pers statistiche;
tabEquip_t equipaggiamento;

}PG;

typedef struct nodo_personaggio *link;
typedef struct nodo_personaggio{

link next;
PG perso;
}nodoPG;

typedef struct{

link headPG;
link TailPG;
int nPG;

}tabPG_t;

link listInsHead (link h, PG val);
link newNode(PG val, link next);
link Attr(link h);
link listDelKey(link h,char *codice);
void inizializzazione_personaggi(tabPG_t *tab);
void acquisire_personaggio(tabPG_t *tab);
void eliminazione_personaggio(tabPG_t *tab);
void aggiunta_personaggioequip(tabPG_t *tab,tabInv_t *tab2);
PG listSearch(link h,char*codice,Oggetti* A);
void rimuovereoggetto_apers(tabPG_t *tab);
PG listSearch2(link h,char*codice,char*nome);
void calcolo_stats(tabPG_t *tab);
PG listSearch3(link h,char*codice);
PG ricerca_personaggio(tabPG_t *tab);
PG ricerca(link h,char *codice);
void stampa_personaggio(tabPG_t *tab);
void liberapg(tabPG_t *tab);
#endif // PERSONAGGI_H_INCLUDED
