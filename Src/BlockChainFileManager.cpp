/*
 * BlockChainFileManager.cpp
 *
 *  Created on: 25 oct. 2020
 *      Author: Ramiro
 */

#include "BlockChainFileManager.h"


BlockChainFileManager::BlockChainFileManager() {
	pRawData = NULL;
}

BlockChainFileManager::~BlockChainFileManager() {
	if(this->pRawData != NULL){
		pRawData->inTx = 0;
		delete [] pRawData->IN_tableOfTxId; 		pRawData->IN_tableOfTxId    = NULL;
		delete [] pRawData->IN_tableOfIndex;		pRawData->IN_tableOfIndex   = NULL;
		delete [] pRawData->IN_tableOfAddr;			pRawData->IN_tableOfAddr    = NULL;
		pRawData->outTx = 0;
		delete [] pRawData->OUT_tableOfValues;		pRawData->OUT_tableOfValues = NULL;
		delete [] pRawData->OUT_tableOfAddr;		pRawData->OUT_tableOfAddr   = NULL;
		delete pRawData;
		pRawData = NULL;
	}
}
status_t BlockChainFileManager::validate(std::istream * iss){
	if( ! this->isEmpty(iss)){
			int inTxTotal,outTxTotal;
		if( this->isTxIndexFromStream(iss,'\n',&inTxTotal) == false ) 	return STATUS_CORRUPT_FORMAT_BAD_TXIN;
		for(int inTx = 0 ; inTx < inTxTotal ; inTx++){
			if( this->isHashFromStream(iss,' ') == false ) 				return STATUS_CORRUPT_FORMAT_BAD_HASH;
			if( this->isTxIndexFromStream(iss,' ') == false ) 			return STATUS_CORRUPT_FORMAT_BAD_TXINDEX;
			if( this->isHashFromStream(iss) == false ) 					return STATUS_CORRUPT_FORMAT_BAD_HASH;
		}
		if( this->isTxIndexFromStream(iss,'\n',&outTxTotal) == false ) 	return STATUS_CORRUPT_FORMAT_BAD_TXOUT;
		for(int outTx = 0 ; outTx < outTxTotal ; outTx++){
			if( this->isBTCValueFromStream(iss,' ') == false ) 			return STATUS_CORRUPT_FORMAT_BAD_BTCVALUE;
			if( this->isHashFromStream(iss) == false ) 				    return STATUS_CORRUPT_FORMAT_BAD_HASH;
		}
		if( this->isEofFromStream(iss) == false ) 						return STATUS_CORRUPT_FORMAT;
	}
	return STATUS_OK;
}

bool BlockChainFileManager::isEmpty(std::istream  * iss)
{
	// PRECONDICION: ESTA FUNCION SOLO DEBE USARSE ANTES DE HACER
	// EL TRABAJO DEL ARCHIVO PUESTO QUE AL TERMINAR DEJA APUNTANDO
	// AL PRINCIPIO

	bool empty;
	//Voy al final de File
	iss->seekg(0, ios::end);
	empty = (iss->tellg() == 0)? true: false;
	//Vuelvo al principio del File
	iss->clear();
	iss->seekg(0, iss->beg);
	return empty;

}

bool BlockChainFileManager::isTxIndexFromStream(std::istream *iss,char delim , int * pValue)
{
	int IndexValue;
	std::string line;
	std::stringstream ss;

	std::getline(*iss, line,delim);
	ss.str(line);
	if ((ss >> IndexValue).fail())	  return false;
	if (IndexValue < 0) 			  return false;
	//Debug
	//std::cout << line << std::endl;
	if(pValue != NULL) *pValue = IndexValue;
	return true;
}

bool BlockChainFileManager::isHashFromStream(std::istream *iss,char delim, std::string * pString)
{
	std::string line;
	std::stringstream ss;
	std::getline(*iss, line,delim);
	if( line.back() == '\r'){  				//Para portabilidad Linux - Window
		line.substr(0, line.size()-1);
	}
	if ( line.size() != (size_t) LargoHash::LargoHashEstandar ) 	return false;
	for (unsigned int i = 0; i < line.length(); ++i) {
		if ( ! isxdigit ( line[i] ) ) 								return false;
	}
	//Debug
	//std::cout << line << std::endl;
	if(pString != NULL) *pString = line;
	return true;

}

bool BlockChainFileManager::isBTCValueFromStream(std::istream *iss,char delim,float * pFloat)
{
	float floatValue;
	std::string line;
	std::stringstream ss;

	std::getline(*iss, line,delim);
	ss.str(line);
	if ((ss >> floatValue).fail())	  return false;
	if (floatValue < 0) 			  return false;
	//Debug
	//std::cout << line << std::endl;
	if(pFloat != NULL) *pFloat = floatValue;
	return true;
}

