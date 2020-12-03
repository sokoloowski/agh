#include <stdio.h>

void wypisz(int *t, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", t[i]);
    printf("\n");
}

void sortuj(int *t, int len)
{
    int n = len - 1;
    while (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (t[i] > t[i + 1])
            {
                int tmp = t[i];
                t[i] = t[i + 1];
                t[i + 1] = tmp;
            }
        }
        n--;
    }
}

int main(void)
{
    int arr[10] = {5, 992, 32, 72, 1112, 132, 4, 24, 4, 8};
    sortuj(arr, 10);
    wypisz(arr, 10);
    return 0;
}