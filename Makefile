splashapp:
	g++ -std=c++0x -o splash Main.cpp ST.cpp Bucket.cpp MHash.cpp
genapp:
	clang++ -std=c++0x GenerateFile.cpp ST.cpp Bucket.cpp MHash.cpp

clean:
	rm probe splash *.o
	rm -rf *.dSYM

# this one is for the CLIC lab
probeapp:
	gcc -msse4.1 -o probe simd_probe.c /usr/lib/x86_64-linux-gnu/libm.a

probeapp-mac:
	gcc -msse4.1 -o probe simd_probe.c



