#include <iostream>
#include <sstream>

using namespace std;

#pragma region deklaracja

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

#pragma endregion

#pragma region implementacje

void Komora::normalizuj()
{
    if (this->x1 > this->x2)
        swap(this->x1, this->x2);
    if (this->y1 < this->y2)
        swap(this->y1, this->y2);
    if (this->z1 < this->z2)
        swap(this->z1, this->z2);
}

bool Komora::czy_przecina(const Komora &other) const
{
    return (((this->x1 < other.x2) && (this->x2 > other.x1)) &&
            ((this->y2 < other.y1) && (this->y1 > other.y2)) &&
            ((this->z2 < other.z1) && (this->z1 > other.z2)));
}

string Komora::to_string() const
{
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

ostream &Komora::wypisz(ostream &os) const
{
    os << this->to_string();
    return os;
}

istream &Komora::wczytaj_ze_spacjami(istream &is)
{
    string s;
    is >> s; // otwarcie nawiasu
    if (s != "(")
        is.setstate(ios::failbit);
    if (is.rdstate() != ios::failbit)
    {
        is >> this->x1;
        is >> this->y1;
        is >> this->z1;
    }
    is >> s; // przecinek
    if (s != ",")
        is.setstate(ios::failbit);
    if (is.rdstate() != ios::failbit)
    {
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
istream &Komora::wczytaj(istream &is)
{
    string s;

    getline(is, s, ',');   // wczytaj do przecinka
    int idx = s.find('('); // znajdź nawias
    if (idx == string::npos)
    {
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
    this->x1 = xmin + (rand() % (xmax - xmin + 1));
    this->y1 = ymin + (rand() % (ymax - ymin + 1));
    this->z1 = zmin + (rand() % (zmax - zmin + 1));

    do
    {
        this->x2 = xmin + (rand() % (xmax - xmin + 1));
    } while (this->x1 == this->x2);

    do
    {
        this->y2 = ymin + (rand() % (ymax - ymin + 1));
    } while (this->x1 == this->x2);

    do
    {
        this->z2 = xmin + (rand() % (zmax - zmin + 1));
    } while (this->x1 == this->x2);
}

void Komora::przesun(int dx, int dy, int dz)
{
    this->x1 += dx;
    this->y1 += dy;
    this->z1 += dz;

    this->x2 += dx;
    this->y2 += dy;
    this->z2 += dz;
}

#pragma endregion

#pragma region testy

void test_komora_wypisz()
{
    Komora k(1, 2, 3, 4, 5, 6);
    k.wypisz(cout);
}

void test_komora_odczyt_spacje()
{
    istringstream is("( 1 2 3 , 4 5 -6 )");
    Komora k;
    k.wczytaj_ze_spacjami(is);
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

void test_przecinanie(const char *komora2, bool expected)
{
    string komora = "( 3 7 8 , 7 2 2 )";
    istringstream is(komora.append(komora2));
    Komora k;
    k.wczytaj(is);
    Komora k2;
    k2.wczytaj(is);
    if (k.czy_przecina(k2) != expected)
        cerr << "For " << komora << " got " << k.czy_przecina(k2) << ", excepted " << expected;
}

void test_czy_losowe_przecina()
{
    Komora k(7, 3, 8, 7, 2, 2);
    k.wypisz(cout);
    cout << endl;
    srand(0);
    for (int i = 0; i < 10; i++)
    {
        Komora k2;
        k2.losuj(0, 0, 0, 10, 10, 10);
        k2.wypisz(cout);
        cout << " " << k.czy_przecina(k2) << endl;
    }
}

#pragma endregion

int main()
{
    // test_komora_wypisz();
    // test_komora_odczyt_spacje();
    // test_komora_odczyt();
    // test_czy_przecina();
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
