/*
 * BlockChainDataTypes.h
 *
 *  Created on: 4 nov. 2020
 *      Author: Ramiro
 */

#ifndef BLOCKCHAINDATATYPES_H_
#define BLOCKCHAINDATATYPES_H_
#include <string>
//Interfaz entre FileManager Hacia Builder
typedef struct{
	int inTx;
	std::string * IN_tableOfTxId;
	int * IN_tableOfIndex ;
	std::string * IN_tableOfAddr;
	int outTx;
	float * OUT_tableOfValues;
	std::string * OUT_tableOfAddr;
} raw_t;



#endif /* BLOCKCHAINDATATYPES_H_ */
