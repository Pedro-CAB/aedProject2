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

    Graph g(9, false);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,4);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(5,6);
    g.addEdge(5,7);
    g.addEdge(6,9);
    g.addEdge(7,8);

    g.bfs(1);
    cout << endl << g.nodes[4].pred;
}
