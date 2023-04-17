#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct {

Oggetti* vetteq[8];
int inUso;

}tabEquip_t;

typedef struct{

char codice[7];
char nome[51];
char classe[51];
Stat_pers statistiche;
tabEquip_t equipaggiamento;

}PG;

typedef struct nodo_personaggio *link;
typedef struct nodo_personaggio{

link next;
PG perso;
}nodoPG;

typedef struct{

link headPG;
link TailPG;
int nPG;

}tabPG_t;

link listInsHead(link h,PG val);
link newNode(PG val,link next);
link Attr(link h);
link listDelKey(link h,char *codice);
PG listSearch(link h,char*codice,Oggetti* A);
PG listSearch2(link h,char*codice,char*nome);
PG listSearch3(link h,char*codice);

int main()
{
int i,flag=0;
FILE *fp;
FILE *fp2;
tabInv_t *tabinv;
tabPG_t *tabPG;
PG A;
Oggetti* D=NULL;
char nome[51];
char codice[7];

tabPG->headPG=NULL;
tabPG->nPG=0;
tabPG->TailPG=NULL;

char comando[50];

char comandi[][50]={"acquisizione_personaggio",
                    "cancellazione_personaggio",
                    "aggiungere_equipaggiamento",
                    "rimuovere_equipaggiamento",
                    "calcolo_stats",
                    "Fine"
                    };
 tabinv->maxinv=8;
 fp=fopen("inventario.txt","r");

 if(fp==NULL)
    {
    printf("problema apertura inventario");
    return -1;
    }
 fscanf(fp,"%d",&tabinv->nOgg);

 tabinv->vettOgg=malloc(tabinv->nOgg*sizeof(Oggetti));

 for(i=0;i<tabinv->nOgg;i++)
    {
    fscanf(fp,"%s %s %d %d %d %d %d %d",tabinv->vettOgg[i].Nome,tabinv->vettOgg[i].Tipologia,&tabinv->vettOgg[i].statOgg.hp,&tabinv->vettOgg[i].statOgg.mp,&tabinv->vettOgg[i].statOgg.atk,&tabinv->vettOgg[i].statOgg.def,&tabinv->vettOgg[i].statOgg.mag,&tabinv->vettOgg[i].statOgg.spr);
    if(strlen(tabinv->vettOgg[i].Nome)>50 || strlen(tabinv->vettOgg[i].Tipologia)>50)
        {
        printf("problema con il nome o la tipologia numero %d",i);
        }

    }
fclose(fp);



fp2=fopen("pg.txt","r");

tabPG->nPG=0;


while(!feof(fp2))
    {
    fscanf(fp2,"%s %s %s %d %d %d %d %d %d",A.codice,A.nome,A.classe,&A.statistiche.hp,&A.statistiche.mp,&A.statistiche.atk,&A.statistiche.def,&A.statistiche.mag,&A.statistiche.spr);
    tabPG->nPG++;
    tabPG->headPG=listInsHead(tabPG->headPG,A);
    tabPG->headPG->perso.equipaggiamento.inUso=0;
    tabPG->TailPG=Attr(tabPG->headPG);
    }


fclose(fp2);

do{

printf("inserire comando da effettuare, la lista dei comandi possibili é:\n acquisizione_personaggio,cancellazione_personaggio\naggiungere_equipaggiamento,rimuovere_equipaggiamento\ncalcolo_stats,Fine\n");

scanf("%s",comando);

if(strcmp(comandi[0],comando))
    {
    printf("acquisire il codice, nome, classe e 6 statistiche");
    scanf("%s %s %s %d %d %d %d %d %d",A.codice,A.nome,A.classe,&A.statistiche.hp,&A.statistiche.mp,&A.statistiche.atk,&A.statistiche.def,&A.statistiche.mag,&A.statistiche.spr);
    tabPG->nPG++;
    tabPG->headPG=listInsHead(tabPG->headPG,A);
    tabPG->headPG->perso.equipaggiamento.inUso=0;
    tabPG->TailPG=Attr(tabPG->headPG);
    }

if(strcmp(comandi[1],comando))
    {
    printf("inserire nome codice del personaggio da eliminare");
    scanf("%s",codice);
    tabPG->headPG=listDelKey(tabPG->headPG,codice);
    tabPG->nPG--;
    tabPG->TailPG=Attr(tabPG->headPG);
    }

if(strcmp(comandi[2],comando))
    {
    printf("inserire nome oggetto da equipaggiare");
    scanf("%s",nome);
    for(i=0;i<tabinv->nOgg;i++)
        {
        if(strcmp(nome,tabinv->vettOgg[i].Nome)==0)
            {
            D=&(tabinv->vettOgg[i]);
            }
        }


    printf("\ninserire codice personaggio a cui equipaggiare l'oggetto\n");
    scanf("%s",codice);

    A=listSearch(tabPG->headPG,codice,D);

    if(strcmp(A.codice,"PG0000")==0)
        {
        printf("\ncodice del personaggio non trovato o già 8 item equipaggiati\n");
        }
   }

if(strcmp(comandi[3],comando))
    {
    printf("\ninserire codice del personaggio a cui vogliamo togliere un oggetto\n");
    scanf("%s",codice);

    printf("inserire nome dell'oggetto da sottrarre");
    scanf("%s",nome);

    A=listSearch2(tabPG->headPG,codice,nome);

    if(strcmp(A.codice,"PG0000")==0)
        {
        printf("\n operazione di cancellamento fallita\n");
        }

    }

if(strcmp(comandi[4],comando))
    {
    printf("inserire codice del personaggio di cui i vuole conoscere le statistiche");
    scanf("%s",codice);
    A=listSearch3(tabPG->headPG,codice);

    if(strcmp(A.codice,"PG0000"))
        {
        printf("problema nel calcolo delle statistiche");
        }
    }

if(strcmp(comandi[5],comando))
    {
    flag=1;
    }
}while(flag==0);

free(tabinv->vettOgg);
return 0;
}

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


PG listSearch2(link h,char*codice,char*nome)
{
link x;
int k,j,n;
PG i;
strcpy(i.codice,"PG0000");
for (x=h; x!=NULL; x=x->next)
    {
    if (strcmp(codice,x->perso.codice))
        {
        n=x->perso.equipaggiamento.inUso;
        for(j=0;j<n;j++)
            {
            if(strcmp(x->perso.equipaggiamento.vetteq[j]->Nome,nome)==0)
                {
                for(k=j;k<x->perso.equipaggiamento.inUso;k++)
                    {
                    x->perso.equipaggiamento.vetteq[k]=x->perso.equipaggiamento.vetteq[k+1];
                    }
                }
            }
        return x->perso;
        x->perso.equipaggiamento.inUso--;
        }
    }
return i;
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
