#ifndef EQUIPARRAY_H_INCLUDED
#define EQUIPARRAY_H_INCLUDED
#include "invArray.h"

typedef struct tabEquip_t *tabeq;


void equipaggia(int indice,tabeq t);
void cancellazione(char *nome,tabeq t,tabinv t1);

void stampa_stat_equip(int indice,tabeq t,tabinv t2);


#endif // EQUIPARRAY_H_INCLUDED
