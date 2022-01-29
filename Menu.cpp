//
// Created by Aulas FEUP on 27/01/2022.
//
#include "Menu.h"
#include "StopDist.h"
#include <cmath>

using namespace::std;

Menu::Menu():graph(2487, true) {
    readFiles();
    for (Stop s : stops){
        addEdges(s);
    }
}

//Funções Auxiliares ===============================================================================
/**
 * Esta função procura a paragem mais próxima das coordenadas fornecidas
 * @param lat latitude
 * @param lon longitude
 * @return StopDist retorna uma estrutura que contem o código e a distância da paragem mais perto
 *
 * Complexidade temporal: O(n), sendo n o tamanho do vector stops
 */
StopDist Menu::coordToStop(float lat, float lon){
    string closestStop = "NULL";
    float minDist = INT_MAX;
    for (Stop s : stops){
        float lat2 = s.lat, lon2 = s.lon;
        float dist = haversine(lat,lon,lat2,lon2);
        if (dist < minDist){
            minDist = dist;
            closestStop = s.code;
        }
    }
    return StopDist({closestStop,minDist});
}

float Menu::haversine(float lat1, float lon1, float lat2, float lon2){
    float dLat = (lat2-lat1)* M_PI / 180;
    float dLon = (lon2-lon1)* M_PI / 180;
    lat1 = lat1 * M_PI /180;
    lat2 = lat2 * M_PI /180;
    float a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    float rad = 6371;
    float c = 2 * asin(sqrt(a));
    return (rad * c) * 1000;
}
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
StopPair Menu::createStopPair(string origin, string destination){
    StopPair p;
    p.origin = origin, p.destination = destination;
    return p;
}

float Menu::distance(Stop stop1, Stop stop2){
    return haversine(stop1.lat,stop1.lon,stop2.lat,stop2.lon);
}

/**
 * Esta função permite verificar se de uma paragem para outra se mudou de zona
 */
int Menu::zoneChange(Stop stop1, Stop stop2){
    if (stop1.zone != stop2.zone)
        return 100;
    return 1;
}

/**
 * Esta função adiciona as arestas ao graph, no sentido direto e no sentido inverso (exceto das linhas
 * circulares, nesse caso só adiciona ao sentido direto)
 * @param stop paragem à qual se vai adicionar as arestas ao graph
 * @return
 *
 * Complexidade temporal: O(n^2), sendo n o tamanho do vector lines
 */
void Menu::addEdges(Stop &stop){
    int scr, dest, it_pred, it_next, zone_c;
    float dist;
    scr = stopIDs[stop.code];
    for (auto line : lines){
        for(int it = 0; it < line.itinerary.size(); it++) {
            if (line.itinerary.at(it).code == stop.code) {
                it_next = it + 1;
                if (it < line.itinerary.size() - 1) {
                    dest = stopIDs[line.itinerary.at(it_next).code];
                    dist = distance(line.itinerary.at(it), line.itinerary.at(it_next));
                    zone_c = zoneChange(line.itinerary.at(it), line.itinerary.at(it_next));
                    graph.addEdge(scr, dest, {dist, zone_c}, line.name);
                }
            } else if (distance(stop, line.itinerary.at(it)) < 100){
                dest = stopIDs[line.itinerary.at(it).code];
                dist = distance(stop, line.itinerary.at(it));
                zone_c = zoneChange(line.itinerary.at(it), stop);
                graph.addEdge(scr, dest, {dist, zone_c}, "walking");
            }
        }
        if (line.code < "300" || line.code > "303"){
            for(int it = 0; it < line.itineraryReverse.size(); it++) {
                if (line.itineraryReverse.at(it).code == stop.code) {
                    it_next = it + 1;
                    //cout << line.code<< " " << it_pred << " " << it_next << " ";
                    if (it < line.itineraryReverse.size() - 1) {
                        dest = stopIDs[line.itineraryReverse.at(it_next).code];
                        //cout << dest <<" ";
                        dist = distance(line.itineraryReverse.at(it), line.itineraryReverse.at(it_next));
                        zone_c = zoneChange(line.itineraryReverse.at(it), line.itineraryReverse.at(it_next));
                        graph.addEdge(scr, dest, {dist, zone_c}, line.name);
                    }
                }
                else if (distance(stop, line.itineraryReverse.at(it)) < 100) {
                    dest = stopIDs[line.itineraryReverse.at(it).code];
                    dist = distance(stop, line.itineraryReverse.at(it));
                    zone_c = zoneChange(line.itineraryReverse.at(it), stop);
                    graph.addEdge(scr, dest, {dist, zone_c}, "walking");
                }
            }
        }
    }
}

