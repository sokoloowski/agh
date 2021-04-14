#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#pragma region Komora

class Komora {
public:
    int x1;
    int y1;
    int z1;
    int x2;
    int y2;
    int z2;

    Komora(int _x1 = 0, int _y1 = 0, int _z1 = 0, int _x2 = 0, int _y2 = 0, int _z2 = 0)
            : x1(_x1), y1(_y1), z1(_z1), x2(_x2), y2(_y2), z2(_z2) {
        normalizuj();
    }

    /*
     * Znormalizuj tak aby x1<=x2, y1>=y2, z1>=z2
     */
    void normalizuj();

    /*
     * Czy nasza jama przecina się z inną komorą?
     * Jeżeli dwie komory graniczą z zewnątrz ścianami
     * (współrzędne są równe) to nie przecinają się
     */
    bool czy_przecina(const Komora &other) const;

    /*
     * zwróć string sformatowany jako ( x1 y1 z1 , x2 y2 z2 )
     */
    string to_string() const;

    /*
     * wypisz w formacie ( x1 y1 z1 , x2 y2 z2 )
     */
    ostream &wypisz(ostream &os) const;

    /*
     * wczytaj w takim samym formacie ( x1 y1 z1 , x2 y2 z2 )
     */
    istream &wczytaj_ze_spacjami(istream &is);

    /*
     * Docelowa wersja, nawiasy i przecinki mogą łączyć się z liczbami
     * wczytaj w formacie (x1 y1 z1,x2 y2 z2)
     */
    istream &wczytaj(istream &is);

    /*
     * wylosuj wartości z podanych zakresów
     * Zadbaj, aby współrzedne były rózne, np. stosujac do-while
     */
    void losuj(int xmin, int ymin, int zmin, int xmax, int ymax, int zmax);

    /*
     * przesuwa współrzedne komory o wektor (dx,dy,dz)
     */
    void przesun(int dx, int dy, int dz);
};

void Komora::normalizuj() {
    if (this->x1 > this->x2)
        swap(this->x1, this->x2);
    if (this->y1 < this->y2)
        swap(this->y1, this->y2);
    if (this->z1 < this->z2)
        swap(this->z1, this->z2);
}

bool Komora::czy_przecina(const Komora &other) const {
    return (((this->x1 < other.x2) && (this->x2 > other.x1)) &&
            ((this->y2 < other.y1) && (this->y1 > other.y2)) &&
            ((this->z2 < other.z1) && (this->z1 > other.z2)));
}

string Komora::to_string() const {
    ostringstream os;
    os << "( ";
    os << this->x1;
    os << " ";
    os << this->y1;
    os << " ";
    os << this->z1;
    os << " , ";
    os << this->x2;
    os << " ";
    os << this->y2;
    os << " ";
    os << this->z2;
    os << " )";
    return os.str();
}

ostream &Komora::wypisz(ostream &os) const {
    os << this->to_string();
    return os;
}

istream &Komora::wczytaj_ze_spacjami(istream &is) {
    string s;
    is >> s; // otwarcie nawiasu
    if (s != "(")
        is.setstate(ios::failbit);
    if (is.rdstate() != ios::failbit) {
        is >> this->x1;
        is >> this->y1;
        is >> this->z1;
    }
    is >> s; // przecinek
    if (s != ",")
        is.setstate(ios::failbit);
    if (is.rdstate() != ios::failbit) {
        is >> this->x2;
        is >> this->y2;
        is >> this->z2;
    }
    is >> s; // zamknięcie nawiasu
    if (s != ")")
        is.setstate(ios::failbit);
    normalizuj();
    return is;
}

