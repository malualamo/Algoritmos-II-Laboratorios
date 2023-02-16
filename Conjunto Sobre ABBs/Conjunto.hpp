#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruirNodos(_raiz);
}

template<class T>
void Conjunto<T>::destruirNodos(Nodo* actual) {
    if(actual != nullptr){
        destruirNodos(actual->izq);
        destruirNodos(actual->der);
        delete actual;
    }
}


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    if(_raiz == nullptr) {
        return false;
    }
    if(_raiz->valor==clave ) {
        return true;
    }
    while (actual!= nullptr) {
        if (actual->valor == clave) {
            return true;
        }
        if(actual->valor < clave) {
            actual = actual->der;
        }else{
            actual = actual->izq;
        }
    }
    return false;
}




template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!this->pertenece(clave)) {
        if (_raiz == nullptr) {
            _raiz = new Nodo(clave);
        } else {
            Nodo* padre;
            Nodo* actual = _raiz;
            while (actual != nullptr) {
                if (clave < actual->valor) {
                    padre = actual;
                    actual = actual->izq;
                } else {
                    padre = actual;
                    actual = actual->der;
                }
            }
            if(clave < padre->valor){
                padre->izq = new Nodo(clave);
            } else {
                padre->der = new Nodo(clave);
            }
        }

    }
}


template <class T>
void Conjunto<T>::remover(const T&clave) {
    //busco el nodo que quiero eliminar
    if (pertenece(clave)) {
        //CASO 1: ES LA RAIZ
        if (clave == _raiz->valor) {
            eliminarRaiz();
        } else {
            //PRIMERO LO BUSCO
            Nodo *actual = _raiz;
            Nodo *padre;
            while (actual->valor != clave) {
                if (actual->valor < clave) {
                    padre = actual;
                    actual = actual->der;
                } else {
                    padre = actual;
                    actual = actual->izq;
                }
            }

            //DESPUES CHEQUEO POR CASO

            //CASO 1: ES UNA HOJA
            if (actual->izq == nullptr && actual->der == nullptr) {
                eliminarHoja(actual, padre);

            } else {

                //CASO 2: SI ES UN NODO CON UN HIJO
                if (actual->izq == nullptr || actual->der == nullptr) {
                    eliminarConHijo(actual, padre);
                } else {

                    //CASO 3: SI ES UN NODO CON DOS HIJOS. Nota: Como tiene si o si dos hijos tiene si o si un sig.

                    auto siguiente = this->siguiente(clave);

                    //busco siguiente
                    Nodo *sig = actual;
                    Nodo *padresig;
                    while (sig->valor != siguiente) {
                        if (sig->valor < siguiente) {
                            padresig = sig;
                            sig = sig->der;
                        } else {
                            padresig = sig;
                            sig = sig->izq;
                        }
                    }

                    actual->valor = siguiente; //LE DOY EL VALOR DEL SUCESOR

                    //lo elimino
                    if (sig->izq == nullptr && sig->der == nullptr) {
                        eliminarHoja(sig, padresig);
                    } else {
                        eliminarConHijo(sig, padresig);
                    }
                }
            }
        }
    }
}

template<class T>
void Conjunto<T>::eliminarHoja(Conjunto::Nodo *elim, Conjunto::Nodo *padre) {
    if (padre->izq == elim) { //si es hijo izquierdo
        padre->izq = nullptr;
    } else {
        padre->der = nullptr;
    }
    delete elim;
}

template<class T>
void Conjunto<T>::eliminarConHijo(Conjunto::Nodo *elim, Conjunto::Nodo *padre) {
    if (elim->izq == nullptr) {
        if(padre->izq==elim){
            padre->izq = elim->der;
        } else {
            padre->der = elim->der;
        }
    } else {
        if(padre->izq==elim){
            padre->izq = elim->izq;
        } else {
            padre->der = elim->izq;
        }
    }
    delete elim;
}


template<class T>
void Conjunto<T>::eliminarRaiz() {
    if (_raiz->izq == nullptr && _raiz->der == nullptr) {
        delete _raiz;
        _raiz = nullptr;
    } else {
        if (_raiz->der == nullptr) {
            Nodo *izq = _raiz->izq;
            delete _raiz;
            _raiz = izq;
        } else {
            if (_raiz->izq == nullptr) {
                Nodo *der = _raiz->der;
                delete _raiz;    //OJO QUE CAPAZ ACA ESTOY TENIENDO LEAKS
                _raiz = der;
            } else {
                auto siguiente = this->siguiente(_raiz->valor);
                Nodo *sig = _raiz;
                Nodo *padresig;
                while (sig->valor != siguiente) {
                    if (sig->valor < siguiente) {
                        padresig = sig;
                        sig = sig->der;
                    } else {
                        padresig = sig;
                        sig = sig->izq;
                    }
                }
                _raiz->valor = sig->valor;
                if (_raiz->der->valor == siguiente) {
                    _raiz->der = sig->der;
                    delete sig;
                } else {
                    if(sig->der== nullptr && sig->izq== nullptr){
                        eliminarHoja(sig,padresig);
                    } else {
                        eliminarConHijo(sig,padresig);
                    }
                }
            }
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    // Busco el valor que quiero encontrar (PRE: pertenece)
    Nodo* actual = _raiz;
    Nodo* padre;
    while (actual->valor != clave) {
        if(actual->valor < clave) {
            padre = actual;
            actual = actual->der;
        }else{
            padre = actual;
            actual = actual->izq;
        }
    }

    //Si no tiene subarbol der, es el padre. Si tiene, es el minimo de ese subarb.
    if(actual->der == nullptr){
        return padre->valor;
    } else {
        actual = actual->der; //minimo de subarbol derecho
        while(actual->izq!= nullptr){
            actual = actual->izq;
        }
        return actual->valor;
    }

}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = _raiz;
    while(actual->izq!= nullptr){
        actual = actual->izq;
    }
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = _raiz;
    while(actual->der!= nullptr){
        actual = actual->der;
    }
    return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    if(_raiz== nullptr){
        return 0;
    } else {
        return 1+_raiz->izq->cardinal()+_raiz->der->cardinal();
    }
}

template<class T>
unsigned int Conjunto<T>::Nodo::cardinal() {
    if(this == nullptr){
        return 0;
    } else {
        if(der== nullptr && izq== nullptr){
            return 1;
        }
        if(der== nullptr){
            return 1+izq->cardinal();
        } else {
            if(izq == nullptr){
                return 1+der->cardinal();
            } else {
                return 1+izq->cardinal()+der->cardinal();
            }
        }
    }
}



template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {

}

