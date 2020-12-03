// NIE DZIAŁA

#include <stdio.h>

int main(void)
{
    int arr[] = {5, 992, 32, 72, 1112, 132, 4, 24, 4, 8}, *ws, *ws2, *lim, tmp;
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    ws = ws2 = lim = arr;
    ws2++;
    while (lim - arr < arr_size)
    {
        while ((ws - arr < arr_size) && (ws2 - arr < arr_size))
        {
            if (*ws > *ws2)
            {
                tmp = *ws;
                *ws = *ws2;
                *ws2 = tmp;
            }
            ws += 2;
            ws2 += 2;
        }
        lim++;
    }

    for (int i = 0; i < arr_size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}