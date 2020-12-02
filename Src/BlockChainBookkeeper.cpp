/*
 * BlockChainBookkeeper.cpp
 *
 *  Created on: 16 nov. 2020
 *      Author: Ramiro
 */

#include "BlockChainBookkeeper.h"

BlockChainBookkeeper::BlockChainBookkeeper() {
	this->ActualTransaction = NULL;
}

BlockChainBookkeeper::~BlockChainBookkeeper() {
	//if(this->ActualTransaction !=NULL)
		//delete ActualTransaction;
}

status_t BlockChainBookkeeper::createOriginTransaction(payload_t & payload){
	this->ActualTransaction = new Transaction(0,1);
	this->ActualTransaction->getTransactionOutput(1)->setAddr(sha256(sha256(payload.user)));
	this->ActualTransaction->getTransactionOutput(1)->setValue(payload.value);
	return STATUS_FINISH_CONVERT_SUCCESSFULY;
}

Transaction * & BlockChainBookkeeper::getActualTransaction(void){
	return this->ActualTransaction;
}

status_t BlockChainBookkeeper::saveInHistoryBook(Block* block){
	if (BlockChainHistoryBook::AddBlock(block) ) return STATUS_OK;
	else return STATUS_BAD_ALLOC;
}
