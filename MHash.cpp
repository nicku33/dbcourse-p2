#include "MHash.h"

//Constructor
MHash::MHash(uint multiplier, uint S, uint B){
    s = multiplier;
    p = S-log2(B);
}

//Hash function
uint MHash::hash(uint key){
    return (key * s) >> (w - p);
}

int main(){
    MHash::MHash(1231232, 12312232,12322);
    return 0;
}