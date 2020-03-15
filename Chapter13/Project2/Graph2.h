#pragma once
#include <Graph.h>


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
    
    struct Regular_hexagon:Shape
    {
        Regular_hexagon(const Point& xy, int rr) :r(rr)
        {
            if (r <= 3) error("Wrong radius");
            add(xy);
        }
        void draw_lines() const;
    private:
        int r;
    };

    struct Smiley :Circle
    {
        Smiley(Point p, int rr) : Circle(p, rr)
        {}
        void draw_lines() const;

    };
    
    struct Frowny :Circle
    {
        Frowny (Point p, int rr) : Circle(p, rr)
        {}
        void draw_lines() const;
    };

    struct Smiley_hat :Smiley
    {
        Smiley_hat(Point p, int rr) :Smiley(p, rr)
        {}
        void draw_lines() const;
    };
    
    struct Frowny_hat :Frowny
    {
        Frowny_hat(Point p, int rr) : Frowny (p, rr)
        {}
        void draw_lines() const;
    };

    struct Immobile_Circle :Circle
    {
        Immobile_Circle(Point p, int rr) : Circle(p, rr) {}
        void move(int dx, int dy);
        
    };

    struct Stripped_Rectangle:Rectangle
    {
        Stripped_Rectangle(Point xy, int ww, int hh) :Rectangle(xy,ww,hh), lsf(Line_style::solid, 1) {}
        void draw_lines() const;
        void set_fil_style(Line_style sty) { lsf = sty; }
    private:
        Line_style lsf;
    };

   
    

}

