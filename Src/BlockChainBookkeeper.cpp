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

	if ( ! this->TransactionList.vacia() ) {
			lista  <Transaction *>::iterador it( this->TransactionList );
			it = this->TransactionList.primero();
			while ( ! this->TransactionList.isEmpty()) {
				delete it.dato();
				this->TransactionList.eliminar_nodo(it);
			}
	}
	if ( ! this->BlockList.vacia() ) {
				lista  <Block *>::iterador it( this->BlockList );
				it = this->BlockList.primero();
				while ( ! this->BlockList.isEmpty()) {
					delete it.dato();
					this->BlockList.eliminar_nodo(it);
				}
	}
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

Block * & BlockChainBookkeeper::getActualBlock(void){
	return this->ActualBlock;
}

status_t BlockChainBookkeeper::saveOriginBlockInHistoryBook(Block *& block){

	if (! BlockChainHistoryBook::AlgoChain.isEmpty() ) BlockChainHistoryBook::BorrarHistoria();
	return saveBlockInHistoryBook(block);
}

status_t BlockChainBookkeeper::saveBlockInHistoryBook(Block* &block){
	//@TODO falta actualiza lista de usuarios
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
	std::string _user_ = payload.ArgTranfer->dequeue();
	const string hashUser= sha256(sha256(_user_));

	//TODO Buscar en la lista de usuario a ver si tiene saldo

	// Busco en la historia la transaccion asociado al usuario pasado por hash
	Transaction * tr = BlockChainHistoryBook::getTransactionByTransactionOutputUser(hashUser);
	if(tr == NULL){
		 tr = Mempool::searchOutputUser(hashUser);
		 if(tr == NULL) 	 return STATUS_ERROR_HASH_NOT_FOUND;
	}


	// Mirando como es la estructura de la transaccion completo el outpoint

	// Contando con txIn encuentro el valor de indice del outpoint
	unsigned int txIn = 0;
	lista <TransactionOutput *> tOutput;
	tOutput =tr->getTransactionOutputList();
	lista <TransactionOutput  *>::iterador itTransOutput( tOutput);
	itTransOutput = tOutput.primero();
	do {
		if ( hashUser.compare(itTransOutput.dato()->getAddr()) == 0 )  {
		break;
		}
		txIn++;
		itTransOutput.avanzar();
	}  while ( ! itTransOutput.extremo() );

	// Con el doble hash de la transaccion obtengo el valor de Txid
	std::string TxId = sha256(sha256(tr->getConcatenatedTransactions()));

	this->ActualTransaction = new Transaction();
	this->ActualTransaction->addTransactionInput();
	this->ActualTransaction->getTransactionInput(1)->setTxId(TxId);
	this->ActualTransaction->getTransactionInput(1)->setIdx(txIn);
	this->ActualTransaction->getTransactionInput(1)->setAddr(hashUser);

	unsigned int OutputNumber = 1 ;
	while( ! payload.ArgTranfer->isEmpty()){
		this->ActualTransaction->addTransactionOutput();
		this->ActualTransaction->getTransactionOutput(OutputNumber)->setAddr(sha256(sha256(payload.ArgTranfer->dequeue())));
		this->ActualTransaction->getTransactionOutput(OutputNumber)->setValue(std::stof(payload.ArgTranfer->dequeue()));
		OutputNumber++;
	}

	//@TODO falta agregar como output el vuelto
	return STATUS_OK;
}

lista<Transaction *> & BlockChainBookkeeper::getMempool(){
	if (Mempool::getMempoolLength()){
		lista<Transaction *> mempool = Mempool::getTransactionsList();
		lista<Transaction *> ::iterador itMempool(mempool);
		while(! itMempool.extremo()){
			Transaction actualTran;
			actualTran = *(itMempool.dato());
			Transaction * copyTrans = new Transaction(actualTran);
			this->TransactionList.insertar(copyTrans) ;
			itMempool.avanzar();
		}
		Mempool::BorrarMempool();
	}else{
		this->ActualTransaction = new Transaction(0,0);
		this->TransactionList.insertar(this->ActualTransaction );
	}
	return this->TransactionList;
}


status_t BlockChainBookkeeper::saveInMempool(Transaction * trans){
	//@TODO falta actualizar lista de usuarios
	Mempool::addNewTransaction(trans);
	return STATUS_OK;
}

status_t BlockChainBookkeeper::searchInHistoryBook(HashIdType type, std::string hashId){

	switch(type){
	case HashIdType::blockId:{
		Block * B = BlockChainHistoryBook::searchBlock(hashId);
		if(B == NULL) return STATUS_ERROR_HASH_NOT_FOUND;
		Block * newBlock = new Block(*B);
		this->BlockList.insertar(newBlock);
		return STATUS_OK;
		break;
	}

	case HashIdType::txnId:{
		Transaction * TxFromAlgochain = BlockChainHistoryBook::searchTransaction(hashId);
		Transaction * TxFromMempool   = Mempool::searchTransaction(hashId);

		if( TxFromAlgochain == NULL && TxFromMempool == NULL) return STATUS_ERROR_HASH_NOT_FOUND;

		lista <Transaction *>  T;
		if( TxFromAlgochain != NULL )
			T.insertar(TxFromAlgochain);
		else
			T.insertar(TxFromMempool);

		lista<Transaction *> ::iterador it(T);

		while(!it.extremo()){
			Transaction * newTrans = new Transaction(*(it.dato()));
			this->TransactionList.insertar(newTrans) ;
			it.avanzar();
		}
		return STATUS_OK;
		break;
		}
	}
	return STATUS_ERROR_HASH_NOT_FOUND;
}


const lista<Block *> & BlockChainBookkeeper::getBlockChain(void){
	return BlockChainHistoryBook::getListaBlocks();
}

lista<Block *> & BlockChainBookkeeper::getBlockList(void){
	return this->BlockList;
}

lista<Transaction *> & BlockChainBookkeeper::getTransactionList(void){
	return this->TransactionList;
}

status_t BlockChainBookkeeper::eraseAllBlockChainRegisters(void){
	BlockChainHistoryBook::BorrarHistoria();
	Mempool::BorrarMempool();
	return STATUS_OK;
}

std::string BlockChainBookkeeper::getLastBlockHash(void){
	lista<Block *>::iterador AlgoChain( BlockChainHistoryBook::AlgoChain);
	AlgoChain = BlockChainHistoryBook::AlgoChain.ultimo();
	return AlgoChain.dato()->getBlockHash();
}

std::string BlockChainBookkeeper::getTransactionHash(){
	string debugString = this->ActualTransaction->getConcatenatedTransactions();
	return sha256(sha256(debugString));
}
