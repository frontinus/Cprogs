#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

int anno;
int mese;
int giorno;
}data;//struct che contiene i dati delle date

typedef struct{

int ore;
int minuti;
int secondi;
}ora;//struct che contiene i dati degli orari

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
}riga;//struct di una riga

typedef struct {

int numrighe;
riga log[1000];
}tabella;//struct della tabella


tabella leggitabella();
void stampa_video(tabella tab);
void stampa_file(tabella tab);
void ordina_data(tabella tab, riga *p[]);
void ordina_codice(tabella tab, riga *p[]);
void ordina_stazionea(tabella tab, riga *p[]);
void ordina_stazionep(tabella tab, riga *p[]);
void ricerca_partenza(tabella tab);

int main()
{
 tabella tab;
 char comandi[][50] = {"stampa_video",//menu
                        "stampa_file",
                        "ordinamento_data",
                        "ordinamento_codice_tratta",
                        "ordinamento_stazione_partenza",
                        "ordinamento_stazione_arrivo",
                        "ricerca_tratta"
                        };
 int flag=0,i;//flag e int per usare il for

 tab = leggitabella();//funzione che permette di leggere la tabella

 char comando[50];//char comando

 char fine[31]={"fine"};

 riga *puntdata[tab.numrighe];//vettori di puntatori a riga
 riga *puntcodice[tab.numrighe];
 riga *puntstazp[tab.numrighe];
 riga *puntstaza[tab.numrighe];

 do{//ciclo essenzialmente ripreso dal 4.4
 printf(" inserisci il comando, inserisci fine se vuoi uscire \n");
  printf("comandi disponibili: stampa_video , stampa_file ,\n ordinamento_data , ordinamento_codice_tratta ,\n ordinamento_stazione_partenza \n ordinamento_stazione_arrivo , ricerca_tratta \n");
  scanf("%s",comando);

  if(strcmp(comando,comandi[0])==0)
    {
  	stampa_video(tab);//chiamata della funzione che stampa la tabella
    }
  if(strcmp(comando,comandi[1])==0)
    {
  	stampa_file(tab);//chiamata della funzione che stampa la tabella su un file
    }
  if(strcmp(comando,comandi[2])==0)
    {
  	ordina_data(tab,puntdata);//funzione che ordina  i dati in funzione della data
  	for(i=0;i<tab.numrighe;i++)
        {
  		printf("ordinati per data:");//stampa
  		printf( "%s %s %s %s %s %s %d\n", (*puntdata[i]).codice, (*puntdata[i]).partenza, (*puntdata[i]).destinazione, (*puntdata[i]).datainput, (*puntdata[i]).orapinput, (*puntdata[i]).oraainput, (*puntdata[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[3])==0)
    {
  	ordina_codice(tab,puntcodice);//funzione che ordina i dati per codice
  	printf("ordinati per codice: \n");
  		for(i=0;i<tab.numrighe;i++)//stampa
        {

  		printf( "%s %s %s %s %s %s %d\n", (*puntcodice[i]).codice, (*puntcodice[i]).partenza, (*puntcodice[i]).destinazione, (*puntcodice[i]).datainput, (*puntcodice[i]).orapinput, (*puntcodice[i]).oraainput, (*puntcodice[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[4])==0)
    {
  	ordina_stazionep(tab,puntstazp);//funzione che ordina in funzione delle stazioni di partenza
  	printf("ordinati per stazione partenza: \n");
  		for(i=0;i<tab.numrighe;i++)//stampa
        {

  		printf( "%s %s %s %s %s %s %d\n", (*puntstazp[i]).codice, (*puntstazp[i]).partenza, (*puntstazp[i]).destinazione, (*puntstazp[i]).datainput, (*puntstazp[i]).orapinput, (*puntstazp[i]).oraainput, (*puntstazp[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[5])==0)
    {
  	ordina_stazionea(tab,puntstaza);//funzione che ordina le righe in funzione delle stazioni d'arrivo
  		printf("ordinati per stazione arrivo: \n");
  		for(i=0;i<tab.numrighe;i++)//stampa
        {

  		printf( "%s %s %s %s %s %s %d\n", (*puntstaza[i]).codice, (*puntstaza[i]).partenza, (*puntstaza[i]).destinazione, (*puntstaza[i]).datainput, (*puntstaza[i]).orapinput, (*puntstaza[i]).oraainput, (*puntstaza[i]).ritardo);
        }
    }
  if(strcmp(comando,comandi[6])==0)
    {
  	ricerca_partenza(tab);//funzione che ricerca una riga in funzione della stazione di pertenza
    }
  if(strcmp(comando,fine)==0)
    {
  	flag=1;//se viene selezionato il comando fine si esce dal while
    }
}
while(flag==0);

    return 0;
}


tabella leggitabella()
{
FILE*fp;
tabella tab1;
int i;
fp=fopen("log.txt","r");//apertura file

if(fp==NULL)
    {
    printf("errore apertura file");
    return tab1;
    }
fscanf(fp,"%d",&tab1.numrighe);
for(i=0;i<tab1.numrighe;i++)//memorizzazione dei valori nella tabella
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

void ordina_data(tabella tab, riga *p[])//ordinamento per date
{
 int i,diff=-1, j;//iniziai=lizziamo diff a -1 per entrare nel ciclo
  int l = 0, r = (tab.numrighe)-1;
  riga x;

  for(i=0;i<tab.numrighe;i++)
    {
    p[i]=&tab.log[i];//si inizializza il vettore di puntatori memorizzando gli indirizzi di ogni riga
    }


  for(i=l+1; i<=r; i++)
    {
    x=(*p[i]);
    j = i-1;
    while(j>=l && diff < 0)//se diff é positivo significa che abbiamo trovato una data-orario in j più piccola di quella in i, il resto é ripreso dal 4.4
        {
        if((*p[i]).datariga.anno!=(*p[j]).datariga.anno)
            {
            diff=(*p[i]).datariga.anno-(*p[j]).datariga.anno;//diff prende ogni volta il valore della differenza tra le due componenti paragonate
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
//in questo modo sono i vettori di indirizzi di memoria ad essere ordinati in funzione dei valori associati a questi indirizzi ai quali si accede mediamente (*p[])

void ordina_codice(tabella tab, riga *p[])//ordinamento per codice
{
int i,diff=-1, j;
  int l = 0, r = (tab.numrighe)-1;
  riga x;

  for(i=0;i<tab.numrighe;i++)
    {
    p[i]=&tab.log[i];//stesso funzionamento di prima
    }

  for(i=l+1; i<=r; i++)
    {
    x=(*p[i]);
    j = i-1;
    while(j>=l && (diff=strcmp((*p[i]).codice,(*p[j]).codice)<0))//stesso funzionamento di prima, ora siccome la strcmp restituisce la differenza tra i codici ASCII dei caratteri e che essi possono solo essere alfabetici, allora diff é negativa se
        {
        (*p[j+1])=(*p[j]);
        j--;
        }
    (*p[j+1])=x;
    }
}

void ordina_stazionea(tabella tab, riga *p[])//ordinamento per stazione di arrivo
{
int i, j;
int l = 0, r = (tab.numrighe)-1;
riga x;

for(i=0;i<tab.numrighe;i++)//come prima
    {
    p[i]=&tab.log[i];
    }

  for(i=l+1; i<=r; i++)
    {
    x=(*p[i]);
    j = i-1;
    while(j>=l && (strcmp((*p[j]).destinazione,(*p[j+1]).destinazione)<0))//stesso principio di prima ma con les stazioni di destinazione
          {
          (*p[j+1])=(*p[j]);
          j--;
          }
    (*p[j+1])=x;
    }
}
void ordina_stazionep(tabella tab, riga *p[])//ordinamento per stazione di partenza
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
int i,flg=0;

printf("inserire la partenza da ricercare \n");

scanf("%s",stazione);//memorizzazione della stazione da ricercare

for(i=0;i<tab.numrighe;i++)
    {
    if(strcmp(stazione,tab.log[i].partenza)==0)
        {
        printf("tratta disponibile: ");//stampa se trova
        flg=1;
        printf("%s %s %s %s %s %s %d\n", tab.log[i].codice, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].datainput, tab.log[i].orapinput, tab.log[i].oraainput, tab.log[i].ritardo);
		}
	}
if(flg==0)
    {
    printf("la stazione ricercata non é presente nella tabella");
    }

}
