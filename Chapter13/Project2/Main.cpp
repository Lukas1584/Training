#include <Simple_window.h>
#include "Graph2.h"
#include <iostream>


using namespace Graph_lib;
int main()
try
{
    Point tl(100, 100);
    Simple_window win(tl, 1000, 800, "First");
    Immobile_Circle ic(Point(100,100), 50);
    ic.set_color(Color::black);
    ic.move(20, 20);
    win.attach(ic);
    Stripped_Rectangle sr(Point(200, 50), 100, 200);
    sr.set_color(Color::black);
    sr.set_fill_color(Color::black);
    sr.set_fil_style(Line_style(Line_style::solid, 5));
    win.attach(sr);


    win.wait_for_button();               // Display!
}
catch (const exception & e) {
    std::cout << e.what();
    return 1;
}
catch (...) {
    
    return 2;
}
