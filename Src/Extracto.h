/*
 * Extracto.h
 */

#ifndef EXTRACTO_H_
#define EXTRACTO_H_

#include "Block.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "BlockChainDataTypes.h"
#include "BlockChainBuilder.h"
#include "lista.h"

typedef struct {
	std::string txns_hash;						// Id del BlockChain
	std::string tx_id;							// Id del TransactionInput
	int	idx;									// Ubicación en la lista de inputs
	std::string addr;							// Id Cuenta Origen o Destino
	float value;								// monto, débito < 0, crédito > 0
} movimientos_t;

typedef struct {
	std::string txns_hash;						// Id del BlockChain Actual
	TransactionInput * TransIn;					// Transaction Input a buscar el OutPut
} TransactionInput_t;

typedef struct {
	std::string txns_hash;						// Id del BlockChain del OutPut
	std::string addr;							// Id Cuenta Origen
	int to_index;						    	// ID del Transaction OutPut en el BlockChain
	TransactionOutput * TO;						// Transaction OutPut
} TransactionOutPut_t;

typedef struct {
	std::string addr;							// Id Cuenta, formato SHA256
	std::string alias;							// Id Cuenta Alias
	size_t numerocuenta;						// Id Número Cuenta, autonumérico?
	float saldo;								// Saldo
	float pendiente;							// Pendiente en MemPool -> + o -, si es - abs(pendiente) <= saldo
	lista <movimientos_t *> detalle;			// Extracto de la cuenta
} cuentas_t;

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
	static void imprimirdetalle( const cuentas_t * cuenta );
	lista <movimientos_t *> obtenerdetalle( const lista <Block *> & AlgoChain, std::string addr );
	lista <movimientos_t *> obtenerdetalle( std::string cuenta, const lista <Block *> & AlgoChain );
	TransactionOutPut_t obtenerOutput( lista <Block *> & AlgoChain, TransactionInput_t TI );

	//  TODO
	static lista <movimientos_t *> obtenerinputs( const lista <Block *> & AlgoChain, std::string addr, std::string & errores );

	// Para usar con la línea de comandos block <id>
	Block * obtenerBlock( const lista <Block *> & AlgoChain, const std::string txns_hash, std::string & errores );
	// Para usar con la lÍnea de comandos txn <id>
	TransactionInput * obtenerTransactionInput( const lista <Block *> & AlgoChain, const std::string tx_id, std::string & errores );
};

#endif /* EXTRACTO_H_ */