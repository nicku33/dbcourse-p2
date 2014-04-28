#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

unsigned int getRand(unsigned int min, unsigned int max){
        unsigned int u1 = 0x0000ffffU & (unsigned int) rand();
        unsigned int u2 = 0x0000ffffU & (unsigned int) rand();
        u1 = u1 << 16 ;
        u1 = u1 | u2;
        return u1;
}


int main(int argc, char** argv) {
    srand(time(0));

    int larger;
    int smaller;
    unsigned int u;
    int i;
    for(i=0; i < 1000; i++){
        u = getRand(0, UINT_MAX);
        if (u < (0x7fffffffU)){
           smaller++;
        } else {
           larger++;
        }
    }

    printf("%d %d %d \n", larger, smaller, RAND_MAX);
    printf("percent above 2^31: %f\n", (float)larger / (float) (larger + smaller));

}
