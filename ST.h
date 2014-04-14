#ifndef ____ST__
#define ____ST__
#include <string>
#include <vector>
#include <Math.h>
#include <random>
#include <fstream>
#include <iostream>
#include "MHash.h"
#include "Bucket.h"

typedef unsigned int uint;

class SplashTable{

private:
    uint S, B, h, R;
    int noOfBuckets;
    std::vector<MHash> hashes;
    std::vector<Bucket> buckets;
    void init();
    int build(uint key, uint payload, int lim); //Internal build method
    
public:
    SplashTable(int B, int R, int S, int h); //Constructor
    int build(uint key, uint payload); //Build method
    uint probe(uint key); //Probe method, returns payload
    void dump(std::string fileName); //Dumps table structure
    ~SplashTable(); //Deconstrutor method, frees allocated memory in buckets
};

#endif
