#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED
#include "equipArray.h"


typedef struct
{
int hp;
int mp;
int atk;
int def;
int mag;
int spr;

}stat_t;

typedef struct
{
char codice[7];
char nome[51];
char classe[51];
tabeq *equip;
stat_t stat;

}pg_t;


#endif // PG_H_INCLUDED
