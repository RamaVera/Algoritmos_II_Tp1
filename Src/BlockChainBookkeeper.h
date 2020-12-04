/*
 * BlockChainBookkeeper.h
 *
 *  Created on: 16 nov. 2020
 *      Author: Ramiro
 */

#ifndef BLOCKCHAINBOOKKEEPER_H_
#define BLOCKCHAINBOOKKEEPER_H_

#include "BlockChainHistoryBook.h"
#include "BlockChainDataTypes.h"
#include "BlockChainStatus.h"
#include "Mempool.h"
#include "Transaction.h"
#include "Block.h"

#include "sha256.h"

// #include "lista.h"

class BlockChainBookkeeper {

private:
	Block * ActualBlock;
	Transaction * ActualTransaction;
	lista<Block * > BlockList;
	lista<Transaction *> TransactionList;

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
	status_t searchInHistoryBook(HashIdType type, std::string hashId);

	std::string getLastBlockHash(void);
	std::string getTransactionHash(void);
	const lista<Block *> & getBlockChain(void);
	Block * &getActualBlock(void);
	Transaction * & getActualTransaction(void);
	lista<Block *> & getBlockList(void);
	lista<Transaction *> & getTransactionList(void);
	lista<Transaction *> &  getMempool(void );


};

#endif /* BLOCKCHAINBOOKKEEPER_H_ */
