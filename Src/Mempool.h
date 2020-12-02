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
		friend class BlockChainBookkeeper;
		int n_txns;                  		// CANTIDAD DE TRANSACCIONES EN LA MEMPOOL
		MempoolUnit * first_node;     		// PUNTERO AL PRIMER ELEMENTO DE LA MEMPOOL
		MempoolUnit * last_node;		 	// PUNTERO AL ULTIMO ELEMENTO DE LA MEMPOOL

	public:
	// Metodos

		//Constructores
		Mempool();         			    	// INICIALIZACION DE LA MEMPOOL VACIA
		/*Mempool( int pool_size );*/		// INICIALIZACION DE LA MEMPOOL CON
		~Mempool();                     	// DESTRUCCION DE LA MEMPOOL

		// Setters
		void set_new_pool_unit( MempoolUnit * p_memp_unit );     // AGREGA UNA TRANSACCION A LA MEMPOOL

		// Getters
		// Mempool &get_mempool();       		// DEVUELVE LA MEMPOOL
		int get_number_txns();					// DEVUELVE EL NUMERO DE TRANSACCIONES EN LA MEMPOOL

		Transaction get_transaction_n(int n);   // DEVUELVE LA N-ESIMA TRANSACCION DE LA MEMPOOL (LA MEMPOOL SE ORGANIZA EN ORDEN DESCENDENTE) 

};




#endif /* MEMPOOL_H_ */
