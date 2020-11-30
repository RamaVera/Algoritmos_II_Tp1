/*
 * Cuentas.h
 */

#ifndef CUENTAS_H_
#define CUENTAS_H_

#include<string>
#include<iostream>
#include<fstream>

#include "Extracto.h"
#include "TiposHash.h"

#include "lista.h"

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
	const cuentas_t * getdetallecuenta( const std::string addr, lista <Block *> & AlgoChain );
	size_t getcantidad();

	//---Setters---//
	bool setalias( const std::string addr, const std::string alias );
	bool setsaldo( const std::string addr, const float monto );
	bool setpendiente( const std::string addr, const float monto );

	//---Otros---//
	size_t iscuenta( const std::string addr );
	bool addcuenta( const std::string addr, const std::string alias = "", const float monto = 0 );
	bool addcuenta( const std::string addr, const std::string alias = "" );
	bool addcuenta( const std::string addr, const float monto );
	bool deposito( const std::string addr, const float monto );
	bool extraccion( const std::string addr, const float monto );
	bool depositopendiente( const std::string addr, const float monto );
	bool extraccionpendiente( const std::string addr, const float monto );
	void listadototal( const float saldominimo = 0 );

	// Persistencia del Objeto //
	bool openlista( const std::string file );
	bool savelista( const std::string file );

};

#endif /* CUENTAS_H_ */