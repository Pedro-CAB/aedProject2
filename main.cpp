#include <iostream>
#include <vector>
#include "Line.h"
#include "Menu.h"
#include "Graph.h"

using namespace ::std;

int main() {
    Menu m = Menu();
    if(m.menu_intro()){
        return 0;
    }
}
