#ifndef INV_H_INCLUDED
#define INV_H_INCLUDED
#include "pg.h"



typedef struct
{
char nome[51];
char tipologia[51];
stat_t statistiche;

}inv_t;

void salvainv(inv_t *vett,int dim);

#endif // INV_H_INCLUDED
