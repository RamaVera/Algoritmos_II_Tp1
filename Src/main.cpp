//============================================================================
// Name        : main.cpp
// Author      :
// Version     : 1.1.1
// Description : Trabajo Practico Nro. 0
//============================================================================


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "cmdline.h"
#include "BlockChainManager.h"


using namespace std;

static istream* iss = 0;
static ostream* oss = 0;
static fstream ifs;
static fstream ofs;

/*=====================================================================================*/
// 									PROTOTIPOS
/*=====================================================================================*/


static void opt_input(string const &);
static void opt_output(string const &);



/*=====================================================================================*/
// 								ELEMENTOS GLOBALES
/*=====================================================================================*/

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, },
};


/*====================================================================================*/
//									MAIN
/*====================================================================================*/


int main(int argc, char * const argv[]){

	std::cout<<"AlgoChain v2.1.1 - Grupo 5 : Galvan - Vera - Dreszman"<<std::endl;

	//------Valido Argumentos ------//
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	//------Le paso los archivos al Manager ------//

	BlockChainManager::proccesBlockChain(iss,oss);

	//------Se cierran los archivos ------//
	ifs.close();
	ofs.close();

	return 0;
}



/*====================================================================================*/
// 						FUNCIONES INVOCADAS EN EL MAIN
/*====================================================================================*/

//------------------ Callbacks de CMDLINE ------------------------------//





static void opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// est?dar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
		cout<<"La direccion del archivo Origen es : Cin (Entrada Standar)" <<endl;

	}
	else {
		ifs.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
		try {
			ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
											// sequence of characters (i.e., a C-string) representing
											// the current value of the string object.
		}
		catch (std::system_error& e) {
			std::cerr << "Exception opening/reading/closing file error: " << e.code().message() << "\n";
		}
		iss = &ifs;
		cout<<"La direccion del archivo Origen es : "<< arg.c_str() << endl;

	}

	// Verificamos que el stream este OK.
	//
	if ( !iss->good() ) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		std::abort();
	}
}

static void opt_output(string const &arg)
{

	// Si el nombre del archivos es "-", usaremos la salida
	// est?dar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	//outputFileName = arg.c_str();

	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
		cout<< "La direccion del archivo Destino es: Cout (Salida Standar)" << endl;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
		cout<< "La direccion del archivo Destino es : "<< arg.c_str() <<endl;
	}

}

