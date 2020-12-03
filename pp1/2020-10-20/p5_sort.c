#include <stdio.h>

int main(void)
{
    int A[] = {5, 992, 32, 72, 1112, 132, 4, 24, 4, 8};
    int n = sizeof(A) / sizeof(A[0]);

    while (n > 0)
    {
        for (int _i = 0; _i < n - 1; _i++)
        {
            if (A[_i] > A[_i + 1])
            {
                int temp = A[_i];
                A[_i] = A[_i + 1];
                A[_i + 1] = temp;
            }
        }
        n--;
    }

    n = sizeof(A) / sizeof(A[0]);
    for (int _i = 0; _i < n; _i++)
        printf("%d\n", A[_i]);
    return 0;
}
