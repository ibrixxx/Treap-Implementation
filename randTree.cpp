#ifndef RANDTREE_CPP
#define RANDTREE_CPP
#include "randTree.h"

using namespace std;


template <typename tip>
bool randTree<tip>::FindRek(tip element, Cvor* cvor) {
    if(cvor == nullptr)
        return false;
    if(cvor->vrijednost == element)
        return true;
    if(cvor->vrijednost > element)
        return FindRek(element, cvor->lijevo);
    return FindRek(element, cvor->desno);
}


template <typename tip>
void randTree<tip>::inorderRek(Cvor* cvor) {
    if(cvor) {
        inorderRek(cvor->lijevo);
        cout<<"vrijednost: "<<cvor->vrijednost<<" | prioritet: "<<cvor->prioritet;
        if(cvor->lijevo)
            cout<<", lijevo dijete: "<<cvor->lijevo->vrijednost;
        if(cvor->desno)
            cout<<", desno dijete: "<<cvor->desno->vrijednost;
        cout<<endl;
        inorderRek(cvor->desno);
    }
}


template <typename tip>
typename randTree<tip>::Cvor* randTree<tip>::insertRek(tip element, Cvor* cvor, int prioritett) {
    int randBroj = prioritett;
    if(cvor == nullptr) {
        Cvor* rez = new Cvor(element, randBroj);
        return rez;
    }
    else if(cvor->vrijednost < element) {
        cvor->desno = insertRek(element, cvor->desno, randBroj);
        if(cvor->desno->prioritet > cvor->prioritet){
            Cvor* pom = cvor->desno;
            cvor->desno = pom->lijevo;
            pom->lijevo = cvor;
            return pom;
        }
    }
    else if(cvor->vrijednost > element) {
        cvor->lijevo = insertRek(element, cvor->lijevo, randBroj);
        if(cvor->lijevo->prioritet > cvor->prioritet){
            Cvor* pom = cvor->lijevo;
            cvor->lijevo = pom->desno;
            pom->desno = cvor;
            return pom;
        }
    }
    return cvor;
}



template <typename tip>
typename randTree<tip>::Cvor* randTree<tip>::deleteRek(tip element, Cvor* cvor) {
    if(cvor == nullptr)
        return cvor;
    if(element > cvor->vrijednost)
        cvor->desno = deleteRek(element, cvor->desno);
    else if(element < cvor->vrijednost)
        cvor->lijevo = deleteRek(element, cvor->lijevo);
    else if(!cvor->lijevo){
        Cvor* pom = cvor->desno;
        delete(cvor);
        cvor = pom;
    }
    else if(!cvor->desno){
        Cvor* pom = cvor->lijevo;
        delete(cvor);
        cvor = pom;
    }
    else if(cvor->lijevo->prioritet < cvor->desno->prioritet) {
        Cvor* pom = cvor->desno;
        cvor->desno = pom->lijevo;
        pom->lijevo = cvor;
        cvor = pom;
        cvor->lijevo = deleteRek(element, cvor->lijevo);
    }
    else {
        Cvor* pom = cvor->lijevo;
        cvor->lijevo = pom->desno;
        pom->desno = cvor;
        cvor = pom;
        cvor->desno = deleteRek(element, cvor->desno);
    }
    return cvor;
}


template <typename tip1>
pair<randTree<tip1>, randTree<tip1>> Split(tip1 element, randTree<tip1> &s) {
    int pr = s.korijen->prioritet;
    pr++;
    s.Insert(element, pr);
    randTree<tip1> s1;
    randTree<tip1> s2;
    s1.korijen = s.korijen->lijevo;
    s2.korijen = s.korijen->desno;
    pair<randTree<tip1>, randTree<tip1>> rez;
    rez.first = s1;
    rez.second = s2;
    return rez;
}




#endif //RANDTREE_CPP
