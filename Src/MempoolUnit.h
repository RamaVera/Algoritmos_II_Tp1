/*
 * MempoolUnit.h
 *
 *  Created on: Nov 19, 2020
 *      Author: a
 */

#ifndef MEMPOOLUNIT_H_
#define MEMPOOLUNIT_H_

#include "Transaction.h"

using namespace std;

class MempoolUnit{

	private:
		const Transaction * txn;						// UN PUNTERO A UNA TRANSACCION
		MempoolUnit * nxt_mem_unit;						// UN PUNTERO AL SIGUIENTE ELEMENTO DE LA MEMPOOL

	public:
		MempoolUnit();									// CONSTRUYE UN OBJETO MEMPOOL UNIT VACIO
		MempoolUnit( const Transaction * new_txn );		// CONSTRUYE UN OBJETO MEMPOOL UNIT CARGADO CON LA TTRANSACCION EN new_txn
		~MempoolUnit();									// DESTRUCTOR DE OBJETO MEMPOOL UNIT
		Transaction get_txn();							// DEVUELVE LA TRANSACCION DE UNA MEMPOOL UNIT
		MempoolUnit * get_next_unit();					// DEVUELVE EL PUNTERO AL OBJETO MEMPOOL UNIT ENCADENADO SIGUIENTE
		void set_next_node( MempoolUnit * p_mem_unit);	// SETEA EL NODO SIGUIENTE EN EL ATRIBUTO nxt_mem_unit DEL OBJETO REFERIDO
};


#endif /* MEMPOOLUNIT_H_ */
