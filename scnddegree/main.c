#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {

float coeff1;
float coeff2;
float coeff3;
}Coeffs;

float calcolodet(float Coeffa,float Coeffb,float Coeffc);

float calcrad1(float Coeffa,float deter,float Coeffb);

float calcrad2(float Coeffa,float deter,float Coeffb);

int main()
{
    Coeffs coefficenti;
    float det;

    printf("Write the coefficients a:b:c\n");
    scanf("%f:%f:%f",&coefficenti.coeff1,&coefficenti.coeff2,&coefficenti.coeff3);
    det=calcolodet(coefficenti.coeff1,coefficenti.coeff2,coefficenti.coeff3);

    if(det<0)
        {
        printf("determinant is below 0\n");
        return -1;
        }
    else
        {
        printf("radice1:%f radice2:%f ",calcrad1(coefficenti.coeff1,det,coefficenti.coeff2),calcrad2(coefficenti.coeff1,det,coefficenti.coeff2));
        }
    return 0;
}


float calcolodet(float Coeffa,float Coeffb,float Coeffc){

return pow(Coeffb,2)-4*Coeffa*Coeffc;

}


float calcrad1(float Coeffa,float deter,float Coeffb){

return (-Coeffb-sqrt(deter))/(2*Coeffa);

}

float calcrad2(float Coeffa,float deter,float Coeffb){

return (-Coeffb+sqrt(deter))/(2*Coeffa);

}

