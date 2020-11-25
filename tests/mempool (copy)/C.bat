echo off
echo Inicio de compilacion
if not exist %1.cpp goto Error1
c++ %1.cpp cmdline.cc Block.cpp BlockChainManager.cpp BlockChainBuilder.cpp BlockChainFileManager.cpp sha256.cpp Transaction.cpp TransactionInput.cpp TransactionOutput.cpp -o %1 -g -Wall -Werror -pedantic
if errorlevel 1 goto Error2
echo.
if errorlevel 0 echo Compilacion Ok
echo.
goto Final

:Error1
echo Archivo de codigo fuente inexistente
goto Final

:Error2
echo %ERRORLEVEL%

:Final
if exist *.o del *.o