#include <stdio.h>

int main(void)
{
    double mac1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double mac2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double mac3[3][3];

    for (int w = 0; w < 3; w++)
    {
        for (int k = 0; k < 3; k++)
        {
            mac3[w][k] = mac1[w][k] + mac2[w][k];
            printf("%.0f\t", mac3[w][k]);
        }
        printf("\n");
    }

    return 0;
}