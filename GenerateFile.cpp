#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>  //For reading inputfile
#include <stdlib.h> //exit, EXIT_FAILURE
#include <Math.h>
#include <random>
#include "ST.h"

using namespace std;
typedef unsigned int uint;

uint getRandom(uint min, uint max){
    //Initialize random device and random engine
    std::random_device rd;
    std::mt19937 engine(rd());
    
    //Initialize uniform distribution
    std::uniform_int_distribution<> uniform(min,max);
    
    //Return a number from the distribution
    return uniform(engine);
}

void testTable(uint B, uint R, uint S, uint h){
    SplashTable sTable(B, R, S, h);
    uint lim = exp2(S);
    
    //Key limit
    uint keyLim = exp2(32)-1;
    
    //Arrays holding generated keys
    uint *keys = new uint[lim];
    uint *payloads = new uint[lim];
    
    for(uint i = 0; i < lim; i++){
        
        do{
            keys[i] = getRandom(1,keyLim-1);
        } while(sTable.probe(keys[i]));
        
        payloads[i] = getRandom(1,keyLim-1);
        
        if(sTable.insert(keys[i], payloads[i], 0, -1)){
            cout << keys[i] << " " << payloads[i] << "\n";
        } else {
            break;
        }
        
        
    }
    sTable.dump("dump.txt");
    
    delete [] keys;
    delete [] payloads;
}

int main(int argc, char* argv[]){
    uint B, R, S, h;
    
    //Initialize arguments
    switch (argc) {
        case 5: //No dumpfile
            B = stoi(argv[1]);
            R = stoi(argv[2]);
            S = stoi(argv[3]);
            h = stoi(argv[4]);
            break;
        default:
            cout << "Missing arguments:\nB: Bucket size\nR: Recursions\n";
            cout << "S: 2^S entries\nh: Hash functions\n";
            exit(EXIT_FAILURE);
            break;
    }
    testTable(B, R, S, h);
}