// to można zrealizować zgrabniej wyrażeniami regularnymi
istream &Komora::wczytaj(istream &is) {
    string s;

    getline(is, s, ',');   // wczytaj do przecinka
    int idx = s.find('('); // znajdź nawias
    if (idx == string::npos) {
        is.setstate(ios::failbit);
        return is;
    }

    s = s.substr(idx + 1); // wydziel fragment po nawiasie
    istringstream iss(s);  // utwórz wejściowy strumień z obiektu string
    iss >> x1;             // wczytaj współrzędne
    iss >> y1;
    iss >> z1;

    getline(is, s, ')'); // wczytaj do nawiasu zamykajacego
    iss.clear();         // czyszczenie strumienia
    iss.str(s);          // przypnij strumień do nowego stringu
    iss >> x2;           // następne współzedne
    iss >> y2;
    iss >> z2;
    if (!iss) {
        is.setstate(ios::failbit);
        return is;
    }
    normalizuj();
    return is;
}

void Komora::losuj(int xmin, int ymin, int zmin, int xmax, int ymax, int zmax) {
    this->x1 = xmin + (rand() % (xmax - xmin + 1));
    this->y1 = ymin + (rand() % (ymax - ymin + 1));
    this->z1 = zmin + (rand() % (zmax - zmin + 1));

    do {
        this->x2 = xmin + (rand() % (xmax - xmin + 1));
    } while (this->x1 == this->x2);

    do {
        this->y2 = ymin + (rand() % (ymax - ymin + 1));
    } while (this->y1 == this->y2);

    do {
        this->z2 = zmin + (rand() % (zmax - zmin + 1));
    } while (this->z1 == this->z2);
    normalizuj();
}

void Komora::przesun(int dx, int dy, int dz) {
    this->x1 += dx;
    this->y1 += dy;
    this->z1 += dz;

    this->x2 += dx;
    this->y2 += dy;
    this->z2 += dz;
}

#pragma endregion

#pragma region Kretowisko

class Kretowisko {
public:
    vector<Komora> komory;

    /*
     * dodaje komorę, ale tylko w przypadku,
     * kiedy nie przecina się z posotałymi
     */
    bool dodaj(const Komora &k);

    /*
     * Buduje kretowisko losując n komór o współrzednych x, y z zakresu [min,max]
     * Wygenerowane komory należy przesunąć o dx=rand()%scatter, dy=rand()%scatter i dz=0
     * Ponieważ komory są pod ziemią - dla współrzednej z losuj z zakresu -abs(depth) do -1
     */
    void buduj(int n, int min, int max, int depth, int scatter);

    /*
     * Zapisz w formacie ( komora1,komora2,komora3,....)
     */
    ostream &wypisz(ostream &os) const;

    /*
     * Wczytaj w takim formacie, jak zapisałeś
     */
    istream &wczytaj(istream &is);

    /*
     * Zwróć całkowitą powierzchnię komór
     */
    int powierzchnia() const;

    /*
     * Zwróć  powierzchnię komór na głębokości depth
     */
    int powierzchnia(int depth) const;

    /*
     * Zwróć całkowitą objętość komór
     */
    int objetosc() const;

    /*
     * Zwróć objętość komór od -inf do głębokości depth
     * Jest to patrząc formalnie całka powierzchnia(d) delta_d
     * Ale powierzchnia(d) to funkcja odcnikami stała...
     */
    int objetosc(int depth) const;

    /*
     * Wszystkie komory są połączone ze sobą. Złośliwy ogrodnik wlał do kretowiska wodę,
     * która rozpłynęła się pomiędzy komoram.
     * Załóż że objętość wlanej wody nie przewyższa sumarycznej objętości komór
     * Oblicz do jakiego poziomu zostaną zalane komory?
     */
    double poziom_wody(double v) const;
};

bool Kretowisko::dodaj(const Komora &k) {
    for (int i = 0; i < this->komory.size(); i++) {
        if (k.czy_przecina(komory[i]))
            return false;
    }
    this->komory.push_back(k);
    return true;
}

