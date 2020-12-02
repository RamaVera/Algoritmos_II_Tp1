/*
 * mempool.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: Alan Dreszman
 */

#include "Mempool.h"


Mempool::Mempool(){
	this->n_txns = 0;
	this->first_node = new MempoolUnit();
	this->last_node = NULL;
}


/*Mempool::Mempool( int pool_size ){
	this->n_txns = pool_size;
	this->first_node = *(new MempoolUnit[pool_size]);
	this->last_node = &( (*first_node)[pool_size] );
};*/


Mempool::~Mempool(){
	if (this->first_node != NULL){
		try{
		std::cout<<"1) antes de empezar a borrar la mempool" <<std::endl;
		throw 0;
		delete this->first_node;

		}
		catch (...){
		    cout << " Excepcion ocurrida tratando de borrar la mempool " <<std::endl;
		}
	}
	std::cout<<"Se termino de borrar la mempool!" <<std::endl;
	// delete this->last_node;
}




void Mempool::set_new_pool_unit( MempoolUnit * p_memp_unit){

	if ( this->n_txns == 0  ){
		std::cout<<"Mempool vacia. Creando 1er nodo" <<std::endl;

		this->first_node = p_memp_unit;
		this->last_node = this->first_node;
		this->n_txns = 1;

	}
	else{
		int aux = this->n_txns + 1;
		std::cout<<"Creando nodo numero "<< aux <<std::endl;

		(*(this->last_node)).set_next_node( p_memp_unit );
		this->last_node = p_memp_unit;

		this->n_txns += 1;

	}


}


int Mempool::get_number_txns(){
	int a = this->n_txns;
	return a;
}



Transaction Mempool::get_transaction_n(int n){
	MempoolUnit * n_node = this->first_node;

	std::cout<< "get_transac_n, todo bien hasta aca" << std::endl;

	for(int i = 1; i < n; i++){
		std::cout<< "get_transac_n, adentro del for, todo bien hasta aca" << std::endl;
		n_node = (*n_node).get_next_unit();
	}

	std::cout<< "get_transac_n, fuera del for, todo bien hasta aca" << std::endl;
	return (*n_node).get_txn();

}


