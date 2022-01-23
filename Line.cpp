//
// Created by Aulas FEUP on 18/01/2022.
//

#include "Line.h"

Line::Line(string code, string name) {
    this -> code = code;
    this -> name = name;
    itinerary = {};
    itineraryReverse = {};
}
