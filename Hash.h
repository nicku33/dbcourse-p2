#ifndef HASH_H
#define HASH_H
class Hash {
	int seed;
	int s;
public:
	Hash(int s, int seed);
	int get( int v);
};
#endif
