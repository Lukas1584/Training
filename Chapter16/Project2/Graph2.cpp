#include "Graph2.h"
#include <cmath>
#include "Simple_Window.h"

namespace Graph_lib {
        
    void error_win(string s)
    {
        int width = 10*s.size() + 100;
        Simple_window alert(Point(300, 300), width, 150, "Error");
        Text t(Point(50, 70), s);
        t.set_color(Color::black);
        alert.attach(t);
        alert.wait_for_button();
    }

    My_window::My_window(Point xy, int w, int h, const string& title) :
        Window(xy, w, h, title),
        next_button(Point(x_max() - 150, 0), 70, 20, "Next", cb_next),
        button_pushed(false),
        quit_button(Point(x_max() - 70, 0), 70, 20, "Quit", cb_quit)
    {
        attach(next_button);
        attach(quit_button);
    }

    bool My_window::wait_for_button()      
    {
        show();
        button_pushed = false;
        while (!button_pushed) Fl::wait();
        Fl::redraw();
        return button_pushed;
    }

    void My_window::cb_next(Address, Address pw)        
    {
        reference_to<My_window>(pw).next();
    }

    void My_window::next()
    {
        button_pushed = true;
        hide();
    }
   
    void My_window::cb_quit(Address, Address pw)
    {
        reference_to<My_window>(pw).quit();
    }

    void My_window::quit()
    {
        hide();
    }

}
