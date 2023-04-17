#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgList.h"
#include "invArray.h"

int main()
{
int flag=0;

tabinv tabv;
tabPG tabPG1;
inv_t A;
pg_t B;

tabv=NULL;
tabPG1=NULL;
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

inizializzazione_oggetti(tabv);
inizializzazione_personaggi(tabPG1);


do{

printf("inserire comando da effettuare, la lista dei comandi possibili é:\n acquisizione_personaggio,cancellazione_personaggio\naggiungere_equipaggiamento,rimuovere_equipaggiamento\ncalcolo_stats ,ricerca_oggetto, stampa_oggetto\nricerca_personaggio, stampa_personaggio, Fine\n");

scanf("%s",comando);

if(strcmp(comandi[0],comando))
    {
    acquisire_personaggio(tabPG1);
    }

if(strcmp(comandi[1],comando))
    {
    eliminazione_personaggio(tabPG1);
    }

if(strcmp(comandi[2],comando))
    {
    equipaggiare_item(tabPG1,tabv);
    }

if(strcmp(comandi[3],comando))
    {
    rimuovereoggetto_apers(tabPG1,tabv);
    }

if(strcmp(comandi[4],comando))
    {
    calcolo_stats(tabPG1,tabv);
    }
if(strcmp(comandi[5],comando))
    {
    A=ricerca_oggetto(tabv);
    }

if(strcmp(comandi[6],comando))
    {
    stampa_oggetto(tabv);
    }

if(strcmp(comandi[7],comando))
    {
    B=ricerca_personaggio(tabPG1);
    }

if(strcmp(comandi[8],comando))
    {
    stampa_personaggio(tabPG1,tabv);
    }

if(strcmp(comandi[9],comando))
    {
    flag=1;
    }
}while(flag==0);

liberatutto(tabv);
liberalista(tabPG1);

return 0;
}


