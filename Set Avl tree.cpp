/*#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;
template<class T, class F=Comparator<T>> class set {
    struct element {
        T info;
        element* st, * dr;
        int h;
    }*el;
    int nr_elem;
    F comp;
public:
    set();
    set(const set& a);
    set<T, F>& operator=(const set<T, F>& nou);
    void add(T a);
    void del(T a);
    template<typename U, typename G>
    friend ostream& operator<<(ostream&, set<U, G>&);
    int size() const;
    bool find(const T a);
    void elem(element*el, T* a, int i);
    set<T, F>& rot_dr();
    set<T, F>& rot_st();
    void fr_st();
    void fr_dr();
    void inaltime(T a);
};
template<class T, class F>
void set<T, F>::inaltime(T a) {
        set<T, F> aux;
        aux.el = el;
        bool ok = true;
        while (ok) {
            if (a > aux.el->info)
            {
                aux.el->h--;
                aux.el = aux.el->dr;
            }
            else if (a < aux.el->info) {
                aux.el->h--;
                aux.el = aux.el->dr;
            }
            else {
                ok = false;
            }
        }
    }

template<class T, class F>
void set<T, F>::add(T a) {
    if (nr_elem == 0) {
        el->info = a;
        el->h = 1;
        nr_elem = 1;
    }
    else{
        set<T, F> aux;
        aux.el = el;
        bool ok = true;
        while (ok) {
            if (a > aux.el->info)
            {
                if (aux.el->dr == NULL) {
                    aux.el->dr = new element;
                    aux.el->dr->info = a;
                    aux.el->dr->dr = NULL;
                    aux.el->dr->st = NULL;
                    aux.el->dr->h = 1;
                    if (aux.el->st != NULL) {
                    aux.el->h++;
                    this->inaltime(a);
                    }
                    nr_elem++;
                }
                else {
                    aux.el->h++;
                    aux.el = aux.el->dr;
                    ok = false;
                }
            }
            else if (a < aux.el->info) {
                if (aux.el->st == NULL) {
                    aux.el->st = new element;
                    aux.el->st->info = a;
                    aux.el->st->dr = NULL;
                    aux.el->st->st = NULL;
                    aux.el->st->h = 1;
                    if (aux.el->dr == NULL) {
                        aux.el->h++;
                        this->inaltime(a);
                    }
                    nr_elem++;
                }
                else {
                    aux.el->h++;
                    aux.el = aux.el->dr;
                    ok = false;
                }
            }
        }
    }
    if (el->st != NULL && el->dr != NULL)
    {
        int balans = el->st->h - el->dr->info;
        if (balans > 1 && a < el->st->info)
            this->rot_dr();
        if (balans<-1 && a>el->dr->info)
            this->rot_st();
        if (balans > 1 && a > el->st->info)
        {
            this->fr_st();
            this->rot_dr();
        }
        if (balans < -1 && a < el->dr->info)
        {
            this->fr_dr();
            this->rot_st();
        }
    }
}
template<class T, class F>
set<T, F>::set() {
    el = new element;
    el->st = NULL;
    el->dr = NULL;
    el->h = 0;
    nr_elem = 0;
}

template<class T, class F>
set<T, F>::set(const set& a) {
    el = new element;
    el.info = a.el->info;
    el.st = a.el->st;
    el.dr = a.el->dr;
    el.h = a.el->h;
    nr_elem = a.nr_elem;
    cout << "Copiere efectuata" << endl;
}

template<class T, class F>
int set<T, F>::size() const {
    return nr_elem;
}

template<class T, class F>
bool set<T, F>::find(const T a) {
    set<T, F> c;
    c.el = el;
    while(true) {
        if (a > c.el->info && c.el->dr != NULL)
            c.el = c.el->dr;
        else
            if (a < c.el->info && c.el->st != NULL)
                c.el = c.el->st;

        else 
            if (a == c.el->info)
                return true;
        else
        return false;
    }
}

template<class T, class F>
void set<T, F>::fr_dr() {
    set<T, F> rad;
    set<T, F> aux;
    rad.nr_elem = nr_elem;
    aux.nr_elem = nr_elem;
    rad.el = el->dr->st;
    aux.el = el->dr;

    aux.el->st = rad.el->dr;
    rad.el->dr = aux.el;
    el->dr = rad.el;
    aux.el->h = max(aux.el->st->h, aux.el->dr->h) + 1;
    rad.el->h = max(rad.el->st->h, rad.el->dr->h) + 1;
    el->h = max(el->st->h, el->dr->h) + 1;
}

template<class T, class F>
void set<T, F>::fr_st() {
    set<T, F> rad;
    set<T, F> aux;
    rad.nr_elem = nr_elem;
    aux.nr_elem = nr_elem;
    rad.el = el->st->dr;
    aux.el = el->st;

    aux.el->dr = rad.el->st;
    rad.el->st = aux.el;
    el->st = rad.el;
    aux.el->h = max(aux.el->st->h, aux.el->dr->h) + 1;
    rad.el->h = max(rad.el->st->h, rad.el->dr->h) + 1;
    el->h = max(el->st->h, el->dr->h) + 1;
}

template<class T, class F>
set<T, F>& set<T, F>::rot_st()
{
    set<T, F> rad;
    set<T, F> aux;
    rad.nr_elem = nr_elem;
    aux.nr_elem = nr_elem;
    rad.el = el->dr;
    aux.el = rad.el->st;

    rad.el->st = el;
    el->dr = aux.el;

    el->h = max(el->st->h, el->dr->h) + 1;
    rad.el->h = max(rad.el->st->h, rad.el->dr->h) + 1;
    return rad;
}

template<class T, class F>
set<T,F>& set<T,F>:: rot_dr()
{
    set<T, F> rad;
    set<T, F> aux;
    rad.nr_elem = nr_elem;
    aux.nr_elem = nr_elem;
    rad.el = el->st;
    aux.el = rad.el->dr;

    rad.el->dr = el;
    el->st = aux.el;

    el->h = max(el->st->h, el->dr->h) + 1;
    rad.el->h = max(rad.el->st->h, rad.el->dr->h) + 1; 
    return rad;
}

template<class T, class F>
void set<T, F>::elem(element* el, T* a, int i) {
    if (i<nr_elem)
    {
        a[i] = el->info;
        if (el->st != NULL)
        {
            elem(el->st, a, i + 1);
            i++;
        }
        if (el->dr != NULL)
            elem(el->dr, a, i + 1);
    }
}

template<class T, class F>
set<T, F>& set<T, F>::operator=(const set<T, F>& nou) {
    el.info=nou.el->info;
    el.st = nou.el->st;
    el.dr = nou.el->dr;
    el.h = nou.el->h;
    nr_elem = nou.nr_elem;
}

template<class T, class F>
ostream& operator<<(ostream& out, set<T, F>& s) {
    out << s.nr_elem << ' ';
    T *a = new T[s.nr_elem];
    s.elem(s.el, a, 0);
    for (int i = 0; i < s.nr_elem; i++)
        out << a[i] << ' ';
    return out;
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
    set<int> a;
    a.add(2);
    a.add(3);
    a.add(1);
    cout << a;
}

*/