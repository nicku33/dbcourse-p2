#include <stdio.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>

void pv(__m128i to, char * s){
    uint32_t * out =(uint32_t *) &to;
    printf("%s: %u %u %u %u\n", s, out[3], out[2], out[1], out[0]);
}

int main(int argc, char* argv[]){

	__m128i x0=_mm_set_epi32(1,2,3,4);
	__m128i x1=_mm_set_epi32(10,20,30,40);
	__m128i to=_mm_add_epi32(x0,x1);

        uint32_t * out =(uint32_t *) &to;

        const int LIMIT=40;
        void * p;

       // c99 version 
        posix_memalign(&p, 16, sizeof(unsigned int) * LIMIT);
       // a=aligned_alloc(16, sizeof(unsigned int) * LIMIT);
       
        int* a = (int*)p;
        int i;
        for(i=0; i< LIMIT; i++) {
            a[i]=(unsigned int) i;
        }
/*
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
        */
        for(i=0; i< LIMIT/4; i++) {
            __m128i * av=(__m128i*) a+i;
            __m128i th=_mm_load_si128(&av[0]);
            pv( th, "th");
        }
	return 0;

}
