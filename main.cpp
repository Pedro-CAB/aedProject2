#include <iostream>
#include <vector>
#include "Line.h"
#include "Menu.h"
#include "Graph.h"

using namespace ::std;

int main() {
    Menu m = Menu();
    /*double lat1 = 41.14954216;
    double lon1 = -8.610023615;
    double lat2 = 41.14969203;
    double lon2 = -8.611312751;
    cout << m.haversine(lat1, lon1,
                              lat2, lon2) *1000 << " m";
    */
    if(m.menu_intro()){
        return 0;
    }
    //cout << m.distance(m.stops[3], m.stops[4]) << " m";

}
