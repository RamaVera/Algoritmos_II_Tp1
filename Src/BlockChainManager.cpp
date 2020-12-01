/*
 * BlockChainManager.cpp
 *
 *  Created on: 25 oct. 2020
 *      Author: Ramiro
 */
 
#include "BlockChainManager.h"

status_t BlockChainManager::state = STATUS_OK;
status_t BlockChainManager::command = STATUS_READING_COMMANDS;

// Descripcion: proccesBlockChain es un metodo que encapsula toda la logica interna de blockchain
// en este metodo, dependiendo el comando de entrada, se instanciaran las clases BlockChainBuilder,
// BlockChainBookkeeper y BlockChainFileManafer que realizaran la tarea seleccionada.
// Precondicion: Toda logica relacionada a blockchain debe estar invocada desde esta zona
// Postcondicion:
void BlockChainManager::proccesBlockChain(){
	BlockChainManager::proccesStatus(STATUS_READING_COMMANDS);
	std::string command;
	payload_t payload;
	BlockChainFileManager fileManager;

	while (BlockChainManager::command != STATUS_NO_MORE_COMMANDS ){
		BlockChainManager::proccesStatus( fileManager.translateCommands(payload) );
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
					// BlockChainManager::proccesStatus( bookkeeper.checkInformation(payload.raw) )

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
					// BlockChainManager::proccesStatus( builder.setTransaction( bookkeeper.getMempool() ) )

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
					file_t newFile;
					newFile.fileID = payload.filename;
					newFile.type = FileTypes::loadBlockChainFile;
					newFile.mode = ios::in;
					newFile.isStandard = false;
					BlockChainManager::proccesStatus( fileManager.addFile(newFile) );


					// Filemanager valida que la estructura de la blockchain este correctamente
					BlockChainManager::proccesStatus( fileManager.validateBlockChain() );

					// Bookkeeper guarda en la historia
					// BlockChainManager::proccesStatus( bookkeeper.saveInHistoryBook( X.getBlockChainPointer());

					// Filemanager cierra el archivo pasado como argumento dentro del payload.
					BlockChainManager::proccesStatus( fileManager.removeFile( newFile.type) );
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
					BlockChainBookkeeper bookkeeper;
					file_t newFile;
					newFile.fileID = payload.filename;
					newFile.type = FileTypes::saveBlockChainFile;
					newFile.mode = ios::out;
					newFile.isStandard = false;

					// Filemanager abre el archivo pasado como argumento dentro del payload.
					BlockChainManager::proccesStatus( fileManager.addFile(newFile) );


					fileManager << newFile.type << "Mensaje Especial\n";
					fileManager << newFile.type << "Mensaje Especial 2 \n";

					std::cout<< "Begin Converting Block to File ..." << std::endl;
					//BlockChainManager::proccesStatus( fileManager.convert(fileManager.oss, bookkeeper.getHistoryBook() );

					// Filemanager cierra el archivo pasado como argumento dentro del payload.
					BlockChainManager::proccesStatus( fileManager.removeFile( newFile.type) );

				}
				break;
			default:
				BlockChainManager::command  = STATUS_NO_MORE_COMMANDS;
				std::cout<< "Fail: Error Not Defined"<< std::endl;
				break;
		}
	}
	BlockChainManager::proccesStatus(fileManager.removeAllFiles());
	cout << "Finishing Execution " << endl;
}

// Descripcion: proccesStatus es un metodo que analiza los estados de salida de las clases
// BlockChainBuilder,BlockChainBookkeeper y BlockChainFileManafer que son las que realizan
// las tareas. En base a dichos estados BlockChainManager decide el flujo del programa.
// Precondicion:
// Postcondicion:
void BlockChainManager::proccesStatus(status_t status){
	BlockChainFileManager fileManager;
	state = status;
	switch(status){
	// -------- Terminaciones Correctas-----//
	case STATUS_OK:
		//std::cout << "Done" << std::endl;
		break;
	case STATUS_READING_COMMANDS:
		command = STATUS_READING_COMMANDS;
		//std::cout << "Reading.." << std::endl;
		break;
	case STATUS_NO_MORE_COMMANDS:
		command = STATUS_NO_MORE_COMMANDS;
		//std::cout << "Reading.." << std::endl;
		break;
	case STATUS_OPEN_FILE_SUCCESSFULY:
		break;
	case STATUS_CLOSE_FILE_SUCCESSFULY:
		break;
	case STATUS_FINISH_CONVERT_SUCCESSFULY:
		fileManager << FileTypes::userCommandResponseFiles << "OK\n";
		break;
	//-------- Errores ------------------//
	case STATUS_ERROR_COMMAND_NOT_FOUND:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		std::cerr << "Error Comando no conocido" << std::endl;
		//std::abort();
		break;
	case STATUS_ERROR_COMMAND_PAYLOAD:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		std::cerr << "Error Comando con argumentos invalidos" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Formato Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Formato Incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_BITS:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Hash incorrecto" << std::endl;
		std::cerr << "Error de Formato: Hash incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_NONCE:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Hash incorrecto" << std::endl;
		std::cerr << "Error de Formato: Hash incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_HASH:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Hash incorrecto" << std::endl;
		std::cerr << "Error de Formato: Hash incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_TXINDEX:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Indice de Tx incorrecto" << std::endl;
		std::cerr << "Error de Formato: Indice de Tx incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_TXIN:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Indice Tx In Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Indice Tx In Incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_TXOUT:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Indice Tx Out Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Indice Tx Out Incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_CORRUPT_FORMAT_BAD_BTCVALUE:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Formato: Valor de Bitcoin Incorrecto" << std::endl;
		std::cerr << "Error de Formato: Valor de Bitcoin Incorrecto" << std::endl;
		//std::abort();
		break;
	case STATUS_BAD_ALLOC:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de sistema: Memoria insuficiente" << std::endl;
		std::cerr << "Error de sistema: Memoria insuficiente" << std::endl;
		std::abort();
		break;
	case STATUS_BAD_READ_INPUT_FILE:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Lectura: Archivo de entrada da�ado" << std::endl;
		std::cerr << "Error de Lectura: Archivo de entrada da�ado" << std::endl;
		std::abort();
		break;
	case STATUS_BAD_READ_OUTPUT_FILE:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Lectura: Archivo de salida da�ado" << std::endl;
		std::cerr << "Error de Lectura: Archivo de salida da�ado" << std::endl;
		std::abort();
		break;
		case STATUS_NO_BLOCKS_TO_CONVERT:
		fileManager << FileTypes::userCommandResponseFiles << "FAIL\n";
		//std::cout << "Error de Conversion: No hay nada que convertir" << std::endl;
		std::cerr << "Error de Conversion: No hay nada que convertir" << std::endl;
		//std::abort();
		break;
	default:
		std::cout << std::endl;
		break;
	}
}


