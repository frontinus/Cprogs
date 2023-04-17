#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "personaggi.h"

int main()
{
int flag=0;

tabInv_t *tabinv;
tabPG_t *tabPG;
Oggetti A;
PG B;


char comando[50];

char comandi[][50]={"acquisizione_personaggio",
                    "cancellazione_personaggio",
                    "aggiungere_equipaggiamento",
                    "rimuovere_equipaggiamento",
                    "calcolo_stats",
                    "ricerca_oggetto",
                    "stampa_oggetto",
                    "ricerca_personaggio"
                    "stampa_personaggio"
                    "Fine"
                    };

inizializzazione_oggetti(tabinv);
inizializzazione_personaggi(tabPG);


do{

printf("inserire comando da effettuare, la lista dei comandi possibili é:\n acquisizione_personaggio,cancellazione_personaggio\naggiungere_equipaggiamento,rimuovere_equipaggiamento\ncalcolo_stats ,ricerca_oggetto, stampa_oggetto\nricerca_personaggio, stampa_personaggio, Fine\n");

scanf("%s",comando);

if(strcmp(comandi[0],comando))
    {
    acquisire_personaggio(tabPG);
    }

if(strcmp(comandi[1],comando))
    {
    eliminazione_personaggio(tabPG);
    }

if(strcmp(comandi[2],comando))
    {
    aggiunta_personaggioequip(tabPG,tabinv);
    }

if(strcmp(comandi[3],comando))
    {
    rimuovereoggetto_apers(tabPG);
    }

if(strcmp(comandi[4],comando))
    {
    calcolo_stats(tabPG);
    }
if(strcmp(comandi[5],comando))
    {
    A=ricerca_oggetto(tabinv);
    }

if(strcmp(comandi[6],comando))
    {
    stampa_oggetto(tabinv);
    }

if(strcmp(comandi[7],comando))
    {
    B=ricerca_personaggio(tabPG);
    }

if(strcmp(comandi[8],comando))
    {
    stampa_personaggio(tabPG);
    }

if(strcmp(comandi[9],comando))
    {
    flag=1;
    }
}while(flag==0);

liberatab(tabinv);
liberapg(tabPG);

return 0;
}

