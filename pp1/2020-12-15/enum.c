#include <stdio.h>

enum liczby {
    zero = 0,
    jeden,
    dwa,
    trzy,
    cztery
};

int main(void) {
    enum liczby l;
    l = dwa;
    if (l < trzy) printf("3 < 2\n------------\n");

    for (enum liczby i = zero; i <= cztery; i++) {
        printf("%d", i);
        if (i == trzy) printf(" == trzy");
        if (i <= jeden) printf(" <= jeden");
        printf("\n");
    }
}