//Leitura de Ficheiros ================================================================================
void Menu::readFiles() {
    readStops();
    readLines();
}

/**
 * Esta função lê as paragens e guarda-as num objeto da classe Stop e adiciona a paragem ao graph
 */
void Menu::readStops() {
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
                stopCode.insert({id, stop.code});
                stopName.insert({id, stop.name});
                graph.addNode(id, name, zone);
            }
            id++;
        }
    }
    stops.pop_back();
    fileReader.close();
}

/**
 * Esta função lê os ficheiros de cada linha de autocarro e guarda-os num vector que pertencem à Line
 */
vector<Stop> Menu::getLine(string lineName, const string &dir, const vector<Stop> &stops) {
    lineName.append(dir);
    lineName.append(".csv");
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

/**
 * Esta função lê o ficheiro das linhas de autocarros e guarda-os nos objetos da classe Line
 */
void Menu::readLines() {
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
            lineFile = "../resources/line_";
            lineFile.append(code);
            lineFile.append("_");

            l.itinerary = getLine(lineFile, "0", stops);
            l.itineraryReverse = getLine(lineFile, "1", stops);
            lines.push_back(l);
            if (id > 0) {
                lineIDs.insert({l.code, id});
            }
            id++;
        }
    }
    lines.pop_back();
    fileReader.close();
}

/**
 * Esta função retorna uma lista com o nome das paragens de autocarros, a partir da lista de int que
 * representam os nós do graph
 * @param ids lista com os identificadores dos nós do graph que pertencem ao caminho calculado
 * @return list<StopNameCode> retorna uma lista que contem o nome e o código de cada paragem do caminho
 *
 * Complexidade temporal: O(n), sendo n o tamanho da lista ids
 */
list<StopNameCode> Menu::convertPath(list<int> ids) {
    list<StopNameCode> path;
    for(auto i: ids){
        path.push_back({stopName[i],stopCode[i]});
    }
    return path;
}

