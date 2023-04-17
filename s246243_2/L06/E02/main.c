#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{

char inputdata[11];
int cap;
char cognome[51];
char nome[51];
char citta[51];
char via[51];
char codice[5];
int giorno;
int anno;
int mese;
int numcodice;
}Item;//anagrafe

typedef struct node{//struct nodo
Item val;
struct node *next;

}node_t,*link;

link SortListIns(link header, Item A);
link newNode(Item A, link next);
Item listSearch(link h, char* k);
Item listExtrKeyP(link* hp, char *k);
Item listExtrKeyP2(link* hp,char *dat1,char *dat2 );
int Confrontadate(Item B,int day, int month, int year);
void stampafile(link h);

int main()
{

link head=NULL;
    char comandi[][50]={"acquisizione_tastiera",
    "acquisizione_file",
    "ricerca_per_codice",
    "cancellazzione_singola",
    "cancellazzione_tra_2_date",
    "stampa_lista",
    "fine"
    };

char comando[50];

int flag=0;//flag che serve a determinare quando uscire dal ciclo principale

char strstdin[217];//stringa per acquisire un anagrafe a tastiera,217 é la lunghezza massima di una riga,é probabilmente un po uno spreco di memoria ma non potendola allocare dinamicamente non c'é scelta

char chiave[6];//key

char data1[11];
char data2[11];

FILE *fp;

Item A;

fp=fopen("anagrafica.txt","r");
if(fp==NULL)
    {
    printf("problema apertura file");
    }

do//do-while simile a quello del 5lab4
    {
    printf("i comandi disponibili sono:\n acquisizione_tastiera acquisizione_file\n ricerca_per_codice cancellazzione_singola\ncancellazzione_tra_2_date stampa_lista\nfine\n\ninserire comando:");
    scanf("%s",comando);

    if(strcmp(comando,comandi[0]))//acquisizione tastiera
        {
        printf("\nacquisire dati come segue:\ncodice(AXXXX) nome(max 50 caratteri) cognome(max 50 caratteri)\ndata di nascita (gg/mm/aaaa) via(max 50) città(max 50) e cap(intero)\n");
        gets(strstdin);
        sscanf(strstdin,"%s %s %s %s %s %s %d",A.codice,A.nome,A.cognome,A.inputdata,A.via,A.citta,&A.cap);//divisione della stringa in sottostringhe e allocate nell'item
        sscanf(A.inputdata,"%2d/%2d/%4d",&A.giorno,&A.mese,&A.anno);
        head=SortListIns(head,A);//restituisce l'head dopo averci aggiunto un nodo ordinato
        }
    if(strcmp(comando,comandi[1]))
        {
        fscanf(fp,"%s %s %s %s %s %s %d",A.codice,A.nome,A.cognome,A.inputdata,A.via,A.citta,&A.cap);//acquisizione per file
        sscanf(A.inputdata,"%d/%d/%d",&A.giorno,&A.mese,&A.anno);//stesso principio di prima
        head=SortListIns(head,A);//stessa funzione di prima
        }
    if(strcmp(comando,comandi[2]))
        {
        printf("\ninserire codice di ricerca\n");
        scanf("%s",chiave);//chiave corrispondente al codice di ricerca
        A=listSearch(head,chiave);
        if(A.cap!=-1)//prendiamo tutti gli item con cap=-1 come item void poiché é impossibile aver un cap negativo
            {
            printf("%s %s %s %s %s %s %d",A.codice,A.nome,A.cognome,A.inputdata,A.via,A.citta,A.cap);//stampa della riga sopressa
            }
        else
            {
            printf("codice non trovato");
            }

        }
    if(strcmp(comando,comandi[3]))
        {
        printf("inserire codice da cancellare");
        scanf("%s",chiave);//acquisizione della chiave che contiene il codice della riga da cancellare
        A=listExtrKeyP(&head,chiave);//funzione che restituisce la riga d'anagrafe cancellata
        if(A.cap!=-1)
            {
            printf("Item cancellato :%s %s %s %s %s %s %d\n",A.codice,A.nome,A.cognome,A.inputdata,A.via,A.citta,A.cap);
            }
        }
   if(strcmp(comando,comandi[4]))
        {
        printf("\ninserire le due date estreme dell'insieme dei delle date da cancellare (prima quella più bassa e con formato gg/mm/aaaa)\n");
        scanf("%s %s",data1,data2);//si prendono le due date limite

        while(A.cap!=-1)//finché non ci arriva un Item void continuamo a iterare la funzione e stampare
            {
            A=listExtrKeyP2(&head,data1,data2);
            printf("Item cancellato:%s %s %s %s %s %s %d\n",A.codice,A.nome,A.cognome,A.inputdata,A.via,A.citta,A.cap);
            }
        }
    if(strcmp(comando,comandi[5]))
        {
        stampafile(head);//si manda il puntatore head alla funzione per stampare la lista
        }
   if(strcmp(comando,comandi[6]))
        {
        flag=1;//se il comando dice "fine", allora si modifica il file per uscire dal ciclo e dal programma
        }
    }while(flag==0);

fclose(fp);

    return 0;
}

