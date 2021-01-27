#ifndef RANDTREE_H
#define RANDTREE_H
#include <cstdlib>
#include <utility>

using namespace std;

template <typename tip>
class randTree {
    struct Cvor {
        tip vrijednost;
        int prioritet;
        Cvor *lijevo, *desno, *roditelj;
        Cvor() {}
        Cvor(tip vrijednost, int prioritet, Cvor* roditelj = nullptr, Cvor* lijevo = nullptr, Cvor* desno = nullptr):
            vrijednost(vrijednost), prioritet(prioritet), roditelj(roditelj), lijevo(lijevo), desno(desno) {}
    };
    Cvor* korijen;

    bool FindRek(tip element, Cvor* cvor);

    void inorderRek(Cvor* cvor);

    Cvor* insertRek(tip element, Cvor* cvor, int prioritett = rand() % 1000 + 1);

    Cvor* deleteRek(tip element, Cvor* cvor);

    public:

    randTree(): korijen(nullptr) {}

    bool Find(tip element) { return FindRek(element, korijen); }

    void Insert(tip element) { korijen = insertRek(element, korijen); }

    void Delete(tip element) { korijen = deleteRek(element, korijen); }

    template <typename tip1>
    friend pair<randTree<tip1>, randTree<tip1>> Split(tip1 element, randTree<tip1> &s);

    void inorderIspis() { inorderRek(korijen); }

};

#include "randTree.cpp"

#endif // RANDTREE_H
