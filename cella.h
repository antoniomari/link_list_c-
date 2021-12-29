//
// Created by 39347 on 02/11/2021.
//

#ifndef CELLA_H
#define CELLA_H

template<class T>
class Cella
{
public:
    typedef T tipoelem;
    Cella() { prec = nullptr; succ = nullptr; }
    explicit Cella(const tipoelem& elemento){ prec= nullptr; succ = nullptr; this->elemento = elemento; }
    void setElemento(tipoelem e){ elemento = e; }
    tipoelem getElemento() const {return elemento; }
    tipoelem& elem() {return elemento;}
    void setSucc(Cella* p){ succ = p; }
    Cella* getSucc() const{ return succ;}
    void setPrec(Cella* p) { prec = p;}
    Cella* getPrec() const{ return prec;}
private:
    tipoelem elemento;
    Cella * prec;
    Cella * succ;
};
#endif //CELLA_H