void Kretowisko::buduj(int n, int min, int max, int depth, int scatter) {
    int i = 0;
    if (depth > 0)
        depth *= -1;
    while (i < n) {
        Komora k;
        k.losuj(min, min, -abs(depth), max, max, -1);
        k.przesun(rand() % scatter, rand() % scatter, 0);

        if (this->dodaj(k))
            i++;
    }
}

ostream &Kretowisko::wypisz(ostream &os) const {
    os << '(';
    for (int i = 0; i < this->komory.size() - 1; i++) {
        this->komory[i].wypisz(os);
        os << ' ';
    }
    this->komory.back().wypisz(os);
    os << ')';
    return os;
}

istream &Kretowisko::wczytaj(istream &is) {
    komory.clear(); // nie chcemy poprzednio zdefiniowanych komór
    int c;
    do {
        c = is.get();
    } while (is && c != '('); // znajdź '(' ale przerwij, gdy !is

    for (int i = 0;; i++) {
        c = is.get();
        // jeżeli koniec pliku lub napotkano ')' to przerwij
        if (c == ')' || c == EOF) break;
        if (c == '(') {
            // jeżeli napotkano '(', to
            // cofnij znak do strumienia za pomocą unget()
            // wczytaj komorę i dodaj do kretowiska
            is.unget();
            Komora k;
            k.wczytaj(is);
            this->dodaj(k);
        }
    }
    return is;
}

int Kretowisko::powierzchnia() const {
    int p = 0;
    for (const Komora &k : this->komory)
        p += abs(k.x1 - k.x2) * abs(k.y1 - k.y2);
    return p;
}

int Kretowisko::powierzchnia(int depth) const {
    int p = 0;
    for (const Komora &k : this->komory)
        if (k.z2 <= depth && k.z1 > depth)
            p += abs(k.x1 - k.x2) * abs(k.y1 - k.y2);
    return p;
}

int Kretowisko::objetosc() const {
    int o = 0;
    for (const Komora &k : this->komory) {
        o += abs(k.x1 - k.x2) * abs(k.y1 - k.y2) * abs(k.z1 - k.z2);
    }
    return o;
}

int Kretowisko::objetosc(int depth) const {
//    int o = 0;
//    for (const Komora &k : this->komory) {
//        int fz1 = k.z1 < depth ? k.z1 : depth;
//        int fz2 = k.z2 < depth ? k.z2 : depth;
//        o += abs(k.x1 - k.x2) * abs(k.y1 - k.y2) * abs(fz1 - fz2);
//    }
//    return o;

#warning READ ME BEFORE GRADING!
    // dla n = 100 wyniki były błędne (zbyt mała dokładność), w skrajnych przypadkach objętość malała przy zbliżaniu się
    // do powierzchni
    double n = 10000;

    // ze względu na pewien margines błędu występujący przy całkowaniu metodą trapezów próba policzenia objętości
    // dla depth > 0 będzie skutkowała niepoprawnymi wynikami przy małej ilości punktów / trapezów
    int a = 0, b = depth > 0 ? 0 : depth;
    for (const Komora &k : this->komory)
        a = k.z2 < a ? k.z2 - 1 : a;
    double h = (b - a) / n; // wysokosć trapezów
    double S = 0.0;         // zmienna będzie przechowywać sumę pól trapezów
    double podstawa_a = powierzchnia(a), podstawa_b;

    for (int i = 1; i <= n; i++) {
        podstawa_b = powierzchnia(a + h * i);
        S += (podstawa_a + podstawa_b);
        podstawa_a = podstawa_b;
    }
    return (int) ceil(S * 0.5 * h);
}

double Kretowisko::poziom_wody(double v) const {
    if (v > (double) this->objetosc()) return LONG_MAX;
    int z_min = 0;
    int i;
    for (const Komora &k : this->komory)
        z_min = k.z2 < z_min ? k.z2 - 1 : z_min;
    for (i = z_min; i < 0; i++) {
        if (v < this->objetosc(i))
            break;
    }
    int diff = this->objetosc(i) - this->objetosc(i - 1);
    v -= this->objetosc(i);
    return i + (v / (double) diff);
}

