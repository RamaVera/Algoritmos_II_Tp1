//Archivo fuente clase Block / AlgoBlock del tp0 para la materia 9512 Algoritmos y Programación 2.

#include "Block.h"


// Constructores
Block::Block()
	: pre_block(""), txns_hash(""), bits(3  /* El valor por default establecido en el TP0 */), nonce(0), eBlock(StatusBlock::BlockSinDatos), txn_count(0), CurTran(NULL)
	// ver el #define DIFFICULTY_DEFAULT_VALUE 3
{
	//this->ListaTran = NULL;
	// this->CurTran = NULL;
	// this->txn_count = 0;
	// this->eBlock = StatusBlock::BlockSinDatos;
}

Block::Block( const raw_t & raw )
	: pre_block(""), txns_hash(""), bits( 3  /* El valor por default establecido en el TP0 */), nonce(0), eBlock(StatusBlock::BlockSinDatos)
{
	/* Básicamente:
			se instancia un objeto Transaction, se asume que se reciben datos consistentes.
			Se le transfiere en crudo el raw_t, (por ejemplo en el constructor directamente).
			La clase Transaction luego debería instanciar los TransactionInput y TransactionOutput correspondientes.
			Y calcular al finalizar la carga de los objetos el string de resultado.
			Al final se añade el objeto a ListaTran.
		Dudas:
			si en el txt se lee un Block que contiene varios Transaction, como los recibe Block ? 
			      En una lista lista.h o en un arreglo dinámico vector.h raw_t?
			En este caso se recibe solo un raw_t, igualmente lo cargo en una lista, para hacerlo más genérico.
	*/
	try {
		this->CurTran = new Transaction( raw );  	// <- Ojo, nuevo constructor
		this->ListaTran.insertar( this->CurTran );	// Para el Constructor con un contenedor de raw_t habrá que iterar pasando el mismo tipo de parámetros al constructor de Transaction
		this->txn_count = 1;						// Para el Constructor que recibe un Contenedor, se incrementa en cada instancia nueva de Transaction
		this->eBlock = StatusBlock::BlockPendienteCadena_prehash;
		RecalculoHash();
	}
	catch (std::bad_alloc& ba)
	{
		this->eBlock = StatusBlock::BlockBadAlloc;
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
	}
}

// Destructor
Block::~Block() {
	// ListaTran se autodestruye, antes debo liberar la memoria asignada en cada elemento * ListaTran de la lista
	if ( ! this->ListaTran.vacia() ) {

		lista <Transaction *>::iterador it(ListaTran);
		/* Itero la lista para recuperar todos los strings de la coleccion Transaction
		   que necesito para calcular el Hash.
		*/
		it = this->ListaTran.primero();
		while ( ! it.extremo() ) {
			delete it.dato();
			it.avanzar();
		}
	}
}

// Getters
unsigned int Block::gettxn_count() {
	return this->txn_count;
}

std::string Block::getpre_block() {
	return this->pre_block;
}

std::string Block::gettxns_hash() {
	return this->txns_hash;
}

unsigned int Block::getbits() {
	return this->bits;
}

unsigned int Block::getnonce() {
	return this->nonce;
}

std::string Block::getcadenaprehash() {
	return this->cadena_prehash;
}

// Setters
bool Block::setpre_block( std::string valor ) {
	if ( valor.empty() ) {
		this->pre_block = "";
		// Hay que anotar, en un status ?, el error o disparar un throw
	}
	else {
		/* 1) Debo validar que sea una cadena de 32 bytes o 64 dígitos Hexa
		   2) Chequear que cada byte sea un caracter hexa válido.
		   2) Chequear que cada byte sea un caracter hexa válido. Se elimina se supone que vien externamente validado.
		   		if ( BlockChainBuilder::CheckHash( valor, TiposHash::clavehash256 ) ) {
					this->pre_block = valor;
		*/
		this->pre_block = valor;
	}
	return true;
}

bool Block::settxns_hash( std::string valor ) {
	if ( valor.empty() ) {
		this->txns_hash = "";
		// Hay que anotar, en un status ?, el error o disparar un throw
	}
	else {
		/* 1) Debo validar que sea una cadena de 32 bytes o 64 dígitos Hexa
		   2) Chequear que cada byte sea un caracter hexa válido. Se elimina se supone que viene externamente validado.
		   		if ( BlockChainBuilder::CheckHash( valor, TiposHash::clavehash256 ) ) {
			this->txns_hash = valor;
		}
		*/
		this->txns_hash = valor;
	}
	return true;
}

bool Block::setbits( unsigned int valor ) {
	if ( !valor ) {
		this->bits = 0;
		// Hay que anotar, en un status ?, el error o disparar un throw
	}
	else {
		this->bits = valor;
	}
	return true;
}

bool Block::setnonce( int valor ) {
	if ( valor < 0 ) {
		this->nonce = 0;
		// Hay que anotar, en un status ?, el error o disparar un throw
	}
	else {
		/* No se valida nada, puede ser cualquier dato */
		this->nonce = (unsigned int) valor;
	}
	return true;
}

bool Block::settransaction( const raw_t & raw ) {
	try {
		this->CurTran = new Transaction( raw );  	// <- Ojo, nuevo constructor
		this->ListaTran.insertar( this->CurTran );	// Para el Constructor con un contenedor de raw_t habrá que iterar pasando el mismo tipo de parámetros al constructor de Transaction
		this->txn_count = 1;						// Para el Constructor que recibe un Contenedor, se incrementa en cada instancia nueva de Transaction
		this->eBlock = StatusBlock::BlockPendienteCadena_prehash;
		RecalculoHash();
		return true;
	}
	catch (std::bad_alloc& ba)
	{
		this->eBlock = StatusBlock::BlockBadAlloc;
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
		return false;
	}
}

std::string Block::RecalculoHash( void ) {
	std::string cadena = "";
	if ( ! this->ListaTran.vacia() ) {
		lista <Transaction *>::iterador it(ListaTran);
		/* Itero la lista para recuperar todos los strings de la coleccion Transaction
		   que necesito para calcular el Hash.
		*/
		it = this->ListaTran.primero();
		while ( ! it.extremo() ) {
			cadena += it.dato()->getConcatenatedTransactions();
			it.avanzar();
		}
	}
	if ( ! cadena.empty() ) {
		this->cadena_prehash = cadena;
		this->eBlock = StatusBlock::BlockCalculadoCadena_prehash;
	}
	else this->eBlock = StatusBlock::BlockPendienteCadena_prehash;
	return cadena;
}
