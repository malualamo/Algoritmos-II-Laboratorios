#include <cassert>
#include "Lista.h"

Lista::Lista(): primero_(nullptr), ultimo_(nullptr), long_(0) {
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* eliminado = primero_;
    while(eliminado!= nullptr){
        Nodo* guardo = eliminado->sig;
        delete eliminado;
        eliminado = guardo;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    if(long_!=0){
        int longit=long_;
        for(int i=0;i<longit;i++){
            eliminar(0);
        }
    }
    for(int j=0; j<aCopiar.longitud(); j++){
        this->agregarAtras(aCopiar.iesimo(j));
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo= new Nodo(elem);
    if(long_==0){
        ultimo_ = nuevo;
        primero_ = nuevo;
    } else {
        nuevo->sig = primero_;//el siguiente del nuevo pasa a ser el primero anterior
        primero_->ant=nuevo;
        primero_ = nuevo;
    }
    long_++;
    //no hace falta poner que el anterior va a ser nullptr porque se inicializa de esa manera.
}

void Lista::agregarAtras(const int& elem) {
    //creo puntero a nodo con elemento
    if(long_==0){
        agregarAdelante(elem);
    } else {
        Nodo* nuevo = new Nodo(elem);
        nuevo->ant = ultimo_; //el anterior al nuevo pasa a ser el ultimo orig
        ultimo_->sig=nuevo;
        ultimo_ = nuevo; //el nuevo pasa a ser el ultimo
        long_++;
    }
}

void Lista::eliminar(Nat i) {
    Nodo* actual = primero_;
    for (int j=0; j<i && i!=long_-1; j++) {
        actual = actual->sig;
    }
    if (i == 0) {
        if(long_==1){
            primero_= nullptr;
            ultimo_ = nullptr;
            delete actual;
        } else {
            primero_ = primero_->sig;
            primero_->ant= nullptr;
            delete actual;
        }
    } else {
        if (i==long_-1) {
            actual = ultimo_;
            ultimo_ = ultimo_->ant;
            ultimo_->sig = nullptr;
        } else {
            actual->ant->sig = actual->sig;
            actual->sig->ant = actual->ant;
        }
        delete actual;
    }
    long_--;
}


int Lista::longitud() const {
    return long_;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual = primero_;
    for(int j=0; j<i; j++){ //empieza desde 1 porque el 0 esta arriba. Termina en i-1 porque el ult tambien esta arr.
        actual = actual->sig; //va pasando uno por uno
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    Nodo* actual = primero_;
    for(int j=0; j<i; j++){ //empieza desde 1 porque el 0 esta arriba. Termina en i-1 porque el ult tambien esta arr.
        actual = actual->sig; //va pasando uno por uno
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
}