#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>

using namespace std;

class Array {
    double *data;
    int n;

public:
    Array(int size = 20) : data(0) {
        n = (size >= 0) ? size : 0;
        if (n > 0)
            data = new double[n];
    }

    ~Array() {
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

    /*
     * Zmień kolejność elementów
     * Seed analogicznie, jak dla random
     * powtórz n/2 razy:
     *      wylosuj indeks i
     *      wylosuj indeks j
     *      zamień miejscami data[i] i data[j]
     * */
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

bool Array::linspace(double start, double end) {
    if (start > end)
        return false;
    double range = end - start;
    double jump = range / (this->n - 1);
    for (int i = 0; i < this->n; i++) {
        this->data[i] = jump * i;
    }
    return true;
}

void Array::random(int seed) {
    if (seed == -1)
        srand(time(0));
    else
        srand(seed);
    for (int i = 0; i < this->n; i++)
        this->data[i] = (double) rand() / (RAND_MAX);
}

void Array::write_formatted(ostream &os) const {
    os << this->n /*<< ","*/;
    for (int i = 0; i < this->n; i++)
        os << " " << this->data[i];
    os << endl;
}

void Array::read_formatted(istream &is) {
    if (this->data)
        delete[] this->data;
    is >> this->n;
    this->data = new double[this->n];
    for (int i = 0; i < this->n; i++)
        is >> this->data[i];
}

void Array::add(double v) {
    for (int i = 0; i < this->n; i++)
        this->data[i] += v;
}

void Array::mul(double v) {
    for (int i = 0; i < this->n; i++)
        this->data[i] *= v;
}

void Array::shuffle(int seed) {
    if (seed == -1)
        srand(time(0));
    else
        srand(seed);
    for (int i = 0; i < this->n / 2; i++) {
        int a = rand() * this->n / RAND_MAX;
        int b = rand() * this->n / RAND_MAX;
        swap(this->data[a], this->data[b]);
    }
}

void Array::bubble_sort() {
    int n = this->n - 1;
    while (n > 0) {
        for (int i = 0; i < n; i++)
            if (this->data[i] > this->data[i + 1])
                swap(this->data[i], this->data[i + 1]);
        n--;
    }
}

void Array::qsort() {
    std::qsort(this->data, this->n, sizeof(double),
//               wyrażenie lambda - https://docs.microsoft.com/pl-pl/cpp/cpp/lambda-expressions-in-cpp
               [](const void *a, const void *b) {
                   if (*(double *) a > *(double *) b)
                       return 1;
                   else if (*(double *) a < *(double *) b)
                       return -1;
                   else
                       return 0;
               });
}

bool Array::equals(const Array &other, double tol) {
    for (int i = 0; i < this->n; i++) {
        if (this->n != other.n || fabs(this->data[i] - other.data[i]) > tol)
            return false;
    }
    return true;
}

/*
 * Przetestuj działanie dla różnych start i end kombinacji start i end
 * Wypisuj zawartość tablicy
 */
void test_linspace() {
    Array arr(10);
    for (int i = 1; i <= 10; i++) {
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
void test_random() {
    Array arr(10);
    for (int i = 1; i <= 10; i++) {
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
void test_mul_add() {
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
void test_file_write(const char *nazwa_pliku) {
    Array array(100);
    array.random();
    ofstream os(nazwa_pliku);
    if (!os) {
        cerr << "Błąd otwarcia pliku: " << nazwa_pliku << endl;
        return;
    }
    array.write_formatted(os);
}

/*
 * Przetestuj odczyt z pliku
 * Przeczytaj i wypisz
 */
void test_file_read(const char *nazwa_pliku) {
    Array array(0);
    ifstream is(nazwa_pliku);
    array.read_formatted(is);
    array.write_formatted(cout);
}

/*
 * Utwórz tablicę 10 obiektów typu array
 * Wypełnij je wartościami losowymi z zakresu [i,i+1], gdzie i = 0,...,10
 * Zapisz do pliku liczbę 10
 * W kolejnych wierszach zapisz tab[i]
 */
void test_save_array_2D(const char *file_name) {
    Array *tab = new Array[10];
    ofstream os(file_name);
    if (!os) {
        cerr << "Błąd otwarcia pliku: " << file_name << endl;
        return;
    }
    os << 10 << endl;
    for (int i = 0; i < 10; i++) {
        tab[i].random(i);
        tab[i].add(i);
        tab[i].write_formatted(os);
    }
    delete[]tab;
}

/*
 * Przeczytaj z pliku liczbę tablic
 * Utwórz dynamicznie tablicę obiektów typu Array
 * Przeczytaj z pliku zawartość kolejnych tablic
  */
void test_load_array_2D(const char *file_name) {
    ifstream is(file_name);
    int size;
    is >> size;
    Array *tab = new Array[size];
    for (int i = 0; i < size; i++) {
        tab[i].read_formatted(is);
        tab[i].write_formatted(cout);
    }
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
string load_file(const char *name) {
    ifstream is(name);
    if (!is) {
        cerr << "Bład otwarcia pliku:" << name << endl;
        return "";
    }
    string r;
    for (;;) {
        int c = is.get();
        if (c < 0)
            break;
        r += c;
    }
    return r;
}

/*
 * wykonaj test_save_array_2D, test_load_array_2D i test_save_array_2D - zapisując do dwóch różnych plików
 * porównaj zawartość plików
 */
void test_load_save() {
    test_save_array_2D("plik1.txt");
    test_load_array_2D("plik1.txt");
    test_save_array_2D("plik2.txt");
    string s1 = load_file("plik1.txt");
    string s2 = load_file("plik2.txt");
    cout << (s1 == s2) << endl;
}

/*
 * Zmień kolejność elementów za pomocą shuffle
 * Wypisz
 * Posortuj metodą bubble sort
 * Wypisz
 */
void test_shuffle_bubble_sort() {
    Array arr;
    arr.linspace();
    arr.shuffle();
    arr.write_formatted(cout);
    arr.bubble_sort();
    arr.write_formatted(cout);
}

/*
 * Zmień kolejność elementów za pomocą shuffle
 * Wypisz
 * Posortuj metodą qsort
 * Wypisz
 */
void test_shuffle_qsort() {
    Array arr;
    arr.linspace();
    arr.shuffle();
    arr.write_formatted(cout);
    arr.qsort();
    arr.write_formatted(cout);
}

int main() {
//    test_linspace();
//    test_random();
//    test_mul_add();
//    test_file_write("test.txt");
//    test_file_read("test.txt");

//    test_save_array_2D("test.txt");
//    test_load_array_2D("test.txt");
//    cout << load_file("test2.txt") << endl;
    test_load_save();
    test_shuffle_bubble_sort();
    test_shuffle_qsort();
}