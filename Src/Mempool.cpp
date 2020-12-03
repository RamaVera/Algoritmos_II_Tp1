/*
 * mempool.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: Alan Dreszman
 */

#include "Mempool.h"
#include "lista.h"

lista <Transaction *> Mempool::transList;

void Mempool::addNewTransaction(Transaction * new_txn){

	transList.insertar( new_txn );

}


lista <Transaction *> & Mempool::getTransactionsList(){

	return transList;

}

size_t Mempool::getMempoolLength(){
	return transList.tamano();
}






/*
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
*/

