#ifndef RANDTREE_H
#define RANDTREE_H
#include <cstdlib>

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

    Cvor* rotirajLijevo(Cvor* cvor) {
        Cvor* pom = cvor->desno;
        cvor->desno = pom->lijevo;
        pom->lijevo = cvor;
        return pom;
    }

    Cvor* rotirajDesno(Cvor* cvor) {
        Cvor* pom = cvor->lijevo;
        cvor->lijevo = pom->desno;
        pom->desno = cvor;
        return pom;
    }

    void izvrsiRotacije(Cvor* dijete) {
        while(dijete->roditelj != nullptr && dijete->prioritet > dijete->roditelj->prioritet) {
            if(dijete->roditelj->lijevo == dijete){
                Cvor* pom1 = dijete->desno;
                Cvor* pom2 = dijete->roditelj->roditelj;
                    dijete->desno = dijete->roditelj;
                    dijete->desno->roditelj = dijete;
                    dijete->desno->lijevo = pom1;
                dijete->roditelj = pom2;
                cout<<"pomjeram "<<dijete->vrijednost<<endl;
                cout<<"sada "<<dijete->prioritet<<endl;
            }
            else{
                Cvor* pom1 = dijete->lijevo;
                Cvor* pom2 = dijete->roditelj->roditelj;
                    dijete->lijevo = dijete->roditelj;
                    dijete->lijevo->roditelj = dijete;
                    dijete->lijevo->desno = pom1;

                dijete->roditelj = pom2;
                cout<<"pomjeram "<<dijete->vrijednost<<endl;
                cout<<"sada "<<dijete->prioritet<<endl;
            }
        }
        if(dijete->prioritet > korijen->prioritet)
            korijen = dijete;
    }

    bool FindRek(tip element, Cvor* cvor) {
        if(cvor == nullptr)
            return false;
        if(cvor->vrijednost == element)
            return true;
        if(cvor->vrijednost > element)
            return FindRek(element, cvor->lijevo);
        return FindRek(element, cvor->desno);
    }

    void inorderRek(Cvor* cvor) {
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

    public:

    randTree(): korijen(nullptr) {}

    bool Find(tip element) {
        return FindRek(element, korijen);
    }

    void Insert(tip element) {
        int randomBroj = rand() % 1000 + 1;
        if(korijen == nullptr){
            korijen = new Cvor(element, randomBroj);
            return;
        }
        Cvor* trenutni = korijen;
        while(trenutni != nullptr) {
            if(trenutni->vrijednost == element)
                return;
            if(trenutni->vrijednost > element) {
               if(trenutni->lijevo != nullptr)
                 trenutni = trenutni->lijevo;
               else {
                 trenutni->lijevo = new Cvor(element, randomBroj, trenutni);
                 izvrsiRotacije(trenutni->lijevo);
                 return;
               }
            }

            else {
               if(trenutni->desno != nullptr)
                 trenutni = trenutni->desno;
               else {
                 trenutni->desno = new Cvor(element, randomBroj, trenutni);
                 izvrsiRotacije(trenutni->desno);
                 return;
               }
            }
        }
    }


    void inorderIspis() {
        inorderRek(korijen);
    }

};


#endif // RANDTREE_H
