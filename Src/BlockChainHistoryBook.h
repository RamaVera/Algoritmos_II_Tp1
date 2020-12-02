/*
 * BlockChainHistoryBook.h
 *
 *  Created on: 30 nov. 2020
 *      Author: ramiro
 */

#ifndef BLOCKCHAINHISTORYBOOK_H_
#define BLOCKCHAINHISTORYBOOK_H_

#include <string>
#include "lista.h"
#include "Block.h"

class BlockChainHistoryBook {
private:
	friend class BlockChainBookkeeper;
	static lista<Block*> AlgoChain;
	//---Getters---//
	static const lista <Block *> & getListaBlocks(){return AlgoChain;};
	// Para usar x línea de comandos block <id>
	static const Block * getBlock( const std::string txns_hash );							// Ante cualquier error devuelve NULL
	// Para usar x línea de comandos txn <id>
	static const TransactionInput * obtenerTransactionInput( const std::string tx_id );	// Ante cualquier error devuelve NULL
	//---Setters---//
	//---Otros---//
	static void BorrarHistoria( void );
	static bool AddBlock( Block * B );
	static bool AddListaBlocks( lista <Block *> & lista );
public:
};

#endif /* BLOCKCHAINHISTORYBOOK_H_ */