bool BlockChainFileManager::isEofFromStream(std::istream *iss){
	std::string line;
	if (iss->eof()) return true;
	try{
		if (std::getline(*iss, line,'\r').fail() ) return true;
	}catch(const std::ios_base::failure& ex) {
		//std::cerr << "Caught: std::ios_base::failure" << std::endl;
		iss->clear();
		return true;
	}
	if (line.size() != 0 )
		return false;
	return true;
}


status_t BlockChainFileManager::parse(std::istream * iss, raw_t * &pBuilderRawData){

	//Creo el archivo raw_t en el entorno del filemanager
	this->pRawData = new raw_t{0};
	if ( ! this->isEmpty(iss)){
		if(pRawData == NULL) return STATUS_BAD_ALLOC;
		pRawData->inTx = this->getTxIndexFromStream(iss,'\n');

		pRawData->IN_tableOfTxId = new std::string[pRawData->inTx];
		pRawData->IN_tableOfIndex = new int[pRawData->inTx];
		pRawData->IN_tableOfAddr = new std::string[pRawData->inTx];
		if(		pRawData->IN_tableOfTxId == NULL  ||
				pRawData->IN_tableOfIndex == NULL ||
				pRawData->IN_tableOfAddr == NULL ) 	return STATUS_BAD_ALLOC;

		for(int i = 0; i < pRawData->inTx; i++)
		{
			pRawData->IN_tableOfTxId[i]  = this->getHashFromStream(iss,' ');
			pRawData->IN_tableOfIndex[i] = this->getTxIndexFromStream(iss,' ');
			pRawData->IN_tableOfAddr[i]  = this->getHashFromStream(iss);
		}

		pRawData->outTx = this->getTxIndexFromStream(iss,'\n');
		pRawData->OUT_tableOfValues = new float[pRawData->outTx];
		pRawData->OUT_tableOfAddr = new std::string[pRawData->outTx];
		if(		pRawData->OUT_tableOfValues == NULL  ||
				pRawData->OUT_tableOfAddr   == NULL  ) 	return STATUS_BAD_ALLOC;

		for(int i = 0; i < pRawData->outTx; i++)
		{
			pRawData->OUT_tableOfValues[i]  = this->getBTCValueFromStream(iss,' ');
			pRawData->OUT_tableOfAddr[i] = this->getHashFromStream(iss);
		}
	}
	pBuilderRawData = this->pRawData;

	return STATUS_OK;
}


int BlockChainFileManager::getTxIndexFromStream(std::istream *iss,char delim)
{
	int IndexValue;
	std::string line;
	std::stringstream ss;

	std::getline(*iss, line,delim);
	ss.str(line);
	ss >> IndexValue;
	return IndexValue;
}

std::string BlockChainFileManager::getHashFromStream(std::istream *iss,char delim)
{
	std::string line;
	std::stringstream ss;
	std::getline(*iss, line,delim);
	return line;
}

float BlockChainFileManager::getBTCValueFromStream(std::istream *iss,char delim)
{
	float floatValue;
	std::string line;
	std::stringstream ss;

	std::getline(*iss, line,delim);
	ss.str(line);
	ss >> floatValue;
	return floatValue;
}



status_t BlockChainFileManager::convert(std::ostream * iss, const lista <Block *> & BlockChain){
	lista <Block *> ::iterador it(BlockChain);
	std::string obtainedHash;

	if(!iss->good())						return STATUS_BAD_READ_OUTPUT_FILE;
	if( BlockChain.vacia() )				return STATUS_NO_BLOCKS_TO_CONVERT;
	while(!it.extremo()){
		*iss << it.dato()->getpre_block() << '\n';
		*iss << it.dato()->gettxns_hash() << '\n';
		*iss << it.dato()->getbits( )	  << '\n';
		*iss << it.dato()->getnonce()	  << '\n';
		*iss << it.dato()->gettxn_count() << '\n';
		*iss << it.dato()->getcadenaprehash();	
		it.avanzar();
	}
	return STATUS_FINISH_CONVERT_SUCCESSFULY;
}


