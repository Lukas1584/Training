#include <Simple_window.h>
#include <Graph.h> 
#include <std_lib_facilities.h>
#include "Graph2.h"
#include <iostream>


using namespace Graph_lib;
int main()
try
{
    Point tl(100, 100);
    Simple_window win(tl, 600, 400, "First");
    Box a(Point(150, 120), 200, 150, 8);
    a.set_color(Color::blue);
    Line_style st(Line_style::solid, 4);
    a.set_style(st);
    win.attach(a);
    Box b(Point(100, 100), 300, 200, 10);
    b.set_color(Color::black);
    b.set_style(Line_style::dash);
    win.attach(b);
    Arrow ar1(Point(50, 50),Point(200,200),20, 10);
    ar1.set_color(Color::black);
    win.attach(ar1);
    Arrow ar2(Point(50,200), Point(250, 200), 20, 10);
    ar2.set_color(Color::black);
    win.attach(ar2);
    Arrow ar3(Point(300, 300), Point(150, 10), 20, 10);
    ar3.set_color(Color::black);
    win.attach(ar3);
    Arrow ar4(Point(420, 300), Point(420, 50), 30, 20);
    ar4.set_color(Color::black);
    win.attach(ar4);
    win.wait_for_button();               // Display!
}
catch (exception & e) {
    std::cout << e.what();
    return 1;
}
catch (...) {
    
    return 2;
}
