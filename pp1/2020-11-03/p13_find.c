#include <stdio.h>

int chfind(char ch, char *string)
{
    int i = 0;
    while (*string)
    {
        if (*string == ch)
            i++;
        *string++;
    };
    return i;
}

int strfind(char *word, char *string)
{
    int i = 0;
    char *start = word;
    while (*string)
    {
        word = start;
        if (*string == *word)
        {
            while (*word)
            {
                if (*string++ != *word++)
                    break;
            }
            if (!*word)
                i++;
        }
        else
        {
            *string++;
        }
    };
    return i;
}

// int strpos(char *word, char *string)
// {
//     int i = 0;
//     char *len = string;
//     while (*string)
//     {
//         if (*string == *word)
//         {
//             while (*word)
//             {
//                 if (*string++ != *word++)
//                     break;
//             }
//             if (!*word)
//                 break;
//         }
//         else
//         {
//             *string++;
//         }
//     };
//     i = string - len;
//     return i;
// }

int main(void)
{
    char *ws, tekst[100] = "ala ma kot kota", search = 'a';

    printf("Liczba wystapien \"a\" to %d\n", chfind('a', tekst));
    printf("Liczba wystapien \"kot\" to %d\n", strfind("kot", tekst));
    // printf("%d\n", strpos("kot", tekst));

    return 0;
}