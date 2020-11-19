/*
 * Extracto.cpp
 */

#include "Extracto.h"
#include "Transaction.h"

#include "lista.h"

//---Constructores---//

Extracto::Extracto() {
	this->saldo = 0;
}

Extracto::Extracto( std::string valor ) {
 // TODO, opciones 
 //   1) Buscar ver la estructura de cuentas/saldos
 //   2) Iterar la cadena AlgoChain
	this->saldo = 0;
	this->addr = valor;
}

//---Destructor---//

Extracto::~Extracto() {
 // lista->detalle se elimina en el ámbito del destructor de lista.h
 // Sólo hay que liberar los punteros dentro de cada dato.
	if ( ! this->detalle.vacia() ) {
		lista <movimientos_t *>::iterador it( detalle );
		it = this->detalle.primero();
		do {
			delete it.dato();
			it.avanzar();
		} while ( ! it.extremo() );
	}
}

//---Getters---//

std::string Extracto::getaddr() {
	return this->addr;
}

float Extracto::getsaldo() {
	return this->saldo;
}

//---Setters---//

bool Extracto::setaddr( std::string valor ) {
	this->addr = valor;
	return true;
}

//---Otros---//

void Extracto::imprimirdetalle() {
	// TODO
	// Imprimir cabecera siempre.
	// Movimientos
	if ( ! this->detalle.vacia() ) {
		lista <movimientos_t *>::iterador it( detalle );
		it = this->detalle.primero();
		do {
			it.avanzar();
		} while ( ! it.extremo() );
	}
}

lista <movimientos_t *> Extracto::obtenerdetalle( lista <Block *> & AlgoChain, std::string cuenta ) {
	// TODO
	if ( cuenta.empty() ) {
		cuenta = this->addr;
	}
	std::string cuentaorigen = "";
	if ( ! AlgoChain.vacia() ) {
		lista <Block *>::iterador it( AlgoChain );
		it = AlgoChain.primero();
		do {
			// Se itera dentro de las transacciones
			lista <Transaction *> trns;
			// Block * BlockAux;
			// BlockAux = it.dato();
			trns = it.dato()->getListaTran();
			lista <Transaction *>::iterador itTrans( trns );
			itTrans = trns.primero();
			if ( ! trns.vacia() ) {
				do {
					Transaction * Trans = itTrans.dato();
					lista <TransactionInput *> intputs = Trans->getListaTransactionInput();
					lista <TransactionInput *>::iterador itIn( intputs );
					if ( ! intputs.vacia() ) {
						// Si hay entradas a addr se cargan en lista->detalle como crédito
						if ( itIn.dato()->getAddr() == cuenta ) {
							// Se carga en detalle
							// Cargar el lista detalle
							cuentaorigen = cuenta;
						}
					}
					// Se itera dentro de Outs
					lista <TransactionOutput *> outputs = Trans->getTransactionOutput();
					lista <TransactionOutput *>::iterador itOut( outputs );
					if ( ! outputs.vacia() ) {
						// Si hay salidas desde addr se cargan en lista->detalle como débito
						do {
							if ( ! cuentaorigen.empty() ) {
								if ( itOut.dato()->getAddr() ==  cuenta ) {
									// Se carga en detalle el crédito
									movimientos_t * entrada = new movimientos_t;
									// Cargar datos
									entrada->txns_hash = it.dato()->gettxns_hash();
									entrada->addr = itOut.dato()->getAddr();
									entrada->value = itOut.dato()->getValue();
									this->detalle.insertar( entrada );
									this->saldo += entrada->value;
								}
							}
							else {
								// Son todas salidas de débitos en la cuenta
								movimientos_t * salida = new movimientos_t;
								// Cargar datos
								salida->txns_hash = it.dato()->gettxns_hash();
								salida->addr = itOut.dato()->getAddr();
								salida->value = - itOut.dato()->getValue();
								this->detalle.insertar( salida );
								this->saldo -= salida->value;
							}
							itOut.avanzar();
						} while ( ! itOut.extremo() );
					}
					itTrans.avanzar();
				} while ( ! itTrans.extremo() );
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return this->detalle;
}