#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *cercaRegexp(char *src, char *regexp);

int main()
{char *testo,*stringaricerca;

printf("inserire testo \n");
scanf("%s",testo);//testo sul quale provare ma regexp
printf("ora regexp\n");
scanf("%s",stringaricerca);//regexp da provare

testo=malloc(strlen(testo)*sizeof(char));//allocazioni dinamiche
regexp=malloc(strlen(testo)*sizeof(char));

cercaRegexp(testo,stringaricerca);//funzione principale



    return 0;
}

char *cercaRegexp(char *src,char *regexp)
    {
    int sizereg,i,j,sizesrc,k=0,flag=1,t=1,l;

    char *solu;//puntatore da restituire alla chiamante

    sizesrc=strlen(src);

    sizereg=strlen(regexp);

    for(j=0;j<sizesrc;j++)
        {
        solu=src+j;//si sposta il puntatore a misura che si avanza nel testo
        k=0;
        flag=1;//flag inizializzato a uno per entrare nel ciclo
        for(i=0;i<sizereg && flag==1;i++)
            {
            if(regexp[i]!=src[j+i])//se si notano divergenze si pone il flag a 0
                {
                flag=0;
                }

            if(regexp[i]=='.')//divergenza acccettabile
                {
                flag=1;
                }

            if(regexp[i]=='\\' && regexp[i+1]=='a' && islower(src[j+i])!=0)//divergenza accettabile
                {
                flag=1;
                i++;
                }

            if(regexp[i]=='\\' && regexp[i+1]=='A' && isupper(src[j+i])!=0)//divergenza accettabile
                {
                flag=1;
                i++;
                }

            if(regexp[i]=='[')//divergenza non accetabile accettabile
                {
                if(regexp[i+1]=='^')
                    {
                    while(regexp[i+t+1]!=']')
                        {
                        t++;
                        }
                    for(l=0;l<t-1;l++)
                        {
                        if(regexp[i+1+t]==src[j+i])
                            {
                            flag=0;
                            }
                        }
                    }

                else
                    {
                    while(regexp[i+t]!=']')//divergenza accettabile
                        {
                        t++;
                        }
                    for(l=0;l<t-1;l++)
                        {
                        if(regexp[i+t]==src[j+i])
                            {
                            flag=1;
                            }
                        }
                    }
                }

            t=1;
            k++;
            }


        if(k==sizereg)//restituisce il puntatore se si é finita la regexp
            {
            return solu;
            }
        else
            {
            return NULL;
            }
        }
    }

