#include <Simple_window.h>
#include "Graph2.h"
#include <iostream>


using namespace Graph_lib;
int main()
try
{
    Point tl(100, 100);
    Simple_window win(tl, 1000, 800, "First");
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
    Graph_lib::Rectangle rr(Point(600, 50), 300, 300);
    rr.set_color(Color::green);
    win.attach(rr);
    Line l(nw(rr), se(rr));
    l.set_color(Color::green);
    win.attach(l);
    Line ll(sw(rr), ne(rr));
    ll.set_color(Color::green);
    win.attach(ll);
    Regular_hexagon rh(Point(200, 500), 50);
    rh.set_color(Color::dark_blue);
    win.attach(rh);
    Smiley sm(Point(400, 420), 100);
    sm.set_color(Color::black);
    win.attach(sm);
    Frowny fr(Point(600, 500), 80);
    fr.set_color(Color::black);
    win.attach(fr);
    Smiley_hat sh(Point(800, 400), 120);
    sh.set_color(Color::black);
    win.attach(sh);
    Frowny_hat fh(Point(850, 600), 60);
    fh.set_color(Color::black);
    win.attach(fh);
    
    win.wait_for_button();               // Display!
}
catch (const exception & e) {
    std::cout << e.what();
    return 1;
}
catch (...) {
    
    return 2;
}
