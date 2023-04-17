#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "personaggi.h"




link listInsHead (link h, PG val)
{
h = newNode(val,h);
return h;
}

link newNode(PG val, link next)
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

void inizializzazione_personaggi(tabPG_t *tab)
{
FILE *fp;
PG A;

tab->headPG=NULL;
tab->nPG=0;
tab->TailPG=NULL;


fp=fopen("pg.txt","r");

while(!feof(fp))
    {
    fscanf(fp,"%s %s %s %d %d %d %d %d %d",A.codice,A.nome,A.classe,&A.statistiche.hp,&A.statistiche.mp,&A.statistiche.atk,&A.statistiche.def,&A.statistiche.mag,&A.statistiche.spr);
    tab->nPG++;
    tab->headPG=listInsHead(tab->headPG,A);
    tab->headPG->perso.equipaggiamento.inUso=0;
    tab->TailPG=Attr(tab->headPG);
    }
fclose(fp);

return;
}

void acquisire_personaggio(tabPG_t *tab)
{
PG A;


printf("acquisire il codice, nome, classe e 6 statistiche");
    scanf("%s %s %s %d %d %d %d %d %d",A.codice,A.nome,A.classe,&A.statistiche.hp,&A.statistiche.mp,&A.statistiche.atk,&A.statistiche.def,&A.statistiche.mag,&A.statistiche.spr);
    tab->nPG++;
    tab->headPG=listInsHead(tab->headPG,A);
    tab->headPG->perso.equipaggiamento.inUso=0;
    tab->TailPG=Attr(tab->headPG);
}

void eliminazione_personaggio(tabPG_t *tab)
{
char codice[7];
printf("inserire nome codice del personaggio da eliminare");
    scanf("%s",codice);
    tab->headPG=listDelKey(tab->headPG,codice);
    tab->nPG--;
    tab->TailPG=Attr(tab->headPG);
}

void aggiunta_personaggioequip(tabPG_t *tab,tabInv_t *tab2)
{

Oggetti* D;
PG B;

char codice[7];

D=equipaggiamento_oggetto(tab2);

if(D==NULL)
    {
    printf("problema nell'equipaggiamento");
    }

printf("\ninserire codice personaggio a cui equipaggiare l'oggetto\n");
scanf("%s",codice);

B=listSearch(tab->headPG,codice,D);

    if(strcmp(B.codice,"PG0000")==0)
        {
        printf("\ncodice del personaggio non trovato o già 8 item equipaggiati\n");
        }
}


PG listSearch(link h,char*codice,Oggetti* A)
{
link x;
PG i;
strcpy(i.codice,"PG0000");
for (x=h; x!=NULL; x=x->next)
    {if (strcmp(x->perso.codice,codice))
        {
        if(x->perso.equipaggiamento.inUso<8)
            {
            x->perso.equipaggiamento.vetteq[x->perso.equipaggiamento.inUso]=A;
            x->perso.equipaggiamento.inUso++;
            }
        else
            {
            return i;
            }
        return x->perso;
        }
    }

return i;
}

void rimuovereoggetto_apers(tabPG_t *tab)
{
PG A;
char codice[7];
char nome[51];
printf("\ninserire codice del personaggio a cui vogliamo togliere un oggetto\n");
scanf("%s",codice);

printf("inserire nome dell'oggetto da sottrarre");
scanf("%s",nome);
A=listSearch2(tab->headPG,codice,nome);

if(strcmp(A.codice,"PG0000")==0)
        {
        printf("\n operazione di cancellamento fallita\n");
        }
}

PG listSearch2(link h,char*codice,char*nome)
{
link x;
int k,j,n;
PG i;
strcpy(i.codice,"PG0000");
for (x=h; x!=NULL; x=x->next)
    {
    if (strcmp(codice,x->perso.codice)==0)
        {
        n=x->perso.equipaggiamento.inUso;
        for(j=0;j<n;j++)
            {
            if(strcmp(x->perso.equipaggiamento.vetteq[j]->Nome,nome)==0)
                {
                for(k=j;k<n;k++)
                    {
                    x->perso.equipaggiamento.vetteq[k]=x->perso.equipaggiamento.vetteq[k+1];
                    }
                 x->perso.equipaggiamento.inUso--;
                return x->perso;
                }
            }

        }
    }
return i;
}

