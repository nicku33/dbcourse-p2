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