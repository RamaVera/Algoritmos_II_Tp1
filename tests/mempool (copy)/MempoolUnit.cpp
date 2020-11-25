/*
 * MempoolUnit.cpp
 *
 *  Created on: Nov 19, 2020
 *      Author: a
 */

#include "MempoolUnit.h"



MempoolUnit::MempoolUnit(){
	this->txn = NULL;
	this->nxt_mem_unit = NULL;
};

MempoolUnit::MempoolUnit( const MempoolUnit & last_node , const Transaction & new_txn ){
	last_node.nxt_mem_unit = &this;
	this->txn = new_txn;
	this->nxt_mem_unit = NULL;
};

MempoolUnit::~MempoolUnit(){
	delete this->txn;
	delete this->nxt_mem_unit;
};
