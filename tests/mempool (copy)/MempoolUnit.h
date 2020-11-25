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
		Transaction * txn;
		MempoolUnit * nxt_mem_unit;

	public:
		MempoolUnit();
		MempoolUnit( const MempoolUnit & last_node , const Transaction & new_txn );
		~MempoolUnit();
};


#endif /* MEMPOOLUNIT_H_ */
