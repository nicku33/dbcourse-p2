#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>  //For reading inputfile
#include <stdlib.h> //exit, EXIT_FAILURE
#include <math.h>
#include <random>
#include "GenST.h"

using namespace std;


uint getRandom(uint min, uint max){
     return min + ((uint) rand() % (max - min + 1)); 
}

void testTable(uint B, uint R, uint S, uint h, string probename, string inputname){
    SplashTable sTable(B, R, S, h);
    uint lim = exp2(S-1);
    
    //Key limit
    uint keyLim = exp2(32)-1;
    
    //Arrays holding generated keys
    uint *keys = new uint[lim];
    uint *payloads = new uint[lim];
    
    ofstream probeFile, inputFile;
    probeFile.open(probename);
    inputFile.open(inputname);
    int notFirst = 0;

    for(uint i = 0; i < lim; i++){
        do{
            keys[i] = getRandom(1,keyLim-1);
        } while(sTable.probe(keys[i]));
        
        payloads[i] = getRandom(1,keyLim-1);
	        
        if(sTable.insert(keys[i], payloads[i], 0, -1)){
            inputFile << keys[i] << " " << payloads[i] << "\n";
            if(getRandom(0,1)){
                if(notFirst){
                    probeFile << "\n";
                }
                probeFile << keys[i];
                notFirst = 1;
            }
        } else {
            break;
        }
        
        
    }
    probeFile.close();
    inputFile.close();
    delete [] keys;
    delete [] payloads;
}

int main(int argc, char* argv[]){
    uint B, R, S, h;
    string probefile; 
    string inputfile;
    srand( time(0));
    //Initialize arguments
    switch (argc) {
        case 7: //No dumpfile
            B = stoi(argv[1]);
            R = stoi(argv[2]);
            S = stoi(argv[3]);
            h = stoi(argv[4]);
            probefile=argv[5];
            inputfile=argv[6];
            break;
        default:
            cout << "Missing arguments:\nB: Bucket size\nR: Recursions\n";
            cout << "S: 2^S entries\nh: Hash functions\n";
            cout << "probefileout inputfileout\n";
            exit(EXIT_FAILURE);
            break;
    }
    testTable(B, R, S, h, probefile, inputfile);
}







