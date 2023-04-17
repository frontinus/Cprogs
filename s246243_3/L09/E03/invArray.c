#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invArray.h"


struct tabInv_t
{

inv_t *vettInv;
int ninv;
int maxinv;

};

void inizializzazione_oggetti(tabinv t)
{
FILE *fp;
int i;

t->maxinv=8;

fp=fopen("inventario.txt","r");

if(fp==NULL)
    {
    printf("problema con il file inventario");
    return;
    }
fscanf(fp,"%d",&t->ninv);

t->vettInv=malloc(t->ninv*sizeof(inv_t));

fclose(fp);
salvainv(&(t->vettInv),t->ninv);


return;
}




int cerca_oggetto(char *nome,tabinv t)
{
int i,k=-1;

for(i=0;i<t->ninv;i++)
    {
    if(strcmp(t->vettInv[i].nome,nome)==0)
        {
        k=i;
        }
    }
return k;
}

inv_t ricerca_oggetto(tabinv t)
{
char nome[51];
int i=0;
inv_t j;

printf("\ninserire nome dell'oggetto ricercato");
scanf("%s",nome);

strcpy(j.nome,"00");

while(strcmp(nome,t->vettInv[i].nome)==0)
    {
    i++;
    }

if(i<t->ninv)
    {
    return t->vettInv[i];
    }
else
    {
    return j;
    }

}

void stampa_oggetto(tabinv t)
{
char nome[51];
int i=0;

printf("\ninserire nome dell'oggetto ricercato\n");
scanf("%s",nome);

while(strcmp(nome,t->vettInv[i].nome)!=0)
    {
    i++;
    }

if(i<t->ninv)
    {
    printf("nome:%s tipo:%s\nhpogg:%d mpogg:%d atkogg:%d defogg:%d magogg:%d sprogg:%d",t->vettInv[i].nome,t->vettInv[i].tipologia,t->vettInv[i].statistiche.hp,t->vettInv[i].statistiche.mp,t->vettInv[i].statistiche.atk,t->vettInv[i].statistiche.def,t->vettInv[i].statistiche.mag,t->vettInv[i].statistiche.spr);
    }
else
    {
    printf("l'oggetto non é presente");
    }
return;
}

void liberatutto(tabinv t)
{
free(t->vettInv);

return;

}

int confronto(char *nome,int indice,tabinv t)
{

if(strcmp(nome,t->vettInv[indice].nome)==0)
    {
    return 0;
    }
else
    {
    return 1;
    }
}

int trova_stat(int indice,tabinv t,int tipo_stat)
{

switch(tipo_stat)
    {
    case 0:
        return t->vettInv[indice].statistiche.hp;
        break;

    case 1:
        return t->vettInv[indice].statistiche.mp;
        break;

    case 2:
        return t->vettInv[indice].statistiche.atk;
        break;

    case 3:
        return t->vettInv[indice].statistiche.def;
        break;

    case 4:
        return t->vettInv[indice].statistiche.mag;
        break;

    case 5:
        return t->vettInv[indice].statistiche.spr;
        break;

    }
}

void stampa_stat_equip2(int indice1,tabinv t2)
{

printf("nomeogg:%s tipogg:%s\nhpogg:%d mpogg:%d atkogg:%d defogg:%d magogg:%d sprogg:%d\n",t2->vettInv[indice1].nome,t2->vettInv[indice1].tipologia,t2->vettInv[indice1].statistiche.hp,t2->vettInv[indice1].statistiche.mp,t2->vettInv[indice1].statistiche.atk,t2->vettInv[indice1].statistiche.def,t2->vettInv[indice1].statistiche.mag,t2->vettInv[indice1].statistiche.spr);

}
