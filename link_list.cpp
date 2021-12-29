//
// implementation of linked list
//


#ifndef LINK_LIST
#define LINK_LIST
#include "abs_list.h"
#include "cella.h"
#include<iostream>

#define END -1

using namespace std;
template<class T = double>
class link_list : public abs_list<T>
{
public:
    typedef Cella<T>* pos;
    link_list(); // costruttore
    link_list(const link_list<T>&); // costruttore di copia
    ~link_list(); // distruttore
    bool is_empty() const;
    T& operator[](int index);
    void insert(T, int);
    void cancel(int);
    //scansione sequenziale
    pos first();
    pos next(pos);
    pos prior(pos);
    bool is_end(pos);
    // operators append and extend
    void append(T);
    void extend(link_list<T>);
private:
    pos list;
    int length;
    //la list è un puntatore ad oggetto Cella
};


// constructor
template<class T>
link_list<T>::link_list()
{
    list = nullptr;
    length = 0;
}


//copy constructor
template<class T>
link_list<T>::link_list(const link_list<T>& l)
{
    //copy length
    length = l.length;
    pos copy_from = l.list;

    //controllo list vuota
    if(copy_from == nullptr)
        list = nullptr;

    list = new Cella<T>;
    list->setElemento(copy_from->getElemento());
    pos copy_to;
    copy_from = copy_from->getSucc();

    //per le successive copie
    pos copy_after_this = list;

    while(copy_from != nullptr)
    {
        copy_to = new Cella<T>(copy_from->getElemento());
        copy_after_this->setSucc(copy_to);
        copy_to->setPrec(copy_after_this);
        //nota: copy_to->getSucc è nullptr

        //aggiorna posizioni
        copy_after_this = copy_after_this->getSucc(); // == copy_to
        copy_from = copy_from->getSucc();
    }

}


template<class T>
link_list<T>::~link_list()
{
    while(list != nullptr)
    {
        pos to_delete = list;
        list = list->getSucc();
        delete to_delete;

    }//end while
}


template<class T>
bool link_list<T>::is_empty() const
{
    return list == nullptr;
}


template<class T>
T& link_list<T>::operator[](int index)
{
    //safe check
    if(index >= length || index < -length)
    {
        throw invalid_argument("Posizione non valida");
    }

    //case negative index
    if(index < 0)
    {
        index = length + index;
    }

    pos temp = list;
    for(int i = 0; i < index; i++)
    {
        temp = temp->getSucc();
    }

    T& elem = temp->elem();
    return elem;
}//end operator[]


template<class T>
void link_list<T>::insert(T a, int index)
{
    // controllo
    if(index > length || index < -length - 1)
        throw invalid_argument("Posizione non valida");

    pos temp = new Cella<T>(a);

    //negative index
    if(index < 0)
        index = length + 1 + index;

    //se inserisci in prima pos
    if(index == 0)
    {
        temp->setSucc(list);
        if(list != nullptr)
            list->setPrec(temp);
        list = temp;
    }
    else //se inserisci in qualunque altra pos
    {
        auto p = list;
        for(int i = 0; i < index - 1; i++)
        {
            p = p->getSucc();
        }

        //caso 1: alla fine
        if(index == length)
        {
            p->setSucc(temp);
            temp->setPrec(p);
        }
        else //caso 2: inner
        {
            (p->getPrec())->setSucc(temp);
            temp->setPrec(p->getPrec());
            temp->setSucc(p);
            p->setPrec(temp);
        }
    }
    length++;
}

template<class T>
void link_list<T>::cancel(int index)
{
    // controllo
    if(index >= length || index < -length)
        throw invalid_argument("Posizione non valida");

    //negative index
    if(index < 0)
        index = length + index;


    //se cancelli la prima pos
    if(index == 0)
    {
        pos temp = list;
        list = list->getSucc();
        list->setPrec(nullptr);
        delete temp;
    }
    else //se cancelli qualunque altra pos
    {
        //posizionati
        pos temp = list;

        for(int i = 0; i < index; i++)
            temp = temp->getSucc();

        (temp->getPrec())->setSucc(temp->getSucc());

        if(temp->getSucc() != nullptr) // se non è l'ultima posizione
            (temp->getSucc())->setPrec(temp->getPrec());

        delete temp;
    }

    length--;
}


//SCANSIONE SEQUENZIALE

template<class T>
typename link_list<T>::pos link_list<T>::first()
{
    return list;
}

template<class T>
typename link_list<T>::pos link_list<T>::next(pos p)
{
    return p->getSucc();
}

template<class T>
typename link_list<T>::pos link_list<T>::prior(pos p)
{
    return p->getPrec();
}

template<class T>
bool link_list<T>::is_end(pos p) //correttamente: is last
{
    return p == nullptr;
}

template<class T>
void link_list<T>::append(T el)
{
    this->insert(el, END);
}

template<class T>
void link_list<T>::extend(link_list<T> l2)
{
    auto iter = l2.first();

    while(!l2.is_end(iter))
    {
        this->insert(iter->getElemento(), END);
        iter = iter->getSucc();
    }

}

#endif //LINK_LIST
