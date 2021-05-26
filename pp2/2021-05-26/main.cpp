#include <iostream>
#include <ctime>

using namespace std;

#pragma region Deklaracje

class TabularListElement {
    friend class TabularList;

    friend class TabularListIterator;

    TabularListElement *next;
    int *table;
    int capacity;
    int count;
public:
    /*
     * Alokuje pamięć dla table. Rozmiar przekazany przez parametr capacity
     * Zeruje pozostałe elementy
     * Jeżeli capacity<=0 koryguje wartość na 128
     */
    TabularListElement(int capacity);

    /*
     * Zwalnia pamięć table
     */
    ~TabularListElement();

    /*
     * Dodaje element do tablicy table i zwraca true
     * Jeżeli nie zmieści się - zwraca false
     */
    bool add(int v);
};

class TabularList {
    friend class TabularListIterator;

    TabularListElement *start;
    TabularListElement *end;
public:
    TabularList() { start = end = 0; }

    ~TabularList() { free(); }

    /*
     * Dodaje wartość do listy.
     * Jeżeli end==0 alokuje pierwszy element
     * Jeżeli wartość v może zostać dodany do end->table dodaje ją
     * W przeciwnym przypadku tworzy nowy obiekt TabularListElement  o dwa razy dłuższej tablicy i dodaje na końcu listy,
     * a następnie wpisuje do niego wartość v
     */
    void push_back(int v);

    /*
     * Konstruktory/operatory przypisania  kopiujące/przenoszące
     */
    TabularList(const TabularList &other);

    TabularList(TabularList &&other);

    TabularList &operator=(const TabularList &other);

    TabularList &operator=(TabularList &&other);

protected:
    /*
     * Zwalnia pamięć listy
     */
    void free();

    /*
     * Kopiuje zawartość other - wołając push_back()
     */
    void copy(const TabularList &other);

    /*
     * Przenosi własność elementów other
     */
    void move(TabularList &other);
};


class TabularListIterator {
    /*
     * Wskażnik na element listy
     */
    TabularListElement *cursor;
    /*
     * Indeks wartości wewnątrz tablicy, czyli adresowanym elementem jest:
     * cursor->table[idx_cursor];
     */
    int idx_cursor;
public:
    /*
     * Konstruktor, inicjuje kursory
     */
    TabularListIterator(const TabularList &tlist);

    /*
     * Sprawdza, czy nie wyszliśmy poza listę
     */
    bool at_end() const;

    /*
     * Operator prefiksowy
     * Sprawdza, czy można przesunąć idx_cursor w elemencie wskazywanym przez cursor
     * Jeżeli tak - zwieksza idx_cursor o 1
     * Jeżeli nie: przesuwa cursor na następny element
     */
    TabularListIterator &operator++();

    /*
     * Standardowa implementacja
     */
    TabularListIterator operator++(int);

    /*
     * Dostęp do elementu wskazywanego przez dwa kursory
     */
    int &get() const;
};

#pragma endregion

#pragma region Implementacja TabularListElement

TabularListElement::TabularListElement(int _capacity) {
    if (_capacity <= 0) _capacity = 128;
    this->capacity = _capacity;
    this->table = new int[this->capacity];
    this->count = 0;
    this->next = nullptr;
}

TabularListElement::~TabularListElement() {
    delete[] this->table;
}

bool TabularListElement::add(int v) {
    if (this->capacity == this->count) return false;
    this->table[this->count++] = v;
    return true;
}

#pragma endregion

#pragma region Implementacja TabularList

void TabularList::push_back(int v) {
    if (!this->end) {
        TabularListElement *tle = new TabularListElement(128);
        this->start = tle;
        this->end = tle;
    }
    if (!this->end->add(v)) {
        TabularListElement *tle = new TabularListElement(this->end->capacity * 2);
        tle->add(v);
        this->end->next = tle;
        this->end = tle;
    }
}

TabularList::TabularList(const TabularList &other) {
    this->copy(other);
}

TabularList::TabularList(TabularList &&other) {
    this->move(other);
}

TabularList &TabularList::operator=(const TabularList &other) {
    if (&other != this) {
        this->free();
        this->copy(other);
    }
    return *this;
}

TabularList &TabularList::operator=(TabularList &&other) {
    if (&other != this) {
        this->free();
        this->move(other);
    }
    return *this;
}

void TabularList::free() {
    for (TabularListElement *i = this->start; i != nullptr;) {
        TabularListElement *tle = i;
        i = i->next;
        delete tle;
    }
    this->start = this->end = nullptr;
}

void TabularList::copy(const TabularList &other) {
    // jedna linijka z petlą for - użyj iteratora
    for (TabularListIterator tli(other); !tli.at_end(); tli++) {
        this->push_back(tli.get());
    }
}

void TabularList::move(TabularList &other) {
    // przestaw wskaźniki
    this->start = other.start;
    this->end = other.end;
    other.start = other.end = nullptr;
}

#pragma endregion

#pragma region Implementacja TabularListIterator

TabularListIterator::TabularListIterator(const TabularList &tlist) {
    this->cursor = tlist.start;
    this->idx_cursor = 0;
}

bool TabularListIterator::at_end() const {
    return cursor == nullptr;
}

TabularListIterator &TabularListIterator::operator++() {
    if (!this->at_end()) {
        if (idx_cursor < cursor->count - 1) {
            idx_cursor++;
        } else {
            cursor = cursor->next;
            idx_cursor = 0;
        }
    }
    return *this;
}

TabularListIterator TabularListIterator::operator++(int) {
    // standardowa implementacja: skopiuj do tmp, wywołaj operator prefiksowy
    TabularListIterator tabularListIterator = *this;
    ++*this;
    return tabularListIterator;
}

int &TabularListIterator::get() const {
    return cursor->table[idx_cursor];
}

#pragma endregion

#pragma region Funkcje testujące

void test_add_iterate() {
    TabularList list;
    for (int i = 0; i < 1024; i++) {
        list.push_back(i);
    }

    for (TabularListIterator it(list); !it.at_end(); ++it) {
        cout << it.get() << endl;
    }
}

void test_big() {
    TabularList list;
    clock_t t0 = clock();
    for (int i = 0; i < 256 * 1024 * 1024; i++) {
        list.push_back(i);
    }
    clock_t t1 = clock();
    cout << "Allocation time" << (double) (t1 - t0) / CLOCKS_PER_SEC << endl;
    int cnt = 0;
    for (TabularListIterator it(list); !it.at_end(); ++it) {
        if (it.get() == 256 * 1024 * 1024 - 1) {
            cout << it.get() << endl;
        }
        cnt++;
    }
    clock_t t2 = clock();
    cout << "#elements: " << cnt << endl;
    cout << "Iteration time" << (double) (t2 - t1) / CLOCKS_PER_SEC << endl;
}

TabularList foo() {
    TabularList r;
    for (int i = 0; i < 1024; i++) r.push_back(i);
    return r;
}

void test_move() {
    // podczas debuggowania
    // ustaw break w move
    TabularList a;
    a = foo();
}

void test_copy_elision() {
    TabularList a = foo();
}

#pragma endregion

int main() {
    test_add_iterate();
    test_big();
    test_move();
    test_copy_elision();
    return 0;
}
