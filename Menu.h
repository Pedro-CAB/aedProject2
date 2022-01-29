//
// Created by up202007554 on 21/01/2022.
//

#ifndef AED2122_TRABALHO2_COMPANY_H
#define AED2122_TRABALHO2_COMPANY_H
#include "Line.h"
#include "Stop.h"

#include "Graph.h"
#include "StopPair.h"
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
    map<int, string> stopName;
    map<int, string> lineName;
    bool on = true;
    Graph graph;
    Menu();

    //Displays do Menu
    bool menu_intro();
    void stop_options();
    void stop_optionsDisplay();
    void coord_input();
    void stop_input();
    static void invalid_Input();
    void path_choice(const StopPair &p);
    void path_choiceInput(const StopPair &p);

    float distance(Stop stop1, Stop stop2);
    int zoneChange(Stop stop1, Stop stop2);
    void addEdges(Stop &stop);

    list<string> convertPath(list<int> ids);
    //Leitura de Files
    void readFiles();
    void readLines();
    void readStops();
    vector<Stop> getLine(string lineName, const string &dir, const vector<Stop> &stops);

    //Auxiliares
    string coordToStop(float lat,float lon);
    float haversine(float lat1, float lon1, float lat2, float lon2);
    static bool isFloat(const string &str);
    static bool isInt (const string &str);
    bool stopExists(const string &name);
    int intInputCheck();
    float floatInputCheck();
    string checkStopInput();
    bool checkZeroInput(const string &str);
    static StopPair createStopPair(string origin, string destination);
};