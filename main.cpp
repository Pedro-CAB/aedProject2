#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Line.h"
using namespace::std;

bool isFloat( string myString ) {
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

void readFiles(){
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open("../resources/stops.csv");
    vector<Stop> stops;
    if (fileReader.is_open()){
        string dummy;
        getline(fileReader, dummy);
        while (!fileReader.eof()){
            string line;
            getline(fileReader,line);
            stringstream lineReader(line);
            string code,name,zone,lat,lon;
            getline(lineReader,code,',');
            getline(lineReader,name,',');
            getline(lineReader,zone,',');
            getline(lineReader,lat,',');
            getline(lineReader,lon);
            float latF, lonF;
            if (isFloat(lat)){
                latF = stof(lat);
            }
            if (isFloat(lon)){
                lonF = stof(lon);
            }
            Stop stop(code,name,zone,latF,lonF);
            stops.push_back(stop);
        }
    }
    stops.pop_back();
    fileReader.close();
}

int main() {
    readFiles();
}
