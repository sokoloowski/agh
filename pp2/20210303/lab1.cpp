#include <iostream>
#include <string>
#define DEFINICJA 3

using namespace std;

#pragma region Zadanie_1
void zadanie1()
{
    int x = 7,
        y = 8;
    cout << x << endl;
    cin >> x >> y;
    string imie;
    string nazwisko;
    cin >> imie >> nazwisko;
    cout << imie << " " << nazwisko;
}
#pragma endregion

#pragma region Zadanie_2
void fibo1()
{
    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13};
    for (int _i = 0; _i < 8; _i++)
    {
        cout << arr[_i] << endl;
    }
}
#pragma endregion

#pragma region Zadanie_3
void fibo2(int n)
{
    int *arr = new int[n];
    arr[0] = 0;
    if (n > 1)
        arr[1] = 1;
    for (int _i = 2; _i < n; _i++)
    {
        arr[_i] = arr[_i - 1] + arr[_i - 2];
    }
    for (int _i = 0; _i < n; _i++)
    {
        cout << arr[_i] << endl;
    }
    delete[] arr;
}
#pragma endregion

#pragma region Zadanie_4
class Fibo1
{
    int *arr;
    int n;

public:
    void init(int _n);
    void destroy();
    void fill();
    void print();
};

void Fibo1::init(int n)
{
    if (n <= 0)
        Fibo1::arr = 0;
    else
    {
        Fibo1::n = n;
        Fibo1::arr = new int[Fibo1::n];
    }
}

void Fibo1::destroy()
{
    delete[] Fibo1::arr;
}

void Fibo1::fill()
{
    Fibo1::arr[0] = 0;
    if (Fibo1::n > 1)
        Fibo1::arr[1] = 1;
    for (int _i = 2; _i < Fibo1::n; _i++)
    {
        Fibo1::arr[_i] = Fibo1::arr[_i - 1] + Fibo1::arr[_i - 2];
    }
}

void Fibo1::print()
{
    for (int _i = 0; _i < Fibo1::n; _i++)
    {
        cout << Fibo1::arr[_i] << endl;
    }
}

void test_fibo1()
{
    Fibo1 fibo1;
    fibo1.init(11);
    fibo1.fill();
    fibo1.print();
    fibo1.destroy();
}
#pragma endregion

#pragma region Zadanie_5
class Fibo
{
    int *arr;
    int n;

public:
    Fibo(int n);
    void fill();
    void print();
    ~Fibo();
};

Fibo::Fibo(int _n)
{
    if (_n <= 0)
        arr = 0;
    else
    {
        n = _n;
        arr = new int[n];
    }
}

Fibo::~Fibo()
{
    delete[] arr;
}

void Fibo::fill()
{
    Fibo::arr[0] = 0;
    if (Fibo::n > 1)
        Fibo::arr[1] = 1;
    for (int _i = 2; _i < Fibo::n; _i++)
    {
        Fibo::arr[_i] = Fibo::arr[_i - 1] + Fibo::arr[_i - 2];
    }
}

void Fibo::print()
{
    for (int _i = 0; _i < Fibo::n; _i++)
    {
        cout << Fibo::arr[_i] << endl;
    }
}

void test_fibo()
{
    Fibo fibo(12);
    fibo.fill();
    fibo.print();
}
#pragma endregion

#pragma region Zadanie_6
class ArithmeticSequence
{
    double *arr;
    int n;
    double first, r;

public:
    ArithmeticSequence(int n, double first, double r);
    void fill();
    void print();
    ~ArithmeticSequence();
};

ArithmeticSequence::ArithmeticSequence(int _n, double _first, double _r)
{
    n = _n;
    first = _first;
    r = _r;
    arr = new double[n];
}

ArithmeticSequence::~ArithmeticSequence()
{
    delete[] arr;
}

void ArithmeticSequence::fill()
{
    ArithmeticSequence::arr[0] = ArithmeticSequence::first;
    for (int _i = 1; _i < ArithmeticSequence::n; _i++) {
        ArithmeticSequence::arr[_i] = ArithmeticSequence::arr[_i - 1] + ArithmeticSequence::r;
    }
}

void ArithmeticSequence::print()
{
    for (int _i = 0; _i < ArithmeticSequence::n; _i++)
    {
        cout << ArithmeticSequence::arr[_i] << endl;
    }
}

void test_as() {
    ArithmeticSequence arithmeticSequence(10, 2.1, 3.1);
    arithmeticSequence.fill();
    arithmeticSequence.print();
}
#pragma endregion

int main()
{
    // zadanie1();
    // fibo1();
    // fibo2(10);
    // test_fibo1();
    // test_fibo();
    test_as();
    return 0;
}