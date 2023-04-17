#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSO 0

typedef enum {
    zaffiro,
    rubino,
    topazio,
    smeraldo,
    errore
} pietre;
typedef enum {
    numero,
    prezzo_pietra,
    occorrenza_consecutiva,
    fatal
} dati;

int verifica(int pietre,int possibilita);
int prezzo(int *sol,int n,int **mark);
void disp_rep(int *sol,int *finalSol,int n,int k,int pos,int **mark,int ripetizione_massima,int *prezzo_finale);

int main() {
    char val[errore]={'S', 'R', 'T', 'E'};
    FILE *fp;
    int *soluzione;
    int *finsol;
    int i,j,lunghezza_massima,price,maxrep;
    int **mark;

    mark=malloc(errore*sizeof(int *));

    for (i=0;i<errore;i++)
        {
        mark[i]=malloc(fatal*sizeof(int));
        }

    fp=fopen("file_informazioni.txt", "r");

    if(fp==NULL)
        {
        printf("problema apertura file");
        return-1;
        }

    fscanf(fp,"%*d");
    while(!feof(fp))
        {
        for (i=0;i<occorrenza_consecutiva;i++)
            {
            for (j=0;j<errore;j++)
                {
                fscanf(fp,"%d",&mark[j][i]);
                mark[j][occorrenza_consecutiva] = 0;
                }
            }
        fscanf(fp,"%d",&maxrep);

        for (i=lunghezza_massima=0; i<errore; i++)
            {
            lunghezza_massima +=mark[i][numero];
            }
        finsol =malloc(lunghezza_massima * sizeof(int));

        for (i=0;i<lunghezza_massima;i++)
            {
            finsol[i]=-1;
            }
        printf("\nSomma: %d\n",lunghezza_massima);

        for (i=1,price=0;i<lunghezza_massima+1;i++)
            {
            soluzione=malloc(i*sizeof(int));

            disp_rep(soluzione,finsol,errore,i,0,mark,maxrep,&price);
            free(soluzione);
            }
        printf("\nLa collana con il prezzo più alto é: %d Euros ed é composta da:\n",price);
        for (i=0;i<lunghezza_massima && finsol[i]!=-1;i++)
            {
            printf("%c ",val[finsol[i]]);
            }
        printf("\nLa massima ripetizione di una pietra é: %d\n", maxrep);
        free(finsol);
        }
    for (i=0;i<errore;i++)
        {
        free(mark[i]);
        }
    free(mark);
    fclose(fp);
    return 0;
}

int verifica(int pietra, int possibilita)
 {
    switch(pietra)
    {
        case zaffiro:
        case topazio:
            switch(possibilita)
            {
                case zaffiro:
                case rubino:
                    return 1;
                default:
                    break;
            }
            break;
        case rubino:
        case smeraldo:
            switch(possibilita)
             {
                case smeraldo:
                case topazio:
                    return 1;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return FALSO;
}
int prezzo(int *sol, int n, int **mark)
 {
    int i;
    int cont;

    for (i = cont= 0; i < n; i++)
        {
        cont += mark[sol[i]][prezzo_pietra];
        }
    return cont;
}
void disp_rep(int *sol,int *solfin,int n,int k,int pos,int **mark,int ripetizione_massima,int *prezzo_finale)
{
    int i;
    int contaZaffiro;
    int contaSmeraldo;

    if(pos >= k)
        {
        for (i = contaSmeraldo = contaZaffiro = 0; i < pos; i++)
            {
            switch(sol[i])
                {
                case zaffiro:
                    contaZaffiro++;
                    break;
                case smeraldo:
                    contaSmeraldo++;
                    break;
                default:
                    break;
                }
            }
        if(contaZaffiro<=contaSmeraldo)
            {
            i=prezzo(sol,pos,mark);
            if(i>*prezzo_finale)
                {
                *prezzo_finale=i;
                for (i=0;i<pos;i++)
                    {
                    solfin[i]=sol[i];
                    }
                }
            }
        return;
        }
    for (i=0;i<n;i++)
        {
        if(mark[i][numero]>0)
            {
            if(pos==0)
                {
                switch(i)
                    {
                    case zaffiro:
                        contaSmeraldo = mark[smeraldo][occorrenza_consecutiva];
                        mark[smeraldo][occorrenza_consecutiva] = 0;
                        mark[i][occorrenza_consecutiva]++;
                        break;
                    case smeraldo:
                        contaZaffiro = mark[zaffiro][occorrenza_consecutiva];
                        mark[zaffiro][occorrenza_consecutiva] = 0;
                        mark[i][occorrenza_consecutiva]++;
                        break;
                    default:
                        break;
                    }
                if(mark[i][occorrenza_consecutiva]<=ripetizione_massima)
                    {
                    mark[i][numero]--;
                    sol[pos]=i;
                    disp_rep(sol, solfin, n, k, pos + 1, mark, ripetizione_massima, prezzo_finale);
                    mark[i][numero]++;
                    }
                switch(i)
                    {
                    case zaffiro:
                        mark[smeraldo][occorrenza_consecutiva] = contaSmeraldo;
                        mark[i][occorrenza_consecutiva]--;
                        break;
                    case smeraldo:
                        mark[zaffiro][occorrenza_consecutiva] = contaZaffiro;
                        mark[i][occorrenza_consecutiva]--;
                        break;
                    default:
                        break;
                    }
                }
            else if (verifica(sol[pos - 1], i) != FALSO)
                {
                switch(i)
                    {
                    case zaffiro:
                        contaSmeraldo = mark[smeraldo][occorrenza_consecutiva];
                        mark[smeraldo][occorrenza_consecutiva] = 0;
                        mark[i][occorrenza_consecutiva]++;
                        break;
                    case smeraldo:
                        contaZaffiro = mark[zaffiro][occorrenza_consecutiva];
                        mark[zaffiro][occorrenza_consecutiva] = 0;
                        mark[i][occorrenza_consecutiva]++;
                        break;
                    default:
                        break;
                    }
                if(mark[i][occorrenza_consecutiva] <= ripetizione_massima)
                    {
                    mark[i][numero]--;
                    sol[pos] = i;
                    disp_rep(sol, solfin, n, k, pos + 1, mark, ripetizione_massima, prezzo_finale);
                    mark[i][numero]++;
                    }
                switch(i)
                    {
                    case zaffiro:
                        mark[smeraldo][occorrenza_consecutiva] = contaSmeraldo;
                        mark[i][occorrenza_consecutiva]--;
                        break;
                    case smeraldo:
                        mark[zaffiro][occorrenza_consecutiva] = contaZaffiro;
                        mark[i][occorrenza_consecutiva]--;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
}
