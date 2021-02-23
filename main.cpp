#include <iostream>
#include "randTree.h"

using namespace std;


int main() {
    srand (time(NULL));

    randTree<int> t;
    randTree<int> tt;

    t.Insert(18);
    tt.Insert(2);
    t.Insert(4);
    tt.Insert(12);
    t.Insert(20);
    tt.Insert(68);
    t.Insert(88);
    tt.Insert(58);
    t.Insert(48);


    //randTree<int> tre = Union(t, tt); tre.inorderIspis();
    //cout<<tre.dajKorijen().first<<' '<<tre.dajKorijen().second<<endl;

    //cout<<boolalpha<<t.Find(12)<<endl;
    t.inorderIspis();
    cout<<endl;
    t.Delete(22);
    t.Insert(22, 999);
    t.inorderIspis();
    cout<<endl;
    t.Delete(22);
    //t.inorderIspis();

    t.inorderIspis();
    cout<<t.dajKorijen().first<<' '<<t.dajKorijen().second<<endl;

    /*
    pair<randTree<int>, randTree<int>> p =  Split(22, t);

    randTree<int> tr = p.first;
    tr.inorderIspis();

    randTree<int> t2 = p.second;
    t2.inorderIspis();

    randTree<int> ttt = Join(tr, t2);
    ttt.inorderIspis();
    cout<<ttt.dajKorijen().first<<' '<<ttt.dajKorijen().second;
    */

    return 0;
}
