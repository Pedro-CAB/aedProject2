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
    string code, name;
    list<Stop> stops;
    Line(string code, string name);
};


#endif //AED2122_TRABALHO2_LINE_H