link SortListIns(link header, Item A) //funzione aggiunta di un nuovo nodo in modo ordinato
{
 link x, p;

 if (header==NULL ||Confrontadate(A,header->val.giorno,header->val.mese,header->val.anno))//quando confrontadate restituisce 0, significa che la data in esame é più vecchia di quella nella lista, percio si agiunge il nodo
 return newNode(A, header);
 for (x=header->next, p=header; (x!=NULL && Confrontadate(A,x->val.giorno,x->val.mese,x->val.anno));p=x, x=x->next);
 p->next = newNode(A,x);
 return header;//si ritorna il puntatore header
}


link newNode(Item A, link next)//funzioneimplementazione di un nuovo nodo
{
 link x = malloc(sizeof *x);
 if (x==NULL)
 return NULL;
 else {
 x->val = A;//l'Item contenuto nel nodo diventa quello in esame
 x->next = next;
 }
 return x;//ritorno del puntatore alla nuova struct node
}


Item listSearch(link h, char* k)//funzione ricerca liste
{
    link x;
    for (x=h; x!=NULL; x=x->next)
        {
        if (strcmp(k,x->val.codice))
            {
            return x->val;//appena si trova una riga d'anagrafe con il codic giusto si ritorna al main (ogni codice é unico dunque non ci possono essere altre righe che soddisfano il requisito)
            }
        }
x->val.cap=-1;//se non si é riusciti a trovare una riga con il codice giusto si ritorna item void
return x->val;
}
Item listExtrKeyP(link *hp, char *k)//funzione che estrae fino al main la riga d'anagrafe da cancellare
{
    link *xp, t;
    Item i;
    i.cap=-1;//settamento a item void nel caso non si trovasse nessuna riga da cancellare
    for (xp=hp;(*xp)!=NULL;xp=&((*xp)->next))
        {
        if (strcmp((*xp)->val.codice,k))//confronto tra la chiave e i codici
            {
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
            }
        }
    return i;
}


Item listExtrKeyP2(link *hp,char *dat1,char *dat2 )
{
link *xp, t;
int g1,m1,a1,g2,m2,a2;
sscanf(dat1,"%d/%d/%d",&g1,&m1,&a1);//dividiamo le stringhe in interi per poterli inviare nella funzione confrontadate
sscanf(dat2,"%d/%d/%d",&g2,&m2,&a2);
Item i;
i.cap=-1;//si inizializza al Item void
for (xp=hp;(*xp)!=NULL ;xp=&((*xp)->next))
    {
    if (Confrontadate((*xp)->val,g1,m1,a1)==1 && Confrontadate((*xp)->val,g2,m2,a2)==0)//si va avanti solo se la data in esame é superiore alla prima e inferiore alla seconda
        {
        t = *xp;//t é una variabile temporanea che permette di mantenere in memoria la casella puntata da xp
        *xp = (*xp)->next;
        i = t->val;
        free(t);
        break;
        }
    }
return i;//si ritorna la riga d'anagrafe cancellata cancellata

}

int Confrontadate(Item B,int day, int month, int year)//se la data in B é più remota in confronto a quella in year/month/day ritorna 0 ,1 nel caso contrario
{
if(B.anno==year)
    {
    if(B.mese==month)
        {
        if(B.giorno==day)
            {
            return 0;
            }
        if(B.giorno<day)
            {
            return 0;
            }
        if(B.giorno>day)
            {
            return 1;
            }
        }
    if(B.mese<month)
        {
        return 0;
        }
    if(B.mese>month)
        {
        return 1;
        }
    }
if(B.anno<year)
    {
    return 0;
    }
if(B.anno>year)
    {
    return 1;
    }
return -1;
}


void stampafile(link h)
{
link x=h;
FILE *fs;

fs=fopen("anagrafica_scritt.txt","w");//apertura di un file per scriverci il contenuto della lista


while(x!=NULL)
    {
    fprintf(fs,"%s %s %s %s %s %s %d",x->val.codice,x->val.nome,x->val.cognome,x->val.inputdata,x->val.via,x->val.citta,x->val.cap);
    x=x->next;
    }
fclose(fs);
}


