#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


unsigned int*  __attribute__ ((aligned (16))) keys;
unsigned int*  __attribute__ ((aligned (16))) pay;

int B;  // number of entries per bucket
int S;  // 2^S = max number of entries
int h; // number of hashes;
int N; // number of filled data points
int Nm; // number of entries, for conventience
int Nb;  // number of buckets
int p;
const unsigned int w = sizeof(int) * 8; 
int hashes[2] ;

// SIMD values which we only need to init once
__m128i t; // number of tables
__m128i hm; 
