#include <Simple_window.h>
#include "Graph2.h"
#include <iostream>


using namespace Graph_lib;
int main()
try
{   
    My_window win(Point(100, 100), 800, 600, "Chapter 15 task 6");
    win.wait_for_button();
}
catch (const exception & e) {
    error_win(e.what());
    return 1;
}
catch (...) {
    
    return 2;
}
