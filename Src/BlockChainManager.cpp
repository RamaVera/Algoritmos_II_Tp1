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
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// std::string usr	 = payload.user;
					// float value 		 = payload.value;
					// unsigned int bits = payload.bits;
					//--------------------------------------------------------------//

					//BlockChainBookkeeper bookkeeper;
					//BlockChainBuilder builder(payload.bits);

					// Builder crea un bloque origen con los datos suministrados en payload
					// BlockChainManager::proccesStatus( builder.createOriginBlock(payload) );
					// std::cout<< "Finish mining with hash :" << builder.getObtainedHash() << std::endl;

					// Bookkeeper guarda ese bloque en la historia y actualiza su lista de usuarios
					// BlockChainManager::proccesStatus( bookkeeper.saveInHistoryBook(builder.getBlockChainPointer());

				}
				break;
			case Commands::transfer:
				{
					std::cout<< "Done"<< std::endl;
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// raw_t * pRaw = payload.pRaw;

					// OBSERVACION IMPORTANTE:
					// El raw_t que se tiene por comandos no esta completo puesto que no se sabe
					// el valor del outpoint (no se da esos datos por comando).
					// El Bookkeeper debe completar los datos del outpoint del history book de lo
					// contrario devolver error puesto que no existe el usuario
					//--------------------------------------------------------------//

					//BlockChainBookkeeper bookkeeper;

					// Bookkeeper intenta completar el raw_t, funciona como validacion puesto que
					// si no lo logra completar, el usario no existe en la historia
					// BlockChainManager::proccesStatus( bookkeeper.checkInformation(payload) )

					// Bookkeeper guarda ese bloque en la mempool y actualiza su lista de usuarios
					// BlockChainManager::proccesStatus( bookkeeper.saveInMempool(payload) );

				}
			break;
			case Commands::mine:
				{
					std::cout<< "Done"<< std::endl;
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// unsigned int bits = payload.bits;
					//--------------------------------------------------------------//
					// BlockChainBookkeeper bookkeeper;
					// BlockChainBuilder builder(payload.bits);

					// Builder le pide la mempool a bookkeeper y la guarda en su raw
					// BlockChainManager::proccesStatus( builder.setRawData( bookkeeper.getMempool() ) )

					// Builder mina el bloque como lo hacia anteriormente
					// BlockChainManager::proccesStatus( builder.createBlockChain() );
					// std::cout<< "Finish mining with hash :" << builder.getObtainedHash() << std::endl;

					// Bookkeeper guarda ese bloque en la historia y actualiza su lista de usuarios
					//BlockChainManager::proccesStatus( bookkeeper.saveInHistoryBook(builder.getBlockChainPointer());
				}
				break;
			case Commands::block:
				{
					std::cout<< "Done"<< std::endl;
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// std::string id = payload.id;
					//--------------------------------------------------------------//
					// BlockChainBookkeeper bookkeeper;

					// Blockkeeper busca en su libro contable el bloque requerido.
					// 'Block' es un tipo enumerativo interno de bookkeeper para
					// buscar solo mirando los hash de bloques.
					// BlockChainManager::proccesStatus( bookkeeper.searchInHistoryBook( 'Block', payload.id );
				}
				break;
			case Commands::balance:
				{
					std::cout<< "Done"<< std::endl;
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// std::string usr = payload.usr;
					//--------------------------------------------------------------//
					// BlockChainBookkeeper bookkeeper;

					// Blockkeeper busca en su libro lista de usuarios al usr correspondiente
					// BlockChainManager::proccesStatus( bookkeeper.searchInUserList( payload.usr );
				}
				break;
			case Commands::txn:
				{
					std::cout<< "Done"<< std::endl;
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// std::string id = payload.id;
					//--------------------------------------------------------------//
					// BlockChainBookkeeper bookkeeper;

					// Blockkeeper busca en su libro contable la transaccion requerida.
					// 'Transaction' es un tipo enumerativo interno de bookkeeper para
					// buscar solo mirando los hash de Transaction.
					// BlockChainManager::proccesStatus( bookkeeper.searchInMempool( 'Transaction', payload.id );
				}
				break;
			case Commands::load:
				{
					std::cout<< "Done"<< std::endl;
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// std::string filename = payload.filename;
					//--------------------------------------------------------------//
					// El filemanager ya esta intanciado antes.
					// BlockChainBookkeeper bookkeeper;

					// Filemanager abre el archivo pasado como argumento dentro del payload.
					// BlockChainManager::proccesStatus( filemanager.open( payload.filename ) )

						// ifs.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
						// try {
						//	ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
															// sequence of characters (i.e., a C-string) representing
															// the current value of the string object.
						//}
						//catch (std::system_error& e) {
						//	std::cerr << "Exception opening/reading/closing file error: " << e.code().message() << "\n";

					// Filemanager valida que la estructura de la blockchain este correctamente
					// BlockChainManager::proccesStatus( filemanager.validate( payload.filename ) )

					// Aca se me ocurre el laburo de 2 maneras, pero no estoy seguro.
					// 1)  Hacer que filemanager aprenda el formato de lista<Bloques> y trabaje con ella
					// y le pase la lista de bloques a bookkeeper y el la agrege en la historia. En el Tp0
					// solo usaba lista de bloques para convertir, pero nunca habia tenido que leer lista
					// de bloques
					// o
					// 2)  Instanciar a builder que ya aprendio a usar lista de bloques y que filemanager
					// lo cargue con setters de builder y que luego bookkeeper toma la lista de bloques de builder

					// Bookkeeper guarda en la historia
					// BlockChainManager::proccesStatus( bookkeeper.saveInHistoryBook( X.getBlockChainPointer());

					// Filemanager cierra el archivo pasado como argumento dentro del payload.
					// BlockChainManager::proccesStatus( filemanager.close( payload.filename ) )
				}
				break;
			case Commands::save:
				{
					std::cout<< "Done"<< std::endl;
					//--------------------------------------------------------------//
					// Datos del payload que sirven en este caso.
					// std::string filename = payload.filename;
					//--------------------------------------------------------------//
					// El filemanager ya esta intanciado antes.
					// BlockChainBookkeeper bookkeeper;

					// Filemanager abre el archivo pasado como argumento dentro del payload.
					// BlockChainManager::proccesStatus( filemanager.open( payload.filename ) )

					//std::cout<< "Begin Converting Block to File ..." << std::endl;
					//BlockChainManager::proccesStatus( fileManager.convert(fileManager.oss, bookkeeper.getHistoryBook() );


}
				break;
			default:
				std::cout<< "Error Not Defined"<< std::endl;
				break;
		}
	}
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
