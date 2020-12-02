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

	status_t createOriginTransaction(payload_t & payload);
	status_t saveInHistoryBook(Block * block);
	Transaction * & getActualTransaction(void);
};

#endif /* BLOCKCHAINBOOKKEEPER_H_ */
