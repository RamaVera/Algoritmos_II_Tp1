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
	if(this->ActualTransaction !=NULL)
		delete ActualTransaction;
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


status_t BlockChainBookkeeper::saveOriginBlockInHistoryBook(Block *& block){

	if (! BlockChainHistoryBook::AlgoChain.isEmpty() ) BlockChainHistoryBook::BorrarHistoria();
	return saveBlockInHistoryBook(block);
}

status_t BlockChainBookkeeper::saveBlockInHistoryBook(Block* &block){
	if (BlockChainHistoryBook::AddBlock(block) ) return STATUS_OK;
	else return STATUS_BAD_ALLOC;
}

status_t BlockChainBookkeeper::saveUserBlockChainInHistoryBook(lista<Block*> &listaBlock){
	if (! BlockChainHistoryBook::AlgoChain.isEmpty() ) BlockChainHistoryBook::BorrarHistoria();
	lista<Block*>::iterador it(listaBlock);
	it = listaBlock.ultimo();
	while(!it.extremo()){
		if (! BlockChainHistoryBook::AddBlock(it.dato() ) ) return STATUS_BAD_ALLOC;
	it.retroceder();
	}
	return STATUS_OK;
}

status_t BlockChainBookkeeper::createTransaction(payload_t payload){
	const TransactionInput * trIn;
	const string hashInput = sha256(sha256(payload.ArgTranfer->dequeue()));
	trIn = BlockChainHistoryBook::obtenerTransactionInput(hashInput);
	if(trIn == NULL) return STATUS_ERROR_HASH_NOT_FOUND;

	//TODO Buscar en la lista de usuario a ver si tiene saldo

	this->ActualTransaction = new Transaction();
	this->ActualTransaction->addTransactionInput();
	this->ActualTransaction->getTransactionInput(1)->setAddr(trIn->getAddr());
	this->ActualTransaction->getTransactionInput(1)->setIdx(trIn->getIdx());
	this->ActualTransaction->getTransactionInput(1)->setTxId(trIn->getTxId());

	unsigned int OutputNumber = 1 ;
	while(payload.ArgTranfer->isEmpty()){
		this->ActualTransaction->addTransactionInput();
		this->ActualTransaction->getTransactionOutput(OutputNumber)->setAddr(sha256(sha256(payload.ArgTranfer->dequeue())));
		this->ActualTransaction->getTransactionOutput(OutputNumber)->setValue(std::stof(payload.ArgTranfer->dequeue()));
		OutputNumber++;
	}
	return STATUS_OK;
}


status_t BlockChainBookkeeper::saveInMempool(Transaction * trans){

	//if( Mempool::set_trans(trans) )
		return STATUS_BAD_ALLOC;
	return STATUS_OK;
}

const lista<Block *> & BlockChainBookkeeper::getBlockChain(void){
	return BlockChainHistoryBook::getListaBlocks();
}

status_t BlockChainBookkeeper::eraseAllBlockChainRegisters(void){
	BlockChainHistoryBook::BorrarHistoria();
	//Mempool::borrarMempool();
	return STATUS_OK;
}


