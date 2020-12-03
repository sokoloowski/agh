#include <stdio.h>
#include <stdint.h>

int main(void)
{
    printf("char:\t\t%d\n", sizeof(char));             // 1
    printf("int_fast8_t:\t%d\n", sizeof(int_fast8_t)); // 1
    printf("int:\t\t%d\n", sizeof(int));               // 4
    printf("float:\t\t%d\n", sizeof(float));           // 4
    printf("int32_t:\t%d\n", sizeof(int32_t));         // 4
    printf("long int:\t%d\n", sizeof(long int));       // 8
    printf("int64_t:\t%d\n", sizeof(int64_t));         // 8
    printf("double:\t\t%d\n", sizeof(double));         // 8
    printf("long long:\t%d\n", sizeof(long long));     // 8
    printf("long double:\t%d\n", sizeof(long double)); // 16
    return 0;
}