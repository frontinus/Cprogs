#include <stdio.h>
#include <stdlib.h>

int main()
{float a,b,c;
scanf("%f%f%f",&a,&b,&c);

if (b*b-1*4*a*c<0)
    printf("non ci sono soluzioni reali");
else
    if(b*b-1*4*a*c>0)
    printf("2 soluzioni reali");
else
    printf("una sola soluzione ");

    return 0;
}
