/*
 * BlockChainHistoryBook.cpp
 *
 *  Created on: 30 nov. 2020
 *      Author: ramiro
 */

#include "BlockChainHistoryBook.h"

lista<Block*> BlockChainHistoryBook::AlgoChain;
Cuentas BlockChainHistoryBook::ListadoCuentas;

// Para usar x línea de comandos block <id>
Block * BlockChainHistoryBook::searchBlock( const std::string HashBlock ) {
	Block * B = nullptr;
	std::string b_prev = "";

	// EL HASH YA ES VALIDADO EN FILEMANAGER, 
	// Checks
	//if ( HashBlock.empty()  ) {
	//	return B;
	//}
	//else if ( ! Block::CheckHash( HashBlock, TiposHash::clavehash256 ) ) {
	//	return B;
	//}
	// End Checks

	for ( size_t i = 0; i < (size_t) LargoHash::LargoHashEstandar; i++) { b_prev += '0'; }  // Block Zero
	if ( ! AlgoChain.vacia() ) {
		lista <Block *>::iterador it( AlgoChain );
		it = AlgoChain.ultimo();
		if ( ! ( it.dato()->getpre_block() == b_prev ) ) {
			// Mal definido el Block Zero y esta el error en AlgoChains,txt de prueba
			return B;
		}
		do {
			if ( ! ( it.dato()->gettxns_hash() == HashBlock ) ) {
				B = it.dato();
				break;
			}
			b_prev = it.dato()->gettxns_hash();
			it.retroceder();
			// Check de continuidad de la cadena
			if ( ! ( it.dato()->getpre_block() == b_prev ) ) {
				break;
			}
		} while ( ! it.extremo() );
	}
	return B;
}

