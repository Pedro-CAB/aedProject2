//
// Created by Aulas FEUP on 27/01/2022.
//
#include "Menu.h"

using namespace::std;

Menu::Menu() {
    readFiles();
}


//Funções Auxiliares ===============================================================================
bool Menu::isFloat(string str) {
    istringstream iss(str);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}
bool Menu::isInt(string str){
    istringstream iss(str);
    int i;
    iss >> noskipws >> i;
    return iss.eof() && !iss.fail();
}
bool Menu::stopExists(string code){
    for (Stop s : stops){
        if(s.code == code){
            return true;
        }
        cout << s.code<< " ";
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
    cin.ignore();
}
void Menu::checkZeroInput(string input){
    if (input == "0"){
        menu_intro();
    }
}


//Leitura de Ficheiros ================================================================================
void Menu::readFiles() {
    readStops();
    readLines();
    cout << "N Paragens no Vetor: "<< stops.size() << " N Linhas no Vetor: " << lines.size()<<endl;
    cout << "N Paragens no Map: "<< stopIDs.size() << " N Linhas no Mapa: " << lineIDs.size()<<endl;
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
            }
            id++;
        }
    }
    stops.pop_back();
    fileReader.close();
}

vector<Stop> Menu::getLine(string lineName, string dir, vector<Stop> &stops) {
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
    while(true) {
        string option;
        cin >> option;
        switch(option.at(0)){
            case 'A':
            case 'a':
                coord_input();
                break;
            case 'B':
            case 'b':
                stop_input();
                break;
            case 'Q':
            case 'q':
                on = false;
                break;
            default:
                invalid_Input();
                stop_options();
                break;
        }
        break;
    }
}
void Menu::coord_input() {
    int lat, lon;
    string destination;
    cout << "Insira a sua latitude atual:" << endl;
    cout << "(Pressione 0 para voltar ao menu)" << endl;
    lat = floatInputCheck();
    cout << "Insira a sua longitude atual:" <<endl;
    cout << "(Pressione 0 para voltar ao menu)"<<endl;
    lon = floatInputCheck();
    cout << "Insira o codigo da paragem de destino:"<<endl;
    cout << "(Pressione 0 para voltar ao menu)"<<endl;
    destination = checkStopInput();
    cout << "==PLACEHOLDER=="<<endl;
    cout << "Latitude = " << lat << " Longitude = "<< lon<< endl << "Destino: "<< destination;
}
void Menu::stop_input(){
    string origin, destination;
    cout << "Insira o codigo da paragem de partida abaixo:"<<endl;
    origin = checkStopInput();
    cout << "Insira o codigo da paragem de destino abaixo:"<<endl;
    destination = checkStopInput();
    cout << "==PLACEHOLDER=="<<endl;
    cout << "Partida: "<< origin << endl << "Destino: "<< destination;
}
void Menu::path_choice(){
    cout << "Escolha o criterio para obtencao do trajeto:"<<endl;
    cout << "A)O que fizer menos paragens."<<endl;
    cout << "B)O que percorre menor distancia."<<endl;
    cout << "C)O que muda menos vezes de autocarro/linha."<<endl;
    cout << "D)O que muda menos vezes de zona."<<endl;
    cout << "Pressione 0 para regressar ao menu principal"<<endl;
}
void Menu::path_choiceInput(){
    string choice;
    getline(cin, choice);
    checkZeroInput(choice);
    while(true) {
        switch (choice.at(0)) {
            case 'A':
            case 'a':
                cout << "==PLACEHOLDER" << endl;
                cout << "Indica caminho com menos paragens" << endl;
                break;
            case 'B':
            case 'b':
                cout << "==PLACEHOLDER" << endl;
                cout << "Indica caminho que percorre menor distância" << endl;
                break;
            case 'C':
            case 'c':
                cout << "==PLACEHOLDER" << endl;
                cout << "Indica caminho com menos mudanças de linha" << endl;
                break;
            case 'D':
            case 'd':
                cout << "==PLACEHOLDER" << endl;
                cout << "Indica caminho com menos mudanças de zona" << endl;
                break;
            default:
                invalid_Input();
                break;
        }
    }
}

