#include <Simple_window.h>
#include "Graph2.h"
#include <iostream>


using namespace Graph_lib;
int main()
try
{   
    Chess win(Point(100, 100), 800, 600);
    win.wait_for_button();
}
catch (const exception & e) {
    error_win(e.what());
    return 1;
}
catch (...) {
    
    return 2;
}