//Funções do Menu =============================================================================================
bool Menu::menu_intro() {
    if(on) {
        cout << "======================== STCP Paragens ========================" << endl;
        cout << "Bem vindo ao assistente de utilizacao das rede STCP!" << endl;
        cout << "Selecione a opcao desejada de entre as abaixo:" << endl;
        stop_optionsDisplay();
    }

    return on;
}
void Menu::stop_optionsDisplay() {
    byCoords = false;
    cout << "Como prefere inserir a localizacao de partida?"<<endl;
    cout << "A) Atraves das suas Coordenadas"<<endl;
    cout << "B) Atraves do Codigo da Paragem Escolhida"<<endl;
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
    byCoords = true;
    float latO, lonO, latD, lonD;
    string origin, destination;
    while(true) {
        cout << "Insira a sua latitude atual:" << endl;
        cout << "(Pressione 0 para voltar ao menu)" << endl;
        latO = floatInputCheck();
        cout << "Insira a sua longitude atual:" << endl;
        cout << "(Pressione 0 para voltar ao menu)" << endl;
        lonO = floatInputCheck();
        if (coordToStop(latO, lonO).code != "NULL") {
            origin = coordToStop(latO, lonO).code;
            originDist = coordToStop(latO, lonO).dist;
            break;
        }
        else{
            cout << "Nao existe nenhuma estacao nas proximidades da localizacao de partida designada. "<<endl<<"Por favor insira outras coordenadas."<<endl;
        }
    }
    while(true) {
        cout << "Insira a latitude do seu destino:" << endl;
        cout << "(Pressione 0 para voltar ao menu)" << endl;
        latD = floatInputCheck();
        cout << "Insira a longitude do seu destino:" << endl;
        cout << "(Pressione 0 para voltar ao menu)" << endl;
        lonD = floatInputCheck();
        if (coordToStop(latD, lonD).code != "NULL") {
            destination = coordToStop(latD, lonD).code;
            destinationDist = coordToStop(latD, lonD).dist;
            break;
        }
        else{
            cout << "O destino escolhido nao possui paragens nas proximidades. "<<endl<<"Por favor insira outras coordenadas de destino."<<endl;
        }
    }
    path_choice(createStopPair(origin,destination));
}
void Menu::stop_input(){
    string origin, destination;
    cout << "Insira o codigo da paragem de partida abaixo:"<<endl;
    origin = checkStopInput();
    cout << "Insira o codigo da paragem de destino abaixo:"<<endl;
    destination = checkStopInput();
    path_choice(createStopPair(origin,destination));

}
void Menu::path_choice(const StopPair &p){
    cout << "Escolha o criterio para obtencao do trajeto:"<<endl;
    cout << "A)O que fizer menos paragens."<<endl;
    cout << "B)O que percorre menor distancia."<<endl;
    cout << "C)O que muda menos vezes de zona."<<endl;
    cout << "Pressione 0 para regressar ao menu principal"<<endl;
    path_choiceInput(p);
}
void Menu::path_choiceInput(const StopPair &p){
    string choice;
    list<StopNameCode> path;
    bool loop = true;
    getline(cin, choice);
    checkZeroInput(choice);
    string input;
    while(loop) {
        int j = 0;
        switch (choice.at(0)) {
            case 'A':
            case 'a':
                loop = false;
                j = 0;
                path = convertPath(graph.bfs_path(stopIDs[p.origin], stopIDs[p.destination]));
                if (originDist > 0 && byCoords){
                    cout << "Caminhe "<< originDist<< " metros."<<endl;
                }
                for(const auto &i :path){
                    if (j == 0){
                        cout << "PARTIDA : " << i.stop_name << " || " << i.stop_code << endl;
                    }
                    else if (j>0 && j<path.size()-1){
                        cout <<"  ||==> " << i.stop_name << " || " << i.stop_code << endl;
                    }
                    else{
                        cout <<"CHEGADA : " << i.stop_name << " || " << i.stop_code << endl;
                    }
                    j++;
                }
                if (destinationDist > 0 && byCoords){
                    cout << "Apos sair da paragem, caminhe "<< destinationDist<< " metros."<<endl;
                }
                cout << "Paragens : "<<path.size()<<endl;
                cout << "Insira 0 para voltar ao menu principal"<<endl;
                while(!checkZeroInput(input)){
                    cin.clear();
                    getline(cin,input);
                    invalid_Input();
                }
                break;
            case 'B':
            case 'b':
                loop = false;
                j = 0;
                path = convertPath(graph.dijkstra_path_dist(stopIDs[p.origin], stopIDs[p.destination]));
                if (originDist > 0 && byCoords){
                    cout << "Caminhe "<< originDist<< " metros."<<endl;
                }
                for(const auto &i :path){
                    if (j == 0){
                        cout << "PARTIDA : " << i.stop_name << " || " << i.stop_code << endl;
                    }
                    else if (j>0 && j<path.size()-1){
                        cout <<"  ||==> " << i.stop_name << " || " << i.stop_code << endl;
                    }
                    else{
                        cout <<"CHEGADA : "<< i.stop_name << " || " << i.stop_code << endl;
                    }
                    j++;
                }
                if (destinationDist > 0 && byCoords){
                    cout << "Apos sair da paragem, caminhe "<< destinationDist<< " metros."<<endl;
                }
                cout << "Paragens : "<<path.size()<< " Distancia total : " << graph.nodes.at(stopIDs[p.destination]).dist<<endl ;
                cout << endl << "Insira 0 para voltar ao menu principal" << endl;
                while (!checkZeroInput(input)) {
                    cin.clear();
                    getline(cin, input);
                    invalid_Input();
                }
                break;
            case 'C':
            case 'c':
                loop = false;
                j = 0;
                path = convertPath(graph.dijkstra_path_zone(stopIDs[p.origin], stopIDs[p.destination]));
                if (originDist > 0 && byCoords){
                    cout << "Caminhe "<< originDist<< " metros."<<endl;
                }
                for(const auto &i :path){
                    if (j == 0){
                        cout << "PARTIDA : " << i.stop_name << " || " << i.stop_code << endl;
                    }
                    else if (j>0 && j<path.size()-1){
                        cout <<"  ||==> " << i.stop_name << " || " << i.stop_code << endl;
                    }
                    else{
                        cout <<"CHEGADA : "<< i.stop_name << " || " << i.stop_code << endl;
                    }
                    j++;
                }
                if (destinationDist > 0 && byCoords){
                    cout << "Apos sair da paragem, caminhe "<< destinationDist<< " metros."<<endl;
                }
                cout << "Paragens : "<<path.size()<< " Mudanças de zona : " << graph.nodes.at(stopIDs[p.destination]).dist<<endl ;
                cout << "Insira 0 para voltar ao menu principal"<<endl;
                while(!checkZeroInput(input)){
                    cin.clear();
                    getline(cin,input);
                    invalid_Input();
                }
                break;
            default:
                invalid_Input();
                break;
        }
    }
}

