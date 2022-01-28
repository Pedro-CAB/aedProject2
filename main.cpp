#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Line.h"
#include "Menu.h"
#include "Graph.h"
#include <map>

using namespace ::std;

int main() {
    Menu m = Menu();
    if(m.menu_intro()){
        return 0;
    }

    Graph g(7, false);
    g.addEdge(1, 2, 12);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 4, 8);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 1);
    g.addEdge(3, 5, 9);
    g.addEdge(3, 6, 3);
    g.addEdge(3, 7, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(4, 6, 5);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7,1);

    cout << g.dijkstra_distance(1, 5);

}
