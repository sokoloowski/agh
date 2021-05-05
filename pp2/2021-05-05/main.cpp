#include <iostream>
#include <cstdio>
#include <cstring>
#include <exception>

using namespace std;

#pragma region Deklaracja

class bad_index : public std::exception {
};

class String {
    /*
     * txt to wskażnik na tablice znaków o pojemności capacity,
     * czyli zdolną pomieścić capacity-1 znaków. Zawsze pamiętaj o miejscu na znak 0 na końcu
     * długość tekstu nie musi być przechowywana, używamy funkcji strlen()
     */
    char *txt = 0;
    int capacity = 0;
public:
    /*
     * Konstruktor - jeżeli tekst niezerowy, przydziela pamięć
     */
    String(const char *_txt = "");

    /*
     * Destruktor
     */
    ~String() { free(); }

    /*
     * Konstruktor kopiujący
     */
    String(const String &other) { copy(other); }

    /*
     * Operator przypisania.
     * Dodajmy optymalizację: jeżeli other.txt zmieści się w txt, nie zwalniajmy pamięci
     * jeżeli nie zmieści się: stosujemy free + copy
     */
    String &operator=(const String &other);

    /*
     *  Dostęp do znaku, może generować wyjątek bad_index;
     */
    char &operator[](int idx);

    /*
     * Dodaje tekst na końcu może rozszerzać tekst
     */
    String &operator+=(const char *_txt);

    /*
     * Zwraca obiekt String, którego zawartość jest konkatenacją obu tekstów
     */
    String operator+(const char *_txt) const;

    /*
     * Dodaje znak na końcu, może rozszerzać długość tablicy
     */
    String &operator+=(char c);

    /*
     * Zwraca nowy obiekt zawierający tekst ze znakiem na końcu
     */
    String operator+(char c) const;

    /*
     * Dodaje na końcu tektową reprezentację arg. Użyj funkcji sprintf()
     */
    String &operator+=(int arg);

    /*
     * Zwraca nowy obiekt zawierający tekst z dodaną tekstową reprezentacją argumentu
     */
    String operator+(int arg) const;

    /*
     * Dodaje na końcu tektową reprezentację arg. Użyj funkcji sprintf()
     */
    String &operator+=(double arg);

    /*
     * Zwraca nowy obiekt zawierający tekst z dodaną tekstową reprezentacją argumentu
     */
    String operator+(double arg) const;

    /*
     * Zwraca nowy obiekt zawierający zawartość wzorca (this->txt) powtórzoną n razy i sklejoną
     */
    String operator*(int n) const;

    /*
     * Jeżeli txt jest wskaźnikiem o wartości zerowej (nullptr) zwraca ""
     * w przeciwnym przypadku zwraca ptr
     */
    operator const char *() const;

    /*
     * Porównanie zawartości
     */
    bool operator==(const char *_txt) const;

    bool operator!=(const char *_txt) const {
        return !(*this == _txt);
    }

    /*
     * Porównanie leksykograficzne, użyj strcmp()
     */
    bool operator<(const char *txt) const;

    /*
     * Zwraca rozmiar (nie licząc znaku 0 na końcu). Jeżeli is_empty() zwraca 0;
     */
    int size() const;

    /*
     * Zwraca capacity
     */
    int get_capacity() const { return capacity; }

    /*
     * Test czy tekst jest pusty
     */
    bool is_empty() const { return !txt || !*txt; }

protected:
    /*
     * Zwalnia pamięć, zeruje zmienne
     */
    void free();

    /*
     * Kopiuje zawartość do pustego stringu
     */
    void copy(const String &other);

    /*
     * Rozszerza pamięć tablicy do rozmiaru równego co najmniej newcapacity
     * Implementuje własną logikę...
     */
    void reserve(int newcapaicty);
};

#pragma endregion

#pragma region Implementacja metod

String::String(const char *_txt) {
    if (_txt != nullptr) {
        this->reserve(strlen(_txt));
        this->txt = new char[this->get_capacity()];
        for (int i = 0; i < this->get_capacity(); i++) {
            this->txt[i] = _txt[i];
        }
    } else {
        txt = 0;
        capacity = 0;
    }
}

/*
 * Operator przypisania
 * Dodajmy optymalizację: jeżeli other.txt zmieści się w txt, nie zwalniajmy pamięci
 * jeżeli nie zmieści się: stosujemy free + copy
 */
String &String::operator=(const String &other) {
    if (other.size() < this->capacity) {
        this->txt = other.txt;
    } else {
        this->free();
        this->copy(other);
    }
    return *this;
}

/*
 *  Dostęp do znaku, może generować wyjątek bad_index{}
 */
char &String::operator[](int idx) {
    if (idx > this->size()) {
        throw bad_index{};
    } else {
        return this->txt[idx];
    }
}

/*
 * Dodaje tekst na końcu może rozszerzać tekst
 */
