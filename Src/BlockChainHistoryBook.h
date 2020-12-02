/*
 * BlockChainHistoryBook.h
 *
 *  Created on: 30 nov. 2020
 *      Author: ramiro
 */

#ifndef BLOCKCHAINHISTORYBOOK_H_
#define BLOCKCHAINHISTORYBOOK_H_

#include "lista.h"
#include "Block.h"

class BlockChainHistoryBook {
private:
	friend class BlockChainBookkeeper;
	lista<Block*> AlgoChain;
	//---Getters---//
	const lista <Block *> & getListaBlocks();
	// Para usar x línea de comandos block <id>
	const Block * getBlock( const std::string txns_hash );							// Ante cualquier error devuelve NULL
	// Para usar x línea de comandos txn <id>
	const TransactionInput * obtenerTransactionInput( const std::string tx_id );	// Ante cualquier error devuelve NULL
	//---Setters---//
	//---Otros---//
	void BorrarHistoria( void );
	bool AddBlock( Block * B );
	bool AddListaBlocks( lista <Block *> & lista );
public:
};

#endif /* BLOCKCHAINHISTORYBOOK_H_ */
