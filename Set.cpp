#include <iostream>
using namespace std;
template<class T, class F=Comparator<T>> class set {
    T* elem;
    int nr_elem;
    F comp;
public:
    set();
    set(const set& a);
    set& operator=(const set& nou);
    void add(T a);
    void del(T a);
    template<typename U, typename G>
    friend ostream& operator<<(ostream&, const  set<U, G>&);
    int size() const;
    bool find(const T a);
    void testare();
};

template<class T, class F>
set<T, F>::set() {
    elem = NULL;
    nr_elem = 0;
}

template<class T, class F>
set<T, F>::set(const set& a) {
    elem = new T[a.nr_elem];
    for (int i = 0;i < a.nr_elem; i++)
        elem[i] = a.elem[i];
    nr_elem =a.nr_elem;
    cout << "Copiere efectuata"<<endl;
}

template<class T, class F>
ostream& operator<<(ostream& out, const  set<T, F>& s) {
    out << s.nr_elem << endl;
    for (int i = 0; i < s.nr_elem; i++)
        out << s.elem[i] << " ";
    cout << endl;
    return out;
}

template<class T, class F>
set<T, F>& set<T, F>::operator=(const set& nou){
    delete[] elem;
    elem = new T[nou.nr_elem];
    for (int i = 0;i < nou.nr_elem; i++)
        elem[i] = nou.elem[i];
    nr_elem = nou.nr_elem;
    return *this;
}

template<class T, class F>
void set<T, F>::add(T a) {
    bool ok=false;
    for (int i = 0; i < nr_elem; i++)
        if (comp(elem[i], a) == true)
            ok = true;
    if (ok == false)
    {
        set<T> aux;
        aux.elem = new T[nr_elem + 1];
        for (int i = 0; i < nr_elem; i++)
            aux.elem[i] = elem[i];
        aux.elem[nr_elem] = a;
        aux.nr_elem = nr_elem + 1;
        *this = aux;
    }
}

template<class T, class F>
void set<T, F>::del(T a) {
    bool ok = false;
    for (int i = 0; i < nr_elem; i++)
        if (comp(elem[i], a) == true)
            ok = true;
    if (ok == true) {
        for (int i = 0; i < nr_elem; i++) {
            if (elem[i] == a)
            {
                for (int j = i; j < nr_elem - 1; j++)
                    elem[j] = elem[j + 1];
                break;
            }
        }
        nr_elem--;
    }
}

template<class T, class F>
int set<T, F>::size() const {
    return nr_elem;
}

template<class T, class F>
bool set<T, F>::find(const T a) {
    bool ok = false;
    for (int i = 0; i < nr_elem; i++)
        if (comp(elem[i], a) == true)
            ok = true;
    return ok;
}

template <class T> class Comparator {
public:
    bool operator () (const T& x, const T& y) {
        if (x == y)
            return true;
        else
            return false;
    }
};

template <> class Comparator<int> {
public:
    bool operator () (const int& x, const int& y) {
        if (x % 2 == 0 && y % 2 == 0 || x % 2 != 0 && y % 2 != 0)
            return true;
        else
            return false;
    }
};

int main()
{
    set<char> a;
    a.add('a');
    a.add('b');
    a.add('c');
    a.add('d');
    a.add('c');
    cout << a;
    a.del('c');
    a.del('e');
    cout << a;
    cout << a.find('d') << ' ' << a.find('g') << endl;
    set<int> b;
    for (int i = 0; i < 4; i++)
        b.add(i);
    cout << b;
    b.del(3);
    b.del(0);
    cout << b;
}

