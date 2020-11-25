/*
 * mempool.h
 *
 *  Created on: Nov 16, 2020
 *      Author: a
 */

#ifndef MEMPOOL_H_
#define MEMPOOL_H_


using namespace std;
#include "MempoolUnit.h"

class Mempool{
	private:
		int n_txns;                  	// CANTIDAD DE TRANSACCIONES EN LA MEMPOOL
		MempoolUnit *first_node;     	// PUNTERO AL PRIMER ELEMENTO DE LA MEMPOOL
		MempoolUnit *last_node;		 	// PUNTERO AL ULTIMO ELEMENTO DE LA MEMPOOL

	public:
	// Metodos

		//Constructores
		Mempool();         			    // INICIALIZACION DE LA MEMPOOL VACIA
		/*Mempool( int pool_size );*/	// INICIALIZACION DE LA MEMPOOL CON
		~Mempool();                     // DESTRUCCION DE LA MEMPOOL

		// Setters
		bool set_new_pool_unit( const Mempool & mem_pool , const Transaction & new_txn );     // AGREGA UNA TRANSACCION A LA MEMPOOL

		// Getters
		Mempool &get_mempool( const Mempool & mem_pool );       // DEVUELVE LA MEMPOOL

};




#endif /* MEMPOOL_H_ */
