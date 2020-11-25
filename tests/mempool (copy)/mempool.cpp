/*
 * mempool.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: a
 */

#include "mempool.h"


Mempool::Mempool(){
	this->n_txns = 0;
	this->first_node = *(new MempoolUnit);
	this->last_node = first_node;
};


/*Mempool::Mempool( int pool_size ){
	this->n_txns = pool_size;
	this->first_node = *(new MempoolUnit[pool_size]);
	this->last_node = &( (*first_node)[pool_size] );
};*/


Mempool::~Mempool(){
	delete this->first_node;
	delete this->last_node;
};


bool Mempool::set_new_pool_unit( const Mempool & mem_pool , const Transaction & new_txn ){
	if ( mem_pool.n_txns == 0  ){
		MempoolUnit( *(mem_pool.first_node) , new_txn );
		mem_pool.last_node = first_node;
		mem_pool.n_txns = 1;
	}
	else{
		MempoolUnit( *(mem_pool.last_node) , new_txn );
		mem_pool.n_txns += 1;
	}
	return 0;
};


Mempool &get_mempool( const Mempool & mem_pool ){
	return * mem_pool;
};

