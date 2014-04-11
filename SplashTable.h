#ifndef SPLASH_TABLE_H
#define SPLASH_TABLE_H
#include "Hash.h"
class SplashTable {
private:
	int s; // this is the (initial) number of hash buckets 
	int b; // the number of buckets
	int h; // number of hash functions
	int lim; // maximum number of recursions
	int * counts;
	int ** table;
	Hash ** hashes;
	void init();
	int getBucket(int v);
	int insert(int v, int l);
public:
	SplashTable(int s, int b, int h, int lim);
	int insert(int v);
	void dump();
	int probe(int key);
};
#endif
