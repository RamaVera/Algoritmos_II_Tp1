
OBJECTS = main.o TransactionInput.o TransactionOutput.o Transaction.o MempoolUnit.o mempool.o # Los archivos compilados individuales
PROGR = mempool_test.exe # Nombre del archivo ejecutable
CPPFLAGS = -g -Wall -pedantic -Werror# -g opcion de g++ para debugear

# Compiladores #
CC = g++ -std=c++17 # Para linux
CCW = i686-w64-mingw32-g++ --static # Para windows (requiere mingw32)

$(PROGR) : $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(PROGR) $(OBJECTS)
main.o : main.cpp mempool.h
	$(CC) $(CPPFLAGS) -c main.cpp
mempool.o : mempool.cpp mempool.h MempoolUnit.h
	$(CC) $(CPPFLAGS) -c mempool.cpp
MempoolUnit.o : MempoolUnit.cpp MempoolUnit.h Transaction.h
	$(CC) $(CPPFLAGS) -c MempoolUnit.cpp
Transaction.o : Transaction.cpp Transaction.h lista.h TransactionOutput.h TransactionInput.h  BlockChainDataTypes.h
	$(CC) $(CPPFLAGS) -c Transaction.cpp
TransactionOutput.o : TransactionOutput.cpp TransactionOutput.h
	$(CC) $(CPPFLAGS) -c TransactionOutput.cpp
TransactionInput.o : TransactionInput.cpp TransactionInput.h
	$(CC) $(CPPFLAGS) -c TransactionInput.cpp
	



clean:
	rm -f core $(PROGR) $(OBJECTS)
all: $(PROGR)
	$(CC) $(CPPFLAGS) -o $(PROGR) $(OBJECTS)
run : $(PROGR)
	valgrind --leak-check=yes ./$(PROGR) # -i input.txt -o output.txt -d 3
