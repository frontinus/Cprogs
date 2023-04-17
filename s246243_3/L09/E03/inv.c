#include <stdio.h>
#include <stdlib.h>
#include "inv.h"

void salvainv(inv_t *vett,int dim)
{

int i;
FILE *fp;

fp=fopen("inventori.txt","r");

for(i=0;i<dim;i++)
    {
    fscanf(fp,"%s %s %d %d %d %d %d %d",vett[i].nome,vett[i].tipologia,&vett[i].statistiche.hp,&vett[i].statistiche.mp,&vett[i].statistiche.atk,&vett[i].statistiche.def,&vett[i].statistiche.mag,&vett[i].statistiche.spr);
    }
fclose(fp);
return;
}
