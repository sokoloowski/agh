#include <cstring>
#include <iostream>

using namespace std;

#pragma region Deklaracje

class TextListElement {
    friend class TextList;

    /*
     * Tworzy kopię tekstu txt alokując pamięć na stercie
     * za pomocą operatora new
     */
    TextListElement(const char *txt);

    /*
     * Zwalnia pamięć elementu i jego danych!
     */
    ~TextListElement();

    TextListElement *next;
    TextListElement *prev;
    char *value;
};

class TextList {
    /* wskaźnik na pierwszy element */
    TextListElement *start;
    /* wskaźnik na ostatni element */
    TextListElement *end;
public:
    /* konstruktor*/
    TextList();

    /* destruktor */
    ~TextList();

    /*
     * Dodaje tekst na początku listy
     */
    void pushFront(const char *v);

    /*
     * Dodaje tekst na końcu listy
     */
    void pushBack(const char *v);

    /*
     * Zwraca wskaźnik do tekstu przechowywanego w pierwszym elemencie
     */
    const char *getFront() const;

    /*
     * Zwraca wskaźnik do tekstu przechowywanego w ostatnim elemencie
     */
    const char *getBack() const;

    /*
     * Usuwa pierwszy element
     */
    void deleteFront();

    /*
     * Usuwa ostatni element
     */
    void deleteBack();

    /*
     * Drukuje zawartość listy (w przód).
     * Oddziela elementy listy łańcuchem sep, kończy wydruk listy wypisując endWith
     */
    void dump(const char *sep = " ", const char *endWith = "\n") const;

    /*
     * Drukuje zawartość listy (w tył)
     * Oddziela elementy listy łańcuchem sep, kończy wydruk listy wypisując endWith
     */
    void rdump(const char *sep = " ", const char *endWith = "\n") const;

    /*
     * Konstruktor kopiujący
     */
    TextList(const TextList &other);

    /*
     * Operator przypisania
     */
    TextList &operator=(const TextList &other);

    /*
     * Czy lista jest pusta
     */
    bool isEmpty() const { return !start; }

protected:
    /* funkcja do wykorzystania, zwalania pamięć listy */
    void free();

    /* funkcja do wykorzystania,
     * zakłada, że lista jest pusta
     * ale zeruje wskaźniki start i end - bo będzie użyta w konstruktorze kopującym
     * i kopiuje do niej zawartość listy other
     */
    void copy(const TextList &other);
};

#pragma endregion

#pragma region Implementacje

TextListElement::TextListElement(const char *txt) {
    this->value = new char[strlen(txt) + 1];
    strcpy(this->value, txt);
    this->next = this->prev = nullptr;
}

TextListElement::~TextListElement() {
    delete[]this->value;
}

TextList::TextList() {
    start = end = 0;
}

TextList::~TextList() {
    free();
}

void TextList::pushFront(const char *v) {
    auto *listElement = new TextListElement(v);
    listElement->next = this->start;
    this->start = listElement;
    if (end == 0) this->end = this->start;

}

void TextList::pushBack(const char *v) {
    auto *listElement = new TextListElement(v);
    listElement->next = nullptr;
    listElement->prev = this->end;
    if (this->end) this->end->next = listElement;
    this->end = listElement;
    if (this->start == nullptr) this->start = this->end;
}

const char *TextList::getFront() const {
    return this->start->value;
}

const char *TextList::getBack() const {
    return this->end->value;
}


void TextList::deleteFront() {
    if (!this->start) return;
    TextListElement *to_delete = this->start;
    this->start = this->start->next;
    delete to_delete;
    if (this->start == nullptr) this->end = nullptr;
}

/*
 * Usuwa ostatni element
 */
void TextList::deleteBack() {
    TextListElement *newEnd = nullptr;
    for (TextListElement *i = this->start; i != nullptr; i = i->next) {
        if (i->next != nullptr && i->next == this->end) newEnd = i;
    }
    delete this->end;
    this->end = newEnd;
    if (this->end != nullptr) this->end->next = nullptr;
    if (this->end == nullptr) this->start = nullptr;
}

/*
 * Drukuje zawartość listy (w przód)
 */
void TextList::dump(const char *sep, const char *endWith) const {
    for (TextListElement *i = this->start; i != nullptr; i = i->next) {
        cout << i->value << sep;
    }
    cout << endWith;
}

/*
 * Drukuje zawartość listy (od tyłu do przodu)
 */
void TextList::rdump(const char *sep, const char *endWith) const {
    for (TextListElement *i = this->end; i != nullptr; i = i->prev) {
        cout << i->value << sep;
    }
    cout << endWith;
}

void TextList::free() {
    // jedna linijka
    while (this->start != nullptr) deleteFront();
}

void TextList::copy(const TextList &other) {
    // 4 linijki, pamiętaj w konstruktorze kopiującym kopiujesz dane do niezainicjowanego obiektu
    this->start = this->end = nullptr;
    for (TextListElement *i = other.start; i != 0; i = i->next) {
        this->pushBack(i->value);
    }
}

TextList::TextList(const TextList &other) {
    copy(other);
}

TextList &TextList::operator=(const TextList &other) {
    if (&other != this) {
        free();
        copy(other);
    }
    return *this;
}

#pragma endregion

#pragma region Testy

static void test_push_delete() {
    char buf[] = "aa bb cc dd ee ff gg hh ii jj kk ll";
    TextList list;
    for (char *ptr = strtok(buf, " ,.;\n"); ptr; ptr = strtok(NULL, " ,.;\n")) {
        list.pushBack(ptr);
        list.pushFront(ptr);
    }
    list.dump();
    bool flag = true;
    while (!list.isEmpty()) {
        if (flag)list.deleteFront();
        else list.deleteBack();
        list.dump();
        flag = !flag;
    }
}

static void kochanowski() {
    char buf[] = "Folgujmy paniom nie sobie, ma rada;\n"
                 "Miłujmy wiernie nie jest w nich przysada.\n"
                 "Godności trzeba nie za nic tu cnota,\n"
                 "Miłości pragną nie pragną tu złota.\n"
                 "Miłują z serca nie patrzają zdrady,\n"
                 "Pilnują prawdy nie kłamają rady.\n"
                 "Wiarę uprzejmą nie dar sobie ważą,\n"
                 "W miarę nie nazbyt ciągnąć rzemień każą.\n"
                 "Wiecznie wam służę nie służę na chwilę,\n"
                 "Bezpiecznie wierzcie nierad ja omylę.";
    TextList list;
    for (char *ptr = strtok(buf, " ,.;\n"); ptr; ptr = strtok(NULL, " ,.;\n")) {
        list.pushBack(ptr);
    }
    list.dump();
    std::cout << "-----------------------------------" << std::endl;
    list.rdump();
}


static void test_copy_assignment() {
    char buf[] = "aa bb cc dd ee ff gg hh ii jj kk ll";
    TextList list;
    for (char *ptr = strtok(buf, " ,.;\n"); ptr; ptr = strtok(NULL, " ,.;\n")) {
        list.pushBack(ptr);
        list.pushFront(ptr);
    }
    list.dump();
    TextList list2 = list;
    list2.dump();

    list2.pushFront("11");
    list2.pushFront("22");
    list2.pushFront("33");
    list2.pushFront("44");
    list = list2;
    list.dump();

}

#pragma endregion

int main() {
    test_push_delete();
    kochanowski();
    test_copy_assignment();
    return 0;
}
