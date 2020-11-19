/*
 * Extracto.h
 */

#ifndef EXTRACTO_H_
#define EXTRACTO_H_

#include "Block.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "BlockChainDataTypes.h"
#include "lista.h"

typedef struct {
	std::string txns_hash;						// Id del BlockChain
	std::string addr;							// Id Cuenta Origen o Destino
	float value;								// monto, débito < 0, crédito > 0
} movimientos_t;

typedef struct {
	std::string txns_hash;						// Id del BlockChain Actual
	TransactionInput TI;						// Transaction Input a buscar el outPut
} TransactionInput_t;

typedef struct {
	std::string txns_hash;						// Id del BlockChain del outPut
	size_t to_index;						    // ID del Transaction Output en el BlockChain
	TransactionOutput TO;						// Transaction Output
} TransactionOutPut_t;

class Extracto {
private:
	std::string addr;							// Id Cuenta
	int n_tx_in; 								// Indica cantidad total de inputs
	lista <movimientos_t *> detalle;      		// Lista de movimientos
	int n_tx_out; 								// Indica cantidad total de outputs
	float saldo;								// Saldo real.

public:
	//---Constructores---//
	Extracto();
	Extracto( std::string valor );
	//---Destructor---//
	~Extracto();
	//---Getters---//
	std::string getaddr();
	float getsaldo();
	//---Setters---//
	bool setaddr( std::string valor );
	//---Otros---//
	void imprimirdetalle();
	lista <movimientos_t *> obtenerdetalle( lista <Block *> & AlgoChain, std::string cuenta );
	TransactionOutPut_t obtenerOutput( lista <Block *> & AlgoChain, TransactionInput_t TI );
	Block obtenerBlock( lista <Block *> & AlgoChain, std::string txns_hash );

};

#endif /* EXTRACTO_H_ */