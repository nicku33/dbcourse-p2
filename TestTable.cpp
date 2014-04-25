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

/**
 * Function for SplashTable test, called 'round' times.
 *
 */
int testTable(uint B, uint R, uint S, uint h, int round){
    SplashTable sTable(B, R, S, h);
    uint lim = exp2(S); //Tries to fill up the table
    
    //Key limit
    uint keyLim = exp2(32)-1;
    
    //Arrays holding generated keys
    uint *keys = new uint[lim];
    uint *payloads = new uint[lim];
    
    for(uint i = 0; i < lim; i++){
        keys[i] = getRandom(1,keyLim-1);
        payloads[i] = getRandom(1,keyLim-1);
//        cout << i << ": " << keys[i] << " " << payloads[i] << "\n";
    }
    
    //Parses the arrays and array length to the sTable
    sTable.build(keys, payloads, lim);
    
    /* If dumpfile is needed
    stringstream dumpFileName;
    dumpFileName << "dump" << round << ".txt";
    sTable.dump(dumpFileName.str());
    */
    
    //Frees memory
    delete [] keys;
    delete [] payloads;
    
    //Returns number of inserted values
    return sTable.getCount();
    
}

int main(int argc, char* argv[]){
    uint B, R, S, h, rounds;

    //Initialize arguments
    switch (argc) {
        case 6:
            B = stoi(argv[1]);
            R = stoi(argv[2]);
            S = stoi(argv[3]);
            h = stoi(argv[4]);
            rounds = stoi(argv[5]);
            break;
        default:
            cout << "Missing arguments:\nB: Bucket size\nR: Recursions\n";
            cout << "S: 2^S entries\nh: Hash functions\nrounds: Number of tests\n";
            exit(EXIT_FAILURE);
            break;
    }
    
    //Generate random input and build the table 'round' times
    int counts[rounds];
    for(int i = 0; i<rounds; i++){
        counts[i] = testTable(B, R, S, h, i);
        //Print for tracking the progress
        cout << "Round: " << i << "\t\tCount: " << counts[i] << "\n";
    }
    
    //Computing an average and LF percentage
    cout << "\n";
    int sum = 0;
    for(int i = 0; i < rounds; i++){
        sum += counts[i];
    }
    double avg = (double) sum / rounds;
    cout << "Avg:\t" << avg << "\n";
    
    double percentage = avg / exp2(S);
    cout << "In %:\t" << percentage << "\n";
}







