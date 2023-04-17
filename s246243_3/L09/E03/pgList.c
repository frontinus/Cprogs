#include <stdio.h>
#include <stdlib.h>
#include "pgList.h"

struct tabPG_t
{
link headPG;
link tailPG;
int nPg;

};




link listInsHead (link h,pg_t val)
{
h = newNode(val,h);
return h;
}

link newNode(pg_t val, link next)
{
link x = malloc(sizeof *x);
if (x==NULL)
    {
    return NULL;
    }
else
    {
    x->perso = val;
    x->next = next;
    }
return x;
}

link Attr(link h)
{
link x;

for(x=h;x!=NULL;x=x->next);


return x;

}


link listDelKey(link h,char *codice)
{
link x, p;

if (h == NULL)
        {
        return NULL;
        }
for (x=h, p=NULL; x!=NULL; p=x, x=x->next)
    {
    if (strcmp(codice,x->perso.codice))
        {
        if (x==h)
            {
            h = x->next;
            }
        else
            {
            p->next = x->next;
            }
        free(x);
        break;
        }
    }
return h;
}



void inizializzazione_personaggi(tabPG t)
{
t->headPG=NULL;
t->nPg=0;
t->tailPG=NULL;

salvapg(t);

return;
}

void salvapg(tabPG tab)
{
FILE *fp;
pg_t A;
fp=fopen("pg.txt","r");

if(fp==NULL)
    {
    printf("problema file personaggi");
    return;
    }

while(!feof(fp))
    {
    fscanf("%s %s %s %d %d %d %d %d %d",A.codice,A.nome,A.classe,&A.stat.hp,&A.stat.mp,&A.stat.atk,&A.stat.def,&A.stat.mag,&A.stat.spr);
    tab->nPg++;
    tab->headPG=listInsHead(tab->headPG,A);
    tab->headPG.personaggio.equip.inUso=0;
    tab->TailPG=Attr(tab->headPG);
    }
fclose(fp);

return;


}

void cerca_pg(int ind,char *codice,tabPG t)
{
link x;

for(x=t->headPG;x!=NULL;x=x->next)
    {
    if(strcmp(codice,x->personaggio.codice)==0)
        {
        equipaggia(ind,&x->personaggio.equip);
        return;
        }
    }
return;
}

void acquisire_personaggio(tabPG t)
{
pg_t A;

printf("acquisire il codice, nome, classe e 6 statistiche");
scanf("%s %s %s %d %d %d %d %d %d",A.codice,A.nome,A.classe,&A.stat.hp,&A.stat.mp,&A.stat.atk,&A.stat.def,&A.stat.mag,&A.stat.spr);

t->nPg++;
t->headPG=listInsHead(t->headPG,A);
t->headPG.personaggio.equip.inUso=0;
t->tailPG=Attr(t->headPG);


return;
}

void eliminazione_personaggio(tabPG t)
{
char codice[7];
printf("inserire nome codice del personaggio da eliminare");
    scanf("%s",codice);
    t->headPG=listDelKey(t->headPG,codice);
    t->nPg--;
    t->tailPG=Attr(t->headPG);
return;
}

void equipaggiare_item(tabPG t1,tabinv t2)
{
char nome[51],codice[7];
int indice;


printf("\ninserire nome item da inserire\n");
scanf("%s",nome);

indice=cerca_oggetto(nome,t2);

printf("\inserire codice personaggio\n");
scanf("%s",codice);

cerca_pg(indice,codice,t1);

return;
}

void rimuovereoggetto_apers(tabPG t,tabinv t2)
{

char nome[51],codice[7];

printf("\ninserire nome item da ritirare dall'equipaggiamento\n");
scanf("%s",nome);

printf("inserire codice del personaggio a cui sottrarre l'oggetto");
scanf("%s",codice);

ricerca_cancellazione(nome,codice,t->headPG,t2);
}

void ricerca_cancellazione(char *nome,char *codice,link h,tabinv t)
{
link x;

for(x=h;x!=NULL,x=x->next)
    {
    if(strcmp(x->personaggio.codice,codice)==0)
        {
        cancellazione(nome,&x->personaggio.equip,t);
        return;
        }
    }
return;
}



void calcolo_stats(tabPG t,tabinv t2)
{
char codice[7];

printf("inserire codice del personaggio di cui i vuole conoscere le statistiche");
scanf("%s",codice);

stampa_stat(codice,t2,t->headPG);
}

void stampa_stat(char *codice,tabinv t,link h)
{
link x;
int hp=0,mp=0,atk=0,def=0,mag=0,spr=0,j;

for (x=h; x!=NULL; x=x->next)
    {
    if (strcmp(codice,x->personaggio.codice)==0)
        {
         hp=x->personaggio.stat.hp
         mp=x->perso.stat.mp;
         atk=x->perso.stat.atk;
         def=x->perso.stat.def;
         mag=x->perso.stat.mag;
         spr=x->perso.stat.spr;

         for(j=0;j<x->perso.equipaggiamento.inUso;j++)
            {
            hp=hp+trova_stat(j,t,0);
            mp=mp+trova_stat(j,t,1);
            atk=atk+trova_stat(j,t,2);
            def=def+trova_stat(j,t,3);
            mag=mag+trova_stat(j,t,4);
            spr=spr+trova_stat(j,t,5);
            }
         if(hp<1)
            {
            hp=1;
            }
         if(mp<1)
            {
            mp=1;
            }
         if(atk<1)
            {
            atk=1;
            }
         if(def<1)
            {
            def=1;
            }
         if(mag<1)
            {
            mag=1;
            }
         if(spr<1)
            {
            spr=1;
            }
         printf("Il personaggio di codice %s ha statistiche :\nhp: %d mp: %d atk: %d def: %d mag: %d spr: %d",codice,hp,mp,atk,def,mag,spr);
        return;
        }
    }
}

pg_t ricerca_personaggio(tabPG t)
{
char codice[7];
PG A;

printf("\ninserire codice del personaggio ricercato\n");
scanf("%s",codice);

A=ricerca(t->headPG,codice);

if(strcmp(A.codice,"PG0000")==0)
    {
    printf("codice non trovato");
    return A;
    }
return A;

}

pg_t ricerca(link h,char *codice)
{
link x;
pg_t i;

strcpy(i.codice,"PG0000");

for(x=h;x!=NULL;x=x->next)
    {
    if(strcmp(codice,x->personaggio.codice)==0)
        {
        return x->personaggio;
        }
    }
return i;
}


void stampa_personaggio(tabPG t,tabinv t2)
{
char codice[7];
pg_t A;
int i;

printf("inserire codice del personaggio");
scanf("%s",codice);

A=ricerca(t->headPG,codice);

if(strcmp(A.codice,"PG0000"))
    {
    printf("\npersonaggio non trovato\n");
    return;
    }

printf("\ncaratteristiche personaggio:\n");
printf("codice:%s nome:%s classe:%s\nhpbase:%d mpbase:%d atkbase:%d defbase:%d magbase:%d sprbase:%d",A.codice,A.nome,A.classe,A.stat.hp,A.stat.mp,A.stat.atk,A.stat.def,A.stat.mag,A.stat.spr);
printf("\nstatistiche equipaggiamento:\n");
printf("%d oggetti equipaggiati\n",A.equip.inUso);

for(i=0;i<A.equipaggiamento.inUso;i++)
    {
    stampa_stat_equip(i,&A.equip,t2);
    }
return;
}

void liberalista(tabPG t)
{

link p,q;

for(p=t->headPG;p!=NULL;p=q)
    {
    q=p->next;
    free(p);
    }
return;

}
