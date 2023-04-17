#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

int anno;
int mese;
int giorno;
}data;//struct data

typedef struct{

int ore;
int minuti;
int secondi;
}ora;//struct ora

typedef struct{

char codice[31];
char partenza[31];
char destinazione[31];
char datainput[31];
char orapinput[31];
char oraainput[31];
int ritardo;
data datariga;
ora p,a;
}riga;

typedef struct {

int numrighe;
riga log[1000];
}tabella;


tabella leggitabella();
void stampa_video(tabella tab);
void stampa_file(tabella tab);
void ordina_data(tabella tab, riga *p[]);
void ordina_codice(tabella tab, riga *p[]);
void ordina_stazionea(tabella tab, riga *p[]);
void ordina_stazionep(tabella tab, riga *p[]);
void ricerca_partenza(tabella tab);
tabella legginuovofile(char *nome,riga **puntdata,riga **puntcodice,riga **punstazpart,riga **punstazarr);


int main()
{
 tabella tab;
 char comandi[][50] = {"stampa_video",
                        "stampa_file",
                        "ordinamento_data",
                        "ordinamento_codice_tratta",
                        "ordinamento_stazione_partenza",
                        "ordinamento_stazione_arrivo",
                        "ricerca_tratta",
                        "acquisire_file"
                        };
 int flag=0,i;

 tab = leggitabella();

 char comando[50];

 char *newname;

 char fine[31]={"fine"};

 riga **puntdata;
 riga **puntcodice;
 riga **puntstazp;
 riga **puntstaza;

 *puntdata=malloc(tab.numrighe*sizeof(riga));//vettori di puntatori allocati dinamicamente
 *puntcodice=malloc(tab.numrighe*sizeof(riga));
 *puntstazp=malloc(tab.numrighe*sizeof(riga));
 *puntstaza=malloc(tab.numrighe*sizeof(riga));

 do{
  printf(" inserisci il comando, inserisci fine se vuoi uscire \n");
  printf("comandi disponibili: stampa_video , stampa_file ,\n ordinamento_data , ordinamento_codice_tratta ,\n ordinamento_stazione_partenza \n ordinamento_stazione_arrivo , ricerca_tratta \n acquisire_file");
  scanf("%s",comando);

  if(strcmp(comando,comandi[0])==0)
    {
  	stampa_video(tab);
    }
  if(strcmp(comando,comandi[1])==0)
    {
  	stampa_file(tab);
    }
  if(strcmp(comando,comandi[2])==0)
    {
  	ordina_data(tab,puntdata);
  	for(i=0;i<tab.numrighe;i++)
        {
  		printf("ordinati per data:");
  		printf( "%s %s %s %s %s %s %d\n", (*puntdata[i]).codice, (*puntdata[i]).partenza, (*puntdata[i]).destinazione, (*puntdata[i]).datainput, (*puntdata[i]).orapinput, (*puntdata[i]).oraainput, (*puntdata[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[3])==0)
    {
  	ordina_codice(tab,puntcodice);
  	printf("ordinati per codice: \n");
  		for(i=0;i<tab.numrighe;i++)
        {

  		printf( "%s %s %s %s %s %s %d\n", (*puntcodice[i]).codice, (*puntcodice[i]).partenza, (*puntcodice[i]).destinazione, (*puntcodice[i]).datainput, (*puntcodice[i]).orapinput, (*puntcodice[i]).oraainput, (*puntcodice[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[4])==0)
    {
  	ordina_stazionep(tab,puntstazp);
  	printf("ordinati per stazione partenza: \n");
  		for(i=0;i<tab.numrighe;i++)
        {

  		printf( "%s %s %s %s %s %s %d\n", (*puntstazp[i]).codice, (*puntstazp[i]).partenza, (*puntstazp[i]).destinazione, (*puntstazp[i]).datainput, (*puntstazp[i]).orapinput, (*puntstazp[i]).oraainput, (*puntstazp[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[5])==0)
    {
  	ordina_stazionea(tab,puntstaza);
  		printf("ordinati per stazione arrivo: \n");
  		for(i=0;i<tab.numrighe;i++)
        {

  		printf( "%s %s %s %s %s %s %d\n", (*puntstaza[i]).codice, (*puntstaza[i]).partenza, (*puntstaza[i]).destinazione, (*puntstaza[i]).datainput, (*puntstaza[i]).orapinput, (*puntstaza[i]).oraainput, (*puntstaza[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[6])==0)
    {
  	ricerca_partenza(tab);
    }
  if(strcmp(comando,comandi[7])==0)
    {
    printf("\n inserire nome file da aprire\n");
    scanf("%s",newname);
    free(puntdata);//liberazione dei vettori prima di riallocarli
    free(puntcodice);
    free(puntstazp);
    free(puntstaza);
    tab=legginuovofile(newname,puntdata,puntcodice,puntstazp,puntstaza);
    }
  if(strcmp(comando,fine)==0)
    {
  	flag=1;
    }
}
while(flag==0);



free(puntdata);//liberazione
free(puntcodice);
free(puntstaza);
free(puntstazp);
    return 0;
}


tabella leggitabella()
{
FILE*fp;
tabella tab1;
int i;
fp=fopen("log.txt","r");

if(fp==NULL)
    {
    printf("errore apertura file");
    return ;
    }
fscanf(fp,"%d",&tab1.numrighe);
for(i=0;i<tab1.numrighe;i++)
    {
    fscanf(fp,"%s %s %s %s %s %s %d\n",tab1.log[i].codice,tab1.log[i].partenza,tab1.log[i].destinazione,tab1.log[i].datainput,tab1.log[i].orapinput,tab1.log[i].oraainput,&tab1.log[i].ritardo);
    sscanf(tab1.log[i].datainput,"%d/%d/%d",&tab1.log[i].datariga.anno,&tab1.log[i].datariga.mese,&tab1.log[i].datariga.giorno);
    sscanf(tab1.log[i].orapinput,"%d:%d:%d",&tab1.log[i].p.ore,&tab1.log[i].p.minuti,&tab1.log[i].p.secondi);
    sscanf(tab1.log[i].oraainput,"%d:%d:%d",&tab1.log[i].a.ore,&tab1.log[i].a.minuti,&tab1.log[i].a.secondi);
    }

return tab1;

}

void stampa_video(tabella tab)
{
int i;

for(i=0;i<tab.numrighe;i++)//stampa della tabella a video
    {
    printf("%s %s %s %s %s %s %d\n", tab.log[i].codice,tab.log[i].partenza,tab.log[i].destinazione,tab.log[i].datainput,tab.log[i].orapinput, tab.log[i].oraainput,tab.log[i].ritardo);
    }

}

void stampa_file(tabella tab)
{
int i;
FILE *fs;

fs=fopen("filescritt.txt","w");//apertura file

for(i=0;i<tab.numrighe;i++)//stampa della tabella sul file
    {
    fprintf(fs,"%s %s %s %s %s %s %d\n", tab.log[i].codice,tab.log[i].partenza,tab.log[i].destinazione,tab.log[i].datainput,tab.log[i].orapinput, tab.log[i].oraainput,tab.log[i].ritardo);
    }
fclose(fs);

}

void ordina_data(tabella tab, riga *p[])
{
int i,diff=-1, j;
int l = 0, r = (tab.numrighe)-1;
riga x;

for(i=0;i<tab.numrighe;i++)
    {
    p[i]=&tab.log[i];
    }


for(i=l+1; i<=r; i++)
    {
    x=(*p[i]);
    j = i-1;
    while(j>=l && diff < 0)
        {
        if((*p[i]).datariga.anno!=(*p[j]).datariga.anno)
            {
            diff=(*p[i]).datariga.anno-(*p[j]).datariga.anno;
            }
        else
            {
            if((*p[i]).datariga.mese!=(*p[j]).datariga.mese)
                {
                diff=(*p[i]).datariga.mese-(*p[j]).datariga.mese;
                }
            else
                {
                if((*p[i]).datariga.giorno!=(*p[j]).datariga.giorno)
                    {
                    diff=(*p[i]).datariga.giorno-(*p[j]).datariga.giorno;
                    }
                else
                    {
                    if((*p[i]).p.ore!=(*p[j]).p.ore)
                        {
                        diff=(*p[i]).p.ore-(*p[j]).p.ore;
                        }
                    else
                        {
                        if((*p[i]).p.minuti!=(*p[j]).p.minuti)
                            {
                            diff=(*p[i]).p.minuti-(*p[j]).p.minuti;
                            }
                        else
                            {
                            if((*p[i]).p.secondi!=(*p[j]).p.secondi)
                                {
                            diff=(*p[i]).p.secondi-(*p[j]).p.secondi;
                                }
                            }
                        }
                    }
                }
            }
        (*p[j+1])=(*p[j]);
        j--;
        }
    (*p[j+1])=x;
    }
}

void ordina_codice(tabella tab, riga *p[])
{
int i,diff=-1, j;
  int l = 0, r = (tab.numrighe)-1;
  riga x;

  for(i=0;i<tab.numrighe;i++)
    {
    p[i]=&tab.log[i];
    }

  for(i=l+1; i<=r; i++)
    {
    x=(*p[i]);
    j = i-1;
    while(j>=l && (diff=strcmp((*p[j]).codice,(*p[j+1]).codice)<0))
        {
        (*p[j+1])=(*p[j]);
        j--;
        }
    (*p[j+1])=x;
    }
}

void ordina_stazionea(tabella tab, riga *p[])
{int i, j;
  int l = 0, r = (tab.numrighe)-1;
  riga x;
for(i=0;i<tab.numrighe;i++)
    {
    p[i]=&tab.log[i];
    }

  for(i=l+1; i<=r; i++)
    {
    x=(*p[i]);
    j = i-1;
    while(j>=l && (strcmp((*p[j]).codice,(*p[j+1]).codice)<0))
          {
          (*p[j+1])=(*p[j]);
          j--;
          }
    (*p[j+1])=x;
    }
}
void ordina_stazionep(tabella tab, riga *p[])
{
int i, j;
  int l = 0, r = (tab.numrighe)-1;
  riga x;
for(i=0;i<tab.numrighe;i++)
    {
    p[i]=&tab.log[i];
    }
  for(i=l+1; i<=r; i++)
    {
    x=(*p[i]);
    j = i-1;
    while(j>=l && (strcmp((*p[j]).partenza,(*p[j+1]).partenza)<0))
          {
          (*p[j+1])=(*p[j]);
          j--;
          }
    (*p[j+1])=x;
    }
}
void ricerca_partenza(tabella tab)
{
char stazione[31];
	int i;
	printf("inserire la partenza da ricercare \n");
	scanf("%s",stazione);
	for(i=0;i<tab.numrighe;i++)
	{
		if(strcmp(stazione,tab.log[i].partenza)==0)
		{
			printf("tratta disponibile: ");

			printf( "%s %s %s %s %s %s %d\n", tab.log[i].codice, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].datainput, tab.log[i].orapinput, tab.log[i].oraainput, tab.log[i].ritardo);
		}
	}

}


tabella legginuovofile(char *nome,riga **puntdata,riga **puntcodice,riga **punstazpart,riga **punstazarr)
{
FILE *fp2;
fp2=fopen(nome,"r");//apertura nuovo file
tabella tab2;
int i;
if(fp2==NULL)
    {
    printf("problema con il nuovofile");
    return;
    }

fscanf(fp2,"%d",&tab2.numrighe);

*puntdata=malloc(tab2.numrighe*sizeof(riga));//allocazione con la nuova ampiezza
*puntcodice=malloc(tab2.numrighe*sizeof(riga));
*punstazarr=calloc(tab2.numrighe,sizeof(riga));
*punstazpart=calloc(tab2.numrighe,sizeof(riga));


for(i=0;i<tab2.numrighe;i++)//stampa
    {
    fscanf(fp2,"%s %s %s %s %s %s %d\n",tab2.log[i].codice,tab2.log[i].partenza,tab2.log[i].destinazione,tab2.log[i].datainput,tab2.log[i].orapinput,tab2.log[i].oraainput,&tab2.log[i].ritardo);
    sscanf(tab2.log[i].datainput,"%d/%d/%d",&tab2.log[i].datariga.anno,&tab2.log[i].datariga.mese,&tab2.log[i].datariga.giorno);
    sscanf(tab2.log[i].orapinput,"%d:%d:%d",&tab2.log[i].p.ore,&tab2.log[i].p.minuti,&tab2.log[i].p.secondi);
    sscanf(tab2.log[i].oraainput,"%d:%d:%d",&tab2.log[i].a.ore,&tab2.log[i].a.minuti,&tab2.log[i].a.secondi);
    }

return tab2;

}



