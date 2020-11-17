/*
 * BlockChainManager.h
 *
 *  Created on: 25 oct. 2020
 *      Author: Ramiro
 */

#ifndef BLOCKCHAINMANAGER_H_
#define BLOCKCHAINMANAGER_H_

#include <iostream>
#include "BlockChainStatus.h"
#include "BlockChainFileManager.h"
#include "BlockChainBuilder.h"
#include "BlockChainBookkeeper.h"

class BlockChainManager {
	static status_t state;
	static unsigned int userDefinedDifficulty;
	static void parseCommands(std::string command,payload_t & payload);
public:

	static void	proccesBlockChain( std::istream *iss, std::ostream *oss );
	static void	proccesStatus( status_t status );

	static void setUserDefinedDifficulty(int d);
	static unsigned int getUserDefinedDifficulty(void);

};

#endif /* BLOCKCHAINMANAGER_H_ */
