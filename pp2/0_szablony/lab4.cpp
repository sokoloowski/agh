#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#pragma region Student

class Student
{
public:
    int indeks;
    string imie;
    string nazwisko;
    bool skreslony = false;
    string grupa;

    /*
     * Czytaj dane z istream. Załóż, że pola są oddzielone znakiem tabulacji
     */
    void read(istream &is);

    /*
     * Zapisz dane do istream. Oddzielaj pola znakiem tabulacji. Nie dodawaj endline
     */
    void write(ostream &os) const;
};

#pragma region Implementacje metod klasy Student

void Student::read(istream &is)
{
    // code...
}

void Student::write(ostream &os) const
{
    // code...
}

#pragma endregion

#pragma region Funkcje testujące

// https://upel2.cel.agh.edu.pl/weaiib/pluginfile.php/104259/question/questiontext/176501/1/93449/studenci_isi-2021.csv
// Listę można pobrać bezpośrednio z systemu USOS
void test_read_write()
{
    ifstream is("studenci_isi-2021.csv");
    if (!is)
    {
        cerr << "Błąd otwarcia pliku" << endl;
        return;
    }
    string header;
    // czytaj nagłówek za pomocą getline()
    cout << header << endl;
    while (is)
    {
        Student st;
        //wczytaj
        //zapisz na cout
    }
}

#pragma endregion

#pragma endregion

#pragma region StudentList

class StudentList
{
    Student *tablica = 0;
    int count = 0;
    int capacity = 0;

public:
    StudentList(int cap = 100) : capacity(0), tablica(0)
    {
        if (cap > 0)
        {
            capacity = cap;
            tablica = new Student[cap];
        }
    }
    ~StudentList()
    {
        if (tablica)
            delete[] tablica;
    }

    int getCount() const
    {
        return count;
    }

    /*
     * Dodaj studenta do tablicy. Zwróć wartość false, jeżeli zabrakło miejsca
     */
    bool add(const Student &st);

    /*
     * Czytaj ze strumienia i dodawaj.
     * Strumień nie ma nagłówka
     * Przerwij, gdy nie uda się odczyt lub zabraknie miejsca
     */
    void read(istream &is);

    /*
     *Zapisuj do strumienia (bez nagłówka)
     */
    void write(ostream &os) const;

    /*
     * skreśl studenta o dnaym numerze indeksu - ustaw pole skreślony
     */
    bool skresl(int index)
    {
        return false;
    }

    /*
     * reaktywuj studenta o dnaym numerze indeksu - ustaw pole skreślony
     */
    bool reaktywuj(int index)
    {
        return false;
    }

    /*
     * usuń studenta o danym indeksie z tablicy
     * fizycznie usuń obiekt
     */
    int usun(int index);

    /*
     * Utwórz listęi umieść w niej wszystkich studentów
     * których pole grupa jest równe group
     */
    StudentList selectGroup(const char *group) const;

    /*
     * Utwórz listę i umieść w niej wszystkich studentów
     * którzy spełniają predykat.
     * Predykat jest wskaźnikiem do funkcji boolowskiej, której parametrem jest student
     */
    StudentList select(bool (*pred)(const Student &s)) const;
};

#pragma region Implementacje metod klasy StudentList

bool StudentList::add(const Student &st)
{
    if (count == capacity)
        return false;
    //??
}

void StudentList::write(ostream &os) const
{
    for (int i = 0; i < count; i++)
    {
        // ???
    }
}

void StudentList::read(istream &is)
{
    while (is)
    {
        Student st;
        st.read(is);
        // ???
    }
}

int StudentList::usun(int index)
{
    //???
    return true;
}

StudentList StudentList::selectGroup(const char *group) const
{
    StudentList ret;
    for (int i = 0; i < count; i++)
    {
        //???
    }
    return ret;
}

StudentList StudentList::select(bool (*pred)(const Student &s)) const
{
    StudentList ret;
    for (int i = 0; i < count; i++)
    {
        if (predykat jest true)
        {
            // ??? dodaj studenta do ret
        }
    }
    return ret;
}

#pragma endregion

#pragma region Funkcje testujące

void test_list_read()
{
    ifstream is("studenci_isi.csv");
    if (!is)
    {
        cerr << "Błąd otwarcia pliku" << endl;
        return;
    }
    string header;
    getline(is, header);
    // Utwórz obiekt StudentList, wczytaj resztę pliku do listy, wypisz na cout
}

/*
 * Wczytaj plik do obiektu StudentList
 * Wywołaj funkcję select z parametrem "CWL3"
 * Wypisz zwróconą listę na cout
 */
void test_list_read_select()
{
    ifstream is("studenci_isi-2021.csv");
    if (!is)
    {
        cerr << "Błąd otwarcia pliku" << endl;
        return;
    }
    string header;
    getline(is, header);
    // ????
}

/*
 * Przykład wywołania z predykatem
 */
bool student_na_b(const Student &st)
{
    return st.nazwisko[0] == 'B';
}

void test_list_read_select_pred()
{
    // wczytaj całą listę do slist
    StudentList slist;
    slist.read(is);
    // StudentList slist2 = slist.select([](auto &st){return st.nazwisko[0]=='B';});
    StudentList slist2 = slist.select(student_na_b);
    slist2.write(cout);
}

// Napisz własny predykat (funkcję), który wybierze wszystkie Panie - ich imiona kończą się na literę 'a' - i przetestuj działanie.

#pragma endregion

#pragma endregion

int main()
{
    return 0;
}