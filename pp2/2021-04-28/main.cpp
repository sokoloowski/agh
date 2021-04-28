#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

#pragma region Deklaracja klasy

class Vector : public vector<double> {
public:
    /*
     * Konstruktor. Tworzy wektor n-elementowy (jeżeli n>0)
     */
    Vector(int n = 0);

    /*
     * Mnoży każdy element wektora przez arg (inplace)
     */
    Vector &operator*=(double arg);

    /*
     * Dodaje do każdego elementu wektora arg (inplace)
     */
    Vector &operator+=(double arg);

    /*
     * Zwraca wektor, którego elementy są równe sumie
     * wartości elementów danego wektora i argumentu arg
     */
    Vector operator+(double arg) const;

    /*
     * Zwraca wektor, którego elementy są równe iloczynowi
     * wartości elementów danego wektora i argumentu arg
     */
    Vector operator*(double arg) const;

    /*
     * Jeżeli rozmoary są różne wyrzuca wyjątek
     * Dodaje do każdego i-tego elementu danego wektora i-ty element
     * argumentu arg (inplace)
     */
    Vector &operator+=(const Vector &arg);

    /*
     * Jeżeli rozmoary są różne wyrzuca wyjątek
     * Odejmuje od każdego i-tego elementu danego wektora i-ty element
     * argumentu arg (inplace)
     */
    Vector &operator-=(const Vector &arg);

    /*
     * Jeżeli rozmiary są różne wyrzuca wyjątek
     * Mnoży każdy i-ty element danego wektora przez i-ty element
     * argumentu arg (inplace)
     */
    Vector &operator*=(const Vector &arg);


    /*
     * Zwraca wektor, którego elementy są iloczynami odpowiednich elementów
     * danego wektora i argumentu
     * Może wygenerować wyjątek, jeżeli rozmiary są różne (niekoniecznie bezpośrednio)
     */
    Vector operator*(const Vector &arg) const;

    /*
     * Zwraca wektor, którego elementy są równe sumie odpowiednich elementów
     * danego wektora i argumentu
     * Może wygenerować wyjątek, jeżeli rozmiary są różne (niekoniecznie bezpośrednio)
     */
    Vector operator+(const Vector &arg) const;

    /*
     * Zwraca wektor, którego elementy są równe różnicy odpowiednich elementów
     * danego wektora i argumentu
     * Może wygenerować wyjątek, jeżeli rozmiary są różne (niekoniecznie bezpośrednio)
     */
    Vector operator-(const Vector &arg) const;

    /*
     * Zwraca iloczyn skalarny danego wektora i argumentu
     * Może wygenerować wyjątek, jeżeli rozmiary są różne
     */
    double operator|(const Vector &arg) const;

    /*
    * Oblicza sume elementów wektora
    */
    double sum() const;

    /*
     * Oblicza wartość średnią elementów wektora
     */
    double mean() const;

    /*
     * Oblicza odchylenie standardowe
     */
    double std() const;


    /*
     * Zwraca wektor, którego elementy są wynikiem wywołania funkcji apply
     * na elementach oryginalnego wektora
     */

    Vector apply(double (*f)(double)) const;

    /*
     * Zwraca wektor, którego elementy sa równe elementowi danego wektora
     * podniesionymi do potęgi arg
     */
    Vector operator^(double arg) const;

    /*
     * Zwraca wektor o rozmiarz n wypełnionym zerami
     */
    static Vector zeros(int n);

    /*
     * Zwraca wektor o rozmiarz n wypełnionym losowymi wartościami z zakresu 0-1
     */
    static Vector random(int n);

    /*
     * Zwraca wektor wypełniony wartościam z zakresu start (włącznie) do stop (wyłącznie)
     * Różnica kolejnych wartości wynosi step
     */
    static Vector range(double stop, double start = 0, double step = 1);
};

/*
 * Zapisuje zawartość wektora do strumienia os w formacie
 * [v_0, v_1,     v_last]
 */
ostream &operator<<(ostream &os, const Vector &v);

/*
 * Czyta wektor ze strumienia is zapisany w powyższym formacie
 * [v_0, v_1,     v_last]
 */
istream &operator>>(istream &is, Vector &v);

#pragma endregion

#pragma region Implementacja metod

Vector::Vector(int n) : vector<double>(n > 0 ? n : 0) {
}

Vector &Vector::operator*=(double arg) {
    for (auto &e:*this)e *= arg;
    return *this;
}

Vector Vector::operator*(double arg) const {
    Vector ret(*this);
    ret *= arg;
    return ret;
}

Vector &Vector::operator+=(double arg) {
    for (auto &e:*this)e += arg;
    return *this;
}

Vector Vector::operator+(double arg) const {
    Vector ret(*this);
    ret += arg;
    return ret;
}

Vector &Vector::operator*=(const Vector &arg) {
    if (size() != arg.size())throw "bad size";
    for (int i = 0; i < size(); i++)
        (*this)[i] *= arg[i];
    return *this;
}

Vector &Vector::operator+=(const Vector &arg) {
    if (size() != arg.size())throw "bad size";
    for (int i = 0; i < size(); i++)
        (*this)[i] += arg[i];
    return *this;
}

Vector &Vector::operator-=(const Vector &arg) {
    if (size() != arg.size())throw "bad size";
    for (int i = 0; i < size(); i++)
        (*this)[i] -= arg[i];
    return *this;
}

