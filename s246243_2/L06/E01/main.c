#include <stdio.h>
#include <stdlib.h>

typedef struct
{
int u;
int v;
}Archi;//struct nella quale memorizzeremo gli archi

int comb(int pos, int *val, int *sol, int n, int k, int start, int count,int na, Archi *Arch );

int main()
{FILE *fp;
int nvertici,narchi,i,c,*val,*sol,m;
Archi *Arc;//vettore di struct

fp=fopen("grafo.txt","r");//apertura file

if(fp==NULL)
    {
    printf("errore file");
    return -1;
    }

fscanf(fp,"%d %d",&nvertici,&narchi);//memorizzazione dati

Arc=malloc(narchi*sizeof(Archi));//allocazione del vettore di struct

for(i=0;i<narchi;i++)
    {
    fscanf(fp,"%d %d",&Arc[i].v,&Arc[i].u);//memorizzazione nella struct
    }

val=malloc(nvertici*sizeof(int));//allocazione di val

for(i=0;i<nvertici;i++)
    {
    val[i]=i;
    }

for(m=0;m<nvertici;m++)
    {
    sol=malloc(nvertici*sizeof(int));//allocazione di sol
    c=comb(0,val,sol,nvertici,m,0,0,narchi,Arc);//funzione che stampa i vertex cover
    printf("\n");
    }
 fclose(fp);//liberazione di memoria
 free(val);
 free(sol);
    return 0;
}


int comb(int pos, int *val, int *sol, int n, int k, int start, int count,int na, Archi *Arch )//questo algoritmo é un versione adattata di quello delle combinazioni semplici
{
int i,j,**flags,sum=0,flag=1;//flags é una matrice di vettori

flags=malloc(k*sizeof(int));//allocazione di memoria per il numero di vettori




if (pos >= k)
    {
    for (i=0; i<k; i++)
        {
        flags[k]=malloc(na*sizeof(int));//allocazione di memoria per la lunghezza di ogni vettore
        for(j=0;j<na;j++)
            {
            if(sol[i]!=(*(Arch+j)).u && sol[i]!=(*(Arch+j)).v)//prendiamo i pezzi del powerset uno per uno e li confrontiamo con ogni estremo di ogni arco ad ogni iterazione
                {
                flags[i][j]=0;
                }
            else
                {
                flags[i][j]=1;
                }
            }
        }
    for(j=0;j<na;j++)
        {
        for(i=0;i<k;i++)
            {
            sum=sum+flags[i][j];//sommiamo ogni volta le colonne
            }
        if(sum==0)
            {
            flag=0;//se nella colonna non c'é nessun flag allora significa che uno dei numeri del sottoinsieme che stiamo generando non permette al sottoinsieme di essere un vertex cover
            }
        sum=0;
        }

    if(flag==1)//se alla fine il flag é 1 significa che il sotto insieme é un vertex cover
        {
        for(i=0;i<k;i++)
            {
            printf("%d ",sol[i]);
            }
        }

    printf("\n");
    return count+1;
    }
for (i=start; i<n; i++)
    {
    sol[pos] = val[i];
    count = comb(pos+1, val, sol, n, k, i+1, count, na, Arch);//ricorsione
    }

free(flags);//liberazione della memoria
return count;
}
