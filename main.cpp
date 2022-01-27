#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Line.h"
#include "company.h"
#include "Graph.h"
#include <map>

using namespace ::std;

bool isFloat(string myString) {
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

vector<Stop> readStops() {
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open("../resources/stops.csv");
    vector<Stop> stops;
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

vector<Stop> getLine(string lineName, string dir, vector<Stop> &stops) {
    lineName.append(dir);
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open(lineName);
    vector<Stop> itinerary;
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

vector<Line> readLines(vector<Stop> &stops) {
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open("../resources/lines.csv");
    vector<Line> lines;
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
    vector<Stop> stops = readStops();
    vector<Line> lines = readLines(stops);
    //cout << stops.size() << " " << lines.size();
}
void createMaps(Company company){
    vector<Stop> stops = readStops();
    vector<Line> lines = readLines(stops);

    map<string,int> StopIds;
    map<string,int> LineIds;

    for (int i = 1; i <= stops.size(); i++){
        StopIds.insert({stops[i].code, i});
    }

    for (int i = 1; i <= lines.size(); i++){
        LineIds.insert({lines[i].code, i});
    }

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
}

void menu_intro(){
    cout << "======================== STCP Paragens ========================"<<endl;
    cout << "Bem vindo ao assistente de utilizacao das rede STCP! Selecione "<<endl;
    cout << "a opcao desejada de entre as abaixo:"<<endl;
    }

int main() {
    readFiles();

    Graph g(7, false);
    g.addEdge(1, 2, 12);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 4, 8);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 1);
    g.addEdge(3, 5, 9);
    g.addEdge(3, 6, 3);
    g.addEdge(3, 7, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(4, 6, 5);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7,1);

    cout << g.dijkstra_distance(1, 5);

}
