#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inventario.h"

void inizializzazione_oggetti(tabInv_t *tab)
{
FILE *fp;
int i;
tab->maxinv=8;

fp=fopen("inventario.txt","r");


if(fp==NULL)
    {
    printf("problema apertura inventario");
    return;
    }
 fscanf(fp,"%d",&tab->nOgg);

 tab->vettOgg=malloc(tab->nOgg*sizeof(Oggetti));

 for(i=0;i<tab->nOgg;i++)
    {
    fscanf(fp,"%s %s %d %d %d %d %d %d",tab->vettOgg[i].Nome,tab->vettOgg[i].Tipologia,&tab->vettOgg[i].statOgg.hp,&tab->vettOgg[i].statOgg.mp,&tab->vettOgg[i].statOgg.atk,&tab->vettOgg[i].statOgg.def,&tab->vettOgg[i].statOgg.mag,&tab->vettOgg[i].statOgg.spr);
    if(strlen(tab->vettOgg[i].Nome)>50 || strlen(tab->vettOgg[i].Tipologia)>50)
        {
        printf("problema con il nome o la tipologia numero %d",i);
        }

    }
fclose(fp);
return;
}


Oggetti ricerca_oggetto(tabInv_t *tab)
{
char nome[51];
int i=0;
Oggetti j;

printf("\ninserire nome dell'oggetto ricercato");
scanf("%s",nome);

strcpy(j.Nome,"00");

while(strcmp(nome,tab->vettOgg[i].Nome)==0)
    {
    i++;
    }

if(i<tab->nOgg)
    {
    return tab->vettOgg[i];
    }
else
    {
    return j;
    }
}


void stampa_oggetto(tabInv_t *tab)
{
char nome[51];
int i=0;

printf("\ninserire nome dell'oggetto ricercato\n");
scanf("%s",nome);

while(strcmp(nome,tab->vettOgg[i].Nome)!=0)
    {
    i++;
    }

if(i<tab->nOgg)
    {
    printf("nome:%s tipo:%s\nhpogg:%d mpogg:%d atkogg:%d defogg:%d magogg:%d sprogg:%d",tab->vettOgg[i].Nome,tab->vettOgg[i].Tipologia,tab->vettOgg[i].statOgg.hp,tab->vettOgg[i].statOgg.mp,tab->vettOgg[i].statOgg.atk,tab->vettOgg[i].statOgg.def,tab->vettOgg[i].statOgg.mag,tab->vettOgg[i].statOgg.spr);
    }
else
    {
    printf("l'oggetto non é presente");
    }
return;
}


Oggetti* equipaggiamento_oggetto(tabInv_t *tab)
{
Oggetti* D;
D=NULL;
int i;
char nome[51];


 printf("inserire nome oggetto da equipaggiare");
scanf("%s",nome);
for(i=0;i<tab->nOgg;i++)
        {
        if(strcmp(nome,tab->vettOgg[i].Nome)==0)
            {
            D=&(tab->vettOgg[i]);
            }
        }
return D;
}

void liberatab(tabInv_t *tab)
{

free(tab->vettOgg);

return;
}