const lista<Transaction *> * BlockChainHistoryBook::searchTransaction(const std::string txns_hash ){
	const lista<Transaction *> * T = nullptr;
	std::string b_prev;

	// EL HASH YA ES VALIDADO EN FILEMANAGER
	// Checks
	//if ( txns_hash.empty()  ) {
	//	return B;
	//}
	//else if ( ! Block::CheckHash( txns_hash, TiposHash::clavehash256 ) ) {
	//	return B;
	//}
	// End Checks

	if ( ! AlgoChain.vacia() ) {
		lista <Block *>::iterador it( AlgoChain );
		it = AlgoChain.primero();

		do {
			if ( ! ( it.dato()->gettxns_hash() == txns_hash ) ) {
			T = &(it.dato()->getListaTran());
			break;
			}
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return T;
}

// Para usar x línea de comandos txn <id>
TransactionInput * BlockChainHistoryBook::obtenerTransactionInput( const std::string tx_id ) {
	std::string b_prev = "";
	TransactionInput * TI = nullptr;

	// Checks
	if ( tx_id.empty()  ) {
		return TI;
	}
	// End Checks

	for ( size_t i = 0; i < (size_t) LargoHash::LargoHashEstandar; i++) { b_prev += '0'; }  // Block Zero
	if ( ! AlgoChain.vacia() ) {
		lista <Block *>::iterador itBlock( AlgoChain );
		itBlock = AlgoChain.ultimo();
		do {
			if ( ! ( itBlock.dato()->getpre_block() == b_prev ) ) {
				return TI;
			}
			b_prev = itBlock.dato()->gettxns_hash();
			// Debo abrir un segundo bloque de iteraciones sobre la lista de TI
			lista <Transaction *> trns;
			trns = itBlock.dato()->getListaTran();
			lista <Transaction *>::iterador itTrans( trns );
			// La lista a iterar es la de TransactionInput, no importa orden
			itTrans = trns.primero();
			if ( ! trns.vacia() ) {
				do {
					// De las dos listas, itero las de TI
					lista <TransactionInput *> tInput;
					tInput = itTrans.dato()->getTransactionInputList();
					lista <TransactionInput *>::iterador itTransInput( tInput );
					itTransInput = tInput.primero();
					if ( ! tInput.vacia() ) {
						do {
							/*
							if ( itTransInput.dato()->getTxId() == tx_id ) {
								TI->setTxId( itTransInput.dato()->getTxId() );
								TI->setIdx( itTransInput.dato()->getIdx() );
								TI->setAddr( itTransInput.dato()->getAddr() );
								return TI;
							}
							*/
							if ( tx_id.compare(itTransInput.dato()->getTxId()) )  {
								return itTransInput.dato();
							}
							itTransInput.avanzar();
						}  while ( ! itTransInput.extremo() );
					}
					itTrans.avanzar();
				} while ( ! itTrans.extremo() );
			}
			itBlock.retroceder();
		} while ( ! itBlock.extremo() );
	}
	return TI;
}

Transaction * BlockChainHistoryBook::getTransactionByTransactionOutputUser( const std::string user ) {
	//std::string b_prev;
	//TransactionOutput * TI = NULL;
	Transaction * Trans = nullptr;

	// Checks
//	if ( tx_id.empty()  ) {
//		return TI;
//	}
//	else if ( ! Block::CheckHash( tx_id, TiposHash::clavehash256 ) ) {
//		return TI;
//	}
	// End Checks

	//for ( size_t i = 0; i < (size_t) LargoHash::LargoHashEstandar; i++) { b_prev += '0'; }  // Block Zero
	if ( ! AlgoChain.vacia() ) {
		lista <Block *>::iterador itBlock( AlgoChain );
		itBlock = AlgoChain.primero();
		do {

			// Si el primer elemento no es el bloque origen hubo corrupcion de Algochain
			// Esl problema es que la implementacion de listas dejan el primer elemento
			// al final por eso genera error al usar AlgoChain.primero()
			//if ( ! ( it.dato()->getpre_block() == b_prev ) ) { return TI; }

			//b_prev = it.dato()->getpre_block();
			// Debo abrir un segundo bloque de iteraciones sobre la lista de TI
			lista <Transaction *> trns;
			trns = itBlock.dato()->getListaTran();
			lista <Transaction *>::iterador itTrans( trns );
			// La lista a iterar es la de TransactionInput
			itTrans = trns.primero();
			if ( ! trns.vacia() ) {
				do {
					// De las dos listas, itero las de TI
					lista <TransactionOutput *> tOutput;
					tOutput = itTrans.dato()->getTransactionOutputList();
					lista <TransactionOutput *>::iterador itTransOutput( tOutput );
					itTransOutput = tOutput.primero();
					if ( ! tOutput.vacia() ) {
						do {
							// Si encuentro al usuario en el output
							// devuelvo el bloque para analizarlo
							// afuera
							if ( user.compare(itTransOutput.dato()->getAddr()) == 0)  {
								return itTrans.dato();
							}
							itTransOutput.avanzar();
						}  while ( ! itTransOutput.extremo() );
					}
					itTrans.avanzar();
				} while ( ! itTrans.extremo() );
			}
			itBlock.avanzar();
		} while ( ! itBlock.extremo() );
	}
	return Trans;
}

void BlockChainHistoryBook::BorrarHistoria( void ) {
	// AlgoChain se autodestruye, antes debo liberar la memoria asignada en cada elemento * AlgoChain de la lista
	// El compilador ejecuta primero los destructores de las clases hijas que liberan su memoria dinámica.
	if ( ! AlgoChain.vacia() ) {
		lista  <Block *>::iterador it( AlgoChain );
		it = AlgoChain.primero();
		while ( ! AlgoChain.isEmpty()) {
			delete it.dato();
			AlgoChain.eliminar_nodo(it);
		}
		BlockChainHistoryBook::ListadoCuentas.vaciarcuentas();
	}
}

bool BlockChainHistoryBook::AddBlock( Block * & B ) {
	Block * newBlock = new Block( *B );
	AlgoChain.insertar( newBlock );
	// Aca debo en Cuentas actualizar datos
	BlockChainHistoryBook::ListadoCuentas.updatedatos( B );

	return true;
}

bool BlockChainHistoryBook::AddListaBlocks( lista <Block *> & lista ) {

	if ( AlgoChain.vacia() ) {
		AlgoChain = lista;
	}
	else if ( !lista.vacia() ) {
			// TODO
	}
	// BlockChainHistoryBook::ListadoCuentas.updatedatos( lista );
	return true;
}

lista <TransactionOutput *> BlockChainHistoryBook::obtenerOutputs( const std::string tx_id, const int idx ) {
	std::string b_prev = "";
	lista <TransactionOutput *> ListaTranOut;

	if ( idx < 0 ) {
		return ListaTranOut;
	}
	// End Checks

	if ( !AlgoChain.vacia() ) {
		for ( size_t i = 0; i < (size_t) LargoHash::LargoHashEstandar; i++) { b_prev += '0'; }  // Block Zero
		lista <Block *>::iterador it( AlgoChain );
		it = AlgoChain.primero();
		do {
			lista <Transaction *> itTrans = it.dato()->getListaTran();
			lista <Transaction *>::iterador itLT( itTrans );
			itLT = itTrans.primero();
			if ( it.dato()->getpre_block() == b_prev ) {
				// Shathosi Block
				return itLT.dato()->getTransactionOutputList();
			}
			do {
				lista <TransactionInput *> LTI = itLT.dato()->getTransactionInputList();
				lista <TransactionInput *>::iterador itLTI( LTI );
				do {
					if ( itLTI.dato()->getTxId() == tx_id && itLTI.dato()->getIdx() == idx ) {
						return itLT.dato()->getTransactionOutputList();
					}
					itLTI.avanzar();
				} while ( ! itLTI.extremo() );
				itLT.avanzar();
			} while ( ! itLT.extremo() );
			it.avanzar();
		} while ( ! it.extremo() );
	}
	return ListaTranOut;
}

lista <movimientos_t *> BlockChainHistoryBook::obtenerdetalle( std::string addr ) {
	lista <movimientos_t *> detalle;
	float saldoactual = 0;

	// Checks
	if ( addr.empty() ) {
		return detalle;
	}
	// End Checks

	std::string cuentaorigen = "";
	if ( ! BlockChainHistoryBook::AlgoChain.vacia() ) {

		// Primero reviso si addr esta el Listado de Cuentas
		if ( ! ListadoCuentas.addaddr( addr, 0 ) ) return detalle;

		lista <Block *>::iterador it( AlgoChain );
		it = BlockChainHistoryBook::AlgoChain.ultimo();
		do {
			// Se itera dentro de las transacciones
			lista <Transaction *> trns;
			trns = it.dato()->getListaTran();
			if ( ! trns.vacia() ) {
				lista <Transaction *>::iterador itTrans( trns );
				itTrans = trns.primero();
				do {
					Transaction * Trans = itTrans.dato();
					lista <TransactionInput *> intputs = Trans->getTransactionInputList();
					lista <TransactionInput *>::iterador itIn( intputs );
					if ( ! intputs.vacia() ) {
						// Si hay entradas a addr se cargan en lista->detalle como crédito
						if ( itIn.dato()->getAddr() != addr ) {
							// Cargar en lista detalle, se asume una única cuenta en toda la lista de TI
							cuentaorigen = addr;
						}
					}
					// Se itera dentro de Outs
					lista <TransactionOutput *> outputs = Trans->getTransactionOutputList();
					lista <TransactionOutput *>::iterador itOut( outputs );
					if ( ! outputs.vacia() ) {
						// Si hay salidas desde addr se cargan en lista->detalle como débito
						itOut = outputs.primero();
						do {
							if ( ! cuentaorigen.empty() ) {
								if ( itOut.dato()->getAddr() ==  addr ) {
									// Se carga en detalle el crédito
									movimientos_t * entrada = new movimientos_t;
									// Cargar datos
									entrada->txns_hash = it.dato()->gettxns_hash();
									entrada->addr = cuentaorigen;
									entrada->value = itOut.dato()->getValue();
									detalle.insertar( entrada );
									saldoactual += entrada->value;
								}
							}
							else if ( cuentaorigen ==  addr ) {
								// Son todas salidas de débitos en la addr
								if ( itOut.dato()->getAddr() !=  addr ) {
									movimientos_t * salida = new movimientos_t;
									// Cargar datos
									salida->txns_hash = it.dato()->gettxns_hash();
									salida->addr = itOut.dato()->getAddr();
									salida->value = - itOut.dato()->getValue();
									detalle.insertar( salida );
									saldoactual -= salida->value;
								}
								else {
									// Debo anotar salida en - y entrada en +, es un movimiento de orden
									movimientos_t * salida = new movimientos_t;
									// Cargar datos
									salida->txns_hash = it.dato()->gettxns_hash();
									salida->addr = addr;
									salida->value = - itOut.dato()->getValue();
									detalle.insertar( salida );
									// this->saldo -= salida->value;   // No afecta el saldo.
								}
							}
							itOut.avanzar();
						} while ( ! itOut.extremo() );
					}
					itTrans.avanzar();
				} while ( ! itTrans.extremo() );
			}
			it.retroceder();
		} while ( ! it.extremo() );

		if ( ListadoCuentas.setsaldo( addr, saldoactual ) ) {
			if ( ! ListadoCuentas.setdetalle( addr, detalle ) ) {
				return detalle;
			}
		}

	}

	// TODO Revisar MemPool
	// pendienteactual = 0;

	return detalle;
}

bool BlockChainHistoryBook::updatedatosdatos() {

	if ( BlockChainHistoryBook::AlgoChain.vacia() ) return false;

	ListadoCuentas.vaciarcuentas();	// se resetean todos los saldos.
	// TODO Resetear la MemPool

	lista <Block *>::iterador it( AlgoChain );
	it = AlgoChain.ultimo();
	do {
		// Se itera dentro de las transacciones
		lista <Transaction *> trns;
		trns = it.dato()->getListaTran();
		if ( ! trns.vacia() ) {
			lista <Transaction *>::iterador itTrans( trns );
			itTrans = trns.primero();
			do {
				Transaction * Trans = itTrans.dato();
				lista <TransactionInput *> intputs = Trans->getTransactionInputList();
				lista <TransactionInput *>::iterador itIn( intputs );
				if ( ! intputs.vacia() ) {
					// Si hay entradas a addr se cargan en lista->detalle como crédito
					ListadoCuentas.addcuenta( itIn.dato()->getAddr(), 0 );
				}
				// Se itera dentro de Outs
				lista <TransactionOutput *> outputs = Trans->getTransactionOutputList();
				lista <TransactionOutput *>::iterador itOut( outputs );
				if ( ! outputs.vacia() ) {
					do {
						if ( ! itIn.dato()->getAddr().empty() ) {
							// Se carga el detalle del crédito
							movimientos_t * entrada = new movimientos_t;
							entrada->txns_hash = it.dato()->gettxns_hash();
							entrada->addr = itIn.dato()->getAddr();
							entrada->value = itOut.dato()->getValue();
							ListadoCuentas.addaddr( itOut.dato()->getAddr(), itOut.dato()->getValue() );
							ListadoCuentas.addmovimiento( itOut.dato()->getAddr(), entrada );
							// Debito en cuenta Origen
							movimientos_t * salida = new movimientos_t;
							salida->txns_hash = it.dato()->gettxns_hash();
							salida->addr = itIn.dato()->getAddr();
							salida->value = - itOut.dato()->getValue();
							ListadoCuentas.addaddr( itIn.dato()->getAddr(), -itOut.dato()->getValue() );
							ListadoCuentas.addmovimiento( itIn.dato()->getAddr(), salida );
						}
						else {
							// El primer movimiento, implica sólo un crédito, sin débito.
							std::string b_prev = "";
							for ( size_t i = 0; i < (size_t) LargoHash::LargoHashEstandar; i++) { b_prev += '0'; }  // Block Zero
							// Debería ser el primer Block
							if ( it.dato()->gettxns_hash() == b_prev ) {
								movimientos_t * entrada = new movimientos_t;
								entrada->txns_hash = it.dato()->gettxns_hash();	
								entrada->addr = itOut.dato()->getAddr();
								entrada->value = itOut.dato()->getValue();
								ListadoCuentas.addaddr( itOut.dato()->getAddr(), itOut.dato()->getValue() );
								ListadoCuentas.addmovimiento( itOut.dato()->getAddr(), entrada );
							}
							else {
								// Pifff
								return false;
							}
						}
						itOut.avanzar();
					} while ( ! itOut.extremo() );
				}
				itTrans.avanzar();
			} while ( ! itTrans.extremo() );
		}
		it.retroceder();
	} while ( ! it.extremo() );

	return true;
}

void BlockChainHistoryBook::imprimirdetalle( const std::string addr ) {
	cuentas_t * E = nullptr;
	size_t movimientos = 0;
	float saldo = 0;

	// Cheacks
	if ( addr.empty() ) { return; }
	if ( BlockChainHistoryBook::ListadoCuentas.getcantidad() == 0 ) { return; }

	// Imprimir cabecera siempre.
	// Movimientos
	E  = BlockChainHistoryBook::ListadoCuentas.getcuenta( addr );
	cout << "--------------------------------------------------";
	cout << "Hash Cuenta : " << addr << '\n';
	if ( ! E->alias.empty() ) {
		cout << "Alias Cuenta: " << E->alias << '\n';
	}
	cout << "-------------------------------------------------------------------------------";
	cout << "[Cuenta Origen]" << '\n';
	cout << "[AlgoChain Id]" << '\n';
	cout << "    Crédito             Débito             Saldo" << '\n';
	if ( ! E->detalle.vacia() ) {
		lista <movimientos_t *>::iterador it( E->detalle );
		it = E->detalle.primero();
		do {
			saldo += it.dato()->value;
			movimientos++;
			it.avanzar();
		} while ( ! it.extremo() );
	}
	cout << "-------------------------------------------------------------------------------";
}