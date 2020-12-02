//Archivo fuente clase Block / AlgoBlock del tp0 para la materia 9512 Algoritmos y Programación II.

#include<string>
#include <cstdlib>
#include <iostream>
#include <time.h> 

#include "Block.h"
#include "TiposHash.h"
#include "Transaction.h"
#include "BlockChainBuilder.h"

#include "sha256.h"
#include "vector.h"

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
size_t Block::gettxn_count() {
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

std::string Block::getnonce() {
	return this->nonce;
}

std::string Block::getcadenaprehash() {
	return this->cadena_prehash;
}

double Block::tiempominado() {
	return this->seconds;
}

Transaction * Block::getTran( size_t Index ) {
	Transaction * T = NULL;
	size_t i = 0;
	// Checks
	if ( Index <= 0 ) { return T; }
	else if ( Index > this->txn_count ) { return T; }
	if ( ! this->ListaTran.vacia() ) {
		lista <Transaction *>::iterador it(ListaTran);
		it = this->ListaTran.primero();
		do  {
			if ( Index == i++ ) {
				T = it.dato();
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return T;
}

const lista <Transaction *> Block::getListaTran() {
	return this->ListaTran;
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

bool Block::setbits( size_t valor ) {
	if ( !valor ) {
		this->bits = 0;
		// Hay que anotar, en un status ?, el error o disparar un throw
	}
	else {
		this->bits = valor;
	}
	return true;
}

bool Block::setnonce( std::string valor ) {
	this->nonce = valor;
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
bool Block::setseconds( double segundos ) {
	this->seconds = segundos;
	return true;
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
		this->hash_Merkle = ArbolMerkle();
	}
	else this->eBlock = StatusBlock::BlockPendienteCadena_prehash;
	return cadena;
}

std::string Block::Calculononce() {
	size_t contador = 0;
	this->nonce = std::to_string( contador++ );
	return this->nonce;
}

bool Block::Minando() {
	std::string resultado = "", hash_resultado = "";

	time_t timer1, timer2;
	time(&timer1);  	/* get current time; same as: timer = time(NULL)  */
	resultado = this->getpre_block() + '\n';          // <- getter que extrae la clave doble hash del Block previo.
	resultado += this->getcadenaprehash() + '\n'; 	// <- getter que extrae el string en la Clase Transaction.
	resultado += std::to_string( this->getbits() ) + '\n';
	if ( resultado.length() > 0 ) {
		while ( true ) {
			std::string nonce_temp = "";
			nonce_temp = this->Calculononce();
			hash_resultado = sha256 ( sha256( resultado + nonce_temp ) );
			if ( CalculoBits( hash_resultado, this->bits ) ) {
				this->txns_hash = hash_resultado;
				break;	// Corto el bucle.
			}
		}
	}
	time(&timer2);
	this->seconds = difftime( timer1, timer2 );

	return true;
}

bool Block::CalculoBits( std::string hash, size_t bits ) {
	int resultado;
	if ( hash.length() > 0  ) {
		std::string hash_hex = "";
		hash_hex = Block::hex_str_to_bin_str( hash );  // No lleva this-> porque es static
		resultado = Block::CheckDificultadOk( hash_hex, bits );
		if ( resultado == 1 ) {
			return true;
		}
		else {
			// Incluye cadena hash vacia y bits == 0
			// Lo bueno de los booleanos es que siempre estas como máximo a un bit de acertar.
			return false;
		}
	}
	else {
		return false;
	}
}

std::string Block::ArbolMerkle( void ) {
	/*
	   Dudas
       Utilizar recursividad plantea un aumento de espacio con una misma complejidad log(n).
	   Al utilizar iteraciones combinado con el uso de un vector inplace() elimina el aumento de espacio y posee la misma complejidad
	   Con la última transaction si es impar se asume que la de al lado es el mismo y se hace un sha256.
	*/
	std::string cadena = "";
	if ( ! this->ListaTran.vacia() ) {
		// rellenado del vector.
		// Esto se podria implementar para optimizar en la iteracion de RecalculoHash.
		// A costa de extender el espacio de memoria consumido por strMerkle[] a lo largo de toda la instancia de Block.
		lista <Transaction *>::iterador it(ListaTran);
		size_t largo = this->ListaTran.tamano();  // Lo almaceno para no recalcularlo en cada iteración
		vector < std::string > strMerkle( largo );
		it = this->ListaTran.primero();
		size_t i = 0, tam = largo;
		while ( ! it.extremo() ) {
			strMerkle[i++] =  sha256( sha256( it.dato()->getConcatenatedTransactions() ) );
			it.avanzar();
		}
		// TODO. Analizar ventajas en este tramo de llevarlo a recursivo e inplace.
		for ( size_t j = 0; ( j < tam ) && ( tam > 1 ); j++  ) {
			for ( i = 0; i < largo; i += 2 ) {
				if ( i == largo - 1) {
					// Lucio me recordó que es hash doble !!
					strMerkle[ i ] = sha256( sha256( strMerkle[ i ] + strMerkle[ i ] ) );
				}
				else {
					strMerkle[ i ] = sha256( sha256( strMerkle[ i ] + strMerkle[ i + 1 ] ) );
				}
			}
			// ( tam % 2 ) ? tam <<= 1 : tam = ( tam + 1 ) << 1;   <- Opcion rápida con operadores de bits.
			if ( tam % 2 ) {
				tam /= 2;
			}
			else {
				tam = ( tam + 1) / 2;
			}
		}
		cadena = strMerkle[ 0 ];
	}
	return cadena;
}

std::string Block::gethash_Merkle() {
	return this->hash_Merkle;
}

int Block::dificultad( const std::string & value, const size_t dif ) {
	// Se corta el recorrido de la cadena una vez alcanzado el valor dif
	size_t j = 0;

	if ( value.empty() ) return -1;
	else if ( dif == 0 ) return -1;

	for ( size_t i = 0;  value[ i ]; i++ ) {
		if ( value[ i ] == '0' ) j++;
		else if ( value[ i ] == '1' ) break;
		else return -1;
		if ( j >= dif ) break; 
	}
	return j;
}

int Block::CheckDificultadOk( const std::string & cadenaHexa, const size_t dif ) {
	int d;
	if ( cadenaHexa.empty() ) return -3;
	if ( dif == 0 ) return -2;
	d = dificultad( cadenaHexa, dif);
	if ( d < 0 ) return -1;
	return (size_t) d >= dif ? 1 : 0;
}

size_t Block::CheckHexa( const std::string value ) {
	size_t i;
	for (i = 0; i != value.length(); ++i) {
		if ( ! isxdigit ( value[i] ) ) break;
	}
	if ( i < value.length() ) return i;
	return 0;
}

bool Block::CheckHash( const std::string valor, TiposHash Tipo ) {
	if ( valor.empty() ) {
		return false;
	}
	//else if ( Tipo  == TiposHash::clavehash256 && valor.length() != LargoHashEstandar ) {
	else if ( Tipo  == TiposHash::clavehash256 && valor.length() != (size_t) LargoHash::LargoHashEstandar ) {
		return false;
	}
	//else if ( Tipo  == TiposHash::clavefirma && valor.length() != LargoHashFirma ) {
	else if ( Tipo  == TiposHash::clavefirma && valor.length() != (size_t) LargoHash::LargoHashFirma ) {
		return false;
	}
	else {
		size_t i = Block::CheckHexa( valor );
		if ( i > 0 ) {
			// Anotar la posición y valor del dígito erróneo
			return false;
		}
		else return true;
	}
}

std::string Block::hex_str_to_bin_str( const std::string & hex )
{
    // TODO use a loop from <algorithm> or smth
    std::string bin;
	std::string hexbin;
    for( size_t i = 0; i != hex.length(); ++i ) {
		hexbin = hex_char_to_bin( hex[i] );
		if ( hexbin.empty() ) return "";
		bin += hexbin;
	}
    return bin;
}

const char* Block::hex_char_to_bin( char c )
{
    // TODO handle default / error
	// https://stackoverflow.com/questions/18310952/convert-strings-between-hex-format-and-binary-format
    switch( toupper(c) )
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
		default: return "";
    }
}