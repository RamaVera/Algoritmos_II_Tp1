/*
 * BlockChainBookkeeper.h
 *
 *  Created on: 16 nov. 2020
 *      Author: Ramiro
 */

#ifndef BLOCKCHAINBOOKKEEPER_H_
#define BLOCKCHAINBOOKKEEPER_H_

#include "BlockChainStatus.h"
#include "BlockChainDataTypes.h"
#include "Block.h"
// #include "lista.h"

class BlockChainBookkeeper {
private:
	lista <Block *> AlgoChain;

public:
	BlockChainBookkeeper();
	~BlockChainBookkeeper();
	//---Getters---//
	const lista <Block *> & getListaBlocks();
	// Para usar x línea de comandos block <id>
	const Block * getBlock( const std::string txns_hash );
	// Para usar x línea de comandos txn <id>
	const TransactionInput * obtenerTransactionInput( const std::string tx_id );
	//---Setters---//
	//---Otros---//
	bool AddBlock( Block * B );
	bool AddListaBlocks( lista <Block *> & lista );
};

#endif /* BLOCKCHAINBOOKKEEPER_H_ */
