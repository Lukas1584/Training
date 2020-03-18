#pragma once
#include <Graph.h>
#include "GUI.h" 


namespace Graph_lib 
{
    void error_win(string s);

    struct My_window : Window 
    {
        My_window(Point xy, int w, int h, const string& title);
        bool wait_for_button(); 
    private:
        Button next_button;    
        bool button_pushed;     
        Button quit_button;
        static void cb_next(Address, Address);
        static void cb_quit(Address, Address);
        void next();
        void quit();
    };

    struct Chess :My_window
    {
        Chess(Point xy, int w, int h);
        void attach(Widget* w);
        void attach(Widget& w);
        Out_box outb;
    private:
        
        void do_some(void* pb);
        
    };

}