Vector Vector::operator+(const Vector &arg) const {
    Vector ret(*this);
    ret += arg;
    return ret;
}

Vector Vector::operator-(const Vector &arg) const {
    Vector ret(*this);
    ret -= arg;
    return ret;
}

Vector Vector::operator*(const Vector &arg) const {
    Vector ret(*this);
    ret *= arg;
    return ret;
}

double Vector::operator|(const Vector &arg) const {
    Vector ret(*this);
    double res = 0.0;
    if (ret.size() == arg.size()) {
        for (int i = 0; i < ret.size(); i++) {
            res += ret[i] * arg[i];
        }
    } else {
        throw "bad size";
    }
    return res;
}

Vector Vector::zeros(int n) {
    Vector vector;
    for (int i = 0; i < n; i++) {
        vector.push_back(0);
    }
    return vector;
}

Vector Vector::random(int n) {
    Vector vector;
    srand(static_cast <unsigned int>(time(nullptr)));
    for (int i = 0; i < n; i++) {
        vector.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    }
    return vector;
}

Vector Vector::range(double stop, double start, double step) {
    Vector vector;
    for (int i = start; i < stop; i += step) {
        vector.push_back(i);
    }
    return vector;
}

double Vector::sum() const {
    double sum = 0;
    Vector vector(*this);
    for (double e : vector) {
        sum += e;
    }
    return sum;
}

double Vector::mean() const {
    Vector vector(*this);
    return vector.sum() / vector.size();
}

/*
 * Oblicza odchylenie standardowe
 */
double Vector::std() const {
    Vector vector(*this);
    double d = 0,
            mean = vector.mean();
    for (double e : vector) {
        d += pow(e - mean, 2);
    }
    return sqrt(d / mean);
}

/*
 * Zwraca wektor, którego elementy są wynikiem wywołania funkcji apply
 * na elementach oryginalnego wektora
 */
Vector Vector::apply(double (*f)(double)) const {
    Vector vector(*this);
    for (double &e : vector) {
        e = f(e);
    }
    return vector;
}

/*
 * Zwraca wektor, którego elementy sa równe elementowi danego wektora
 * podniesionymi do potęgi arg
 */
Vector Vector::operator^(double arg) const {
    Vector vector(*this);
    for (double &e : vector) {
        e = pow(e, arg);
    }
    return vector;
}

ostream &operator<<(ostream &os, const Vector &v) {
    os << "[";
    for (int i = 0; i < v.size(); i++) {
        if (i != 0)os << ", ";
        os << v[i];
    }
    os << "]";
    return os;
}

istream &operator>>(istream &is, Vector &v) {
    v.clear();
    string s;
    getline(is, s, ']'); // wczytaj do znaku ]
    // zamień (przecinki i nawiasy) , ] na spacje
    replace(s.begin(), s.end(), ',', ' ');
    replace(s.begin(), s.end(), '[', ' ');
    replace(s.begin(), s.end(), ']', ' ');
    istringstream iss(s);
    while (!iss.eof()) {
        // wczytaj liczby double i dodaj do wektora
        double value;
        iss >> value;
        if (!iss)
            break;
        v.push_back(value);
    }
    return is;
}

#pragma endregion

#pragma region Funkcje testujące

static void test_read_write() {
    Vector r = Vector::range(10);
    ostringstream oss;
    oss << r;
    string repr = oss.str();
    cout << repr << endl;
    istringstream iss(repr);
    Vector v;
    iss >> v;
    v *= 2;
    cout << v << endl;
}

static void test_add() {
    int n = 10;
    Vector a = Vector::range(10);
    Vector b = Vector::range(10) * 5 + 2;
    Vector c = a + b;
    cout << c << endl;
    cout << c[1] << endl;
}

// iloczyn skalarny dwóch wektorów
void test_dot() {
    Vector a = Vector::range(10);
    Vector b = Vector::zeros(10) + 2;
    double c = a | b;
    cout << c << endl;
}

// podnoszenie elementów wektora do potęgi
void test_pow() {
    Vector a = Vector::range(10) ^2;
    cout << a << endl;
}

double fun1(double x) {
    cout << exp(log(x)) << endl;
    return x;
}

// wypisuje wektor po zastosowaniu logarytmu, a następnie exp(log(x))
void test_apply() {
    Vector a = Vector::range(10);
    Vector b = a.apply(log);
    cout << b << endl;
    a.apply(fun1);
}

// wypełnia wektor wartościami losowymi z przedziału 0,1
// dodaje -0.5 i mnoży przez 20
// kazdy element przekształca według przepisu exp(-(x^2)/8)
// wyznacza średnią i odchylenie standardowe

double fun2(double x) {
    return exp(-(pow(x, 2))/8);
}

void test_stats() {
    Vector a = Vector::random(10) + (-0.5) * 20;
    a = a.apply(fun2);
    cout << a.mean() << endl;
    cout << a.std() << endl;
}

#pragma endregion

int main() {
    cout << "Test 1" << endl;
    test_read_write();
    cout << endl << "Test 2" << endl;
    test_add();
    cout << endl << "Test 3" << endl;
    test_dot();
    cout << endl << "Test 4" << endl;
    test_pow();
    cout << endl << "Test 5" << endl;
    test_apply();
    cout << endl << "Test 6" << endl;
    test_stats();
    return 0;
}
