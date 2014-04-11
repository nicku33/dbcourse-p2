#include "MHash.h"

//Constructor
MHash::MHash(int multiplier, int S, int B){
    s = multiplier;
    p = S-log2(B);
}

//Hash function
int MHash::hash(int key){
    return (key * s) >> (w - p);
}