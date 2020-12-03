#include <stdio.h>

double f1(double a, double b)
{
    double w;
    w = a + b;
    return w;
}

int main(void)
{
    double z1, z2;
    z1 = 5;
    z2 = f1(2, z1);
    printf("%lf\n", z2);
    return 0;
}