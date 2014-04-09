//
//  Main.cpp
//
//  Created by Anders Rydbirk on 09/04/14.
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
        
    //Initialize arguments
    //SplashTable.init with parameters
    //sTable = new SplashTable();
    //sTable.init();

    
    
    string line = "";
    ifstream inputfile(argv[1]);
    
    try {
        if(inputfile.is_open()){
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
    }

}

/**
 * Returns a vector holding the input split on whitespaces
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

