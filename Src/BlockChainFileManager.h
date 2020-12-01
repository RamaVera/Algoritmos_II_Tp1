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
#include <fstream>
#include <string>
#include "BlockChainStatus.h"
#include "BlockChainBuilder.h"
#include "BlockChainDataTypes.h"
#include "TiposHash.h"
#include "Queue.h"
#include "lista.h"


class BlockChainFileManager {
private:

	raw_t * pRawData;
	static lista<file_t *> fileList;
	//-----Metodos sobre Streams ------- //
	bool isEmpty(std::istream  * iss);
	bool isTxIndexFromStream(std::istream *iss,char delim = '\n', int * pValue = NULL);
	bool isHashFromStream(std::istream *iss,char delim = '\n', std::string * pString = NULL);
	bool isBTCValueFromStream(std::istream *iss,char delim = '\n', float * pFloat = NULL);
	bool isEofFromStream(std::istream *iss);

	int  getTxIndexFromStream(std::istream *iss,char delim = '\n');
	std::string getHashFromStream(std::istream *iss,char delim = '\n');
	float getBTCValueFromStream(std::istream *iss,char delim = '\n');

	// ---- Metodos sobre Strings -------//
	bool isHashFromString(std::string line);
	bool isPositiveIntNumberFromString(std::string line);
	bool isPositiveFloatNumberFromString(std::string line);


	unsigned int getPositiveNumberFromString(std::string line);

	std::string getSubString(std::string line,size_t delim,unsigned int substringNum,bool * pState = NULL);

	// --- Metodos sobre lista de Archivos --//
	bool getFilefromList(FileTypes type,std::fstream * & fs);
	bool getIssfromList(FileTypes type,std::istream * & iss);
	bool getOssfromList(FileTypes type,std::ostream * & oss);


	bool isOnValidCommandTable(std::string command,Commands & commandType);
	unsigned int getNumberOfValidFunctions( void );
	void safeValuePayload(payload_t & payload);

public:
	BlockChainFileManager();
	~BlockChainFileManager();
	status_t validate(std::istream * iss);
	status_t validateBlockChain( void );
	status_t parse(std::istream * iss,raw_t * &pRawData);
	status_t convert(std::ostream * oss,const lista <Block *> & BlockChain);
	status_t translateCommands(payload_t & payload);
	status_t addFile( file_t & newFile);
	status_t removeFile(FileTypes type);
	status_t removeAllFiles();

	BlockChainFileManager& operator<<(std::string message);
	BlockChainFileManager& operator<<(FileTypes type);

};

#endif /* BLOCKCHAINFILEMANAGER_H_ */
