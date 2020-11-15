//Archivo fuente header clase Block / AlgoBlock del tp0 para la materia 9512 Algoritmos y Programación II.

#ifndef BLOCK_H_
#define BLOCK_H_

#include<string>
#include "TiposHash.h"
#include "Transaction.h"
#include "lista.h"
#include "BlockChainDataTypes.h"

// const size_t LargoHashEstandar = 64;
// const size_t LargoHashFirma    = 40;	// Hash Pública de la Cuenta
// https://stackoverflow.com/questions/2268749/defining-global-constant-in-c
// Análisis de Pro vs Contras contra #define y otras formas

/*
   1ª Cuestión. La class Block carece de lógica interna, no accede a la función sha256(), por ejemplo
      En la situación del TP1, 
	    a) se le dan funcionalidades a Block haciéndola más autónoma y reutilizable
	    b) O Builder accede y compagina dentro de Block y Transaction los hash del árbol
					La función ArbolMerkle debe ser recursiva. Toma de a pares hasta que sólo quedan <= 2.
		https://bitcoin.es/criptomonedas/funciones-hash-y-arboles-de-merkle-protegen-blockchain/
		https://viviendo20.wordpress.com/2018/06/08/blockchain-el-arbol-de-merkle/
*/

using namespace std;

class Block {
	private:
		// Atributos Seccion Header
		std::string pre_block;
		std::string txns_hash;	// <- retiene el hash256(hash256(cadena_prehash))
		size_t bits;	/* La dificultad de bits */
		std::string nonce;
		StatusBlock eBlock;
		// Atributos Seccion Body;
		size_t txn_count;
		lista <Transaction *> ListaTran;
		Transaction * CurTran;
		std::string cadena_prehash;
		std::string hash_Merkle;
		// Para medir tiempos de minado x Block.
		double seconds;
		// Métodos privados
		std::string RecalculoHash( void );
		std::string ArbolMerkle( void );

	public:
    // Métodos
        // Constructores
        Block();
		Block( const raw_t & raw );
		//Block( const & std::string previo_block, size_t bits, const & raw_t );
		// size_t bits sale de BlockChainManager::getUserDefinedDifficulty(void), pero referenciar a esta clase implica un encastramiento indeseado.
        // Destructor
        ~Block();
		// Getters
        int getCantTransacciones();
		std::string getpre_block();
		std::string gettxns_hash();
		unsigned int getbits();
		std::string getnonce();
		std::string getcadenaprehash();
		double tiempominado();
		// Setters
		bool setpre_block( std::string valor );
		bool settxns_hash( std::string valor );		// Debo dejar el método de asignación. El cálculo Hash es externo al objeto block, no está encapsulado.
		bool setbits( unsigned int valor );
		bool setnonce( std::string valor );			// Debo dejar el método de asignación. El cálculo del Nonce es externo al objeto block, no está encapsulado.
		bool setseconds( double segundos );
		bool settransaction( const raw_t & raw ) ;  // TODO
		StatusBlock EstatusBlock();

};

#endif /* BLOCK_H_ */