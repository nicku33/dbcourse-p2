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
    std::string dumpFileName;
    void init();
    int build(uint key, uint payload, int lim);
    
public:
    std::vector<Bucket> buckets;
    SplashTable(int S, int B, int h, int R);
    int build(uint key, uint payload);
    uint probe(uint key);
    void dump();
    void dump(std::string fileName);
    ~SplashTable();
};

#endif
