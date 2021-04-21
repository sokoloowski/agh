#include <iostream>
#include <string>
using namespace std;

/*
 * Napisz funkcję void fibo1(). Wewnątrz funkcji zadeklaruj tablicę typu int
 * o stałym rozmiarz N i wypełnj ją wartościami ciągu Fibbonaciego.
 * Następnie wypisz na cout
 */
void fibo1();

/*
 * Napisz funkcję void fibo2(int n), która
 *
 * Alokuje pamięć dla tablicy o rozmiarze n za pomocą operatora new
 * Wypełnia ją elementami ciągu Fibbonaciego
 * Wypisuje zawartość na cout
 * Zwalnia pamięć tablicy
 * int*t = new int[10]
 * ...
 * delete []t;
 */
void fibo2(int n);

class Fibo1
{
    int *tab;
    int n;

public:
    /*
     * ustawia n=_n, a następnie alokuje pamięć dla tab (tablicę o rozmiarze n)
     */
    void init(int _n);

    /*
     * usuwa zaalokowaną pamięć
     */
    void destroy();

    /*
     * wypełnia tablicę elementami ciagu
     */
    void fill();

    /*
     * wypisuje zawartość tablicy na cout
     */
    void print();
};

int main()
{
    int x = 7, y = 8;
    std::cout << x << std::endl;
    cout << x << "+" << y << "=" << x + y << endl;
    cin >> x >> y;
    string imie;
    string nazwisko;
    cin >> imie >> nazwisko;
    cout << imie << " " << nazwisko;
    return 0;
}