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
	bool completeFlag;
} raw_t;

//Precondicion:  La enum class como la tabla debe estar ordenada de la misma manera y commandNotDefined debe ir siempre al final.
const static std::string _commands_[] = { "init", "mine", "transfer", "block", "balance", "txn","load","save"};

enum class Commands{
		init,
		mine,
		transfer,
		block,
		balance,
		txn,
		load,
		save,
		commandNotDefined,
};

typedef struct{
	Commands command;
	raw_t * pRaw;
	std::string filename;
	std::string user;
	std::string id;
	float value;
	int bits;
}payload_t;



#endif /* BLOCKCHAINDATATYPES_H_ */