#include <iostream>
#include <vector>
#include "Line.h"
#include "Menu.h"
#include "Graph.h"

using namespace ::std;

int main() {
    Menu m = Menu();
    /*double lat1 = 41.15233447;
    double lon1 = -8.499795572;
    double lat2 = 41.1522233;
    double lon2 = -8.49992706;
    cout << m.haversine(lat1, lon1,
                              lat2, lon2) << " m";
    */
    if(m.menu_intro()){
        return 0;
    }
    //cout << m.distance(m.stops[3], m.stops[4]) << " m";
}
