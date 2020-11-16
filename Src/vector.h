//Clase Vector de numeros complejos
#ifndef _VECTOR_DINAMICO_INCLUDED_
#define _VECTOR_DINAMICO_INCLUDED_

#include<iostream>
#include<string>
#include<sstream>

#include"vector.h"

#define DEFAULT_SIZE 10 //largo inicial por defecto del vector dinámico.
#define RESIZE_FACTOR 1.5 //Factor de redimensionamiento.

using namespace std;

template <class T> class vector {
    //Atributos
    int largo_total;
    int cant_elementos;
    T *ptr;
    //Metodos
    public:
        //Constructores
        vector();
        vector(int);
        vector(const vector &);
        //Destructor
        ~vector();
		//Getter
        int getCantElementos();
        int getLargoTotal();
        //Agregar item
        bool agregar(const T &);
        //Borrar datos
        void borrar_datos();
        //Redimensionar
        bool redimensionar(int);
        //Sobrecarga de operadores
        vector &operator=(const vector &);
        bool operator==(const vector &);
        T &operator[](int);
        template< class U > friend std::ostream &operator<<(std::ostream &, const vector< U >&);
	    template< class U > friend std::istream &operator>>(std::istream &, vector< U >&);
};

template <class T> vector<T>::vector() {
    //Constructor por defecto de la clase
    ptr = new T[DEFAULT_SIZE]; //Crea un array de complejos de largo DEFAULT_SIZE.
    largo_total = DEFAULT_SIZE; //Asigna DEFAULT_SIZE al largo del vector.
    cant_elementos = 0; //Inicializa el largo utilizado actual.
}

template <class T> vector<T>::vector(int l) {
    //Constructor por defecto de la clase
    ptr = new T[l]; //Crea un array de complejos de largo l.
    largo_total = l; //Asigna l al largo del vector.
    cant_elementos = 0; //Inicializa el largo utilizado actual.
}

template <class T> vector<T>::vector(const vector &v) {
    //Constructor por copia de la clase.
    largo_total = v.largo_total; //Asigna el largo total de la instancia base a la nueva instancia.
    cant_elementos = v.cant_elementos; //Asigna el largo usado de la instancia base a la nueva instancia.
    ptr = new T[largo_total]; //Crea un array de complejos del mismo largo l de la instancia base.
    for (int i = 0; i < v.cant_elementos; i++) {
        ptr[i] = v.ptr[i]; //Copia cada elemento en el lugar correspondiente de la nueva instancia.
    }
}

template <class T> vector<T>::~vector() {
    //Destructor de la clase.
    if (ptr) delete[] ptr; //Si el array de complejos existe, libera la memoria.
}

template <class T> int vector<T>::getCantElementos() {
    //Devuelve la cantidad de elementos del vector.
    return cant_elementos;
}

template <class T> int vector<T>::getLargoTotal() {
    //Devuelve el largo total del vector
    return largo_total;
}

template <class T> bool vector<T>::agregar(const T &c) {
    //Agrega un elemento al final del vector,
    //si no hay lugar, se lo redimensiona.
    if (cant_elementos < largo_total) { //Si el largo total es mayor que
                             //la cantidad de elementos,
                             //se puede agregar al final y actualizar
                             //la cantidad de elementos almacenados.
        ptr[cant_elementos] = c;
        cant_elementos++;
    }
    else if (cant_elementos == largo_total) { //Si el vector está lleno,
                                              //se aumenta su largo total
                                              //y se vuelven a colocar los elementos.
        T* aux;
        largo_total = RESIZE_FACTOR * largo_total;
        aux = new T[largo_total];
        for (int i = 0; i < cant_elementos; i++) {
            aux[i] = ptr[i];
        }
        aux[cant_elementos] = c;
        cant_elementos++;
        delete[] ptr;
        ptr = aux;
    }
    return true;
}

template <class T> vector<T>& vector<T>::operator=(const vector &v) {
    //Operador de asignacion
    if (&v != this) { //Si el vector a asignar (de la derecha)_
                          //no es el mismo que el asignado (de la izquierda):

        if (largo_total <= v.cant_elementos) {
            //Si el largo total del vector de la izquierda es menor que la_
            //cantidad de elementos del de la izquierda, se redimensiona_
            //y se pasan los elementos.
            T* aux;
            aux = new T[v.largo_total];
            delete[] ptr;
            largo_total = v.largo_total;
            ptr = aux;
            for (int i = 0; i < v.cant_elementos; i++) {
                ptr[i] = v.ptr[i];
            }
            cant_elementos = v.cant_elementos;
            return *this;
        }
        else {
            //Si hay espacio para almacenar directamente los elementos,
            //se almacenan.
            for (int i = 0; i < v.cant_elementos; i++) {
                ptr[i] = v.ptr[i];
            }
            cant_elementos = v.cant_elementos;
            return *this;
        }
    }
    //Si los vectores son el mismo, lo devuelve directamente.
    return *this;
}

template <class T> bool vector<T>::operator==(const vector &v) {
    //Operador booleano de igualdad
    if(largo_total != v.largo_total
       || cant_elementos != v.cant_elementos) { //Si los largos no son iguales
                                                    //o la cantidad de elementos
                                                    //no es la misma devuelve falso.
        return false;
    }
    else { //Si los largos y la cant de elementos son iguales:
        for (int i = 0; i < cant_elementos; i++) { //Compara todos los elementos entre ambos vectores.
            if (ptr[i] != v.ptr[i]) { //Si hay un par diferente, devuelve falso.
                return false;
            }
        }
    }
    return true; //El largo y todos los elementos son iguales.
}

template <class T> void vector<T>::borrar_datos() {
    if (ptr) delete[] ptr;
    ptr = new T[DEFAULT_SIZE];
    cant_elementos = 0;
    largo_total = DEFAULT_SIZE;
}

template <class T> T& vector<T>::operator[](int i) {
    //Operador de indice.
    return ptr[i]; //Devuelve el elemento de la posicion i.
}

template <class U> ostream& operator<<(std::ostream &os, const vector< U > &v) {
    //Operador put.
    for (int i = 0; i < v.cant_elementos; i++) { //Para cada elemento del vector:
        if (i != v.cant_elementos - 1) { //Si no es el ultimo:
            os << v.ptr[i] << ' '; //Los manda al stream de salida_
                                   //separados por un espacio.
        }
        else { //Si es el ultimo:
            os << v.ptr[i]; //No le agrega un espacio.
        }
    }
    return os;
}

template <class U> istream& operator>>(std::istream &is, vector< U >& v) {
    //Operador get.
	U c;
    string line;
    getline(is, line);
    istringstream iss(line);
    while (iss >> c && !iss.bad()) {
        v.agregar(c);
    }
    if (iss.bad()) {
        is.clear(std::ios::badbit);
    }
    return is;
}



#endif
