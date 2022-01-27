//
// Created by up202007554 on 21/01/2022.
//

#ifndef AED2122_TRABALHO2_COMPANY_H
#define AED2122_TRABALHO2_COMPANY_H
#include "Line.h"
#include "Stop.h"
#include <list>

#endif //AED2122_TRABALHO2_COMPANY_H

using namespace std;

class Company{
public:
    vector<Stop> stops;
    vector<Line> lines;
    Company(){
        stops = {};
        lines = {};
    }
};