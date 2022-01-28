//
// Created by Aulas FEUP on 27/01/2022.
//
#include "Menu.h"
#include <cmath>

using namespace::std;

Menu::Menu():graph(2487, true) {
    readFiles();
    for (Stop s : stops){
        addEdges(s);
    }
}

//Funções Auxiliares ===============================================================================
bool Menu::isFloat(const string &str){
    istringstream iss(str);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}
 bool Menu::isInt(const string &str){
    istringstream iss(str);
    int i;
    iss >> noskipws >> i;
    return iss.eof() && !iss.fail();
}
bool Menu::stopExists(const string &code){
    for (const Stop &s : stops){
        if(s.code == code){
            return true;
        }
    }
    return false;
}
float Menu::floatInputCheck(){
    string value;
    while (true) {
        getline(cin,value);
        checkZeroInput(value);
        if (!isFloat(value)){
            invalid_Input();
        }
        else{break;}
    }
    return stof(value);
}
int Menu::intInputCheck(){
    string value;
    while (true) {
        getline(cin,value);
        checkZeroInput(value);
        if (!isInt(value)){
            invalid_Input();
        }
        else if(stoi(value) == 0){
            menu_intro();
            break;
        }
        else{break;}
    }
    return stoi(value);
}
string Menu::checkStopInput(){
    string value;
    while (true) {
        getline(cin,value);
        checkZeroInput(value);
        if(isInt(value) && stoi(value) == 0){
            menu_intro();
            break;
        }
        else if (!stopExists(value)){
            invalid_Input();
        }
        else{break;}
    }
    return value;
}
void Menu::invalid_Input(){
    cout << "Input Invalido. Por favor, tente novamente."<<endl;
    cin.clear();
}
bool Menu::checkZeroInput(const string &input){
    if (input == "0"){
        menu_intro();
        return true;
    }
    return false;
}
StopPair Menu::createStopPair1(string origin, string destination){
    StopPair p;
    p.type = 1, p.origin = origin, p.destination = destination, p.latO = 0, p.lonO = 0,p.latD = 0, p.lonD = 0;
    return p;
}
StopPair Menu::createStopPair2(float latO, float lonO, float latD, float lonD){
    StopPair p;
    p.type = 2, p.origin = "", p.destination = "", p.latO = latO, p.lonO = lonO,p.latD = latD, p.lonD = lonD;
    return p;
}

float Menu::distance(Stop stop1, Stop stop2){
    double dLat = (stop2.lat - stop1.lat) * M_PI / 180.0;
    double dLon = (stop2.lon - stop1.lon) * M_PI / 180.0;

    // convert to radians
    stop1.lat = (stop1.lat) * M_PI / 180.0;
    stop2.lat = (stop2.lat) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(stop1.lat) * cos(stop2.lat);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

int Menu::zoneChange(Stop stop1, Stop stop2){
    if (stop1.zone != stop2.zone)
        return 1;
    return 0;
}

void Menu::addEdges(Stop stop){
    int scr, dest, it_pred, it_next, zone_c;
    float dist;

    for (auto line : lines){
        for(int it = 0; it < line.itinerary.size() ; it++){
            if(line.itinerary.at(it).code == stop.code){
                it_pred = it--;
                it_next = it++;

                scr = stopIDs[stop.name];
                dest = stopIDs[line.itinerary.at(it_next).name];
                dist = distance(line.itinerary.at(it), line.itinerary.at(it_next));
                zone_c = zoneChange(line.itinerary.at(it), line.itinerary.at(it_next));

                graph.addEdge(scr, dest, {dist, zone_c}, line.name);

                if (line.code < "300" || line.code > "303"){
                    scr = stopIDs[stop.name];
                    dest = stopIDs[line.itinerary.at(it_pred).name];
                    dist = distance(line.itinerary.at(it), line.itinerary.at(it_pred));
                    zone_c = zoneChange(line.itinerary.at(it), line.itinerary.at(it_pred));

                    graph.addEdge(scr, dest, {dist, zone_c}, line.name);
                }
            }
        }
    }
}

//Leitura de Ficheiros ================================================================================
void Menu::readFiles() {
    readStops();
    readLines();
    cout << "N Paragens no Vetor: "<< stops.size() << " N Linhas no Vetor: " << lines.size()<<endl;
    cout << "N Paragens no Map: "<< stopIDs.size() << " N Linhas no Mapa: " << lineIDs.size()<<endl;
    cout << "N Paragens no Graph: "<< graph.nodes.size();
}
void Menu::readStops() {
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open("../resources/stops.csv");
    if (fileReader.is_open()) {
        string dummy;
        getline(fileReader, dummy);
        int id = 0;
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
            if (id > 0) {
                stopIDs.insert({stop.code, id});
                stopName.insert({id, stop.name});
                graph.addNode(id, name, zone);
            }
            id++;
        }
    }
    stops.pop_back();
    fileReader.close();
}

vector<Stop> Menu::getLine(string lineName, const string &dir, const vector<Stop> &stops) {
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
            for (const Stop &stop: stops) {
                if (stop.code == stopCode) {
                    itinerary.push_back(stop);
                    break;
                }
            }
        }
    }
    return itinerary;
}

