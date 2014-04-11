#include "MHash.h"

//Constructor
MHash::MHash(int multiplier, int S, int B){
    s = multiplier;
    p = log2(exp2(S)/B);
}

//Hash function
int MHash::hash(int key){
    return (key * s) >> (w - p);
}