void calcolo_stats(tabPG_t *tab)
{
PG A;
char codice[7];

printf("inserire codice del personaggio di cui i vuole conoscere le statistiche");
    scanf("%s",codice);
    A=listSearch3(tab->headPG,codice);

    if(strcmp(A.codice,"PG0000"))
        {
        printf("problema nel calcolo delle statistiche");
        }

}

PG listSearch3(link h,char*codice)
{
link x;
PG i;
strcpy(i.codice,"PG0000");
int hp=0,mp=0,atk=0,def=0,mag=0,spr=0,j;
for (x=h; x!=NULL; x=x->next)
    {
    if (strcmp(codice,x->perso.codice)==0)
        {
         hp=x->perso.statistiche.hp;
         mp=x->perso.statistiche.mp;
         atk=x->perso.statistiche.atk;
         def=x->perso.statistiche.def;
         mag=x->perso.statistiche.mag;
         spr=x->perso.statistiche.spr;

         for(j=0;j<x->perso.equipaggiamento.inUso;j++)
            {
            hp=hp+x->perso.equipaggiamento.vetteq[j]->statOgg.hp;
            mp=mp+x->perso.equipaggiamento.vetteq[j]->statOgg.mp;
            atk=atk+x->perso.equipaggiamento.vetteq[j]->statOgg.atk;
            def=def+x->perso.equipaggiamento.vetteq[j]->statOgg.def;
            mag=mag+x->perso.equipaggiamento.vetteq[j]->statOgg.mag;
            spr=spr+x->perso.equipaggiamento.vetteq[j]->statOgg.spr;
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
        return x->perso;
        }
    }
return i;
}

PG ricerca_personaggio(tabPG_t *tab)
{
char codice[7];
PG A;

printf("\ninserire codice del personaggio ricercato\n");
scanf("%s",codice);

A=ricerca(tab->headPG,codice);

if(strcmp(A.codice,"PG0000")==0)
    {
    printf("codice non trovato");
    return A;
    }
return A;
}

PG ricerca(link h,char *codice)
{
link x;
PG i;

strcpy(i.codice,"PG0000");

for(x=h;x!=NULL;x=x->next)
    {
    if(strcmp(codice,x->perso.codice)==0)
        {
        return x->perso;
        }
    }
return i;
}


void stampa_personaggio(tabPG_t *tab)
{
char codice[7];
PG A;
int i;

printf("inserire codice del personaggio");
scanf("%s",codice);

A=ricerca(tab->headPG,codice);

if(strcmp(A.codice,"PG0000"))
    {
    printf("\npersonaggio non trovato\n");
    return;
    }
printf("\ncaratteristiche personaggio:\n");
printf("codice:%s nome:%s classe:%s\nhpbase:%d mpbase:%d atkbase:%d defbase:%d magbase:%d sprbase:%d",A.codice,A.nome,A.classe,A.statistiche.hp,A.statistiche.mp,A.statistiche.atk,A.statistiche.def,A.statistiche.mag,A.statistiche.spr);
printf("\nstatistiche equipaggiamento:\n");
printf("%d oggetti equipaggiati\n",A.equipaggiamento.inUso);
for(i=0;i<A.equipaggiamento.inUso;i++)
    {
    printf("nomeogg:%s tipogg:%s\nhpogg:%d mpogg:%d atkogg:%d defogg:%d magogg:%d sprogg:%d\n",A.equipaggiamento.vetteq[i]->Nome,A.equipaggiamento.vetteq[i]->Tipologia,A.equipaggiamento.vetteq[i]->statOgg.hp,A.equipaggiamento.vetteq[i]->statOgg.mp,A.equipaggiamento.vetteq[i]->statOgg.atk,A.equipaggiamento.vetteq[i]->statOgg.def,A.equipaggiamento.vetteq[i]->statOgg.mag,A.equipaggiamento.vetteq[i]->statOgg.spr);
    }
return;
}

void liberapg(tabPG_t *tab)
{
link p,q;

for(p=tab->headPG;p!=NULL;p=q)
    {
    q=p->next;
    free(p);
    }
return;
}
