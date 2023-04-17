#include <stdio.h>
#include <stdlib.h>
#define N 201
#include <string.h>
int main()
{int S,lun1,lun2;
char str[N],*str1,str2[6],str4[6],*k;
FILE*fp1;
FILE*fp2;
FILE*fp3;

fp1=fopen("sorgente.txt","r");//si aprono u files
fp2=fopen("dizionario.txt","r");
fp3=fopen("ricodificato.txt","w");

if(fp1==NULL || fp2==NULL)//verifica
    {printf("errore");
    return -1;}

fscanf(fp2,"%d",&S);//si estrae l'intero che non é parte del dizionario

if(S<=30)
    {while(!feof(fp1))//scandisce il file fino alla fine
        {fgets(str,200,fp1);//selezione della riga intera
            for(str1=strtok(str," \n");str1!=NULL;str1=strtok(NULL," \n"))//divisione della riga parola per parola in quanto queste ultime sono divise da spazi o da fine di riga

                {
                lun1=strlen(str1);
                while(fscanf(fp2,"%s %s",str4,str2)==1)//scandisce il dizionario per verificare se la parola in str1 coincide con una (o contiene una) delle parole del dizionario
                    {
                    if(strstr(str1,str2)!=NULL)
                        {lun2=strlen(str4);
                        k=strstr(str1,str2);//salviamo puntatore alla prima casella di str1 che contiene str2
                        strncpy(k,str4,lun2);//sostituiamo la parte interessante della parola con str4
                        fprintf(fp3,"%s",str1);
                        }

                    }

                }
        fprintf(fp3,"\n");}//scrive la nuova parola in ricodificato

    }

fclose(fp1);//si chiudono i file
fclose(fp2);
fclose(fp3);



    return 0;
}
