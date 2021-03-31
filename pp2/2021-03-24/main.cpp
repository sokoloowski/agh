#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#pragma region Student

class Student {
public:
    int indeks;
    string imie;
    string nazwisko;
    bool skreslony = false;
    string grupa;

    /*
     * Czytaj dane z istream. Załóż, że pola są oddzielone znakiem tabulacji
     * */
    void read(istream &is);

    /*
     * Zapisz dane do istream. Oddzielaj pola znakiem tabulacji. Nie dodawaj endline
     * */
    void write(ostream &os) const;
};

void Student::read(istream &is) {
    is >> this->indeks;
    is >> this->imie;
    is >> this->nazwisko;
    is >> this->skreslony;
    is >> this->grupa;
}

void Student::write(ostream &os) const {
    os << this->indeks << "\t"
       << this->imie << "\t"
       << this->nazwisko << "\t"
       << this->skreslony << "\t"
       << this->grupa;
}

void test_read_write() {
    ifstream is("studenci_isi-2021.csv");
    if (!is) {
        cerr << "Błąd otwarcia pliku" << endl;
        return;
    }
    string header;
    getline(is, header);
    cout << header << endl;
    while (is) {
        Student st;
        st.read(is);
        if (!is) break;
        st.write(cout);
        cout << endl;
    }
}

#pragma endregion
#pragma region StudentList

class StudentList {
    Student *tablica = 0;
    int count = 0;
    int capacity = 0;
public:
    StudentList(int cap = 100) : capacity(0), tablica(0) {
        if (cap > 0) {
            capacity = cap;
            tablica = new Student[cap];
        }
    }

    ~StudentList() {
        if (tablica)delete[]tablica;
    }

    int getCount() const {
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
    bool skresl(int index) {
        return false;
    }

    /*
     * reaktywuj studenta o dnaym numerze indeksu - ustaw pole skreślony
     */
    bool reaktywuj(int index) {
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

bool StudentList::add(const Student &st) {
    if (count == capacity) return false;
    this->tablica[count++] = st;
}


void StudentList::write(ostream &os) const {
    for (int i = 0; i < count; i++) {
        this->tablica[i].write(os);
        os << endl;
    }
}

void StudentList::read(istream &is) {
    while (is) {
        Student st;
        st.read(is);
        this->add(st);
    }
}

int StudentList::usun(int index) {
    for (int i = index; i < this->count; i++) {
        this->tablica[i] = this->tablica[i + 1];
    }
    this->count--;
    return true;
}

StudentList StudentList::selectGroup(const char *group) const {
    StudentList ret;
    for (int i = 0; i < count; i++) {
        if (this->tablica[i].grupa == group) {
            ret.add(this->tablica[i]);
        }
    }
    return ret;
}

StudentList StudentList::select(bool (*pred)(const Student &s)) const {
    StudentList ret;
    for (int i = 0; i < count; i++) {
        if (pred(this->tablica[i])) {
            ret.add(this->tablica[i]);
        }
    }
    return ret;
}

void test_list_read() {
    ifstream is("studenci_isi-2021.csv");
    if (!is) {
        cerr << "Błąd otwarcia pliku" << endl;
        return;
    }
    string header;
    getline(is, header);
    StudentList studentList;
    studentList.read(is);
    studentList.write(cout);
}

/*
 * Wczytaj plik do obiektu StudentList
 * Wywołaj funkcję select z parametrem "CWL3"
 * Wypisz zwróconą listę na cout
 */
void test_list_read_select() {
    ifstream is("studenci_isi-2021.csv");
    if (!is) {
        cerr << "Błąd otwarcia pliku" << endl;
        return;
    }
    string header;
    getline(is, header);
    StudentList studentList;
    studentList.read(is);
    studentList.selectGroup("CWL3").write(cout);
}

/*
 * Przykład wywołania z predykatem
 */
bool student_na_b(const Student &st) {
    return st.nazwisko[0] == 'B';
}

bool studentki(const Student &st) {
    return st.imie.back() == 'a';
}

void test_list_read_select_pred() {
    ifstream is("studenci_isi-2021.csv");
    string header;
    getline(is, header);
    StudentList studentList;
    studentList.read(is);
    studentList.select(student_na_b).write(cout);
}

void test_list_read_select_pred_women() {
    ifstream is("studenci_isi-2021.csv");
    string header;
    getline(is, header);
    StudentList studentList;
    studentList.read(is);
    studentList.select(studentki).write(cout);
}

#pragma endregion

int main() {
    test_read_write();
    test_list_read();
    test_list_read_select();
    test_list_read_select_pred();
    test_list_read_select_pred_women();
    return 0;
}
