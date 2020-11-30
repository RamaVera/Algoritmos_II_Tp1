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

size_t Cuentas::iscuenta( const std::string addr ) {
	size_t numero = 0;
	std::string alias = "";
	if ( addr.empty() ) { 
		return numero;
	}
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return numero;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return numero;
	}

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				numero = it.dato()->numerocuenta;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return numero;
}

float Cuentas::getsaldo( const std::string addr ) {
	float saldo = -1;
	if ( addr.empty() ) { 
		return saldo;
	}
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return saldo;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return saldo;
	}

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				saldo = it.dato()->saldo;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return saldo;
}

float Cuentas::getpendiente( const std::string addr ) {
	float pendiente = 0;
	if ( addr.empty() ) { 
		return pendiente;
	}
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return pendiente;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return pendiente;
	}

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				pendiente = it.dato()->pendiente;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return pendiente;
}

const cuentas_t * Cuentas::getdetallecuenta( const std::string addr, lista <Block *> & AlgoChain ) {
	cuentas_t * C = NULL;
	if ( addr.empty() ) { 
		return C;
	}
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return C;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return C;
	}

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				Extracto E(addr);
				C->addr = addr;
				C->alias = it.dato()->alias;;
				C->saldo = it.dato()->saldo;
				C->numerocuenta = it.dato()->numerocuenta;
				C->pendiente = it.dato()->pendiente;		// No lo tengo
				// lista <movimientos_t *> detalle;			// Extracto de la cuenta, necesito la AlgoChain
				//lista <movimientos_t *> Extracto::obtenerdetalle( const lista <Block *> & AlgoChain, std::string addr ) {
				C->detalle = E.obtenerdetalle( AlgoChain, addr );
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return C;
}

size_t Cuentas::getnumerocuenta( const std::string addr ) {

	// Checks
	if ( addr.empty() ) { return 0; }
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return 0;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return 0;
	}

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				return it.dato()->numerocuenta;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return 0;
}

size_t Cuentas::getnumerocuenta( const std::string addr, const std::string alias ) {
	
	// Checks
	if ( ! addr.empty() ) { return Cuentas::getnumerocuenta(addr); }
	if ( alias.empty() ) { return 0; }

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->alias == alias ) {
				return it.dato()->numerocuenta;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return 0;

}

//---Setters---//
bool Cuentas::setalias( const std::string addr, const std::string alias ) {

	// Checks
	if ( addr.empty() ) { return false; }
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return false;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return false;
	}

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				it.dato()->alias = alias;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
		return ( ! it.extremo() );
	}
	else { return false; }
}

bool Cuentas::setpendiente( const std::string addr, const float monto ) {
	// Checks
	if ( addr.empty() ) { return false; }
	else if ( ! BlockChainBuilder::CheckHash( addr, TiposHash::clavehash256 ) ) { 
		return false;
	}
	else if ( ! BlockChainBuilder::CheckHexa( addr ) ) {
		return false;
	}
	if ( monto == 0 ) { return false; }

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				it.dato()->pendiente = monto;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
		return ( ! it.extremo() );
	}
	else { return false; }
}

bool Cuentas::setsaldo( const std::string addr, const float monto ) {

	// Checks
	if ( addr.empty() ) { return false; }
	if ( monto < 0 ) { return false; }

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				it.dato()->saldo = monto;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
		return ( ! it.extremo() );
	}
	else { return false; }
}

//---Otros---//

size_t Cuentas::NuevoNumero() {
	// Genera un automumérico.
	static size_t Id = 1;	// Arranca de 1, 0 -> error
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

bool Cuentas::deposito( const std::string addr, const float monto ) {

	// Checks
	if ( addr.empty() ) { return false; }
	if ( monto <= 0 ) { return false; }

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				it.dato()->saldo += monto;
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
		return ( ! it.extremo() );
	}
	else { return false; }
}

bool Cuentas::extraccion( const std::string addr, const float monto ) {

	// Checks
	if ( addr.empty() ) { return false; }
	if ( monto > 0 ) { return false; }

	if ( ! this->listadocuentas.vacia() ) {
		lista <cuentas_t *>::iterador it( listadocuentas );
		it = this->listadocuentas.primero();
		do {
			if ( it.dato()->addr == addr ) {
				if ( it.dato()->saldo > monto ) {
					it.dato()->saldo -= monto;
					return true;
				}
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
		return false;
	}
	else { return false; }
}

bool Cuentas::openlista( const std::string file ) {
	std::string linea = "", alias = "", hashcuenta = "";
	if ( file.empty() ) return false;

	ifstream archivoClientes( file, ios::in );
	if ( !archivoClientes ) {
		cerr << "Error al abrir: " << file << endl;
		return false;
	}

	while ( archivoClientes.eof() ) {
		getline( archivoClientes, linea );
		if ( archivoClientes.good() ){
			if ( linea.empty() ) break;
			if ( linea.length() > (size_t) LargoHash::LargoHashEstandar ) {
				size_t pos = 0;
				try {
					// Formato clavehash + ", " + alias
					hashcuenta = linea.substr( 0, (size_t) LargoHash::LargoHashEstandar );
					alias = linea.substr( (size_t) LargoHash::LargoHashEstandar + 1 );;
					pos = alias.find( ", " );
					if ( pos != std::string::npos ) {
						alias = alias.substr( pos + 2 );
					}
					if ( BlockChainBuilder::CheckHash( hashcuenta, TiposHash::clavehash256 ) ) {
						// Ver si ya está en la lista
						if ( ! iscuenta( hashcuenta ) ) {
							cuentas_t * cuenta;
							cuenta = new cuentas_t;
							cuenta->addr = hashcuenta;
							cuenta->alias = alias;
							cuenta->saldo = 0;
							cuenta->pendiente = 0;
							cuenta->numerocuenta = NuevoNumero();
							this->listadocuentas.insertar( cuenta );
							cantidad++;
						}
					}
				}
				catch ( const std::length_error& e )  {
					std::cerr << e.what() << '\n';
				}
				catch (std::bad_alloc& ba) {
					std::cerr << "bad_alloc caught: " << ba.what() << '\n';
				}
			}
			
		}
	}
	archivoClientes.close();

	return true;
}
	
bool Cuentas::savelista( const std::string file ) {
	
	if ( file.empty() ) return false;
	if ( this->listadocuentas.vacia() ) return false;

	ofstream archivoClientes( file, ios::out );
	if ( !archivoClientes ) {
		cerr << "Error al abrir: " << file << endl;
		return false;
	}
	archivoClientes.close();

	return true;
}
