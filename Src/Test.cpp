#include<string>
#include <iostream>

#include "Cuentas.h"
#include "BlockChainBuilder.h"

#include "TiposHash.h"

using namespace std;

int main() {
	Cuentas Usuarios;
	if ( Usuarios.openlista( "Cuentas.txt" ) ) {
		cout << "Cuentas: " << Usuarios.getcantidad() << endl;
	}
	else return -1;

	if ( Usuarios.addcuenta( "5e2149d75798816533665d9f856f670a30da813da690b0bf3def42f7953c84e4", "Cuenta Leandro" , 10 ) ) {
		cout << "Cuentas: " << Usuarios.getcantidad() << endl;
	}
}
