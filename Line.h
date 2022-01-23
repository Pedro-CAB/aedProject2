//
// Created by Aulas FEUP on 18/01/2022.
//

#ifndef AED2122_TRABALHO2_LINE_H
#define AED2122_TRABALHO2_LINE_H
#include <string>
#include <list>
#include "Stop.h"
using namespace::std;

class Line {
public:
    string code, name;
    list<Stop> itinerary;
    list<Stop> itineraryReverse;
    Line(string code, string name);
};


#endif //AED2122_TRABALHO2_LINE_H
