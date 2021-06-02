#include <iostream>

using namespace std;

// Tą flagą przełączamy wersje, będzie to 0,1,2
#define IMPLEMENTACJA 2

#if IMPLEMENTACJA == 0
int left(int i) {
return 2 * (i + 1) - 1;
}

int right(int i) {
    return 2 * (i + 1);
}

void swap(int &a, int &b) {
    int c(a);
    a = b;
    b = c;
}

void max_heapify(int *table, int heapsize, int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heapsize && table[i] < table[l]) {
        largest = l;
    }
    if (r < heapsize && table[largest] < table[r]) {
        largest = r;
    }
    if (largest != i) {
        swap(table[i], table[largest]);
        max_heapify(table, heapsize, largest);
    }
}

void print_heap(int *table, int heapsize, int idx, int indent) {
    if (idx >= heapsize)return;
    std::cout << std::endl;
    for (int i = 0; i < indent; i++)std::cout << "|  ";
    std::cout << table[idx];
    print_heap(table, heapsize, left(idx), indent + 1);
    print_heap(table, heapsize, right(idx), indent + 1);
}

void build_heap(int *table, int size) {
    for (int i = (size) / 2 - 1; i >= 0; i--) {
        max_heapify(table, size, i);
    }
}

void heapsort(int *table, int size) {
    build_heap(table, size);
    for (int i = size - 1; i > 0; i--) {
        swap(table[0], table[i]);
        max_heapify(table, i, 0);
    }
}

void test_int(){
    int tab[]={11,5,67,8,90,2,5,8,9,12,34};
    for(int i:tab){
        cout<<i<<" ";
    }
    cout<<endl<<"build_heap"<<endl;
    build_heap(tab,sizeof(tab)/sizeof(tab[0]));
    for(int i:tab){
        cout<<i<<" ";
    }
    cout<<endl<<"print_heap"<<endl;
    print_heap(tab, sizeof(tab) / sizeof(tab[0]), 0, 0);

    cout<<endl;
    heapsort(tab,sizeof(tab)/sizeof(tab[0]));
    for(int i:tab){
        cout<<i<<" ";
    }
    cout<<endl;
}

int main(){
    test_int();
}
#endif

#if IMPLEMENTACJA == 1

int left(int i) {
    return 2 * (i + 1) - 1;
}

int right(int i) {
    return 2 * (i + 1);
}

void swap(int &a, int &b) {
    int c(a);
    a = b;
    b = c;
}

template<class T>
void max_heapify(T *table, int heapsize, int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heapsize && table[i] < table[l]) {
        largest = l;
    }
    if (r < heapsize && table[largest] < table[r]) {
        largest = r;
    }
    if (largest != i) {
        swap(table[i], table[largest]);
        max_heapify(table, heapsize, largest);
    }
}

template<class T>
void print_heap(T *table, int heapsize, int idx, int indent) {
    if (idx >= heapsize)return;
    std::cout << std::endl;
    for (int i = 0; i < indent; i++)std::cout << "|  ";
    std::cout << table[idx];
    print_heap(table, heapsize, left(idx), indent + 1);
    print_heap(table, heapsize, right(idx), indent + 1);
}

template<class T>
void build_heap(T *table, int size) {
    for (int i = (size) / 2 - 1; i >= 0; i--) {
        max_heapify(table, size, i);
    }
}

template<class T>
void heapsort(T *table, int size) {
    build_heap(table, size);
    for (int i = size - 1; i > 0; i--) {
        swap(table[0], table[i]);
        max_heapify(table, i, 0);
    }
}

class osoba {
public:
    string imie;
    string nazwisko;

    bool operator<(osoba other) const {
        if (this->nazwisko == other.nazwisko) {
            return this->imie < other.imie;
        }
        return this->nazwisko < other.nazwisko;
    }
};

ostream &operator<<(ostream &os, const osoba &o) {
    os << "[" << o.nazwisko << " " << o.imie << "]";
    return os;
}

void test_osoba() {
    osoba tab[]{{"Jan",     "Kowalski"},
                {"Adrian",  "Nowak"},
                {"Zuzanna", "Nowak"},
                {"Anna",    "Kowal"},
                {"Oskar",   "Kowalik"},
                {"Justyna", "Marzec"},
                {"Klemens", "Nowakowski"},
                {"Piotr",   "Piotrowski"},
                {"Julia",   "Piotrowska"},
    };
    for (auto &i:tab) {
        cout << i << " ";
    }
    cout << endl << "build_heap" << endl;
    build_heap(tab, sizeof(tab) / sizeof(tab[0]));
    for (auto &i:tab) {
        cout << i << " ";
    }
    cout << endl << "print_heap" << endl;
    print_heap(tab, sizeof(tab) / sizeof(tab[0]), 0, 0);

    cout << endl;
    heapsort(tab, sizeof(tab) / sizeof(tab[0]));
    for (auto &i:tab) {
        cout << i << " ";
    }
    cout << endl;

}

