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
            //lijeva rotacija
            Cvor* pom = cvor->desno;
            cvor->desno = pom->lijevo;
            pom->lijevo = cvor;
            return pom;
        }
    }
    else if(cvor->vrijednost > element) {
        cvor->lijevo = insertRek(element, cvor->lijevo, randBroj);
        if(cvor->lijevo->prioritet > cvor->prioritet){
            //desna rotacija
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
    typename randTree<tip1>::Cvor *k1 = s.korijen->lijevo;
    typename randTree<tip1>::Cvor *k2 = s.korijen->desno;
    s1.korijen = k1;
    s2.korijen = k2;
    pair<randTree<tip1>, randTree<tip1>> rez;
    rez.first = s1;
    rez.second = s2;
    return rez;
}



template <typename Tip>
randTree<Tip>& Join(randTree<Tip> &t1, randTree<Tip> &t2) {
    typename randTree<Tip>::Cvor *pok1;
    if(t1.korijen->vrijednost < t2.korijen->vrijednost)
        pok1 = t1.korijen;
    else
        pok1 = t2.korijen;
    while(pok1->desno != nullptr)
        pok1 = pok1->desno;

    Tip pom = pok1->vrijednost;
    pom++;

    typename randTree<Tip>::Cvor* cvor = new typename randTree<Tip>::Cvor(pom, -1);
    randTree<Tip>* rez = new randTree<Tip>();

    rez->korijen = cvor;
    rez->korijen->lijevo = t1.korijen;
    rez->korijen->desno = t2.korijen;

    rez->korijen = rez->deleteRek(pom, cvor);

    return *rez;
}


template <typename Tip>
randTree<Tip>& Union(randTree<Tip> &t1, randTree<Tip> &t2) {
    if(t1.korijen == nullptr)
        return t2;
    if(t2.korijen == nullptr)
        return t1;
    if(t1.korijen->prioritet < t2.korijen->prioritet){
        /*auto temp = t1.korijen;
        t1.korijen = t2.korijen;
        t2.korijen = temp;*/
        swap(t1.korijen, t2.korijen);
    }

    pair<randTree<Tip>, randTree<Tip> > p = Split(t1.korijen->vrijednost, t2);

    //randTree<Tip> *t1Lijevo = new randTree<Tip>(), *t1Desno = new randTree<Tip>(), *manje = new randTree<Tip>(), *vece = new randTree<Tip>();
    typename randTree<Tip>::Cvor *k1 = t1.korijen->lijevo;
    typename randTree<Tip>::Cvor *k2 = t1.korijen->desno;

    randTree<Tip> t1Lijevo; t1Lijevo.korijen = k1;
    randTree<Tip> t1Desno; t1Desno.korijen = k2;

    return Join(Union(t1Lijevo, p.first), Union(t1Desno, p.second));
}



#endif //RANDTREE_CPP
