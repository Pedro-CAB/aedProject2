//
// Created by up202007554 on 21/01/2022.
//

#ifndef AED2122_TRABALHO2_COMPANY_H
#define AED2122_TRABALHO2_COMPANY_H
#include "Line.h"
#include "Stop.h"
#include "Graph.h"
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#endif //AED2122_TRABALHO2_COMPANY_H

using namespace std;

class Menu{
public:
    vector<Stop> stops;
    vector<Line> lines;
    map<string, int> stopIDs;
    map<string, int> lineIDs;
    bool on = true;
    Graph graph;
    Menu();

    //Adicionar Valores aos Maps
    void addStop();
    void addLine();

    //Displays do Menu
    bool menu_intro();
    void stop_options();
    void stop_optionsDisplay();
    void coord_input();
    void stop_input();
    void invalid_Input();
    void path_choice();
    void path_choiceInput();

    float distance(Stop stop1, Stop stop2);
    int zoneChange(Stop stop1, Stop stop2);
    void addEdges(Stop stop);

    //Leitura de Files
    void readFiles();
    void readLines();
    void readStops();
    void createMaps();
    vector<Stop> getLine(string lineName, string dir, vector<Stop> &stops);

    //Auxiliares
    bool isFloat(string str);
    bool isInt (string str);
    bool stopExists(string name);
    int intInputCheck();
    float floatInputCheck();
    string checkStopInput();
    void checkZeroInput(string str);
};