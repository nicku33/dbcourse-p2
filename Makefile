default:
	g++ -o splash Main.cpp ST.cpp Bucket.cpp MHash.cpp
run:
	./splash

probe:
	gcc -msse3 -o simd simdst.c /usr/lib/x86_64-linux-gnu/libm.a

probe-mac:
	gcc -g -msse3 -o probe simd_probe.c
