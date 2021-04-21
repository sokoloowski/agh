#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

/*
 * Ten program jest rozbudowywany w lab3.cpp
 * Możesz pominąć tę labkę i robić od razu 3
 */

class Array
{
    double *data;
    int n;

public:
    Array(int size = 20) : data(0)
    {
        n = (size >= 0) ? size : 0;
        if (n > 0)
            data = new double[n];
    }
    ~Array()
    {
        if (data)
            delete data;
    }

    /*
     * wypełnij tablice równomiernie rozłożonymi elementami od start to end
     * Funkcja zwraca false, jeżeli end<start
     */
    bool linspace(double start = 0, double end = 1);

    /*
     * wypełnij tablice losowymi elementami z zakresu 0-1
     *
     * Wywołanie srand()
     * jeżeli seed == -1 zainicjuj generator liczb pseudolosowych time(0)
     * w przeciwnym wypadku zainicjuj wartością seed
     */
    void random(int seed = -1);

    /*
     * zapis do strumienia wyjściowego w formacie:
     * n, ciąg n liczb typu double
     */
    void write_formatted(ostream &os) const;

    /*
     * Zwolnij pamięć
     * Przeczytaj n
     * Przydziel pamięć
     * Przeczytaj liczby
     */
    void read_formatted(istream &is);

    /*
     * Dodaj do każdego elementu tablicy wartość v
     */
    void add(double v);

    /*
     * Pomnóż każdy element tablicy przez wartość v
     */
    void mul(double v);
};

#pragma region Implementacje metod klasy Array

bool Array::linspace(double start, double end)
{
    if (start > end)
        ...
}

void Array::random(int seed)
{
    if (seed == -1)
    {
        srand(time(0));
    }
    else
    {
        srand(seed);
    }
    // ...
}

void Array::write_formatted(ostream &os) const
{
    // code...
}

void Array::read_formatted(istream &is)
{
    // zwolnij pamięć
    // wczytaj n
    // zaalokuj pamięć
    // wczytaj dane
}

void Array::add(double v)
{
    // code...
}

void Array::mul(double v)
{
    // code...
}

#pragma endregion

#pragma region Funkcje testujące

/*
 * Przetestuj działanie dla różnych start i end kombinacji start i end
 * Wypisuj zawartość tablicy
 */
void test_linspace()
{
    // code...
}

/*
 * Przetestuj działanie
 * Czy tablica zawiera liczby z właściwego przedziału?
 */
void test_random()
{
    // code...
}

/*
 * Przetestuj mul i add, tak aby wygenerować
 * - tablicę losowych wartości z zakresu [4,5]
 * - tablicę losowych wartości z zakresu [-10,10]
 * - tablicę kolejnych, równomiernie rozłozonych wartości od 0 do 100
 * - tablicę wartości od 0 do -10
 */
void test_mul_add()
{
    // code...
}

/*
 * Przetestuj zapis do pliku
 */
void test_file_write(const char *nazwa_pliku)
{
    Array array(100);
    // wypełnij wartościami
    ofstream os(nazwa_pliku);
    if (!os)
    {
        cerr << "Błąd otwarcia pliku: " << nazwa_pliku << endl;
        return;
    }
    // ... zapisz array do strumienia os
}

/*
 * Przetestuj odczyt z pliku
 * Przeczytaj i wypisz
 */
void test_file_read(const char *nazwa_pliku)
{
    Array array(0);
}

#pragma endregion

int main()
{
    return 0;
}