#include <iostream>
#include <sstream>
using namespace std;

#pragma region Komora

class Komora
{
public:
    int x1;
    int y1;
    int z1;
    int x2;
    int y2;
    int z2;
    Komora(int _x1 = 0, int _y1 = 0, int _z1 = 0, int _x2 = 0, int _y2 = 0, int _z2 = 0)
        : x1(_x1), y1(_y1), z1(_z1), x2(_x2), y2(_y2), z2(_z2)
    {
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
     *
     */
    istream &wczytaj_ze_spacjami(istream &is);

    /*
     * Docelowa wersja, nawiasy i przecinki mogą łączyć się z liczbami
     * wczytaj w formacie (x1 y1 z1,x2 y2 z2)
     *
     */
    istream &wczytaj(istream &is);

    /*
     * wylosuj wartości z podanych zakresów
     * Zadbaj, aby współrzedne były rózne, np. stosujac do-while
     *
     */
    void losuj(int xmin, int ymin, int zmin, int xmax, int ymax, int zmax);

    /*
     * przesuwa współrzedne komory o wektor (dx,dy,dz)
     */
    void przesun(int dx, int dy, int dz);
};

#pragma region Implementacja metod klasy Komora

void Komora::normalizuj()
{
    // code...
}

bool Komora::czy_przecina(const Komora &other) const
{
    // code...
}

string Komora::to_string() const
{
    ostringstream os;
    // użyj innej metody do wypisania na strumień ostringstream - zapisu do stringu
    return os.str();
}

ostream &Komora::wypisz(ostream &os) const
{
    // wypisz w ustalonym formacie
    return os;
}

istream &Komora::wczytaj_ze_specjami(istream &is)
{
    string s;
    is >> s;
    if (s != "(")
        is.setstate(ios::failbit);
    // wczytaj współrzedne
    // wczytaj przecinek
    // znowu współrzędne
    // nawias
    normalizuj();
    return is;
}

// to można zrealizować zgrabniej wyrażeniami regularnymi
istream &Komora::wczytaj(istream &is)
{
    string s;

    getline(is, s, ',');     // wczytaj do przecinka
    int idx = s.? ? ? ('('); // znajdź nawias
    if (idx == string::npos)
    {
        is.setstate(ios::failbit);
        return is;
    }

    s = s.? ? ?               // wydziel fragment po nawiasie
        istringstream iss(s); // utwórz wejściowy strumień z obiektu string
    iss >> x1;                // wczytaj współrzędne
    iss >> ...;
    iss >> ...;

    getline(is, s, ')'); // wczytaj do nawiasu zamykajacego
    iss.clear();
    iss.str(s); // przypnij strumień do nowego stringu
    iss >> ...; // następne współzedne
    if (!iss)
    {
        is.setstate(ios::failbit);
        return is;
    }
    normalizuj();
    return is;
}

void Komora::losuj(int xmin, int ymin, int zmin, int xmax, int ymax, int zmax)
{
    // code...
}

void Komora::przesun(int dx, int dy, int dz)
{
    // code...
}

#pragma endregion

#pragma region Funkcje testujące

void test_komora_wypisz()
{
    Komora k(1, 2, 3, 4, 5, 6);
    k.wypisz(cout);
}

void test_komora_odczyt_spacje()
{
    istringstream is("( 1 2 3 , 4 5 -6 )");
    Komora k;
    k.wczytaj_ze_specjami(is);
    k.wypisz(cout);
}

void test_komora_odczyt()
{
    istringstream is("(1 2 3,4 5 6)(23 24 25,26 27 28)");
    Komora k;
    k.wczytaj(is);
    k.wypisz(cout);
    k.wczytaj(is);
    k.wypisz(cout);
}

void test_czy_przecina()
{
    istringstream is("(1 1 6,4 4 3)(2 2 8,6 6 5)");
    Komora k;
    k.wczytaj(is);
    k.wypisz(cout);
    Komora k2;
    k2.wczytaj(is);
    k2.wypisz(cout);
    cout << "Przecina:" << k.czy_przecina(k2) << endl;
}

/**
 * @brief Funkcja testująca przecinanie się komór.
 * W przypadku wyniku sprzecznego z zakładanym, wypisuje szczegóły na strumień błędów `cerr`
 * 
 * @param komora Komora w kretowisku w formacie `( x1 y1 z1 , x2 y2 z2)`
 * @param expected Spodziewany wynik testu
 */
void test_przecinanie(const char *komora, bool expected)
{
    string komora1 = "( 3 7 8 , 7 2 2 )";
    istringstream is(komora1.append(komora));
    Komora k;
    k.wczytaj(is);
    Komora k2;
    k2.wczytaj(is);
    if (k.czy_przecina(k2) != expected)
        cerr << "For " << komora << " got " << k.czy_przecina(k2) << ", excepted " << expected;
}

// sprawdź wynik na stronie https://github.com/pszwed-ai/cpp/blob/main/Intersections3D.ipynb
void test_czy_losowe_przecina()
{
    Komora k(--jakieś dane-- -);
    k.wypisz(cout);
    cout << endl;
    srand(0);
    for (int i = 0; i < 10; i++)
    {
        Komora k2;
        k2.losuj(---z jakiegoś zakresu-- -);
        k2.wypisz(cout);
        cout << " " << k.czy_przecina(k2) << endl;
    }
}

#pragma endregion

#pragma endregion

#pragma region Kretowisko

class Kretowisko
{
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
    * Zwróć powierzchnię komór na głębokości depth
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

#pragma region Implementacja metod klasy Kretowisko

bool Kretowisko::dodaj(const Komora &k)
{
    return true;
}
void Kretowisko::buduj(int n, int min, int max, int depth, int scatter)
{
    int i = 0;
    if (depth > 0)
        depth *= -1;
    while (i < n)
    {
        Komora k; // ?????

        if (dodaj(k))
            i++;
    }
}

ostream &Kretowisko::wypisz(ostream &os) const
{
    os << '('; // ...
    os << ')';
    return os;
}

istream &Kretowisko::wczytaj(istream &is)
{
    komory.? ? ? ? ();
    // nie chcemy poprzednio zdefiniowanych komór int c;
    do
    {
        c = is.get();
    } while(????); // znajdź '(' ale przerwij, gdy !is

    for (;;)
    {
        c = is.get(); // jeżeli koniec pliku lub napotkano ')' to przerwij if(c=='('){
                      // jeżeli napotkano '(', to // cofnij znak do strumienia za pomocą unget() // wczytaj komorę i dodaj do kretowiska
    }
    return is;
}

#pragma endregion

#pragma region Funkcje testujące

/*
* Wywołaj metodę buduj i wypisz
*/
void test_kretowisko_buduj()
{
    // code...
}

/*
* Wczytaj ze stringu i wypisz
*/
void test_kretowisko_wczytaj()
{
    string s = "(( 8 15 -5 , 11 14 -7 ) ( 14 13 -4 , 17 11 -8 ) ( 13 7 -3 , 16 4 -4 ) "
               "( 1 6 -7 , 4 4 -10 ) ( 16 20 -4 , 18 19 -10 ) ( 5 16 -7 , 8 14 -8 ) "
               "( 13 11 -3 , 17 10 -5 ) ( 11 20 -2 , 13 18 -7 ) ( 17 14 -5 , 18 12 -8 ) "
               "( 17 18 -4 , 20 16 -9 ) )";
    istringstream is(s);
}

/*
* Zbuduj
* Zapisz do stringu s
* Wczytaj ze stringu s
* Wypisz na cout
* Zapisz do stringu s2
* Porównaj stringi
*/
void test_kretowisko_buduj_zapisz_wczytaj_wypisz()
{
    srand(0);
}

#pragma endregion

#pragma region Funkcje testujące zalewanie wodą

/*
* Utwórz kretowisko z jedną komorą
* Przeiteruj od z2 do z1 w pętli i wypisuj powierzchnię i sumaryczną objetość poniżej z
*/
void test_jedna_komora()
{
    // code...
}

/*
* Analogicznie przetestuj dwie komory
*/
void test_dwie_komory()
{
    // code...
}

/*
* Znajdź z_min i z_max
* W pętli z od z_min do z_max dla 100 punktów
* Wypisz powierzchnię(z), przybliżoną objętość (całkowanie metodą trapezów)
*/
void test_objetosc_odd()
{
    // code...
}

/*
* Oblicz całkowitą objętość komór
* W pętli od 0 do V oblicz głębokość dla v
* Wypisz v, d, i powierzchnię(d)
*/
void test_poziom_wody_odv()
{
    // code...
}

#pragma endregion

#pragma endregion

int main()
{
    // Testy ze strony https://github.com/pszwed-ai/cpp/blob/main/Intersections3D.ipynb
    test_przecinanie("( 0 3 9 , 3 2 5 )", false);
    test_przecinanie("( 2 9 8 , 8 1 6 )", true);
    test_przecinanie("( 5 3 9 , 8 0 6 )", true);
    test_przecinanie("( 2 7 8 , 7 2 5 )", true);
    test_przecinanie("( 3 4 9 , 9 2 6 )", true);
    test_przecinanie("( 0 5 9 , 7 4 5 )", true);
    test_przecinanie("( 0 4 6 , 2 3 5 )", false);
    test_przecinanie("( 1 7 6 , 9 5 5 )", true);
    test_przecinanie("( 5 7 8 , 9 0 6 )", true);
    test_przecinanie("( 0 6 8 , 9 0 5 )", true);
    return 0;
}