//Archivo fuente clase Mempool / AlgoBlock del tp1 para la materia 9512 Algoritmos y Programación II.

/*
   No estoy seguro de usar una Cola.
   Que pasa con las transacciones que no pueden ser minadas o presentan problemas
   Se mantienen en la lista? o se las desencola directamente del MeemPool.
*/

#include <cola.h>

class mempool {
	private:
		Cola <Transaction *> MemPool
	public:
		agregar( Transaction * & T );
		Transaction * T LeerCola();
		Transaction * T DesenColar();
		BorrarCola();
};