#pragma endregion

#pragma region Testy komory

void test_komora_wypisz() {
    Komora k(1, 2, 3, 4, 5, 6);
    k.wypisz(cout);
}

void test_komora_odczyt_spacje() {
    istringstream is("( 1 2 3 , 4 5 -6 )");
    Komora k;
    k.wczytaj_ze_spacjami(is);
    k.wypisz(cout);
}

void test_komora_odczyt() {
    istringstream is("(1 2 3,4 5 6)(23 24 25,26 27 28)");
    Komora k;
    k.wczytaj(is);
    k.wypisz(cout);
    k.wczytaj(is);
    k.wypisz(cout);
}

void test_czy_przecina() {
    istringstream is("(1 1 6,4 4 3)(2 2 8,6 6 5)");
    Komora k;
    k.wczytaj(is);
    k.wypisz(cout);
    Komora k2;
    k2.wczytaj(is);
    k2.wypisz(cout);
    cout << "Przecina:" << k.czy_przecina(k2) << endl;
}

void test_przecinanie(const char *komora2, bool expected) {
    string komora = "( 3 7 8 , 7 2 2 )";
    istringstream is(komora.append(komora2));
    Komora k;
    k.wczytaj(is);
    Komora k2;
    k2.wczytaj(is);
    if (k.czy_przecina(k2) != expected)
        cerr << "For " << komora << " got " << k.czy_przecina(k2) << ", excepted " << expected;
}

void test_czy_losowe_przecina() {
    Komora k(7, 3, 8, 7, 2, 2);
    k.wypisz(cout);
    cout << endl;
    srand(0);
    for (int i = 0; i < 10; i++) {
        Komora k2;
        k2.losuj(0, 0, 0, 10, 10, 10);
        k2.wypisz(cout);
        cout << " " << k.czy_przecina(k2) << endl;
    }
}

#pragma endregion

#pragma region Testy kretowiska

/*
 * Wywołaj metodę buduj i wypisz
 */
void test_kretowisko_buduj() {
    Kretowisko kretowisko;
    kretowisko.buduj(10, 0, 20, 20, 20);
    kretowisko.wypisz(cout);
}

/*
 * Wczytaj ze stringu i wypisz
 */
void test_kretowisko_wczytaj() {
    string s = "(( 8 15 -5 , 11 14 -7 ) ( 14 13 -4 , 17 11 -8 ) ( 13 7 -3 , 16 4 -4 ) "
               "( 1 6 -7 , 4 4 -10 ) ( 16 20 -4 , 18 19 -10 ) ( 5 16 -7 , 8 14 -8 ) "
               "( 13 11 -3 , 17 10 -5 ) ( 11 20 -2 , 13 18 -7 ) ( 17 14 -5 , 18 12 -8 ) "
               "( 17 18 -4 , 20 16 -9 ) )";
    istringstream is(s);
    Kretowisko kretowisko;
    kretowisko.wczytaj(is);
    kretowisko.wypisz(cout);
}

/*
 * Zbuduj
 * Zapisz do stringu s
 * Wczytaj ze stringu s
 * Wypisz na cout
 * Zapisz do stringu s2
 * Porównaj stringi
 */
void test_kretowisko_buduj_zapisz_wczytaj_wypisz() {
    srand(0);

    ostringstream os;
    ostringstream os2;

    Kretowisko kretowisko;
    kretowisko.buduj(10, 0, 20, 20, 20);
    kretowisko.wypisz(os);
    kretowisko.wypisz(cout);
    cout << endl;
    string s = os.str();
    istringstream is(s);
    kretowisko.wczytaj(is);
    kretowisko.wypisz(os2);
    kretowisko.wypisz(cout);
    string s2 = os2.str();
    cout << endl;
    if (s != s2) cerr << "Kretowiska sie roznia!";
}

