#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
/* #include <smmintrin.h> */
/* #include <nmmintrin.h> */
#include <string.h>
#include <math.h>
#include <stdio.h>

/* #include <ammintrin.h>  AMD ONLY */

unsigned int*  __attribute__ ((aligned (16))) keys;
unsigned int*  __attribute__ ((aligned (16))) pay;

int B=4;  // number of entries per bucket
int S=5;  // 2^S = max number of entries
int Nm; // number of entries, for conventience
int Nb;  // number of buckets
int p;
const unsigned int w = sizeof(int) * 8; // why ?
int hashes[2] ;

// SIMD values which we only need to init once
__m128i t; // number of tables
__m128i hm; 

void initialize_buckets(){
    p=S - log2(B);
    Nm=(1 << S); 
    Nb = Nm / B;

    // we will allocate a big block
    posix_memalign((void **)&keys, 16, sizeof(unsigned int) * Nm);
    posix_memalign((void **)&pay, 16, sizeof(unsigned int) * Nm);

    t=_mm_set_epi32(0, Nb, 0, Nb);
    hm=_mm_set_epi32(0, hashes[1], 0, hashes[0]);
}

unsigned int hash(unsigned int key, unsigned int h){
      return(key * h) >> (w - p);
}

/*
 *
 * B S h N
 * H[0] H[1] ... H[h-1] K[0] P[0]
 * K[1] P[1]
 * ...
 * K[2^S-1] P[2^S-1]
 */
void pv(__m128i to, char * s){
    uint32_t * out =(uint32_t *) &to;
    printf("%s: %u %u %u %u\n", s, out[3], out[2], out[1], out[0]);
}

/* example of load */

/*
 *
 * char a[N], b[N], c[N];
 * ...
 * __m128i *av, *bv, *cv;
 * av = (__m128i*)a;
 * bv = (__m128i*)b;
 * cv = (__m128i*)c;
 * for (i = 0; i < N/16; i++)
 * { __m128i br = _mm_loadu_si128(&bv[i];
 *   __m128i cr = _mm_loadu_si128(&cv[i];
 *     __m128i ar = _mm_add_epi8(br, cr);
 *       _mm_storeu_si128(&av[i], ar);
 *       }
 *
 */

void dump_table(char* s){
    int i,j;
    printf("\n%s\n", s);
    for(i=0; i<S; i++){
        printf("%3d:\t",i);
        for(j=0; j<B; j++){
            printf(" %3d:%3d", keys[i*B + j], pay[i*B + j]); 
        }
        printf("\n");
    }

}


unsigned int probe(unsigned int key){

    // this stuff applies to both
    __m128i k=_mm_set1_epi32(key);
    __m128i hv= _mm_mul_epu32(hm, k);
    __m128i hs= _mm_mul_epu32(hv, t);

    // now we need to extract the buckets
    // cast it as array
    uint32_t * hsa =(uint32_t *) &hs;

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

    // I couldn't find or across will do manually
    __m128i to=both;
   
    uint32_t * ex =(uint32_t *) &to;
    unsigned int out = ex[0] | ex[1] | ex[2] | ex [3];  
    return out;
}

// need to do this on initialization
//    s = multiplier;
//    p = S-log2(B);

int main(int argc, char* argv[]){
    if(!strcmp(argv[1], "test")){
        unsigned int h0=0xf918720c;
        unsigned int h1=0x8f7201cc;
        hashes[0]=h0;
        hashes[1]=h1;
        initialize_buckets();
       
        // let's insert some values, then probe
        int bucket,i;
        for(i=0;i<40;i++){
            int v1=i;
            bucket=hash(v1, h0);
            int offset=(bucket * B) + (i % 4);
            printf("i: %d, bucket %d, off: %d\n", i, bucket, offset);
            keys[(bucket * B) + (i % 4)]=v1;
            pay[(bucket * B) + (i % 4)]=v1 * 10;
        }
        dump_table("init");       
        for(i=1;i<40;i++){
            unsigned int out = probe(i);
            printf("%d:%d\t", i,out);
        }
    }
    return 0;
}
