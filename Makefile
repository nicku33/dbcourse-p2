default:
	g++ -o splash Main.cpp ST.cpp Bucket.cpp MHash.cpp

run:
	./splash

tsimd:
	gcc -g -msse3 -o simd simdst.c


play:
	gcc -g -msse3 -o test simdtest.c
	./test
