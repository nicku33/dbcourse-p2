#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <nmmintrin.h>
/* #include <ammintrin.h>  AMD ONLY */

struct MHash{
    unsigned int s;
    unsigned int p;
};

// we should look at makind this a linear 2D array
unsigned int** keys;
unsigned int** payload;
struct MHash ** hashes;

int N=0;
int h=5;
int B=16;
int R=4;
int S=16;
int noOfBuckets;
const unsigned int w = sizeof(int) * 8;

void initialize_buckets(){
	noOfBuckets=(1 << S) / B;  // << equive to 2^S

	keys=malloc(sizeof(unsigned int*) * S);
	payload=malloc(sizeof(unsigned int*) * S);

	int i=0;
	for(i=0;i<S;i++){
		keys[i]=calloc(sizeof(unsigned int),  B);	
		payload[i]=calloc(sizeof(unsigned int), B);	
	}

	// initialize storage for hash parameters
	hashes=malloc(sizeof(struct MHash *) * h);
	for(i=0;i<h;i++){
		hashes[i]=malloc(sizeof(struct MHash));
	}
}

unsigned int hash(unsigned int key, struct MHash * hash){
      return (key * (*hash).s) >> (w - (*hash).p);
}

unsigned int probe(unsigned int key){

    unsigned int hashedValue;
    unsigned int value = 0;
    unsigned int count = 0;

    for(int i = 0; i<h; i++){
        hashedValue = hash(key,hashes[i]);
        for(int k = 0; k<B; k++){
            count += (keys[hashedValue][i] == key);
            value += (((count == 2) & (keys[hashedValue][i] == key)) * payload[hashedValue][k]);
        }
    }

    return value;
}

// need to do this on initialization
//    s = multiplier;
//    p = S-log2(B);

int main(int argc, char* argv[]){
	initialize_buckets();
	return 0;
}
