#ifndef PGLIST_H_INCLUDED
#define PGLIST_H_INCLUDED


typedef struct tabPG_t *tabPG;

typedef struct nodoPg_t *link;
typedef struct nodoPg_t{

pg_t personaggio;
link next;

}nodoPG;


link listInsHead (link h,pg_t val);
link newNode(pg_t val, link next);
link Attr(link h);
link listDelKey(link h,char *codice);
void inizializzazione_personaggi(tabPG t);
void salvapg(tabPG tab);
void cerca_pg(int ind,char *codice,tabPG t);
void acquisire_personaggio(tabPG t);
void eliminazione_personaggio(tabPG t);
void equipaggiare_item(tabPG t1,tabinv t2);
void ricerca_cancellazione(char *nome,char *codice,link h,tabinv t);
void rimuovereoggetto_apers(tabPG t,tabinv t2);
void calcolo_stats(tabPG t,tabinv t2);
void stampa_stat(char *codice,tabinv t,link h);
pg_t ricerca_personaggio(tabPG t);
pg_t ricerca(link h,char *codice);
void stampa_personaggio(tabPG t,tabinv t2);
void liberalista(tabPG t);

#endif // PGLIST_H_INCLUDED
