#include "simd_probe.h"


void initialize_buckets(){
    // setup variables we can cache the results of
    p=S - log2(B);
    Nm=(1 << S);  // equiv to power^2
    Nb = Nm / B;

    // we will allocate a big block which we reference by row * B + col
    // using memalign we should be able to use the aligned SIMD pull instructions
    posix_memalign((void **)&keys, 16, sizeof(unsigned int) * Nm);
    posix_memalign((void **)&pay, 16, sizeof(unsigned int) * Nm);

    // t and hm are constants we use in the SIMD calculations of the hash
    t=_mm_set_epi32(0, Nb, 0, Nb);
    hm=_mm_set_epi32(0, hashes[1], 0, hashes[0]);
}

void cleanup(){
    // release memory before we exit
    free(keys);
    free(pay);
}

unsigned int probe(unsigned int key){

    __m128i k=_mm_set1_epi32(key);
    __m128i hv= _mm_mul_epu32(hm, k);
    __m128i hs= _mm_mul_epu32(hv, t);

    // now we need to extract the buckets
    // cast it as array
    unsigned int * hsa =(unsigned int *) &hs;

    unsigned int a1=hsa[1]; // the bucket number for first hash
    unsigned int a2=hsa[3]; // the bucket number for second hash
    
    a1 = a1 << 2;  // multiply by 4
    a2 = a2 << 2;

    __m128i k1 = _mm_load_si128((__m128i *) &(keys[0 + a1]));
    __m128i mask1=_mm_cmpeq_epi32(k,k1);
    __m128i p1 = _mm_load_si128((__m128i *) &(pay[0 + a1]));
    __m128i v1=_mm_and_si128(p1,mask1);
   
    __m128i k2 = _mm_load_si128((__m128i *) &(keys[0 + a2]));
    __m128i mask2=_mm_cmpeq_epi32(k,k2);
    __m128i p2 = _mm_load_si128((__m128i *) &(pay[0 + a2]));
    __m128i v2=_mm_and_si128(p2,mask2);

    __m128i both=_mm_or_si128(v1, v2);
    
    //Horizontal addition times 2 gives the payload in all slots of sum2
    __m128i sum1 =_mm_hadd_epi32(both, both);
    __m128i sum2 =_mm_hadd_epi32(sum1, sum1);
    
    //The payload is now in every slot, extract one of them
    unsigned int out = (unsigned int) _mm_extract_epi32(sum2, 0);
    return out;
}

int main(int argc, char* argv[]){

   // make sure they included the dumpfile param
   if(argc<2){
        printf("The first parameter should be the dumpfile.\n");
        exit(0);
   }

    FILE *f;
    f=fopen(argv[1], "r");
    // read the params
    fscanf(f, "%d %d %d %d", &B, &S, &h, &N);
    // we can assume that there are only 2 hash functions
    fscanf(f, "%u %u", &hashes[0], &hashes[1]);

    // nof we can loop over the data
    initialize_buckets();
    int LIMIT = 1 << S;
    int i;
    unsigned int k,v;
    for(i=0; i< LIMIT; i++){
        fscanf(f,"%u %d", &k, &v);
        keys[i]=k;
        pay[i]=v;
    }
    fclose(f);

    // now let's probe from stdin;

    unsigned int key, res;
    while(scanf("%u", &key)==1) {
        res=probe(key);
        if(res) {
            printf("%u %u\n", key, res);
        }
    }

    cleanup();
    return 0;
}
