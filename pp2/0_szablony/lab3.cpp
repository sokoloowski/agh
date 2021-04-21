#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

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

    /*
     * Zmień kolejność elementów
     * Seed analogicznie, jak dla random
     * powtórz n/2 razy:
     *      wylosuj indeks i
     *      wylosuj indeks j
     *      zamień miejscami data[i] i data[j]
     */
    void shuffle(int seed = -1);

    /*
     * Posortuj - sortowanie bąbelkowe
     */
    void bubble_sort();

    /*
     * Posortuj za pomocą bibliotecznej funkcji qsort
     */
    void qsort();

    /*
     * porównuje elementy
     * zwraca false jeżeli
     *    - długości tablic są różne
     *    - dla któregoś z elementów zachodzi |data[i] - other.data[i]|>tol
     */
    bool equals(const Array &other, double tol = 1e-10);
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

void Array::shuffle(int seed)
{
    // wywołaj srand() jak dla random
}

void Array::bubble_sort()
{
    // code...
}

void Array::qsort()
{
    // code...
}

bool Array::equals(const Array &other, double tol)
{
    return true;
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

/*
 * Utwórz tablicę 10 obiektów typu array
 * Wypełnij je wartościami losowymi z zakresu [i,i+1], gdzie i = 0,...,10
 * Zapisz do pliku liczbę 10
 * W kolejnych wierszach zapisz tab[i]
 */
void test_save_array_2D(const char *file_name)
{
    Array *tab = new Array[10];

    delete[] tab;
}

/*
 * Przeczytaj z pliku liczbę tablic
 * Utwórz dynamicznie tablicę obiektów typu Array
 * Przeczytaj z pliku src_file_name zawartość kolejnych tablic
 * Zapisz do pliku target_file_name
 */
void test_copy_array_2D(const char *target_file_name, const char *src_file_name)
{
    // code...
}

/*
 * Otwórz plik
 * Sprawdz, czy się udało
 * wczytaj kolejne znaki i dodawaj do obiektu klasy string
 * w petli nieskończonej wykonaj
 *     int c = is.get();
 *     if(c<0)break;
 *     dodaj c do stringu
 * zwróć string
 */
string load_file(const char *name)
{
    ifstream is(name);
    if (!is)
    {
        cerr << "Bład otwarcia pliku:" << name << endl;
        return "";
    }
    string r;
    for (;;)
    {
        //...
    }
    return r;
}

/*
 * wykonaj test_save_array_2D, test_load_array_2D i test_save_array_2D - zapisując do dwóch różnych plików
 * porównaj zawartość plików
 */
void test_load_save()
{
    string s1 = load_file("plik1.txt");
    string s2 = load_file("plik2.txt");
    cout << (s1 == s2);
}

/*
 * Zmień kolejność elementów za pomocą shuffle
 * Wypisz
 * Posortuj metodą bubble sort
 * Wypisz
 */
void test_shuffle_bubble_sort()
{
    // code...
}

/*
 * Zmień kolejność elementów za pomocą shuffle
 * Wypisz
 * Posortuj metodą qsort
 * Wypisz
 */
void test_shuffle_qsort()
{
    // code...
}

#pragma endregion

int main()
{
    return 0;
}