#include <stdio.h>
#define SIZE 4

int main(void)
{
    double mac1[SIZE][SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    double mac2[SIZE][SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    // double mac2[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double mac3[SIZE][SIZE];

    for (int w = 0; w < SIZE; w++)
    {
        for (int k = 0; k < SIZE; k++)
        {
            for (int i = 0; i < SIZE; i++)
            {
                mac3[w][k] += mac1[w][i] * mac2[i][k];
            }
            printf("%.0f\t", mac3[w][k]);
        }
        printf("\n");
    }

    return 0;
}