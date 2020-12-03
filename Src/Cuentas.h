/*
 * Cuentas.h
 */

#ifndef CUENTAS_H_
#define CUENTAS_H_

#include<string>
#include<iostream>
#include<fstream>

#include "Block.h"
#include "Transaction.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "BlockChainBuilder.h"


// #include "TiposHash.h"

// #include "sha256.h"
#include "lista.h"

typedef struct {
	std::string txns_hash;						// Id del BlockChain
	std::string tx_id;							// Id del TransactionInput
	int	idx;									// Ubicación en la lista de inputs
	std::string addr;							// Id Cuenta Origen o Destino
	float value;								// monto, débito < 0, crédito > 0
} movimientos_t;

typedef struct {
	std::string addr;							// Id Cuenta, formato SHA256
	std::string alias;							// Id Cuenta Alias
	size_t numerocuenta;						// Id Número Cuenta, autonumérico?
	float saldo;								// Saldo
	float pendiente;							// Pendiente en MemPool -> + o -, si es - abs(pendiente) <= saldo
	lista <movimientos_t *> detalle;			// Extracto de la cuenta
} cuentas_t;

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

class Cuentas {
private:
	lista <cuentas_t *> listadocuentas;	      	// Lista de cuentas_t
	size_t cantidad; 							// Total de cuentas_t
	size_t NuevoNumero();

public:
	//---Constructores---//
	Cuentas();
	//---Destructor---//
	~Cuentas();
	//---Getters---//
	float getsaldo( const std::string addr );
	float getpendiente( const std::string addr );
	std::string getalias( const std::string addr );
	size_t getnumerocuenta( const std::string addr );
	size_t getnumerocuenta( const std::string addr, const std::string alias );
	// const cuentas_t * getdetallecuenta( const std::string addr, li1sta <Block *> & AlgoChain );
	size_t getcantidad();

	//---Setters---//
	bool setalias( const std::string addr, const std::string alias );
	bool setsaldo( const std::string addr, const float monto );
	bool setpendiente( const std::string addr, const float monto );

	//---Otros---//
	size_t iscuenta( const std::string addr );
	bool addaddr( const std::string addr, const float monto );
	bool addmonto( const std::string addr, const float monto );
	bool addalias( const std::string addr, const std::string alias );
	bool addcuenta( std::string addr, const std::string alias = "", const float monto = 0 );
	bool addcuenta( std::string addr, const std::string alias = "" );
	bool addcuenta( std::string addr, const float monto );
	bool deposito( const std::string addr, const float monto );
	bool extraccion( const std::string addr, const float monto );
	bool depositopendiente( const std::string addr, const float monto );
	bool extraccionpendiente( const std::string addr, const float monto );
	void listadototal( const float saldominimo = 0 );
	void vaciarcuentas( void );
	bool updatedatos( Block *  & B );
	bool updatedatosdatos( lista <Block *> & lista );
	bool updatedatosdatos( Transaction * & T );

	// Persistencia del Objeto //
	bool openlista( const std::string file );
	bool savelista( const std::string file );

};

#endif /* CUENTAS_H_ */