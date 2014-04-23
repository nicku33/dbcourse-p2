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
    SplashTable sTable(B, R, S, h);
    
    //Reads the inputfile and parses it to sTable
    
    ifstream inputfile(inputFileName);
    try {
        if(inputfile.is_open()){
            string line;
            vector<string> input;
            while(getline(inputfile, line)){
                split(line, ' ', input);
                
                //Calls build method for each line
                if(!sTable.build(stoi(input[0]), stoi(input[1]))){ //It failed to insert
                    if(printDumpFile){
                        sTable.dump(dumpFileName);
                    }
                    exit(EXIT_FAILURE);
                }
            }
        }
        
        if(printDumpFile){
            sTable.dump(dumpFileName);
        }
        
    } catch (invalid_argument& e) {
        //Failed to parse string to int
        cout << "An error occured reading the inputfile.\n";
        exit(EXIT_FAILURE);
    }

    //Probe table with overwritten system in/out
    int probeKey;
    while (cin >> probeKey) {
        
        //Probe the key
        int result = sTable.probe(probeKey);
        
        //Not printed if 0.
        if(result){
            //Prints the result to resultfile
            cout << probeKey << " " << result << "\n";
        }
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





