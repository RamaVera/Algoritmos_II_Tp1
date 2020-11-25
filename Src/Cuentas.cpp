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


size_t Cuentas::NuevoNumero() {
	// Genera un automumérico.
	static size_t Id = 0;
	return Id++;
}

bool Cuentas::addcuenta( const std::string addr, const std::string alias, const float monto ) {
	cuentas_t * C = NULL;

	// Checks
	if ( addr.empty() ) { 
		return false;
	}
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return false;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return false;
	}

	try {
		C = new cuentas_t;
		C->addr = addr;
		C->saldo = monto;
		C->alias = alias;
		C->numerocuenta = Cuentas::NuevoNumero();
		this->listadocuentas.insertar( C );
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
	}

	return true;
}

bool Cuentas::addcuenta( const std::string addr, const std::string alias ) {
	return this->addcuenta( addr, alias, 0 /* Para eliminar ambigüedades en la sobrecarga */ );
}

bool Cuentas::addcuenta( const std::string addr, const float monto ) {
	return this->addcuenta( addr, "", monto );
}

std::string Cuentas::getalias( const std::string addr ) {
	std::string alias = "";
	if ( addr.empty() ) { 
		return alias;
	}
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return alias;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return alias;
	}

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				alias = it.dato()->alias;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return alias;
}