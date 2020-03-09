#include "Graph.h"
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include "Point.h"
#include "std_lib_facilities.h"

namespace Graph_lib {


    struct Box : Shape 
    {
        Box (const Point& xy, int ww, int hh, int rr) : w(ww), h(hh), r(rr)
        {
            add(xy);
            if (h <= 0 || w <= 0) error("Bad box: non-positive side");
            if ((r > (h / 2)) || (r > (w / 2))) error("Bad box: non-positive radius");
        }
        Box (const Point& x, Point& y, int rr) : w(y.x - x.x), h(y.y - x.y), r(rr)
        {
            add(x);
            if (h <= 0 || w <= 0) error("Bad rectangle: non-positive width or height");
            if ((r > (h / 2)) || (r > (w / 2))) error("Bad box: non-positive radius");
        }
        void draw_lines() const;
        int height() const { return h; }
        int width() const { return w; }
    private:
        int h;    // height
        int w;    // width
        int r;    // radius
    };

    struct Arrow : Shape 
    {            
        Arrow(const Point& p1, const Point& p2, int ww, int hh) :  w(ww), h(hh)
        {
            if (w <= 0 || h <= 0) error("Bad arrow: non-positive parameters");
            if (w > sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y))) error("Too long arrow");
            add(p1);    
            add(p2); 
        }
        void draw_lines() const;
    private:
        int w;
        int h;
    };
    Point n(const Rectangle& r);
    Point s(const Rectangle& r);
    Point w(const Rectangle& r);
    Point e(const Rectangle& r);
    Point center(const Rectangle& r);
    Point ne(const Rectangle& r);
    Point se(const Rectangle& r);
    Point sw(const Rectangle& r);
    Point nw(const Rectangle& r);
    
    


}