status_t BlockChainFileManager::translateCommands(std::istream * iss, payload_t & payload){
	std::string command,line;
	bool eof = false;
	Commands commandType = Commands::commandNotDefined;

	//Preinicializo el pyaload en valores seguros
	this->safeValuePayload(payload);

	//Detecto de la primer linea, solo el comando
	if (std::getline(*iss,line).eof() )
		eof = true;
	//Encuentro el primer delimitador de comando
	size_t delim1 = line.find(' ');
	if ( delim1 == std::string::npos) 							return STATUS_ERROR_COMMAND_PAYLOAD;
	command = line.substr(0, delim1);

	//Valido y obtengo el comando
	if ( ! this->isOnValidCommandTable(command,commandType) ) 	return STATUS_ERROR_COMMAND_NOT_FOUND;

	//Completo el payload en base al comando
	switch(commandType)
	{
		case Commands::init:
			{
				//std::cout<< "init" << std::endl;
				std::string usr,value,bits;
				std::string::size_type sz;

				size_t delim2 = line.find(' ',delim1+1);
				if ( delim2 == std::string::npos) 	return STATUS_ERROR_COMMAND_PAYLOAD;
				size_t delim3 = line.find(' ',delim2+1);
				if ( delim3 == std::string::npos) 	return STATUS_ERROR_COMMAND_PAYLOAD;

				usr = line.substr(delim1 + 1,delim2 - delim1 - 1 );
				value = line.substr(delim2 + 1,delim3 - delim2 -1);
				bits = line.substr(delim3 + 1);

				//------------Debug -------------//
				//std::cout<< usr << std::endl;
				//std::cout<< value << std::endl;
				//std::cout<< bits << std::endl;

				payload.command = commandType;
				payload.user = usr;
				payload.value = std::stof(value,&sz);
				if( sz != value.size() ) return STATUS_ERROR_COMMAND_PAYLOAD;
				if( payload.value < 0 )	 return STATUS_ERROR_COMMAND_PAYLOAD;
				payload.bits = std::stoi(bits,&sz);
				if( sz != bits.size() )	 return STATUS_ERROR_COMMAND_PAYLOAD;
				if( payload.bits < 0 )	 return STATUS_ERROR_COMMAND_PAYLOAD;

			}
			break;
		case Commands::transfer:
			{
				//std::cout<< "transfer" << std::endl;
				std::string src,dest,value;
				std::string::size_type sz;

				size_t delim2 = line.find(' ',delim1+1);
				if ( delim2 == std::string::npos) 	return STATUS_ERROR_COMMAND_PAYLOAD;
				size_t delim3;
				size_t delim4;
				float auxValue;
				Queue<string> argQueue;
				size_t inTx = 1 ;
				size_t outTx = 0;
				src = line.substr(delim1 + 1,delim2 - delim1 - 1 );
				argQueue.enqueue(src);
				// Esta pasada valida, aucumula los datos
				// y cuenta la cantidad de destinos
				// Para luego pedir memoria dinamica con datos veraces.
				do{
					delim3 = line.find(' ',delim2+1);
					if ( delim3 == std::string::npos) 	return STATUS_ERROR_COMMAND_PAYLOAD;
					delim4 = line.find(' ',delim3+1);
					if ( delim3 != std::string::npos)

					dest = line.substr(delim2 + 1,delim3 - delim2 -1);
					argQueue.enqueue(dest);

					if ( delim4 != std::string::npos)
						value = line.substr(delim3 + 1,delim4 - delim3 -1);
					else{
						value = line.substr(delim3 + 1);
						if(value.empty()) 		return STATUS_ERROR_COMMAND_PAYLOAD;
					}
					auxValue = std::stof(value,&sz);
					if( sz != value.size() ) 	return STATUS_ERROR_COMMAND_PAYLOAD;
					if( auxValue < 0 )			return STATUS_ERROR_COMMAND_PAYLOAD;
					argQueue.enqueue(value);

					outTx ++;
					delim2 = delim4;
				}while( delim4 != std::string::npos);

				// Comienzo a rellenar el payload

				//Creo el archivo raw_t en el entorno del filemanager
				this->pRawData = new raw_t{0};
				if(pRawData == NULL) return STATUS_BAD_ALLOC;
				pRawData->inTx = inTx;

				pRawData->IN_tableOfTxId = new std::string[pRawData->inTx];
				pRawData->IN_tableOfIndex = new int[pRawData->inTx];
				pRawData->IN_tableOfAddr = new std::string[pRawData->inTx];

				if(		pRawData->IN_tableOfTxId == NULL  ||
						pRawData->IN_tableOfIndex == NULL ||
						pRawData->IN_tableOfAddr == NULL ) 	return STATUS_BAD_ALLOC;

				for(int i = 0; i < pRawData->inTx; i++)
				{
					// El outpoint en esta instancia no puede parsearse puesto que como comando
					// no se tiene esa informacion. Tampoco se tiene un hash de la direccion por
					// se envia en el addr el string del nombre.
					pRawData->IN_tableOfTxId[i]  = "";
					pRawData->IN_tableOfIndex[i] = -1;
					pRawData->IN_tableOfAddr[i]  = argQueue.dequeue();
				}

				pRawData->outTx = outTx;
				pRawData->OUT_tableOfValues = new float[pRawData->outTx];
				pRawData->OUT_tableOfAddr = new std::string[pRawData->outTx];

				if(		pRawData->OUT_tableOfValues == NULL  ||
						pRawData->OUT_tableOfAddr   == NULL  ) 	return STATUS_BAD_ALLOC;

				for(int i = 0; i < pRawData->outTx; i++)
				{

					pRawData->OUT_tableOfAddr[i] = argQueue.dequeue();
					pRawData->OUT_tableOfValues[i] = std::stof( argQueue.dequeue() );
				}

				// Como el Raw data no esta completamente relleno puesto
				// que no se tiene toda la data necesaria para el minado
				// se levanta el completeFlag en falso
				pRawData->completeFlag = false;

				payload.command = commandType;
				payload.pRaw = pRawData;
			}
		break;
		case Commands::mine:
			{
				//std::cout<< "mine" << std::endl;
				std::string bits;
				std::string::size_type sz;
				bits = line.substr(delim1 + 1);

				//------------Debug -------------//
				//std::cout<< bits << std::endl;

				payload.command = commandType;
				payload.bits = std::stoi(bits,&sz);
				if( sz != bits.size() )	 return STATUS_ERROR_COMMAND_PAYLOAD;
				if( payload.bits < 0 )	 return STATUS_ERROR_COMMAND_PAYLOAD;
			}
			break;
		case Commands::block:
			{
				//std::cout<< "block" << std::endl;
				std::string id;
				std::string::size_type sz;
				id = line.substr(delim1 + 1);

				//------------Debug -------------//
				//std::cout<< id << std::endl;

				payload.command = commandType;
				payload.id = std::stoi(id,&sz);
				if( sz != id.size() )	 return STATUS_ERROR_COMMAND_PAYLOAD;
				if( payload.bits < 0 )	 return STATUS_ERROR_COMMAND_PAYLOAD;
			}
			break;
		case Commands::balance:
			{
				//std::cout<< "balance" << std::endl;
				std::string usr;
				usr = line.substr(delim1 + 1);

				//------------Debug -------------//
				//std::cout<< usr << std::endl;

				payload.command = commandType;
				payload.user = usr;
			}
			break;
		case Commands::txn:
			{
				//std::cout<< "txn" << std::endl;
				std::string id;
				std::string::size_type sz;
				id = line.substr(delim1 + 1);

				//------------Debug -------------//
				//std::cout<< id << std::endl;

				payload.command = commandType;
				payload.id = std::stoi(id,&sz);
				if( sz != id.size() )	 return STATUS_ERROR_COMMAND_PAYLOAD;
				if( payload.bits < 0 )	 return STATUS_ERROR_COMMAND_PAYLOAD;
			}
			break;
		case Commands::load:
			{
				//std::cout<< "load" << std::endl;
				std::string filename;
				filename = line.substr(delim1 + 1);

				//------------Debug -------------//
				//std::cout<< filename << std::endl;

				payload.command = commandType;
				payload.filename = filename;
			}
			break;
		case Commands::save:
			{
				//std::cout<< "save" << std::endl;
				std::string filename;
				filename = line.substr(delim1 + 1);

				//------------Debug -------------//
				//std::cout<< filename << std::endl;

				payload.command = commandType;
				payload.filename = filename;
			}
			break;
		default:
			break;
	}

	if( eof == true) return STATUS_OK;

	return STATUS_READING_COMMANDS;
}

bool BlockChainFileManager::isOnValidCommandTable(std::string command, Commands & commandType)
{
	size_t i;
	size_t size = BlockChainFileManager::getNumberOfValidFunctions();
	bool functionIsOnTable = false;
	for(i = 0 ; i < size ; ++i)
	{
		if( command.compare(_commands_[i]) == 0 )
		{
			functionIsOnTable = true;
			break;
		}
	}
	commandType = static_cast<Commands>(i);
	return functionIsOnTable;
}

unsigned int BlockChainFileManager::getNumberOfValidFunctions()
{
	return sizeof(_commands_)/sizeof(std::string);
}

void BlockChainFileManager::safeValuePayload(payload_t & payload){
	payload.command = Commands::commandNotDefined;
	payload.pRaw = NULL;
	payload.filename = "";
	payload.id = "";
	payload.user = "";
	payload.value = 0;
	payload.bits = 0;
}
