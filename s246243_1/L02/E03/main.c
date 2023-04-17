#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{int NS,k,numpar=0;
char *parola,seq[6],riga[201];
FILE*fp1;
FILE*fp2;

fp1=fopen("sequenze.txt","r");//apertura file
fp2=fopen("testo.txt","r");

if(fp1==NULL ||fp2==NULL)
    {
    printf("problema apertura file");
    return-1;
    }

fscanf(fp1,"%d",&NS);//lettura numero di sequenze

if(NS<0 || NS>20)
    {printf("problema con il numero numero di sequenze");
    return-2;}

for(k=0;k<NS;k++)//prendiamo una sequenza alla volta, scansionamo il testo dividendolo prima in righe poi in parole e verifichiamo parola per parola se contengono la sequenza
    {fscanf(fp1,"%s",seq);
    printf("la sequenza %s é contenuta in ",seq);
    while(fp2!=NULL)
        {fscanf(fp2,"%s",riga);//lettura di una riga intera
         for(parola=strtok(riga," \t,\n\v\f\r.'");parola!=NULL;parola=strtok(NULL," \t,\n\v\f\r.'"))//divisione delle righe parola per parola
            {numpar++;//incremento contatore
            if(strstr(parola,seq)!=NULL)//verificare se la sequenza é contenuta nella parola
                {
                printf("%s (posizione %d) ",parola,numpar);
                }
            }
        }
    numpar=0;//ri-inizializzazione del contatore quando si finisce di ricercare una sequenza nel testo}

fclose(fp1);//chiusura file
fclose(fp2);
    return 0;
}
