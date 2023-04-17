#ifndef INVARRAY_H_INCLUDED
#define INVARRAY_H_INCLUDED
#include "inv.h"

typedef struct tabInv_t *tabinv;

void inizializzazione_oggetti(tabinv t);

int cerca_oggetto(char *nome,tabinv t);
inv_t ricerca_oggetto(tabinv t);
void stampa_oggetto(tabinv t);
void liberatutto(tabinv t);
int confronto(char *nome,int indice,tabinv t);
int trova_stat(int indice,tabinv t,int tipo_stat);
void stampa_stat_equip2(int indice1,tabinv t2);


#endif // INVARRAY_H_INCLUDED
