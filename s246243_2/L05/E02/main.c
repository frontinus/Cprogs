#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct{
int num_musiche;
char **musiche;
}Amico;

int princ_molt(int pos, Amico *val, char **sol, int n, int count);//funzione che genera il powerset secondo il principio di moltiplicazione

int main()
{int A,c=0,i,j;
FILE *fp;
char brano[256],**sol;
Amico *persone;

fp=fopen("brani.txt","r");//apertura file

if(fp==NULL)
    {
    printf("errore file");
    return -1;
    }

fscanf(fp,"%d",&A);

persone=malloc(A*sizeof(Amico));//allocazione dinamica del vettore di struct

for(i=0;i<A;i++)
    {
    fscanf(fp,"%d",&persone[i].num_musiche);//memorizzazione del numero di canzoni del amico in particolare

    persone[i].musiche=malloc(persone[i].num_musiche*sizeof(char));//allocazione dinamica della matrice musiche (numero di colonne)
    for(j=0;j<persone[i].num_musiche;j++)
        {
        persone[i].musiche[j]=malloc(256*sizeof(char));//allocazione di ogni vettore di musiche
        }
    for(j=0;j<persone[i].num_musiche;j++)
        {
        fscanf(fp,"%s",brano);//memorizzazione di una nuova informazione
        persone[i].musiche[j]=realloc(persone[i].musiche[j],strlen(brano));//riallocazione più precisa della lunghezza di ogni vettore
        strcpy(persone[i].musiche[j],brano);//memorizzazione della stringa nella matrice
        }
    }

sol=malloc(A*sizeof(char));//allocazione della matrice di caratteri (futuro vettore di brani di sol)
for(i=0;i<A;i++)
    {
    sol[i]=malloc(256*sizeof(char));//allocazione di ogni suo vettore
    }

c=princ_molt(0,persone,sol,A,0);//funzione che implementa il metodo delle moltiplicazioni

    return 0;
}

int princ_molt(int pos, Amico *val, char **sol, int n, int count)
{ int i;
 if (pos >= n)
    {
    for (i = 0; i < n; i++)
        {
        printf("%s", sol[i]);//si stampa il sottoinsieme di canzoni
        }
    printf("\n");
    return count+1;
    }
  for (i = 0; i < val[pos].num_musiche; i++)
    {
    strcpy(sol[pos],val[pos].musiche[i]);//si memorizza il brano in sol per poterlo stampare
    count = princ_molt(pos+1, val, sol, n, count);//ricorsione
    }
  return count;
  }

