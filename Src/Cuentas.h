/*
 * Cuentas.h
 */

#ifndef CUENTAS_H_
#define CUENTAS_H_

#include<string>

#include "lista.h"

typedef struct {
	std::string addr;							// Id Cuenta, formato SHA256
	std::string alias;							// Id Cuenta Alias
	size_t numerocuenta;						// Id Número Cuenta, autonumérico?
	float saldo;								// Saldo
	float pendiente;							// Pendiente en MemPool -> + o -, si es - abs(pendiente) <= saldo
} cuentas_t;

class Cuentas {
private:
	lista <cuentas_t *> listadocuentas;	      	// Lista de cuentas_t
	size_t cantidad; 							// Total de cuentas_t

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
	size_t getnumerocuenta( const std::string addr, const std::string alias = "" );
	//---Setters---//
	bool setalias( const std::string addr, const std::string alias );
	bool setsaldo( const std::string addr, const float monto );
	bool setpendiente( const std::string addr, const float monto );
	//---Otros---//
	bool addcuenta( const std::string addr, const std::string alias = "", const float monto = 0 );
	bool addcuenta( const std::string addr, const std::string alias = "" );
	bool addcuenta( const std::string addr, const float monto );
	bool deposito( const std::string addr, const float monto );
	bool extraccion( const std::string addr, const float monto );
	bool depositopendiente( const std::string addr, const float monto );
	bool extraccionpendiente( const std::string addr, const float monto );
};

#endif /* CUENTAS_H_ */