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
     * */
    bool linspace(double start = 0, double end = 1);

    /*
     * wypełnij tablice losowymi elementami z zakresu 0-1
     *
     * Wywołanie srand()
     * jeżeli seed == -1 zainicjuj generator liczb pseudolosowych time(0)
     * w przeciwnym wypadku zainicjuj wartością seed
     * */
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
     * */
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

bool Array::linspace(double start, double end)
{
    if (start > end)
        return false;
    double range = end - start;
    double jump = range / (this->n - 1);
    for (int i = 0; i < this->n; i++)
    {
        this->data[i] = jump * i;
    }
    return true;
}

void Array::random(int seed)
{
    if (seed == -1)
        srand(time(0));
    else
        srand(seed);
    for (int i = 0; i < this->n; i++)
        this->data[i] = ((double)rand() / (RAND_MAX));
}

void Array::write_formatted(ostream &os) const
{
    os << this->n /*<< ","*/;
    for (int i = 0; i < this->n; i++)
        os << " " << this->data[i];
    os << endl;
}

void Array::read_formatted(istream &is)
{
    if (this->data)
        delete[] this->data;
    is >> this->n;
    this->data = new double[this->n];
    for (int i = 0; i < this->n; i++)
        is >> this->data[i];
}

void Array::add(double v)
{
    for (int i = 0; i < this->n; i++)
        this->data[i] += v;
}

void Array::mul(double v)
{
    for (int i = 0; i < this->n; i++)
        this->data[i] *= v;
}

/*
 * Przetestuj działanie dla różnych start i end kombinacji start i end
 * Wypisuj zawartość tablicy
 */
void test_linspace()
{
    Array arr(10);
    for (int i = 1; i <= 10; i++)
    {
        arr.linspace(i, i * 2.34);
        cout << "Test " << i << ": \t";
        arr.write_formatted(cout);
    }
    cout << endl;
}

/*
 * Przetestuj działanie
 * Czy tablica zawiera liczby z właściwego przedziału?
 */
void test_random()
{
    Array arr(10);
    for (int i = 1; i <= 10; i++)
    {
        arr.random(i);
        cout << "Test " << i << ": \t";
        arr.write_formatted(cout);
    }
    cout << endl;
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
    Array arr(10);

    cout << "Test 1: \t";
    arr.random();
    arr.add(4);
    arr.write_formatted(cout);

    cout << "Test 2: \t";
    arr.random();
    arr.add(-0.5);
    arr.mul(20);
    arr.write_formatted(cout);

    cout << "Test 3: \t";
    arr.linspace(0, 100);
    arr.write_formatted(cout);

    cout << "Test 4: \t";
    arr.linspace(0, 10);
    arr.mul(-1);
    arr.write_formatted(cout);
}

/*
 * Przetestuj zapis do pliku
 */
void test_file_write(const char *nazwa_pliku)
{
    Array array(100);
    array.random();
    ofstream os(nazwa_pliku);
    if (!os)
    {
        cerr << "Błąd otwarcia pliku: " << nazwa_pliku << endl;
        return;
    }
    array.write_formatted(os);
}

/*
 * Przetestuj odczyt z pliku
 * Przeczytaj i wypisz
 */

void test_file_read(const char *nazwa_pliku)
{
    Array array(0);
    ifstream is(nazwa_pliku);
    array.read_formatted(is);
    array.write_formatted(cout);
}

int main()
{
    test_linspace();
    test_random();
    test_mul_add();
    test_file_write("test.txt");
    test_file_read("test.txt");
    return 0;
}