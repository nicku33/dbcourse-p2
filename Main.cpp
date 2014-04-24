#include <stdio.h>
#include <iostream>
#include <fstream>  //For reading inputfile
#include <string>   //For reading inputfile
#include <sstream>  //For splitting inputfile line
#include <vector>   //For splitting inputfile line
#include <exception>//invalid_argument exception
#include <stdlib.h> //exit, EXIT_FAILURE
#include "ST.h"

using namespace std;
typedef unsigned int uint;

vector<string> &split(const string &s, char delim, vector<string> &elems);

int main(int argc, char* argv[]){
    string dumpFileName, inputFileName;
    int B, R, S, h, printDumpFile;
    
    //Initialize arguments
    switch (argc) {
        case 7: //dumpfile
            dumpFileName = argv[6];
            printDumpFile = 1;
            
            //No break: Letting case 7 continue into case 6
            
        case 6: //No dumpfile
            B = stoi(argv[1]);
            R = stoi(argv[2]);
            S = stoi(argv[3]);
            h = stoi(argv[4]);
            inputFileName = argv[5];
            break;
        default:
            cout << "Missing arguments:\nB: Bucket size\nR: Recursions\n";
            cout << "S: 2^S entries\nh: Hash functions\nInputfile\n";
            exit(EXIT_FAILURE);
            break;
    }
    uint *keys;
    uint *payloads;
    
    ifstream inputfile(inputFileName);
    if(inputfile.is_open()){
        SplashTable sTable(B, R, S, h);
        
        try {
            
            //Calculates length of input file
            uint length = 0;
            string line;
            while(getline(inputfile, line)){
                length++;
            }
            
            //Initializes arrays
            keys = new uint[length];
            payloads = new uint[length];
            
            //Clear EOF flag and goes back to beginning of file
            inputfile.clear();
            inputfile.seekg(0, ios::beg);
            
            //Loops through file
            vector<string> input;
            for(uint i = 0; i < length; i++){
                getline(inputfile, line);
                split(line, ' ', input);
                keys[i] = (uint) stoul(input[0]);
                payloads[i] = (uint) stoul(input[1]);
            }
            
            if(!sTable.build(keys, payloads, length)){
                //Failed to build table
                //Print dumpfile if argument is present
                if(printDumpFile){
                    sTable.dump(dumpFileName);
                }
                cout << "Failed to insert all keys.\n";
                delete [] keys;
                delete [] payloads;
                exit(EXIT_FAILURE);
            }
            
            if(printDumpFile){
                sTable.dump(dumpFileName);
            }
            
        } catch (invalid_argument& e) {
            //Failed to parse string to int
            delete[] keys;
            delete[] payloads;
            cout << "An error occured reading the inputfile.\n";
            exit(EXIT_FAILURE);
            
        }
        delete[] keys;
        delete[] payloads;
        
        uint probeKey;
        while (cin >> probeKey) {
            
            //Probe the key
            uint result = sTable.probe(probeKey);
            
            //Not printed if 0.
            if(result){
                //Prints the result to resultfile
                cout << probeKey << " " << result << "\n";
            }
        }
    } else {
        cout << "An error occured opening the inputfile.\n";
        exit(EXIT_FAILURE);
    }
}

/**
 * Returns a vector holding the input that is split on whitespaces.
 */
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    //Clears the vector
    elems.clear();
    stringstream ss(s);
    string item;
    //Runs through the stringstream until the delimiter is reached
    while (getline(ss, item, delim)) {
        //Inserts the found string in the back of the vector
        elems.push_back(item);
    }
    return elems;
}





