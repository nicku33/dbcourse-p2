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

//Since keys and payloads are expected to non-negative 32 bit integers
typedef unsigned int uint;

class SplashTable{

private:
    uint S, B, h, R; //Init values
    int noOfBuckets, totalCount; //Internal values
    std::vector<MHash> hashes; //Vector holding hash functions
    std::vector<Bucket> buckets; //Vector holding buckets
    void init(); //Initializes internal values, hashes and buckets
    int insert(uint key, uint payload, int lim, int lastBucket); //Internal build method
    uint getRandom(uint min, uint max); //For random index
    
public:
    SplashTable(int B, int R, int S, int h); //Constructor
    int build(uint *keys, uint *payloads); //Build method
    uint probe(uint key); //Probe method, returns payload
    void dump(std::string fileName); //Dumps table structure
    uint getCount(); //For test purposes
    ~SplashTable(); //Deconstrutor method, frees allocated memory in buckets
};

#endif
