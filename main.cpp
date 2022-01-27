#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Line.h"

using namespace ::std;

bool isFloat(string myString) {
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

list<Stop> readStops() {
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open("../resources/stops.csv");
    list<Stop> stops;
    if (fileReader.is_open()) {
        string dummy;
        getline(fileReader, dummy);
        while (!fileReader.eof()) {
            string line;
            getline(fileReader, line);
            stringstream lineReader(line);
            string code, name, zone, lat, lon;
            getline(lineReader, code, ',');
            getline(lineReader, name, ',');
            getline(lineReader, zone, ',');
            getline(lineReader, lat, ',');
            getline(lineReader, lon);
            float latF, lonF;
            if (isFloat(lat)) {
                latF = stof(lat);
            }
            if (isFloat(lon)) {
                lonF = stof(lon);
            }
            Stop stop(code, name, zone, latF, lonF);
            stops.push_back(stop);
        }
    }
    stops.pop_back();
    fileReader.close();
    return stops;
}

list<Stop> getLine(string lineName, string dir, list<Stop> &stops) {
    lineName.append(dir);
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open(lineName);
    list<Stop> itinerary;
    if (fileReader.is_open()) {
        string dummy, stopCode;
        getline(fileReader, dummy);
        while (!fileReader.eof()) {
            getline(fileReader, stopCode);
            for (Stop stop: stops) {
                if (stop.code == stopCode) {
                    itinerary.push_back(stop);
                    break;
                }
            }
        }
    }
    return itinerary;
}

list<Line> readLines(list<Stop> &stops) {
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open("../resources/lines.csv");
    list<Line> lines;
    if (fileReader.is_open()) {
        string dummy;
        getline(fileReader, dummy);
        while (!fileReader.eof()) {
            string line, code, name, lineFile;
            getline(fileReader, line);
            stringstream lineReader(line);
            getline(lineReader, code, ',');
            getline(lineReader, name, ',');
            Line l(code, name);
            lineFile = "line_";
            lineFile.append(code);
            lineFile.append("_");

            l.itinerary = getLine(lineFile, "0", stops);
            l.itineraryReverse = getLine(lineFile, "1", stops);
            lines.push_back(l);
        }
    }
    lines.pop_back();
    fileReader.close();
    return lines;
}

void readFiles() {
    list<Stop> stops = readStops();
    list<Line> lines = readLines(stops);
    //cout << stops.size() << " " << lines.size();
}

void coord_input(){
    int lat, lon;
    string destination;
    cout << "Insira a sua latitude atual:" << endl;
    cout << "(Pressione 0 para voltar ao menu)"<<endl;
    cin >> lat;
    cout << "Insira a sua longitude atual:" <<endl;
    cout << "(Pressione 0 para voltar ao menu)"<<endl;
    cin >> lon;
    cout << "Insira a paragem de destino:"<<endl;
    cout << "(Pressione 0 para voltar ao menu)"<<endl;
    cin >> destination;
}

void stop_options(){
    string option;
    cout << "Como prefere inserir a localizacao de partida?"<<endl;
    cout << "A) Atraves das suas Coordenadas"<<endl;
    cout << "B) Atraves do Nome da Paragem Escolhida"<<endl;
    cout << "Pressione Q para fechar o programa." << endl;
    cin >> option;
    switc
}

void menu_intro(){
    cout << "======================== STCP Paragens ========================"<<endl;
    cout << "Bem vindo ao assistente de utilizacao das rede STCP! Selecione "<<endl;
    cout << "a opcao desejada de entre as abaixo:"<<endl;
    }

int main() {
    readFiles();
}
