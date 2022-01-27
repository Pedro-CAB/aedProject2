#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Line.h"
#include "Menu.h"
#include <map>

using namespace ::std;

int main() {
    Menu m = Menu();
    if(m.menu_intro()){
        return 0;
    }
}
