default:
	g++ -o splash Main.cpp ST.cpp Bucket.cpp MHash.cpp

run:
	./splash

probe:
	gcc -g -msse3 -o probe simd_probe.c

