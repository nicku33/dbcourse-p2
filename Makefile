splashapp:
	g++ -std=c++0x -o splash Main.cpp ST.cpp Bucket.cpp MHash.cpp
genapp:
	g++ -std=c++0x -o splash GenerateFile.cpp ST.cpp Bucket.cpp MHash.cpp

clean:
	rm probe splash *.o
	rm -rf *.dSYM

# this one is for the CLIC lab
probeapp:
	gcc -msse3 -o probe simd_probe.c /usr/lib/x86_64-linux-gnu/libm.a

probeapp-mac:
	gcc -g -msse3 -o probe simd_probe.c


