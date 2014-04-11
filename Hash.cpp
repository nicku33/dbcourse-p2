#include "Hash.h"
Hash::Hash(int s, int seed) {
		this->s = s;
		this->seed = seed;
}
	
int Hash::get( int v){
		float f = 1/seed;
		int a = (int) v * f;
		return a % s; 
}
