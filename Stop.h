
//
// Created by Aulas FEUP on 18/01/2022.
//

#ifndef AED2122_TRABALHO2_STOP_H
#define AED2122_TRABALHO2_STOP_H
#include <string>

using namespace::std;

class Stop {
public:
    string code, name, zone;
    float lat, lon;
    Stop(string code, string name, string zone, float lat, float lon);
};


#endif //AED2122_TRABALHO2_STOP_H
