#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct{
int num_musiche;
char **musiche;
}Amico;

int princ_molt(int pos, Amico *val, char **sol, int n, int count);

int main()
{int A,c=0,i,j;
FILE *fp;
char brano[256],**sol;
Amico *persone;

fp=fopen("brani.txt","r");

if(fp==NULL)
    {
    printf("errore file");
    return -1;
    }

fscanf(fp,"%d",&A);

persone=malloc(A*sizeof(Amico));

for(i=0;i<A;i++)
    {
    fscanf(fp,"%d",&persone[i].num_musiche);

    persone[i].musiche=malloc(persone[i].num_musiche*sizeof(char));
    for(j=0;j<persone[i].num_musiche;j++)
        {
        persone[i].musiche[j]=malloc(256*sizeof(char));
        }
    for(j=0;j<persone[i].num_musiche;j++)
        {
        fscanf(fp,"%s",brano);
        persone[i].musiche[j]=realloc(persone[i].musiche[j],strlen(brano));
        strcpy(persone[i].musiche[j],brano);
        }
    }

sol=malloc(A*sizeof(char));
for(i=0;i<A;i++)
    {
    sol[i]=malloc(256*sizeof(char));
    }

c=princ_molt(0,persone,sol,A,0);

    return 0;
}

int princ_molt(int pos, Amico *val, char **sol, int n, int count)
{ int i;
 if (pos >= n)
    {
    for (i = 0; i < n; i++)
        {
        printf("%s", sol[i]);
        }
    printf("\n");
    return count+1;
    }
  for (i = 0; i < val[pos].num_musiche; i++)
    {strcpy(sol[pos],val[pos].musiche[i]);
    count = princ_molt(pos+1, val, sol, n, count);
    }
  return count;
  }

