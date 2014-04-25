default:
	g++ -o splash Main.cpp ST.cpp Bucket.cpp MHash.cpp

clean:
	rm probe splash *.o
	rm -rf *.dSYM

# this one is for the CLIC lab
probe:
	gcc -msse3 -o probe simdst.c /usr/lib/x86_64-linux-gnu/libm.a

probe-mac:
	gcc -g -msse3 -o probe simd_probe.c