void test_int() {
    int tab[] = {11, 5, 67, 8, 90, 2, 5, 8, 9, 12, 34};
    for (int i:tab) {
        cout << i << " ";
    }
    cout << endl << "build_heap" << endl;
    build_heap(tab, sizeof(tab) / sizeof(tab[0]));
    for (int i:tab) {
        cout << i << " ";
    }
    cout << endl << "print_heap" << endl;
    print_heap(tab, sizeof(tab) / sizeof(tab[0]), 0, 0);

    cout << endl;
    heapsort(tab, sizeof(tab) / sizeof(tab[0]));
    for (int i:tab) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    test_int();
    test_osoba();
}

#endif

#if IMPLEMENTACJA == 2

class osoba {
public:
    string imie;
    string nazwisko;

    bool operator<(osoba &other) const {
        if (this->nazwisko == other.nazwisko) {
            return this->imie < other.imie;
        }
        return this->nazwisko < other.nazwisko;
    }
};

ostream &operator<<(ostream &os, const osoba &o) {
    os << "[" << o.nazwisko << " " << o.imie << "]";
    return os;
}

template<class T>
class DefaultComparator {
public:
    static bool less(T &a, T &b) {
        return a < b;
    }
};

class MyComparator {
public:
    static bool less(osoba &a, osoba &b) {
        if ((a.imie.back() == 'a' && b.imie.back() == 'a') || (a.imie.back() != 'a' && b.imie.back() != 'a')) {
            if (a.nazwisko == b.nazwisko)
                return a.imie < b.imie;
            return a.nazwisko > b.nazwisko;
        } else if (a.imie.back() == 'a' && b.imie.back() != 'a')
            return true;
        else if (a.imie.back() != 'a' && b.imie.back() == 'a')
            return false;
    }
};

int left(int i) {
    return 2 * (i + 1) - 1;
}

int right(int i) {
    return 2 * (i + 1);
}

void swap(int &a, int &b) {
    int c(a);
    a = b;
    b = c;
}

template<class T, class Comp = DefaultComparator<T>>
void max_heapify(T *table, int heapsize, int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heapsize && Comp::less(table[i], table[l])) {
        largest = l;
    }
    if (r < heapsize && Comp::less(table[largest], table[r])) {
        largest = r;
    }
    if (largest != i) {
        swap(table[i], table[largest]);
        max_heapify<T, Comp>(table, heapsize, largest);
    }
}

template<class T, class Comp = DefaultComparator<T>>
void print_heap(T *table, int heapsize, int idx, int indent) {
    if (idx >= heapsize)return;
    std::cout << std::endl;
    for (int i = 0; i < indent; i++)std::cout << "|  ";
    std::cout << table[idx];
    print_heap<T, Comp>(table, heapsize, left(idx), indent + 1);
    print_heap<T, Comp>(table, heapsize, right(idx), indent + 1);
}

template<class T, class Comp = DefaultComparator<T>>
void build_heap(T *table, int size) {
    for (int i = (size) / 2 - 1; i >= 0; i--) {
        max_heapify<T, Comp>(table, size, i);
    }
}

template<class T, class Comp = DefaultComparator<T>>
void heapsort(T *table, int size) {
    build_heap<T, Comp>(table, size);
    for (int i = size - 1; i > 0; i--) {
        swap(table[0], table[i]);
        max_heapify<T, Comp>(table, i, 0);
    }
}

void test_osoba() {
    osoba tab[]{{"Jan",     "Kowalski"},
                {"Adrian",  "Nowak"},
                {"Zuzanna", "Nowak"},
                {"Anna",    "Kowal"},
                {"Oskar",   "Kowalik"},
                {"Justyna", "Marzec"},
                {"Klemens", "Nowakowski"},
                {"Piotr",   "Piotrowski"},
                {"Julia",   "Piotrowska"},
    };
    for (auto &i:tab) {
        cout << i << " ";
    }
    cout << endl << "build_heap" << endl;
    build_heap<osoba, MyComparator>(tab, sizeof(tab) / sizeof(tab[0]));
    for (auto &i:tab) {
        cout << i << " ";
    }
    cout << endl << "print_heap" << endl;
    print_heap<osoba, MyComparator>(tab, sizeof(tab) / sizeof(tab[0]), 0, 0);

    cout << endl;
    heapsort<osoba, MyComparator>(tab, sizeof(tab) / sizeof(tab[0]));
    for (auto &i:tab) {
        cout << i << " ";
    }
    cout << endl;

}

void test_int() {
    int tab[] = {11, 5, 67, 8, 90, 2, 5, 8, 9, 12, 34};
    for (int i:tab) {
        cout << i << " ";
    }
    cout << endl << "build_heap" << endl;
    build_heap(tab, sizeof(tab) / sizeof(tab[0]));
    for (int i:tab) {
        cout << i << " ";
    }
    cout << endl << "print_heap" << endl;
    print_heap(tab, sizeof(tab) / sizeof(tab[0]), 0, 0);

    cout << endl;
    heapsort(tab, sizeof(tab) / sizeof(tab[0]));
    for (int i:tab) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    test_int();
    test_osoba();
}

#endif