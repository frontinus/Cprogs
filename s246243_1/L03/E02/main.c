#include <stdio.h>
#include <stdlib.h>
void StampaCodifica(void *p,int size,int BigEndian);
int main()
{float af;

double ad;

int dimby[2],dimbi[2],i,BE,x=1;

char *y=(char*)&x;//puntatore y all'indirizzo di memoria di x

dimby[0]=sizeof(af);//numero di bytes di af
dimby[1]=sizeof(ad);//numero di bytes di ad

printf("scrivere 2 volte lo stesso numero in questo modo : numero_numero ");

scanf("%f_%lf",&af,&ad);

for(i=0;i<2;i++)
    {
        dimbi[i]=8*dimby[i];//salva il numero di bits di af e ad
    }

if(*y==0)//se il valore puntato da y é 0...
    {
        BE=1;//Big Endian, poiché significa che il MSB si trova nella cella di memoria più bassa
    }
else
    {
        BE=0;//Little Endian per esculsione
    }
StampaCodifica((void *)&af,dimbi[0],BE);

StampaCodifica((void *)&ad,dimbi[1], BE);

return 0;
}


void StampaCodifica(void *p,int size, int BigEndian)
{
char *d;

d=p;//operazione necessaria nell'intento di manipolare *p

unsigned int bits1[32],bits2[64];//vettori che contengoni i bits organizzati in segno-esponente-mantissa per visualizzarli alla fine

int i,j,k=0;//k contatore utile per riempire il vettore


if(size==32) //rappresentazione float
    {
    if(BigEndian==0)//rappresentazione float nel caso LE
        {
        printf("Rappresentazione Little Endian\n");

        for(i=3;i>=0;i--)//i float hanno 4 bytes, se sono codificati in LE li facciamo scorrere al rovescio
            {for(j=7;j>=0;j--)// 1 byte=8 bits
                {
                bits1[k]=*(d+i)>>j & 0b00000001;//restituisce 1 se l'ultimo bit del byte *(d+i) é 1 e 0 altrimenti,andiamo a registrare ogni volta il risultato in bits1
                k++;
                }
            }

        printf("rappresentazione della codifica interna");//si stampa tutto

        for(i=0;i<32;i++)
            {
            printf("%u",bits1[i]);
            }

        printf("\n bit di segno:%u",bits1[0]);//stampa segno

        printf("\n esponente:");

        for(i=1;i<9;i++)
            {printf("%u",bits1[i]);}//stampa esponente

        printf("\n Mantissa:");

        for(i=9;i<32;i++)
            {printf("%u",bits1[i]);}//stampa mantissa
        }
    else
        {
        printf("Rappresentazione Big Endian\n");//float in caso BE

        for(i=0;i<4;i++)
            {
            for(j=8;j>0;j--)
                {
                bits1[k]=*(d+i)>>j & 0b00000001;
                k++;
                }
            }
        printf("rappresentazione della codifica interna");//si stampa tutto

        for(i=0;i<32;i++)
            {
            printf("%u",bits1[i]);
            }

        printf("\n bit di segno:%u",bits1[0]);//stampa segno

        printf("\n esponente:");

        for(i=1;i<9;i++)
            {printf("%u",bits1[i]);}//stampa esponente

        printf("\n Mantissa:");

        for(i=9;i<32;i++)
            {printf("%u",bits1[i]);}//stampa mantissa
        }


    }


else //rappresentazione double
    {
    if(BigEndian==0)//double se LE
        {
        printf("\nRappresentazione Little Endian:\n");

        for(i=7;i>=0;i--)//i double hanno 8 bytes, se sono codificati in LE li facciamo scorrere al rovescio
            {
            for(j=7;j>=0;j--)
                {
                bits2[k]=*(d+i)>>j & 0b00000001;//stesso principio di prima
                k++;
                }
            }
        printf("rappresentazione della codifica interna");//stampa tutto
        for(i=0;i<64;i++)
            {
            printf("%u",bits2[i]);
            }

        printf("\n bit di segno:%u",bits2[0]);//segno

        printf("\n esponente:");

        for(i=1;i<12;i++)
            {printf("%u",bits2[i]);}//esponente

        printf("\n Mantissa:");

        for(i=12;i<64;i++)
            {printf("%u",bits1[i]);}//mantissa

        }
    else
        {
        printf("\nRappresentazione Big Endian\n"); //Double se BE

        for(i=0;i<8;i++)
            {
            for(j=7;j>0;j--)
                {
                bits2[k]=*(d+i)>>j & 0b00000001;//sempre lo stesso principio
                k++;
                }
            }
        printf("rappresentazione della codifica interna");//stampa tutto
        for(i=0;i<64;i++)
            {
            printf("%u",bits2[i]);
            }

        printf("\n bit di segno:%u",bits2[0]);//segno

        printf("\n esponente:");

        for(i=1;i<12;i++)//esponente
            {printf("%u",bits2[i]);}

        printf("\n Mantissa:");

        for(i=12;i<64;i++)//mantissa
            {printf("%u",bits1[i]);}
        }
    }
return;
}
