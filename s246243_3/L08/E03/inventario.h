#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED


typedef struct {

int hp;
int mp;
int atk;
int def;
int mag;
int spr;

}Stat_pers;

typedef struct{

char Nome[51];
char Tipologia[51];
Stat_pers statOgg;

}Oggetti;

typedef struct {

Oggetti *vettOgg;
int nOgg;
int maxinv;

}tabInv_t;

void inizializzazione_oggetti(tabInv_t *tab);
Oggetti ricerca_oggetto(tabInv_t *tab);
void stampa_oggetto(tabInv_t *tab);
Oggetti* equipaggiamento_oggetto(tabInv_t *tab);
void liberatab(tabInv_t *tab);



#endif // INVENTARIO_H_INCLUDED
