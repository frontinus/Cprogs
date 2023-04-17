#include <stdio.h>
#include <stdlib.h>
#define Max 50

int riconosciregione(int *(*M),int nr,int nc,int r,int c,int *b,int *h);

void leggimatrice(int *(*M),int MAXR,int *nr,int *nc);

int main()
{int nri=Max,nco=Max,mat[Max][Max],p,i,j,flg,k=0,h=1,b=1;

leggimatrice(mat,Max,&nri,&nco);//passagio by reference della matrice e le coordinate massime delle righe e colonne

printf("quante caselle vuole provare?\n");

scanf("%d",&k);//inserire il numero di caselle di cui si vuole verificare se sono l'estremo superiore sinistro di un'area e visualizzarne i dati

for(p=0;p<k;p++)
    {
    printf("\n inserisca coordinate della casella come segue :riga_colonna\n");//inserire coordinate della casella da verificare

    scanf("%d_%d",&i,&j);

    flg=riconosciregione(mat,nri,nco,i,j,&b,&h);//matrice e dati sono passati by reference

    if(flg==0)//se la funzione restituisce 0 significa che la casella non é l'estremo superiore sinistro di un area
        {
        printf("la casella non é un estremo sinistro superiore");
        }

    else
        {
        printf("\nArea rettangolo=%d Base rettangolo=%d Altezza rettangolo=%d Le coordinate del estremo sinistro superiore del rettangolo sono riga=%d e colonna=%d",b*h,b,h,i,j);//stampiamo tutto compresa anche l'area
        }
    }
    return 0;
}


void leggimatrice(int *(*M),int MAXR,int *nr,int *nc)
{int i,j;
FILE*fp;

fp=fopen("mappa.txt","r");//apertura file

if(fp==NULL)
    {printf("problema apertura file");
    return;
    }

fscanf(fp,"%d %d",*nr,*nc);//lettura delle dimensioni reali della matrice e attribuzione a nri e nco by reference

if(*nc>MAXR || *nr>MAXR)
    {printf("errore dimensione matrice");
    return;
    }

for(i=0;i<*nr;i++)
    {for(j=0;j<*nc;j++)
        {fscanf(fp,"%d",&M[i][j]);
        if(M[i][j]!=0 && M[i][j]!=1)
            {printf("problema dati nel file");//registrazione della mappa nella matrice
            return;
            }
        }
    }
fclose(fp);

}

int riconosciregione(int *(*M),int nr,int nc,int r,int c,int *b,int *h)
{int t;
    if(M[r][c]==0)//se la casella é vuota allora di sicuro non é l'estremo superiore sinistro di un area, possiamo restituire 0
    {
    return 0;
    }
else
    {
    if(M[r][c-1]==1 || M[r-1][c]==1)//se la casella ha un altra casella che appartiene a un area alla sua sinistra o sopra, allora di sicuro non é un estremo sinistro, possiamo ritornare 0
        {
        return 0;
        }
    else
        {t=c;//fissiamo le righe e scansionamo le colonne verso destra per vedere quanto é larga l'area
        while(M[r][t]==1 && t<nc)
            {
            t++;
            b++;//contatore larghezza
            }
        t=r;//fissiamo le colonne
        while(M[t][c]==1 && t<nr)//stesso principio di prima ma con le righe verso il basso
            {
            t++;
            h++;//contatore altezza
            }

        }


    }

return 1;//in questo caso la casella é un estremo superiore sinistro, ne ritorniamo la base e l'altezza by value
}
