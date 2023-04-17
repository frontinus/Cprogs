#include <stdio.h>
#include <stdlib.h>

int main()
{int nr,nc,mat[50][50],maxalt=0,maxlarg=0,maxare=0,i,j=0,contalt=0,contlarg=0,contarea=0,k=0,d=0,a=0,l=1,b=1,coord[6],t,dat1[3],dat2[3],dat3[3];

FILE*fp;

fp=fopen("mappa.txt","r");//apertura file

if(fp==NULL)
    {printf("problema apertura file");//controllo apertura
    return-2;
    }

fscanf(fp,"%d %d",&nr,&nc);//assegnazione del numero di righe e colonne tramite fscanf

if(nc>50 || nr>50)
    {printf("errore dimensione matrice");
    return-1;
    }

for(i=0;i<nr;i++)//registrazione della mappa nella matrice mat tramite la fscanf
    {for(j=0;j<nc;j++)
        {fscanf(fp,"%d",&mat[i][j]);
        if(mat[i][j]!=0 && mat[i][j]!=1)
            {printf("problema dati nel file");//controllo supplementare
            return-3;
            }
        }
    }
for(i=0;i<nr;i++)//ciclo di rocerca dell'area con la larghezza maggiore, si fissa la riga nel ciclo principale e si fanno scorrere le colonne verso destra
    {for(j=0;j<nc;j++)
        {if(mat[i][j]==1)
            {if(a==0)//flag
                {k=i;//riga estremo sinistro
                d=j;
                }//colonna estremo sinistro
            contlarg=contlarg+1;//finché non si capita su una casella vuota si continua a incrementare la larghezza
            a++;
            }
        else
            {if(maxlarg<contlarg)
                {maxlarg=contlarg;//se la larghezza appena misurata é la più grande mai incontrata la si salva in maxlarg
                coord[0]=k;
                coord[1]=d;
                }//se l'area é la più "larga" incontrata allora salviamo le coordinate dell'estremo superiore
            a=0;//flag azzerato
            contlarg=0;//contatore azzerato
            }
        }
    }
a=0;
d=0;//riazzeramento del flag e delle coordinate per salvare momentaneamente l'estremo sinistro
k=0;
for(i=0;i<nc;i++)//ciclo ricerca di altezza massima, si fissa la colonna nel ciclo principale e si fanno scorrere le righe dall'alto verso il basso nel ciclo secondario
    {for(j=0;j<nr;j++)
        {if(mat[j][i]==1)
            {if(a==0)
                {k=j;//stesso procedimento che con la larghezza
                d=i;
                }
            a++;
            contalt=contalt+1;}
        else
            {if(maxalt<contalt)
                {maxalt=contalt;//stesso principio di primaa pplicato all'altezza
                coord[2]=j;
                coord[3]=i;//si salva le coordinate dell'estremo superiore dell'area con altezza massima nelle coordinate successive del vettore
                }
            a=0;
            contalt=0;
            }
        }
    }
a=0;
d=0;//riazzeramento
k=0;
for(i=0;i<nr;i++)//ciclo ricerca di area maggiore
    {for(j=0;j<nc;j++)
        {if(mat[i][j]==1)//individua se siamo su una zona piena
            {t=i;//fissiamo temporaneamente le colonne e facciamo scorrere le righe
            while(t<nr && mat[t][j]==1)//ciclo per determinare quante zone si trovano in basso della zona iniziale prima di incontrare un 0
                {t++;
                l++;//incremento altezza finché non si esce dal ciclo
                }
            t=i;//si fissano di nuovo le colonne
            while(t>0 && mat[t][j]==1)//stessa cosa ma in alto ora
                {t--;
                l++;//incremento altezza finché non si capita su un vuoto
                }
            k=t;//salva la riga
            t=j;//si fissa la riga
            while(t<nc && mat[i][t]==1)//stessa cosa ma verso destra
                {t++;
                b++;//incremento larghezza
                }
            t=j;//fissamento riga
            while(t>0 && mat[i][t]==1)//uguale verso sinistra
                {t--;
                b++;//incremento base
                }
            d=t;//salva eventuale casella più a sinistra
            contarea=b*l;//calcolo dell'area
            if(contarea>maxare)
                {dat3[0]=l;//si salva l'area, la larghezza e la base dell'area più grande
                 dat3[1]=b;
                 coord[4]=k;//si salva le coordinate de ll'estremo superiore sinistro nel vettore
                 coord[5]=d;
                 maxare=contarea;
                dat3[2]=maxare;
                }//se é l'area più grande mai incontrata ne salviamo i dati
            else
                {l=1;
                 b=1;
                }
            }
        }
    }
l=1;//ri-inizializzazione dei contatori
b=1;
for(i=coord[1];i<nc && mat[coord[0]][i];i++)//calcoliamo l'area e la larghezza dell'area più alta e ne salviamo i dati
    {
    b++;//si cerca la base dell'area più alta
    }
contarea=l*maxalt;//calcolo dell'area
dat1[0]=maxalt;//registrazione dei dati in vista di stamparli
dat1[1]=b;
dat1[2]=contarea;

for(i=coord[2];i<nr && mat[i][coord[3]];i++)//calcoliamo l'area e l'altezza dell'area più larga e ne salviamo i dati
    {
    l++;//stesso principio di prima
    }
contarea=maxlarg*l;
dat2[0]=l;
dat2[1]=maxlarg;
dat2[2]=contarea;

printf("MAX Base: estr.sup. SX=<%d,%d> b=%d, h=%d, Area=%d",coord[0],coord[1],dat1[1],dat1[0],dat1[2]);
printf("MAX Area: estr.sup. SX=<%d,%d> b=%d, h=%d, Area=%d",coord[4],coord[5],dat3[1],dat3[0],dat3[2]);//stampa dei dati delle 3 aree notevoli
printf("MAX Altezza: estr.sup. SX=<%d,%d> b=%d, h=%d, Area=%d",coord[2],coord[3],dat2[1],dat2[0],dat2[2]);

fclose(fp);//chiusura file
    return 0;
}
