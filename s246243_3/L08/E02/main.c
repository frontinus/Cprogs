#include <stdio.h>
#include <stdlib.h>

typedef struct{

char color1;
char color2;
int rotazione;
int val1;
int val2;

}tessere;

typedef struct
{

tessere **tes;
int nc,nr;

}scacchiera;

int comb(int pos, int *val, int *sol, int n, int k, int start, int count,scacchiera s1,tessere *solu);
int perm(int pos,tessere *val,tessere *sol,int *mark, int n, int count,scacchiera s);

int main()
{
    FILE *fp1,*fp2;
    int nt,i,j,indice,c=0,*mark,tempi;
    tessere *tiles,*sol;
    scacchiera scac;
    char tempc;

    fp1=fopen("tiles.txt","r");

    if(fp1==NULL)
        {
        printf("problema apertura file tiles");
        return -1;
        }

    fscanf(fp1,"%d",&nt);

    tiles=malloc(nt*sizeof(tessere));

    for(i=0;i<nt;i++)
        {
        tiles[i].rotazione=0;
        }

    for(i=0;i<nt;i++)
        {
        fscanf(fp1,"%c %d %c %d",&tiles[i].color1,&tiles[i].val1,&tiles[i].color2,&tiles[i].val2);
        }

    fclose(fp1);


    fp2=fopen("board.txt","r");

    if(fp2==NULL)
        {
        printf("problema apertura file board");
        return -1;
        }

    fscanf(fp2,"%d %d",&scac.nr,&scac.nc);

    if(scac.nr*scac.nc!=nt)
        {
        printf("incoerenza tra i dati presentati nel file");
        return -1;
        }

    scac.tes=malloc(scac.nr*sizeof(tessere));

    for(i=0;i<scac.nr;i++)
        {
        scac.tes[i]=malloc(scac.nr*sizeof(tessere));
        }

    for(i=0;i<scac.nr;i++)
        {
        for(j=0;j<scac.nc;j++)
            {
            fscanf(fp2,"%d/%d",&indice,&scac.tes[i][j].rotazione);

            if(indice>nt || indice<-1)
                {
                printf("problema con l'indice in posizione %d %d nel file board",i,j);
                return -1;
                }

            if(indice>=0)
                {
                scac.tes[i][j].color1=tiles[indice].color1;
                scac.tes[i][j].color2=tiles[indice].color2;
                scac.tes[i][j].val1=tiles[indice].val1;
                scac.tes[i][j].val2=tiles[indice].val2;
                }
            }
        }

    fclose(fp2);

    sol=malloc(nt*sizeof(tessere));

    mark=malloc(nt*sizeof(tessere));

    for(i=0;i<nt;i++)
        {
        mark[i]=0;
        }

    for(i=0;i<scac.nc;i++)
            {
            for(j=0;j<scac.nr;j++)
                {
                if(scac.tes[i][j].rotazione==1)
                    {
                    tempc=scac.tes[i][j].color1;
                    scac.tes[i][j].color1=scac.tes[i][j].color2;
                    scac.tes[i][j].color2=tempc;

                    tempi=scac.tes[i][j].val1;
                    scac.tes[i][j].val1=scac.tes[i][j].val2;
                    scac.tes[i][j].val2=tempi;
                    scac.tes[i][j].rotazione=0;
                    }
                }
            }

    c=perm(0,tiles,sol,mark,nt,c,scac);

    free(tiles);
    free(sol);
    free(mark);

    for(i=0;i<scac.nr;i++)
        {
        free(scac.tes[i]);
        }
    free(scac.tes);

    return 0;
}


int perm(int pos,tessere *val,tessere *sol,int *mark, int n, int count, scacchiera s)
{
    int i,co,vett[n],vett2[n];

    if (pos >= n)
        {
        for(i=0;i<n;i++)
            {
            vett[i]=i;
            }

        for(co=0;co<n;co++)
            {
            count=comb(0,vett,vett2,n,co,0,count,s,sol);
            }
        }
     for (i=0; i<n; i++)
        if (mark[i] == 0)
            {
            mark[i] = 1;
            sol[pos] = val[i];
            count = perm(pos+1, val, sol, mark, n, count,s);
            mark[i] = 0;
            }
    return count;
}

int comb(int pos, int *val, int *sol, int n, int k, int start, int count,scacchiera s1,tessere *solu)
 {
int i,d=0,flag=1,j,tempi,contatore=0,flag1[s1.nr],flag2[s1.nc],maxpunt=0;
char tempc;
tessere tess[n];



for(i=0;i<n;i++)
    {
    tess[i]=solu[i];
    }

if (pos >= k)
    {
    for(i=0;i<k;i++)
        {
        for(j=0;j<n;j++)
            {
            if(sol[i]==j)
                {
                tempc=tess[j].color1;
                tess[j].color1=tess[j].color2;
                tess[j].color2=tempc;


                tempi=tess[j].val1;
                tess[j].val1=tess[j].val2;
                tess[j].val2=tempi;
                }
            }
        }

    for(i=0;i<s1.nr;i++,d++)
        {
        for(j=0;j<s1.nc;j++,d++)
            {
            if((s1.tes[i][j].color1!=tess[d].color1) || (s1.tes[i][j].color2!=tess[d].color2) || (s1.tes[i][j].val1!=tess[d].val1) || (s1.tes[i][j].val2!=tess[d].val2))
                {
                flag=0;
                }
            }
        }

    for(i=0;i<s1.nr;i++)
        {
        d=i*s1.nc;
        while((tess[d].color1==tess[d+1].color1) && (d< i*s1.nc-1))
            {
            d++;
            }
        if(d!=i*s1.nc-1)
            {
            flag1[i]=0;
            }
        }
    for(i=0;i<s1.nc;i++)
        {
        d=i;
        while((tess[d].color2==tess[d+s1.nc].color2) && d<i+s1.nc*(s1.nr-1))
            {
            d=d+s1.nc;
            }
        if(d!=i+s1.nc*(s1.nr-1))
            {
            flag2[i]=0;
            }
        }
    d=0;
    for(i=0;s1.nr;i++,d++)
        {
        if(flag1[i]==1)
            {
            for(j=0;j<s1.nc;j++,d++)
                {
                contatore=contatore+tess[d].val1;
                }
            }
        else
            {
            d=d+s1.nc;
            }
        }

    for(i=0;s1.nc;i++,d++)
        {
        if(flag2[i]==1)
            {
            for(j=0;j<s1.nc*(s1.nr-1);j=j+s1.nc)
                {
                contatore=contatore+tess[i+j].val2;
                }
            }
        }

    if(contatore>maxpunt)
        {
        maxpunt=contatore;
        }
    else
        {
        flag=0;
        }
    if(flag==1)
        {
        for(i=0;i<n;i++)
            {
            printf("\ncolore1:%c valore1:%d colore2:%c valore2:%d\n",tess[i].color1,tess[i].val1,tess[i].color2,tess[i].val2);
            }
        }
    printf("\n\n");
    return count+1;
    }
for (i=start; i<n; i++)
    {
    sol[pos] = val[i];
    count = comb(pos+1, val, sol, n, k, i+1, count,s1,solu);
    }
return count;
}
