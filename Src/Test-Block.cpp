#include<string>
#include <iostream>

#include "Block.h"
#include "BlockChainHistoryBook.h"
#include "BlockChainFileManager.h"
#include "BlockChainDataTypes.h"

#include "lista.h"

using namespace std;

int main() {

	BlockChainFileManager BCFM;
	lista <Block *> lb;
	file_t newFile;

	newFile.fileID = "blockchain.txt";
	newFile.mode = ios::in;
	newFile.type = FileTypes::loadBlockChainFile;
	newFile.isStandard = true;

	if ( ! BCFM.addFile( newFile )  ) return -1;
	cout << "File Ok !" << endl;

	if ( BCFM.loadBlockChain() ) {

		lb = BCFM.getBlockChainPointer();
		if ( ! lb.vacia() ) {
			cout << "Carga completa" << endl;
		}
		else cout << "Carga incompleta" << endl;
	}

	return 0;
	
}