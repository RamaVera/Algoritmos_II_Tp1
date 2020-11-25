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
#include "mempool.h"


using namespace std;

// static istream* iss = 0;

// static ostream* oss = 0;

static fstream ifs;
static fstream ofs;
static string outputFileName;

/*=====================================================================================*/
// 									PROTOTIPOS
/*=====================================================================================*/


/*static void opt_input(string const &);
static void opt_output(string const &);
static void opt_difficulty(string const &);
static void opt_help(string const &);*/


/*=====================================================================================*/
// 								ELEMENTOS GLOBALES
/*=====================================================================================*/

/*static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "d", "difficulty", NULL, opt_difficulty, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};*/


/*====================================================================================*/
//									MAIN
/*====================================================================================*/


//int main(int argc, char * const argv[]){
int main(void){


	std::cout<<"AlgoChain v1.1.1 - Grupo 5 : Galvan - Vera - Dreszman"<<std::endl;
	std::cout<<"MEMPOOL TEST"<<std::endl;



	// ----- INICIALIZO MEMPOOL ----- //
	Mempool mem_pool;
	Mempool * p_mempool;
	p_mempool = &mem_pool;


	// ---- CREO TRANSACCIONES ----- //
	Transaction transaction_1;
	Transaction * p_transaction_1;
	p_transaction_1 = &transaction_1;

	Transaction transaction_2;
	Transaction * p_transaction_2;
	p_transaction_2 = &transaction_2;

	Transaction transaction_3;
	Transaction * p_transaction_3;
	p_transaction_3 = &transaction_3;

	// ---- CARGO UNA TRANSACCION ----- //
	set_new_pool_unit( p_mempool , p_transaction_1 );




	return 0;
}



/*====================================================================================*/
// 						FUNCIONES INVOCADAS EN EL MAIN
/*====================================================================================*/

//------------------ Callbacks de CMDLINE ------------------------------//





/*static void opt_input(string const &arg)
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
	outputFileName = arg.c_str();

	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
		cout<< "La direccion del archivo Destino es: Cout (Salida Standar)" << endl;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
		cout<< "La direccion del archivo Destino es : "<< arg.c_str() <<endl;
	}

}

static void opt_difficulty(string const &arg)
{
	stringstream iss(arg);
	cout<< "La dificultad elegida es = " <<arg.c_str() <<endl;

	// Intentamos extraer el factor de la l?ea de comandos.
	// Para detectar argumentos que ?nicamente consistan de
	// n?meros enteros, vamos a verificar que EOF llegue justo
	// despu? de la lectura exitosa del escalar.
	//

	if (iss.bad()) {
		cerr << "cannot read integer factor."
			 << endl;
		std::abort();
	}
	int num;
	iss>>num;
	BlockChainManager::setUserDefinedDifficulty(num);
}

static void
opt_help(string const &arg)
{
	cout << "cmdline [-i file] [-o file] [-d dificulty ]" << endl;
	cout << "La dificultad debe ser un valor entero mayor a 0 " << endl;
	cout << "El formato de entrada debe ser el presentado en el"
			"enunciado y no debe terminar con una nueva linea" << endl;
	std::abort();
}*/
//
//
//static bool
//openOutputFile(){
//
//
//	if(outputFileName == "-")
//	{
//		oss = & cout;
//	}
//	else{
//		ofs.open(outputFileName.c_str(), ios::out);
//		oss = &ofs;
//
//	}
//	// Verificamos que el stream este OK.
//	//
//	if (!oss->good()) {
//		cerr << "cannot open "
//		<< outputFileName
//		<< "."
//		<< endl;
//
//		ifs.close();
//		return false;
//
//	}
//
//	return true;
//
//}
