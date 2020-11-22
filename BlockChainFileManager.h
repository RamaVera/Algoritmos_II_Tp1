/*
 * BlockChainFileManager.h
 *
 *  Created on: 25 oct. 2020
 *      Author: Ramiro
 */

#ifndef BLOCKCHAINFILEMANAGER_H_
#define BLOCKCHAINFILEMANAGER_H_

#include <iostream>
#include <sstream>
#include <ostream>
#include "BlockChainStatus.h"
#include "BlockChainBuilder.h"
#include "BlockChainDataTypes.h"
#include "TiposHash.h"
#include "Queue.h"

class BlockChainFileManager {
private:
	raw_t * pRawData;

	bool isEmpty(std::istream  * iss);
	bool isTxIndexFromStream(std::istream *iss,char delim = '\n', int * pValue = NULL);
	bool isHashFromStream(std::istream *iss,char delim = '\n', std::string * pString = NULL);
	bool isBTCValueFromStream(std::istream *iss,char delim = '\n', float * pFloat = NULL);
	bool isEofFromStream(std::istream *iss);
	int  getTxIndexFromStream(std::istream *iss,char delim = '\n');
	std::string getHashFromStream(std::istream *iss,char delim = '\n');
	float getBTCValueFromStream(std::istream *iss,char delim = '\n');

	bool isOnValidCommandTable(std::string command,Commands & commandType);
	unsigned int getNumberOfValidFunctions( void );
	void safeValuePayload(payload_t & payload);
public:
	BlockChainFileManager();
	~BlockChainFileManager();
	status_t validate(std::istream * iss);
	status_t parse(std::istream * iss,raw_t * &pRawData);
	status_t convert(std::ostream * oss,const lista <Block *> & BlockChain);

	status_t translateCommands(std::istream * iss, payload_t & payload);
};

#endif /* BLOCKCHAINFILEMANAGER_H_ */
