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
#include "BlockChainHistoryBook.h"
#include "Block.h"
#include "Transaction.h"
#include "sha256.h"

// #include "lista.h"

class BlockChainBookkeeper {

private:
	Transaction * ActualTransaction;
public:
	BlockChainBookkeeper();
	~BlockChainBookkeeper();

	status_t createTransaction(payload_t payload);
	status_t createOriginTransaction(payload_t & payload);
	status_t saveBlockInHistoryBook(Block * &block);
	status_t saveOriginBlockInHistoryBook(Block* &block);
	status_t saveUserBlockChainInHistoryBook(lista<Block*> &listaBlock);
	status_t saveInMempool(Transaction * trans);
	status_t eraseAllBlockChainRegisters(void);

	const lista<Block *> & getBlockChain(void);
	Transaction * & getActualTransaction(void);
};

#endif /* BLOCKCHAINBOOKKEEPER_H_ */
