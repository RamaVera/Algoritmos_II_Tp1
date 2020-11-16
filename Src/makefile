CXXARGS  = -g -Wall -Werror -pedantic 
CXXFLAGS = -I. $(CXXARGS)
CXX = g++

all: tp0

cmdline.o: cmdline.cc cmdline.h
	$(CXX) $(CXXFLAGS) -c cmdline.cc

sha256.o: sha256.cpp sha256.h
	$(CXX) $(CXXFLAGS) -c sha256.cpp

Block.o: Block.cpp Block.h lista.h Transaction.h TiposHash.h sha256.cpp sha256.h vector.h
	$(CXX) $(CXXFLAGS) -c Block.cpp

Transaction.o: Transaction.cpp Transaction.h
	$(CXX) $(CXXFLAGS) -c Transaction.cpp

TransactionInput.o: TransactionInput.cpp TransactionInput.h
	$(CXX) $(CXXFLAGS) -c TransactionInput.cpp

TransactionOutput.o: TransactionOutput.cpp TransactionOutput.h
	$(CXX) $(CXXFLAGS) -c TransactionOutput.cpp

BlockChainManager.o: BlockChainManager.cpp BlockChainManager.h BlockChainStatus.h lista.h Block.h
	$(CXX) $(CXXFLAGS) -c BlockChainManager.cpp

BlockChainBuilder.o: BlockChainBuilder.cpp BlockChainBuilder.h TiposHash.h sha256.h lista.h Block.h BlockChainDataTypes.h
	$(CXX) $(CXXFLAGS) -c BlockChainBuilder.cpp

BlockChainFileManager.o: BlockChainFileManager.cpp BlockChainFileManager.h BlockChainDataTypes.h
	$(CXX) $(CXXFLAGS) -c BlockChainFileManager.cpp

tp0: main.cpp BlockChainManager.h BlockChainBuilder.h BlockChainFileManager.h BlockChainStatus.h TiposHash.h Transaction.h TransactionInput.h TransactionOutput.h lista.h vector.h sha256.h sha256.o Block.o Transaction.o TransactionInput.o TransactionOutput.o cmdline.o BlockChainManager.o BlockChainBuilder.o BlockChainFileManager.o
	$(CXX) $(CXXFLAGS) -o tp0 main.cpp sha256.o Block.o cmdline.o BlockChainManager.o BlockChainBuilder.o BlockChainFileManager.o Transaction.o TransactionInput.o TransactionOutput.o

clean:
	rm -f *.o tp0
