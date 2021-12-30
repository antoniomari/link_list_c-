//
// Created by 39347 on 28/10/2021.
//

#include <iostream>
#include "link_list.cpp"

using namespace std;

template<class T>
void print_list_detailed(link_list<T>&);

template<class T>
void print_list(link_list<T>& l);

int main(){
    link_list<int> l;

    l.insert(5, 0);
    print_list(l);

    l.insert(6, 1);
    print_list(l);

    l.append(10);
    l[0] = 1;
    print_list(l);

    l[1] = 3;
    print_list(l);

    l[-2] = 4;
    print_list(l);

    //-----------------------------------
    //       EXTENDING LISTS
    //-----------------------------------

    link_list<int> l1;
    link_list<int> l2;

    for(int i = 0; i < 5; i++)
        l1.append(i);

    cout << "List 1\n";
    print_list(l1);

    for(int i = 0; i < 5; i++)
        l2.append(i+5);

    cout << "\nList 2\n";
    print_list(l2);

    l1.extend(l2);

    cout << "\nList 1 after extension\n";
    print_list(l1);

    //const auto address1 = l.first();

    /*
    l.cancel(1);
    print_list_detailed(l);
    */

    return 0;
}

template<class T>
void print_list_detailed(link_list<T>& l)
{
    auto iter = l.first();

    for(int c = 0; !l.is_end(iter); c++)
    {

        cout << "Element n: " << c << "- Address: " << iter << endl;
        cout << "- " << iter->getPrec() << " - " << iter->getElemento() << " - " << iter->getSucc() << " -\n";

        iter = l.next(iter);
    }
}

template<class T>
void print_list(link_list<T>& l)
{
    auto iter = l.first();

    cout << "[";
    while(!l.is_end(iter))
    {
        cout << iter->getElemento();

        iter = iter->getSucc();
        if(!l.is_end(iter))
            cout << ", ";
    }//end while

    cout << "]\n";

}//end print_list
