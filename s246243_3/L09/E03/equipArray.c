#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipArray.h"
#include "invArray.h"

struct tabEquip_t
{
int inUso;
int vetteq[8];

};

void equipaggia(int indice,tabeq t)
{

if(t->inUso<8)
    {
    t->vetteq[t->inUso]=indice;
    t->inUso++;
    return;
    }
else
    {
    printf("sono già equipaggiati 8 item");
    return;
    }
return;
}

void cancellazione(char *nome,tabeq t,tabinv t1)
{
int i,k;

for(i=0;i<t->inUso;i++)
    {
    if(confronto(nome,i,t1)==0)
        {
        for(k=i;k<t->inUso;k++)
            {
            t->vetteq[k]=t->vetteq[k+1];
            }
        t->inUso--;
        return;
        }
    }
return;
}




void stampa_stat_equip(int indice,tabeq t,tabinv t2)
{

stampa_stat_equip2(t->vetteq[indice],t2);

return;

}
