#include <Simple_window.h>
#include "Graph2.h"
#include <iostream>


using namespace Graph_lib;
int main()
try
{   
    /*const int xmax = 840;      // window size
    const int ymax = 440;

    const int x_orig = xmax / 2; // position of (0,0) is center of window
    const int y_orig = ymax / 2;
    const Point orig(x_orig, y_orig);

    const int r_min = -10;     // range [-10:10] 
    const int r_max = 10;

    const int x_scale = 40;    // scaling factors
    const int y_scale = 100;

    Simple_window win(Point(100, 100), xmax, ymax, "Chapter 15 task 4");

    const int xlength = xmax - 40;   // make the axis a bit smaller than the window
    const int ylength = ymax - 40;

    Axis x(Axis::x, Point(20, y_orig), xlength, xlength / x_scale, "one notch == 1 rad");
    Axis y(Axis::y, Point(x_orig, ylength + 20), ylength, 5*ylength / y_scale, "one notch == 0.2");
    win.attach(x);
    win.attach(y);
    x.set_color(Color::black);
    y.set_color(Color::black);

    Function sin_(sin, r_min, r_max, orig, 200, x_scale, y_scale);
    sin_.set_color(Color::blue);
    win.attach(sin_);

    Function cos_(cos, r_min, r_max, orig, 200, x_scale, y_scale);
    cos_.set_color(Color::red);
    win.attach(cos_);

    Function c_s{ [](double x) {return sin(x) + cos(x); }, r_min, r_max, orig, 200, x_scale, y_scale };
    c_s.set_color(Color::dark_blue);
    win.attach(c_s);

    Function cs2{ [](double x) {return sin(x)*sin(x) + cos(x)*cos(x); }, r_min, r_max, orig, 200, x_scale, y_scale };
    cs2.set_color(Color::dark_green);
    win.attach(cs2);*/

    Simple_window win(Point(100, 100), 800, 600, "Chapter 15 task 6");
    Hist h(Point(100, 100),580, 400);
    h.set_style(Line_style(Line_style::solid, 2));
    h.set_color(Color::black);
    h.set_fill_color(Color::blue);
    
    for (int i = 0; i < 10; i++)
        h.add(i);
    h.add(4);
    win.attach(h);
    win.wait_for_button();
    h.value(12);
}
catch (const exception & e) {
    error_win(e.what());
    return 1;
}
catch (...) {
    
    return 2;
}