/*
 * Utwórz kretowisko z jedną komorą
 * Przeiteruj od z2 do z1 w pętli i wypisuj powierzchnię i sumaryczną objetość poniżej z
 */
void test_jedna_komora() {
    Kretowisko kretowisko;
    kretowisko.buduj(1, 0, 20, 20, 20);
    Komora k = kretowisko.komory[0];
    for (int i = k.z2; i < k.z1; i++) {
        cout << kretowisko.powierzchnia(i) << '\t' << kretowisko.objetosc(i) << endl;
    }
}

/*
 * Analogicznie przetestuj dwie komory
 */
void test_dwie_komory() {
    Kretowisko kretowisko;
    kretowisko.buduj(2, 0, 20, 20, 20);
    Komora k1 = kretowisko.komory[0];
    Komora k2 = kretowisko.komory[1];
    for (int i = min(k1.z2, k2.z2); i < max(k1.z1, k2.z2); i++) {
        cout << kretowisko.powierzchnia(i) << '\t' << kretowisko.objetosc(i) << endl;
    }
}

/*
 * Znajdź z_min i z_max
 * W pętli z od z_min do z_max dla 100 punktów (przyjąłem 10000 punktów, powód w metodzie objetosc(double v))
 * Wypisz powierzchnię(z), przybliżoną objętość (całkowanie metodą trapezów) 
 */
void test_objetosc_odd() {
    Kretowisko kretowisko;
    kretowisko.buduj(5, 0, 20, 20, 20);
    int z_min = 0, z_max = INT32_MIN;
    for (const Komora &k : kretowisko.komory) {
        z_min = k.z2 < z_min ? k.z2 : z_min;
        z_max = k.z1 > z_max ? k.z1 : z_max;
    }

    for (int z = z_min; z < z_max; z++) {
        cout << kretowisko.powierzchnia(z) << '\t' << kretowisko.objetosc(z) << endl;
    }
}

/*
 * Oblicz całkowitą objętość komór
 * W pętli od 0 do V oblicz głębokość dla v
 * Wypisz v, d, i powierzchnię(d)
 */
void test_poziom_wody_odv() {
    Kretowisko kretowisko;
    kretowisko.buduj(5, 0, 20, 20, 20);
    int V = kretowisko.objetosc();
    for (int v = 0; v < V; v++) {
        double d = kretowisko.poziom_wody(v);
        cout << v << '\t' << d << '\t' << kretowisko.powierzchnia((int) d) << endl;
    }
}

#pragma endregion

int main() {
#warning UNCOMMENT TESTS AND REMOVE THIS LINE
//    test_komora_wypisz();
//    test_komora_odczyt_spacje();
//    test_komora_odczyt();
//    test_czy_przecina();

//    test_przecinanie("( 0 3 9 , 3 2 5 )", false);
//    test_przecinanie("( 2 9 8 , 8 1 6 )", true);
//    test_przecinanie("( 5 3 9 , 8 0 6 )", true);
//    test_przecinanie("( 2 7 8 , 7 2 5 )", true);
//    test_przecinanie("( 3 4 9 , 9 2 6 )", true);
//    test_przecinanie("( 0 5 9 , 7 4 5 )", true);
//    test_przecinanie("( 0 4 6 , 2 3 5 )", false);
//    test_przecinanie("( 1 7 6 , 9 5 5 )", true);
//    test_przecinanie("( 5 7 8 , 9 0 6 )", true);
//    test_przecinanie("( 0 6 8 , 9 0 5 )", true);
//    test_przecinanie("( 0 6 8 , 9 0 5 )", false); // bledna wartosc dla sprawdzenia testu

//    test_kretowisko_buduj();
//    test_kretowisko_wczytaj();
//    test_kretowisko_buduj_zapisz_wczytaj_wypisz();
//    test_jedna_komora();
//    test_dwie_komory();
//    test_objetosc_odd();
//    test_poziom_wody_odv();
    return 0;
}
