//
// Created by up202007554 on 21/01/2022.
//

#ifndef AED2122_TRABALHO2_COMPANY_H
#define AED2122_TRABALHO2_COMPANY_H
#include "Line.h"
#include "Stop.h"
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
    map<string,int> stopIDs;
    map<string,int> lineIDs;
    bool on = true;
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


    //Leitura de Files
    void readFiles();
    void readLines();
    void readStops();
    vector<Stop> getLine(string lineName, const string &dir, const vector<Stop> &stops);

    //Auxiliares
    static bool isFloat(const string &str);
    static bool isInt (const string &str);
    bool stopExists(const string &name);
    int intInputCheck();
    float floatInputCheck();
    string checkStopInput();
    bool checkZeroInput(const string &str);
    static StopPair createStopPair1(string origin, string destination);
    static StopPair createStopPair2(float latO, float lonO, float latD, float lonD);
};