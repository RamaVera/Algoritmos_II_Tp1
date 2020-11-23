/*
 * Cuentas.cpp
 */

#include "Cuentas.h"


//---Constructores---//

Cuentas::Cuentas() {
	this->cantidad = 0;
}

//---Destructor---//

Cuentas::~Cuentas() {
 // lista->listadocuentas se elimina en el ámbito del destructor de lista.h
 // Sólo hay que liberar los punteros dentro de cada dato.
	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			delete it.dato();
			it.avanzar();
		} while ( ! it.extremo() );
	}
}

//---Getters---//

//---Setters---//

//---Otros---//
