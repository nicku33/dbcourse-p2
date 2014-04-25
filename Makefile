default:
	g++ -o splash Main.cpp ST.cpp Bucket.cpp MHash.cpp
run:
	./splash

compile:
	g++ -c -g Hash.cpp
	g++ -c -g SplashTable.cpp
	g++ -c -g SplashTester.cpp 
	g++ -o tester Hash.o SplashTable.o SplashTester.o
simdtest:
	gcc -g -msse4 -o stest simdtest.c 

simd:
	gcc -g -msse4 -o trysimd simdst.c
probe:
	gcc -msse3 -o simd simdst.c /usr/lib/x86_64-linux-gnu/libm.a

probe-mac:
	gcc -g -msse3 -o probe simd_probe.c
