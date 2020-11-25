/*
 * MempoolUnit.cpp
 *
 *  Created on: Nov 19, 2020
 *      Author: Alan Dreszman
 */

#include "MempoolUnit.h"


MempoolUnit::MempoolUnit(){
	this->txn = NULL;
	this->nxt_mem_unit = NULL;
}


MempoolUnit::MempoolUnit( const Transaction * new_txn ){
	//this->nxt_mem_unit = &this;
	this->txn = new_txn;
	this->nxt_mem_unit = new MempoolUnit();
}

MempoolUnit::~MempoolUnit(){

	try{
		throw 0;

		if (this->txn != NULL){
			std::cout<<"Antes de borrar una transaccion" <<std::endl;
			delete this->txn;
			std::cout<<"Despues de borrar una transaccion" <<std::endl;
		}
		if (this->nxt_mem_unit != NULL){
			std::cout<<"Antes de borrar un nodo siguiente" <<std::endl;
			delete this->nxt_mem_unit;
			std::cout<<"Despues de borrar un nodo siguiente" <<std::endl;
		}
	}
	catch(...){
		std::cout<<"Excepcion ocurrida tratando de borrar una Transaccion de la Mempool" <<std::endl;
	}
}

Transaction MempoolUnit::get_txn(){
	std::cout<< "adentro de get_txn" << std::endl;
	return *(this->txn);
}

MempoolUnit * MempoolUnit::get_next_unit(){
	std::cout<< "adentro de get_nxt_unit" << std::endl;
	return this->nxt_mem_unit;
}

void MempoolUnit::set_next_node(MempoolUnit * p_mem_unit){
	this->nxt_mem_unit = p_mem_unit;
}