String &String::operator+=(const char *_txt) {
    if (!_txt) return *this;
    if (this->size() + strlen(_txt) > this->get_capacity())
        this->reserve(this->size() + strlen(_txt));
    strcat(this->txt, _txt);
    return *this;
}

/*
 * Zwraca obiekt String, którego zawartość jest konkatenacją obu tekstów
 */
String String::operator+(const char *_txt) const {
    String res(this->txt);
    res += _txt;
    return res;
}

/*
 * Dodaje znak na końcu, może rozszerzać długość tablicy
 */
String &String::operator+=(char c) {
    if (size() + 2 > this->get_capacity())
        this->reserve(size() + 2);
    this->txt[this->size()] = c;
    return *this;
}

/*
 * Zwraca nowy obiekt zawierający tekst ze znakiem na końcu
 */
String String::operator+(char c) const {
    String res(this->txt);
    return res += c;
}

/*
 * Dodaje na końcu tekstową reprezentację arg. Użyj funkcji sprintf()
 */
String &String::operator+=(int arg) {
    char buf[256];
    sprintf(buf, "%d", arg);
    return *this += buf;
}

/*
 * Zwraca nowy obiekt zawierający tekst z dodaną tekstową reprezentacją argumentu
 */
String String::operator+(int arg) const {
    String res(this->txt);
    return res += arg;
}

/*
 * Dodaje na końcu tektową reprezentację arg. Użyj funkcji sprintf()
 */
String &String::operator+=(double arg) {
    char buf[256];
    sprintf(buf, "%f", arg);
    return *this += buf;
}

/*
 * Zwraca nowy obiekt zawierający tekst z dodaną tekstową reprezentacją argumentu
 */
String String::operator+(double arg) const {
    String res(this->txt);
    return res += arg;
}

/*
 * Zwraca nowy obiekt zawierający zawartość wzorca (this->txt) powtórzoną n razy i sklejoną
 */
String String::operator*(int n) const {
    if (!size() || n <= 0)
        return String();
    String r;
    for (int i = 0; i < n; i++) {
        r += this->txt;
    }
    return r;
}

/*
 * Jeżeli txt jest wskaźnikiem o wartości zerowej (nullptr) zwraca ""
 * w przeciwnym przypadku zwraca ptr
 */
String::operator const char *() const {
    if (this->txt == nullptr)
        return "";
    return this->txt;
}

/*
 * Porównanie zawartości
 */
bool String::operator==(const char *_txt) const {
    return strcmp(this->txt, _txt) == 0;
}

/*
 * Porównanie leksykograficzne, użyj strcmp()
 */
bool String::operator<(const char *_txt) const {
    return strcmp(this->txt, _txt) < 0;
}

/*
 * Zwraca rozmiar (nie licząc znaku 0 na końcu). Jeżeli is_empty() zwraca 0{}
 */
int String::size() const {
    if (this->is_empty())
        return 0;
    int size = 0;
    while (this->txt[size] != '\0')
        size++;
    return size;
}

/*
 * Zwalnia pamięć, zeruje zmienne
 */
void String::free() {
//    if (this->txt)
//        delete[] this->txt;
    this->txt = 0;
    this->capacity = 0;
}

/*
 * Kopiuje zawartość do pustego stringu
 */
void String::copy(const String &other) {
    this->capacity = other.get_capacity();
    this->txt = nullptr;
    if (this->get_capacity() > 0)
        this->txt = new char[get_capacity()];
    this->txt = other.txt;
}

/*
 * Rozszerza pamięć tablicy do rozmiaru równego co najmniej newcapacity
 */
void String::reserve(int newcapaicty) {
    if (newcapaicty <= capacity)
        return;
    int c = 64;
    while (c < newcapaicty)
        c *= 2;
    newcapaicty = c;
    char *tmp = new char[newcapaicty];
    if (txt) {
        memcpy(tmp, txt, size() + 1);
        delete txt;
    } else {
        tmp[0] = 0;
    }

    txt = tmp;
    capacity = newcapaicty;
}

#pragma endregion

#pragma region Funkcje testujące

void test_plus() {
    srand(0);
    String r;
    for (int i = 0; i < 10; i++) {
        r += (char) ('a' + rand() % 26);
    }
    cout << r << endl;
    r += "ABCDEFGH_";
    r += 12;
    r += "_@_";
    r += 3.14;
    r += '_';
    cout << r << endl;
    r = r * 3;
    cout << r << endl;
}

void test_plus2() {
    srand(1);
    String a;
    for (int i = 0; i < 10; i++) {
        a += (char) ('a' + rand() % 26);
    }
    String b;
    for (int i = 0; i < 10; i++) {
        b += (char) ('0' + rand() % 10);
    }
    String c = a + b;
    cout << c << endl;
    c = a + 12.5;
    cout << c << endl;
    c = b + 123.456;
    cout << c << endl;
}

#pragma endregion

int main() {
    cout << "--- Test 1 ---" << endl;
    test_plus();
    cout << endl << endl << "--- Test 2 ---" << endl;
    test_plus2();
    return 0;
}
