/*
 * BlockChainManager.cpp
 *
 *  Created on: 25 oct. 2020
 *      Author: Ramiro
 */
 
#include "BlockChainManager.h"

status_t BlockChainManager::state = STATUS_READING_COMMANDS;

void BlockChainManager::proccesBlockChain(std::istream *iss,std::ostream *oss){
	std::string command;
	payload_t payload;
	BlockChainFileManager fileManager;

	while (BlockChainManager::state == STATUS_READING_COMMANDS  ){

		BlockChainManager::proccesStatus( fileManager.translateCommands(iss,payload) );
		std::cout<< "Begin Parse Command ...";
		switch(payload.command)
		{
			case Commands::init:
				{
					std::cout<< "Done"<< std::endl;
				}
				break;
			case Commands::transfer:
				{
					std::cout<< "Done"<< std::endl;
				}
			break;
			case Commands::mine:
				{
					std::cout<< "Done"<< std::endl;
				}
				break;
			case Commands::block:
				{
					std::cout<< "Done"<< std::endl;
				}
				break;
			case Commands::balance:
				{
					std::cout<< "Done"<< std::endl;
				}
				break;
			case Commands::txn:
				{
					std::cout<< "Done"<< std::endl;
				}
				break;
			case Commands::load:
				{
					std::cout<< "Done"<< std::endl;
				}
				break;
			case Commands::save:
				{
					std::cout<< "Done"<< std::endl;
				}
				break;
			default:
				std::cout<< "Error Not Defined"<< std::endl;
				break;
		}

	}

//	BlockChainBuilder builder(BlockChainManager::getUserDefinedDifficulty());


//	std::cout<< "Begin Validate ...";
//	BlockChainManager::proccesStatus( fileManager.validate(iss) );
//
//	std::cout<< "Begin Parsing ..." ;
//	BlockChainManager::proccesStatus( fileManager.parse(iss,builder.getRawPointer()) );
//
//	std::cout<< "Begin Creating Block ..." ;
//	BlockChainManager::proccesStatus( builder.createBlockChain() );
//
//
//	std::cout<< "Begin Converting Block to File ..." << std::endl;
//	BlockChainManager::proccesStatus( fileManager.convert(oss,builder.getBlockChainPointer()) );
//
//	std::cout<< std::endl;
//	std::cout<< "Finish mining with hash :" << builder.getObtainedHash() << std::endl;
}

void BlockChainManager::proccesStatus(status_t status){
	state = status;
	switch(status){
	case STATUS_READING_COMMANDS:
		std::cout << "Reading.." << std::endl;
		break;
	case STATUS_ERROR_COMMAND_NOT_FOUND:
		std::cout << "FAIL" << std::endl;
		std::cerr << "Error Comando no conocido" << std::endl;
		std::abort();
		break;
	case STATUS_ERROR_COMMAND_PAYLOAD:
		std::cout << "FAIL" << std::endl;
		std::cerr << "Error Comando con argumentos invalidos" << std::endl;
		std::abort();
		break;
	case STATUS_OK:
		//std::cout << "Done" << std::endl;
		break;
	case STATUS_FINISH_CONVERT_SUCCESSFULY:
		break;
	case STATUS_CORRUPT_FORMAT:
		std::cout << "Error de Formato: Formato Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Formato Incorrecto" << std::endl;
		std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_HASH:
		std::cout << "Error de Formato: Hash incorrecto" << std::endl;
		std::cerr << "Error de Formato: Hash incorrecto" << std::endl;
		std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_TXINDEX:
		std::cout << "Error de Formato: Indice de Tx incorrecto" << std::endl;
		std::cerr << "Error de Formato: Indice de Tx incorrecto" << std::endl;
		std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_TXIN:
		std::cout << "Error de Formato: Indice Tx In Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Indice Tx In Incorrecto" << std::endl;
		std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_TXOUT:
		std::cout << "Error de Formato: Indice Tx Out Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Indice Tx Out Incorrecto" << std::endl;
		std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_BTCVALUE:
		std::cout << "Error de Formato: Valor de Bitcoin Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Valor de Bitcoin Incorrecto" << std::endl;
		std::abort();
		break;
	case STATUS_BAD_ALLOC:
		std::cout << "Error de sistema: Memoria insuficiente" << std::endl;
		std::cerr << "Error de sistema: Memoria insuficiente" << std::endl;
		std::abort();
		break;
	case STATUS_BAD_READ_INPUT_FILE:
		std::cout << "Error de Lectura: Archivo de entrada dañado" << std::endl;
		std::cerr << "Error de Lectura: Archivo de entrada dañado" << std::endl;
		std::abort();
		break;
	case STATUS_BAD_READ_OUTPUT_FILE:
		std::cout << "Error de Lectura: Archivo de salida dañado" << std::endl;
		std::cerr << "Error de Lectura: Archivo de salida dañado" << std::endl;
		std::abort();
		break;
		case STATUS_NO_BLOCKS_TO_CONVERT:
		std::cout << "Error de Conversion: No hay nada que convertir" << std::endl;
		std::cerr << "Error de Conversion: No hay nada que convertir" << std::endl;
		std::abort();
		break;
	default:
		std::cout << std::endl;
		break;
	}
}


#define DIFFICULTY_DEFAULT_VALUE 3
unsigned int BlockChainManager::userDefinedDifficulty = DIFFICULTY_DEFAULT_VALUE;

void BlockChainManager::setUserDefinedDifficulty(int d){
	if( d < 0 ){
		std::cout << "Error de Formato: Dificultad debe ser mayor a cero " << std::endl;
		std::cerr << "Error de Formato: Dificultad debe ser mayor a cero" << std::endl;
		std::abort();
	}
	userDefinedDifficulty = (unsigned int) d;
}


unsigned int BlockChainManager::getUserDefinedDifficulty( void ){
	return userDefinedDifficulty;
}
