/*
 * BlockChainBuilder.cpp
 *
 *  Created on: 25 oct. 2020
 *      Author: Ramiro
 */

#include <time.h> 

#include "BlockChainBuilder.h"
#include "Block.h"

#include "TiposHash.h"

#include "lista.h"
#include "sha256.h"

BlockChainBuilder::BlockChainBuilder() : BlocklActual(), ListaBlocks(), hash_resultado( "" ), bits( 3 /* El valor por default establecido en el TP0 */), pRawData(NULL){}

BlockChainBuilder::BlockChainBuilder(size_t d) : BlocklActual(), ListaBlocks(), hash_resultado( "" ), bits( d ), pRawData(NULL){}

BlockChainBuilder::~BlockChainBuilder() {
	// TODO Auto-generated destructor stub
}

int BlockChainBuilder::CheckHexa( string value ) {
	unsigned int i;
	for (i = 0; i != value.length(); ++i) {
		if ( ! isxdigit ( value[i] ) ) break;
	}
	if ( i < value.length() ) return i;
	return 0;
}

bool BlockChainBuilder::CheckHash( std::string valor, TiposHash Tipo ) {
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
		int i = CheckHexa( valor );
		if ( i > 0 ) {
			// Anotar la posición y valor del dígito erróneo
			return false;
		}
		else return true;
	}
}

/*
// Esto es incoherente, implica recalcula afuera, con variables externas a Block y almacenar el resultado dentro de Block
// Un ida y vuelta crítico.
std::string BlockChainBuilder::Calculononce() {
	static int contador = 0;
	return std::to_string( ++contador );

}
*/

bool BlockChainBuilder::CalculoBits( std::string hash, size_t bits ) {
	int resultado;
	if ( hash.length() > 0  ) {
		std::string hash_hex = "";
		hash_hex = BlockChainBuilder::hex_str_to_bin_str( hash );  // No lleva this-> porque es static
		resultado = BlockChainBuilder::CheckDificultadOk( hash_hex, bits );
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

bool BlockChainBuilder::Minando() {
	std::string resultado = "";
	
	if ( ! this->ListaBlocks.vacia() ) {
		lista <Block *>::iterador it;
		/* Itero la lista para recuperar todos los strings de la coleccion Transaction
		   que necesito para calcular el Hash.
		*/
		it = this->ListaBlocks.primero();

		do  {
			time_t timer1, timer2;
			time(&timer1);  	/* get current time; same as: timer = time(NULL)  */
			this->BlocklActual = it.dato();
			resultado = this->BlocklActual->getpre_block() + '\n';          // <- getter que extrae la clave doble hash del Block previo.
			resultado += this->BlocklActual->getcadenaprehash() + '\n'; 	// <- getter que extrae el string en la Clase Transaction.
			resultado += std::to_string( this->BlocklActual->getbits() ) + '\n';
			if ( resultado.length() > 0 ) {
				while ( true ) {
					std::string nonce_temp = "";
					nonce_temp = this->BlocklActual->Calculononce();
					this->hash_resultado = sha256 ( sha256( resultado + nonce_temp ) );
					if ( CalculoBits( this->hash_resultado, this->bits ) ) {
						//this->BlocklActual->setnonce( BlockChainBuilder::Calculononce() );	 // Cada llamada genera un nonce <>, se guarda en Block
						if ( this->BlocklActual->settxns_hash ( this->hash_resultado ) ) {   // <- setter que guarda el string del hash de hash en la Clase Transaction.
							break;	// Corto el bucle y pasaria a un siguiente Block que ahora no hay.
						}
						else {
							// TODO -> Error al almacenar?
						}
					}
				}
			}
			time(&timer2);
			this->BlocklActual->setseconds( difftime( timer1, timer2 ) );
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return false;
}

double BlockChainBuilder::tiempominado() {
	return this->seconds;
}

const char* BlockChainBuilder::hex_char_to_bin( char c )
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

std::string BlockChainBuilder::hex_str_to_bin_str( const std::string & hex )
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

int BlockChainBuilder::dificultad( const std::string & value, const size_t dif ) {
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

int BlockChainBuilder::CheckDificultadOk( const std::string & cadenaHexa, const size_t dif ) {
	int d;
	if ( cadenaHexa.empty() ) return -3;
	if ( dif == 0 ) return -2;
	d = dificultad( cadenaHexa, dif);
	if ( d < 0 ) return -1;
	return (size_t) d >= dif ? 1 : 0;
}