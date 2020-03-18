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
    
    //---------------------------------------------
    Chess::Chess(Point xy, int w, int h) :
        My_window(xy, w, h, "Chess"), 
        outb (Point(xy.x+120,xy.y), 100, 30,"Position:" )
    {   
        attach(outb);
        int count = 0;
        for (int i = 1; i < 5; i++)
            for (int j = 1; j < 5; j++)
            {
                stringstream s; 
                s << i << j;
                attach(*(new Button(Point(xy.x + 50 * i, xy.y + 50 * j), 50, 50, s.str() ,
                    [](void* pwid, void* pw){
                        reference_to<Chess>(pw).do_some(pwid);  
                    })));
            }
    }

    
    void Chess::do_some(void* pwid)
    {
        outb.put(reference_to<Fl_Widget>(pwid).label());
    }

    
    
    
    
    





}