void Menu::readLines() {
    //Leitura das paragens
    ifstream fileReader;
    fileReader.open("../resources/lines.csv");
    if (fileReader.is_open()) {
        string dummy;
        getline(fileReader, dummy);
        int id = 0;
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
            if (id > 0) {
                lineIDs.insert({l.code, id});
                lineName.insert({id, l.name});
            }
            id++;
        }
    }
    lines.pop_back();
    fileReader.close();
}

//Funções do Menu =============================================================================================
bool Menu::menu_intro() {
    if(on) {
        cout << "======================== STCP Paragens ========================" << endl;
        cout << "Bem vindo ao assistente de utilizacao das rede STCP! Selecione " << endl;
        cout << "a opcao desejada de entre as abaixo:" << endl;
        stop_optionsDisplay();
    }
    else{
        return on;
    }
}
void Menu::stop_optionsDisplay() {
    cout << "Como prefere inserir a localizacao de partida?"<<endl;
    cout << "A) Atraves das suas Coordenadas"<<endl;
    cout << "B) Atraves do Nome da Paragem Escolhida"<<endl;
    cout << "Pressione Q para fechar o programa." << endl;
    stop_options();
}
void Menu::stop_options() {
    bool loop = true;
    while(loop) {
        string option;
        getline(cin,option);
        switch(option.at(0)){
            case 'A':
            case 'a':
                loop = false;
                coord_input();
                break;
            case 'B':
            case 'b':
                loop = false;
                stop_input();
                break;
            case 'Q':
            case 'q':
                loop = false;
                on = false;
                break;
            default:
                invalid_Input();
                break;
        }
    }
}
void Menu::coord_input() {
    float latO, lonO, latD, lonD;
    string destination;
    cout << "Insira a sua latitude atual:" << endl;
    cout << "(Pressione 0 para voltar ao menu)" << endl;
    latO = floatInputCheck();
    cout << "Insira a sua longitude atual:" <<endl;
    cout << "(Pressione 0 para voltar ao menu)"<<endl;
    lonO = floatInputCheck();
    cout << "Insira a latitude do seu destino:" << endl;
    cout << "(Pressione 0 para voltar ao menu)" << endl;
    latD = floatInputCheck();
    cout << "Insira a longitude do seu destino:" <<endl;
    cout << "(Pressione 0 para voltar ao menu)"<<endl;
    lonD = floatInputCheck();
    path_choice(createStopPair2(latO,lonO,latD,lonD));
}
void Menu::stop_input(){
    string origin, destination;
    cout << "Insira o codigo da paragem de partida abaixo:"<<endl;
    origin = checkStopInput();
    cout << "Insira o codigo da paragem de destino abaixo:"<<endl;
    destination = checkStopInput();
    path_choice(createStopPair1(origin,destination));

}
void Menu::path_choice(const StopPair &p){
    cout << "Escolha o criterio para obtencao do trajeto:"<<endl;
    cout << "A)O que fizer menos paragens."<<endl;
    cout << "B)O que percorre menor distancia."<<endl;
    cout << "C)O que muda menos vezes de autocarro/linha."<<endl;
    cout << "D)O que muda menos vezes de zona."<<endl;
    cout << "Pressione 0 para regressar ao menu principal"<<endl;
    path_choiceInput(p);
}
void Menu::path_choiceInput(const StopPair &p){
    string choice;
    bool loop = true;
    getline(cin, choice);
    checkZeroInput(choice);
    string input;
    while(loop) {
        switch (choice.at(0)) {
            case 'A':
            case 'a':
                loop = false;
                if (p.type == 1){
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho com menos paragens entre a paragem " << p.origin <<endl
                        <<" e a paragem "<<p.destination<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                else{
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho com menos paragens entre as coordenadas (" << p.latO << ", " << p.lonO << ")"<< endl
                        <<" e as coordenadas ( "<< p.latD << ", "<< p.lonD<< ")"<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                break;
            case 'B':
            case 'b':
                loop = false;
                if (p.type == 1){
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho que percorre menor distancia entre a paragem " << p.origin <<endl
                         <<" e a paragem "<<p.destination<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                else{
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho que percorre menor distancia entre as coordenadas (" << p.latO << ", " << p.lonO << ")"<< endl
                         <<" e as coordenadas ( "<< p.latD << ", "<< p.lonD<< ")"<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                break;
            case 'C':
            case 'c':
                loop = false;
                if (p.type == 1){
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho com menos mudancas de linha entre a paragem " << p.origin <<endl
                         <<" e a paragem "<<p.destination<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                else{
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho com menos mudancas de linha entre as coordenadas (" << p.latO << ", " << p.lonO << ")"<< endl
                         <<" e as coordenadas ( "<< p.latD << ", "<< p.lonD<< ")"<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                break;
            case 'D':
            case 'd':
                loop = false;
                if (p.type == 1){
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho com menos mudancas de zonaa entre a paragem " << p.origin <<endl
                         <<" e a paragem "<<p.destination<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                else{
                    cout << "==PLACEHOLDER==" << endl;
                    cout << "Indica caminho com menos mudancas de zona entre as coordenadas (" << p.latO << ", " << p.lonO << ")"<< endl
                         <<" e as coordenadas ( "<< p.latD << ", "<< p.lonD<< ")"<<endl;
                    cout << "Insira 0 para voltar ao menu principal"<<endl;
                    while(!checkZeroInput(input)){
                        cin.clear();
                        getline(cin,input);
                        invalid_Input();
                    }
                }
                break;
            default:
                invalid_Input();
                break;
        }
    }
}

