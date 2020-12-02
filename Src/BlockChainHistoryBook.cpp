/*
 * BlockChainHistoryBook.cpp
 *
 *  Created on: 30 nov. 2020
 *      Author: ramiro
 */

#include "BlockChainHistoryBook.h"

lista<Block*> BlockChainHistoryBook::AlgoChain;

// Para usar x línea de comandos block <id>
const Block * BlockChainHistoryBook::getBlock( const std::string txns_hash ) {
	Block * B = NULL;
	std::string b_prev = "";

	// EL HASH YA ES VALIDADO EN FILEMANAGER
	// Checks
	//if ( txns_hash.empty()  ) {
	//	return B;
	//}
	//else if ( ! Block::CheckHash( txns_hash, TiposHash::clavehash256 ) ) {
	//	return B;
	//}
	// End Checks

	for ( size_t i = 0; i < (size_t) LargoHash::LargoHashEstandar; i++) { b_prev += '0'; }  // Block Zero
	if ( ! AlgoChain.vacia() ) {
		lista <Block *>::iterador it( AlgoChain );
		it = AlgoChain.primero();
		if ( ! ( it.dato()->getpre_block() == b_prev ) ) {
			// Mal definido el Block Zero
			return B;
		}
		do {
			if ( ! ( it.dato()->getpre_block() == b_prev ) ) {
				b_prev = it.dato()->getpre_block();
			}
			if ( ! ( it.dato()->gettxns_hash() == txns_hash ) ) {
				B = it.dato();
				break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return B;
}

// Para usar x línea de comandos txn <id>
const TransactionInput * BlockChainHistoryBook::obtenerTransactionInput( const std::string tx_id ) {
	std::string b_prev = "";
	TransactionInput * TI = NULL;

	// Checks
//	if ( tx_id.empty()  ) {
//		return TI;
//	}
//	else if ( ! Block::CheckHash( tx_id, TiposHash::clavehash256 ) ) {
//		return TI;
//	}
	// End Checks

	for ( size_t i = 0; i < (size_t) LargoHash::LargoHashEstandar; i++) { b_prev += '0'; }  // Block Zero
	if ( ! AlgoChain.vacia() ) {
		lista <Block *>::iterador it( AlgoChain );
		it = AlgoChain.primero();
		if ( ! ( it.dato()->getpre_block() == b_prev ) ) {
			return TI;
		}
		do {
			if ( ! ( it.dato()->getpre_block() == b_prev ) ) {
				return TI;
			}
			b_prev = it.dato()->getpre_block();
			// Debo abrir un segundo bloque de iteraciones sobre la lista de TI
			lista <Transaction *> trns;
			trns = it.dato()->getListaTran();
			lista <Transaction *>::iterador itTrans( trns );
			// La lista a iterar es la de TransactionInput
			itTrans = trns.primero();
			if ( ! trns.vacia() ) {
				do {
					// De las dos listas, itero las de TI
					lista <TransactionInput *> tInput;
					tInput = itTrans.dato()->getListaTransactionInput();
					lista <TransactionInput *>::iterador itTransInput( tInput );
					itTransInput = tInput.primero();
					if ( ! tInput.vacia() ) {
						do {
							if ( itTransInput.dato()->getTxId() == tx_id ) {
								TI->setTxId( itTransInput.dato()->getTxId() );
								TI->setIdx( itTransInput.dato()->getIdx() );
								TI->setAddr( itTransInput.dato()->getAddr() );
								return TI;
							}
							itTransInput.avanzar();
						}  while ( ! itTransInput.extremo() );
					}
				} while ( ! itTrans.extremo() );
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return TI;
}

void BlockChainHistoryBook::BorrarHistoria(void){
	// AlgoChain se autodestruye, antes debo liberar la memoria asignada en cada elemento * AlgoChain de la lista
	// El compilador ejecuta antes los destructores de las clases hijas que liberan su memoria dinámica.
	if ( ! AlgoChain.vacia() ) {
		lista  <Block *>::iterador it( AlgoChain );
		it = AlgoChain.primero();
		while ( ! it.extremo() ) {
			delete it.dato();
			it.avanzar();
		}
	}
}


bool BlockChainHistoryBook::AddBlock( Block * B ){
	Block * newBlock = new Block(*B);
	AlgoChain.insertar(newBlock);
	return true;
}

