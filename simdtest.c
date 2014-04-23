#include <stdio.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <nmmintrin.h>

int main(int argc, char* argv[]){

	__m128i x0=_mm_set_epi32(1,2,3,4);
	__m128i x1=_mm_set_epi32(10,20,30,40);
	__m128i to=_mm_add_epi32(x0,x1);

        uint32_t * out =(uint32_t *) &to;

	printf ("%i %i %i %i\n",
		out[0], out[1], out[2], out[3]);
	return 0;

}
