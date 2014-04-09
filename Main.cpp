//
//  Main.cpp
//
//  Created by Anders Rydbirk and Nickolas Ursa
//

#include "Main.h"   //Header
#include <stdio.h>
#include <fstream>  //For reading inputfile
#include <string>   //For reading inputfile
#include <sstream>  //For splitting inputfile line
#include <vector>   //For splitting inputfile line
#include <exception>//invalid_argument exception
#include <stdlib.h> //exit, EXIT_FAILURE

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems);
    
int main(int argc, char* argv[]){
    string dumbFileName, inputFileName;
    int B, S, h, R;

    //Initialize arguments
    switch (argc) {
        case 7: //dumbfile
            dumbFileName = argv[6];
            
            //No break: Letting case 7 continue into case 6
            
        case 6: //No dumbfile
            B = stoi(argv[1]);
            S = stoi(argv[2]);
            h = stoi(argv[3]);
            R = stoi(argv[4]);
            inputFileName = argv[5];
            break;
        default:
            cout << "Missing arguments.\n";
            exit(EXIT_FAILURE);
            break;
    }
    
    //SplashTable.init with parameters
    //sTable = new SplashTable();
    //sTable.init(B, S, h, R);
    
    //Reads the inputfile and parses it to sTable
    
    ifstream inputfile(inputFileName);
    try {
        if(inputfile.is_open()){
            string line;
            vector<string> input;
            while(getline(inputfile, line)){
                split(line, ' ', input);
                
                //Calls build method for each line
                //if(!sTable.build(stoi(input[0]), stoi(input[1]))){ //It failed to insert
                //  sTable.dump();
                //  exit(EXIT_FAILURE);
                //}
                
                
                //Prints the content of the file, line by line
                cout << stoi(input[0]) << " " << stoi(input[1]) << "\n";
            }
        }
        
    } catch (invalid_argument& e) {
        //Failed to parse string to int
        cout << "An error occured reading the inputfile.\n";
        exit(EXIT_FAILURE);
    }
    
    //Test override of system in
    int probeKey;
    while (cin >> probeKey) {
        //Just shows it's working
//        cout << probe << "\n";
        
//        int result = sTable.probe(probeKey);
//        if(result){
            //Prints the result to resultfile
            cout << probeKey << "\n"; //Should be result
        //}
            
    }
}

/**
 * Returns a vector holding the input that is split on whitespaces.
 */
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    elems.clear();
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

