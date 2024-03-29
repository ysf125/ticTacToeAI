all :
	make build-dll
	make build-exe
	make test
	make debug

build-exe :
	g++ -L. -lticTacToe -std=c++20 -O3 .\src\main.cpp -o main

build-dll :
	g++ -c -fPIC -std=c++20 .\src\ticTacToe.cpp -o ticTacToe.o
	g++ -shared ticTacToe.o -o ticTacToe.dll
	del "ticTacToe.o"

debug :
	make build-dll
	g++ -L. -lticTacToe -std=c++20 -O0 -g3 .\debugingAndTesting\testAndDebug.cpp -o .\debugingAndTesting\debug.exe

test :
	make build-dll
	g++ -L. -lticTacToe -std=c++20 -O3 .\debugingAndTesting\testAndDebug.cpp -o .\debugingAndTesting\test.exe