lista<file_t *> BlockChainManager::userFiles;

// Descripcion: setUserFilename es un metodo utilizado en cmdline en la version 2.1.1
// con el objetivo de cargar el archivo del usuario en un archivo file_t y darselo al
// filemanager. En este metodo solo se cargaran los campos de filename, mode y type.
// - filename: hace referencia al nombre del archivo. En caso de no ser un archivo real, se
// denominara como Standard Input o Standard Output.
// - mode: hace referencia a si es un archivo de entrada ios::in o de salida ios::out
// - type: hace referencia al tipo de archivo que se pasar�. En este metodo solo existiran
// los tipos FileTypes::userCommandInputFiles y  FileTypes::userCommandResponseFiles.
// Precondicion: Se espera que los argumentos de este setter esten correctos
// Postcondicion: Se da un file_t a fileManager.
void BlockChainManager::setUserFilename(ios_base::openmode mode, std::string filename, bool isStandard){
	BlockChainFileManager fileManager;
	//---Si es un archivo de entrada---//
	if( mode == ios::in){
		if(isStandard){
			filename += " Input";
			cout << "La direccion del archivo Origen es : Cin (Entrada Standard)" << endl;
		}
		else{
			cout<<	"La direccion del archivo Origen es : "<< filename << endl;
		}
		file_t usrFile;
		usrFile.fileID = filename;
		usrFile.mode = mode;
		usrFile.type = FileTypes::userCommandInputFiles;
		usrFile.isStandard = isStandard;
		BlockChainManager::proccesStatus( fileManager.addFile(usrFile) );
	}else //---Si es un archivo de salida---//
		if( mode == ios::out){
		if(isStandard){
			filename += " Output";
			cout<< "La direccion del archivo Destino es: Cout (Salida Standard)" << endl;
		}
		else{
			cout<< "La direccion del archivo Destino es : "<< filename <<endl;;
		}
		file_t usrFile;
		usrFile.fileID = filename;
		usrFile.mode = mode;
		usrFile.type = FileTypes::userCommandResponseFiles;
		usrFile.isStandard = isStandard;
		BlockChainManager::proccesStatus( fileManager.addFile(usrFile) );
	}
}

//-----------------------------------------------------------------------------------//
// OBSOLETO PARA LA VERSION 2.1.1 (TP1)

#define DIFFICULTY_DEFAULT_VALUE 3
unsigned int BlockChainManager::userDefinedDifficulty = DIFFICULTY_DEFAULT_VALUE;


// Descripcion: Metodo que se utilizo en la version 1.1.1 (Tp0) para cargar el valor de
// dificultad (bits) desde la clase cmdline. En la version 2.1.1 (Tp1) ya no se vuelve a usar
// Precondicion: Debe llegar un int para verificar el signo
// Postcondicion: Debe cargarse un unsined_int en la variable estatica userDefinedDifficulty
// con el valor de entrada
void BlockChainManager::setUserDefinedDifficulty(int d){
	if( d < 0 ){
		std::cout << "Error de Formato: Dificultad debe ser mayor a cero " << std::endl;
		std::cerr << "Error de Formato: Dificultad debe ser mayor a cero" << std::endl;
		std::abort();
	}
	userDefinedDifficulty = (unsigned int) d;
}

// Descripcion: Metodo que se utilizo en la version 1.1.1 (Tp0) devolver el valor de
// userDefinedDifficulty. En la version 2.1.1 (Tp1) ya no se vuelve a usar
// Precondicion: Debe haberse cargado userDefinedDifficulty previamente con el metodo setter
// Postcondicion: Devuelve el valor de userDefinedDifficulty
unsigned int BlockChainManager::getUserDefinedDifficulty( void ){
	return userDefinedDifficulty;
}

//-----------------------------------------------------------------------------------//

