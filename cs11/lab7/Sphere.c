#include<math.h>
#include<stdio.h>

int main(){
    const double pi = 3.141592654;
    float r;
    float surface_area,volume;

    printf("Enter radius of the sphere : ");
    scanf("%f",&r);

    surface_area =  4* pi * r * r;
    volume = (4.0/3.0) * pi * r * r * r;

    printf("The volume is %.7f",volume);
    printf(" and the surface area is %.7f",surface_area);
    printf("\n");

    return 0;
}