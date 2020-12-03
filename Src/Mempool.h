/*
 * mempool.h
 *
 *  Created on: Nov 16, 2020
 *      Author: a
 */

#ifndef MEMPOOL_H_
#define MEMPOOL_H_


using namespace std;
//#include "MempoolUnit.h"
#include "Transaction.h"
#include "lista.h"
// static lista <Transaction *> Mempool::Mempool;


class Mempool{

	private:

		//friend class Transaction;
		friend class BlockChainBookkeeper;
		static lista <Transaction *> transList;
		static void addNewTransaction(Transaction * new_txn);     // Usa metodos de LISTA para agregar un nuevo nodo con una transaccion
		//static Transaction & get_transaction_n(int n);   		// DEVUELVE LA N-ESIMA TRANSACCION DE LA MEMPOOL (LA MEMPOOL SE ORGANIZA EN ORDEN DESCENDENTE)
		static lista <Transaction *> & getTransactionsList();     // Devuelve un puntero a la lista de transacciones
		static size_t getMempoolLength();

	public:

};



#endif /* MEMPOOL_H_ */
