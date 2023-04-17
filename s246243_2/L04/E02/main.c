#include <stdio.h>
#include <stdlib.h>

int majority( int *a, int N);


int ricerca( int *v, int p, int r, int *magg);

int main()
{int *vett,n,i=0;

 printf("indicare di che lunghezza deve essere il vettore\n");

 scanf("%d",&n);//memorizzazione della lunghezza del vettore

 vett=malloc(n*sizeof(int));//allocazione del vettore

 printf("\n inserire i %d valori\n",n);

 for(i=0;i<n;i++)
    {
    scanf("%d",&vett[i]);//rimempimento del vettore
    }
 printf("\necco il vettore:\n");

 for(i=0; i<n; i++)
    {
    printf("%d ",vett[i]);
    }

 majority(vett,n);//chiamata alla funzione majority

 return 0;
}

int majority(int *a,int N)
{
int maggioritario,contmaggioritario;

contmaggioritario=ricerca(a,0,N-1,&maggioritario);//chiamata alla funzione ricerca


if(contmaggioritario>=N/2)
    {
    printf("\nmaggioritario: %d",maggioritario);//ferifica se il numero � maggioritario prima di stamparlo
    return contmaggioritario;
    }
else
    {
    printf("\nnon c'� maggioritario");
    return -1;
    }

}


int ricerca( int *v, int p, int r, int *magg)//ricerca in loco di complessit� nlog(n)
{
    int i,maggl,maggr,contmaggl,contmaggr;

    if(p==r)
        {
        *magg=v[p];//se la caselle pi� a destra del vettore � anche quella pi� a sinistra (cio� � rimasta solo una casella)si salva il valore della casella nel magg � viene rimandata alla chimante tramite puntatore
        return 1;
        }

    int m=(r+p)/2;//calcolo celle di mezzo del vettore
    contmaggl=ricercadicotomica(v,p,m,&maggl);//ricorsione sulla parte sinistra del vettore
    contmaggr=ricercadicotomica(v,m+1,r,&maggr);//ricorsione sulla parte destra

    for(i=p;i<=m;i++)
        {
        if(maggr==v[i])
            {
            contmaggr++;//contatore per verificare quante volte appare il maggioritario momentaneo nel sottovettore
            }
        }


    for(i=m+1;i<=r;i++)
        {
        if(maggl==v[i])
            {
            contmaggl++;//stesso scopo ma nell'altro sottovettore
            }
        }

    if(contmaggl>=contmaggr)
        {
        *magg=maggl;//verifica quali dei due � il maggioritario e ne rimanda il conto alla chiamante tramite il risultato e il maggioritario tramite puntatore
        return contmaggl;
        }
    else
        {
        *magg=maggr;//stessa cosa ma nell'altra ipotesi
        return contmaggr;
        }
}
