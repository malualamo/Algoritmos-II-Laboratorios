#include "string_map.h"

template <typename T>
string_map<T>::string_map(): raiz(nullptr), _size(0),_claves(){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    for(string clave : d._claves){
        insert(make_pair(clave,d.at(clave)));
    }
}

template <typename T>
string_map<T>::~string_map(){
    set<string> set = _claves;
    for(string s:set){
        erase(s);
    }
    delete raiz;
    raiz = nullptr;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    /*if(_size==0){
        raiz=new Nodo;
        raiz->siguientes(int('z')-int('a'), nullptr);
        raiz->definicion='"';

    }*/
}

template<typename T>
set<string> string_map<T>::claves() const {
    return _claves;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& p){
    string s=p.first;
    if(raiz== nullptr){
        raiz=new Nodo;
    }
    Nodo* actual=raiz;
    if(count(p.first)==0) {
        for (int i = 0; i < s.size(); i++) {
            if (actual->siguientes[int(s[i])] == nullptr) {
                actual->siguientes[int(s[i])] = new Nodo;
            }
            actual = actual->siguientes[int(s[i])];
        }
        actual->definicion = new T(p.second);
        _size++;
        _claves.insert(p.first);
    } else {
        for(int i = 0; i < s.size(); i++){
            actual = actual->siguientes[int(s[i])];
        }
        delete actual->definicion;
        actual->definicion = new T(p.second);
    }
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    if(raiz== nullptr){
        return 0;
    } else {
        Nodo* actual=raiz;
        for (int i = 0; i < clave.size(); i++) {
            if (actual->siguientes[int(clave[i])]== nullptr){
                return 0;
            }
            actual=actual->siguientes[int(clave[i])];
        }
        if (actual->definicion!= nullptr){
            return 1;
        }
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual=raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual=actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}


template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual=raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual=actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}

template <typename T>
bool string_map<T>::masDeUnHijo(string_map<T>::Nodo *a) const{
    int c=0;
    for (int i = 0; i < 256; i++) {
        if(a->siguientes[i]!= nullptr){
            c++;
        }
    }
    return c>1;
}



template <typename T>
void string_map<T>::erase(const string& clave) {
    if (count(clave) == 1) {
        Nodo *actual = raiz;
        Nodo *borrarDesdeNodo = raiz;
        int j = 0;
        for (int i = 0; i < clave.size(); i++) {
            if (actual->definicion != nullptr || masDeUnHijo(actual)) {
                j = i; //me guardo desde donde borro
                borrarDesdeNodo = actual;
            }
            actual = actual->siguientes[int(clave[i])];
        }
        delete actual->definicion;
        actual->definicion = nullptr;
        _claves.erase(clave);
        _size = _size - 1;

        if (noTieneHijos(actual)) {
            vector<Nodo *> intermedios;
            Nodo *guardar = borrarDesdeNodo; //me lo guardo porque lo necesito abajo
            int iterador = j; //me lo guardo porque tambien lo necesito abajo

            while (borrarDesdeNodo->siguientes[clave[j]] != actual) {
                intermedios.push_back(borrarDesdeNodo->siguientes[clave[j]]);
                borrarDesdeNodo = borrarDesdeNodo->siguientes[clave[j]];
                j++;
            }
            for (int i = 0; i < intermedios.size(); i++) {
                delete intermedios[i];
            }

            guardar->siguientes[clave[iterador]] = nullptr;
            delete actual;
        }
    }
}

template<typename T>
bool string_map<T>::noTieneHijos(string_map::Nodo *a) const {
    for (int i = 0; i < 256; i++) {
        if(a->siguientes[i]!= nullptr){
            return false;
        }
    }
    return true;
}



template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    if(raiz== nullptr){
        return true;
    }
    return false;
}