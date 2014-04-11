default:
	gcc -o splash Main.cpp

run:
	./splash

compile:
	g++ -c -g Hash.cpp
	g++ -c -g SplashTable.cpp
	g++ -c -g SplashTester.cpp 
	g++ -o tester Hash.o SplashTable.o SplashTester.o
