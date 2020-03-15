#include "Graph2.h"
#include <cmath>
#include "Simple_Window.h"

namespace Graph_lib {

    void Box::draw_lines() const
    {
        if (color().visibility()) 
        {    
            fl_color(color().as_int());
            fl_line(point(0).x+r, point(0).y, point(0).x+w-r, point(0).y);
            fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);
            fl_line(point(0).x +w, point(0).y+r, point(0).x + w, point(0).y+h-r);
            fl_arc(point(0).x+w-r-r, point(0).y, r + r, r + r, 0, 90);
            fl_line(point(0).x +w- r, point(0).y+h, point(0).x  + r, point(0).y+h);
            fl_arc(point(0).x + w - r - r, point(0).y+h-r-r, r + r, r + r, 270, 0);
            fl_line(point(0).x , point(0).y+h-r, point(0).x , point(0).y+r);
            fl_arc(point(0).x , point(0).y + h - r - r, r + r, r + r, 180, 270);
        }
    }

    void Arrow::draw_lines() const
    {
        if (color().visibility())
        {
            fl_color(color().as_int());
            fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
            double sina = (point(1).y - point(0).y) / sqrt((point(1).x - point(0).x) * (point(1).x - point(0).x) +
                (point(1).y - point(0).y) * (point(1).y - point(0).y));
            double cosa = (point(1).x - point(0).x) / sqrt((point(1).x - point(0).x) * (point(1).x - point(0).x) +
                (point(1).y - point(0).y) * (point(1).y - point(0).y));
            
            int xd = point(1).x - w * cosa + h * sina / 2;
            int yd = point(1).y - w * sina - h * cosa / 2;
            fl_line(point(1).x, point(1).y, xd,yd);
            int xe= point(1).x - w * cosa - h * sina / 2;
            int ye= point(1).y - w * sina + h * cosa / 2;
            fl_line(point(1).x, point(1).y, xe, ye);
            fl_line(xd, yd, xe, ye);
        }
    }

    Point n(const Rectangle& r)
    {
        return Point(r.point(0).x+r.width()/2, r.point(0).y);
    }
    Point s(const Rectangle& r)
    {
        return Point(r.point(0).x + r.width() / 2, r.point(0).y+r.height());
    }
    Point w(const Rectangle& r)
    {
        return Point(r.point(0).x, r.point(0).y+r.height()/2);
    }
    Point e(const Rectangle& r)
    {
        return Point(r.point(0).x + r.width(), r.point(0).y+r.height()/2);
    }
    Point center(const Rectangle& r)
    {
        return Point(r.point(0).x + r.width() / 2, r.point(0).y+r.height()/2);
    }
    Point ne(const Rectangle& r)
    {
        return Point(r.point(0).x+ r.width(), r.point(0).y);
    }
    Point se(const Rectangle& r)
    {
        return Point(r.point(0).x + r.width(), r.point(0).y+r.height());
    }
    Point sw(const Rectangle& r)
    {
        return Point(r.point(0).x , r.point(0).y+r.height());
    }
    Point nw(const Rectangle& r)
    {
        return Point(r.point(0).x, r.point(0).y);
    }

    void Regular_hexagon::draw_lines() const
    {
        if (color().visibility())
        {
            double cosa = 0.866;
            fl_line(point(0).x - r * cosa, point(0).y - r / 2, point(0).x - r * cosa, point(0).y + r / 2);
            fl_line(point(0).x + r * cosa, point(0).y - r / 2, point(0).x + r * cosa, point(0).y + r / 2);
            fl_line(point(0).x - r * cosa, point(0).y - r / 2, point(0).x, point(0).y - r);
            fl_line(point(0).x + r * cosa, point(0).y - r / 2, point(0).x, point(0).y - r);
            fl_line(point(0).x - r * cosa, point(0).y + r / 2, point(0).x, point(0).y + r);
            fl_line(point(0).x + r * cosa, point(0).y + r / 2, point(0).x, point(0).y + r);
        }
    }

    void Smiley::draw_lines() const
    {
        if (color().visibility())
        {
            int r = radius();
            int x0 = point(0).x;
            int y0 = point(0).y;
            fl_arc(x0          , y0        , r + r , r + r  , 0   , 360);
            fl_arc(x0+0.5*r    , y0+0.8*r  , r     ,  0.8*r , 180 , 0  );
            fl_arc(x0 + 1.1 * r, y0 + 0.6*r, 0.3*r , 0.3 * r, 0   , 360);
            fl_arc(x0 + 0.6 * r, y0 + 0.6*r, 0.3*r , 0.3 * r, 0   , 360);
        }
    }

    void Frowny::draw_lines() const
    {
        if (color().visibility())
        {
            int r = radius();
            int x0 = point(0).x;
            int y0 = point(0).y;
            fl_arc(x0, y0, r + r, r + r, 0, 360);
            fl_arc(x0 + 0.5 * r, y0 + 1.1 * r,       r, 0.8 * r, 0, 180);
            fl_arc(x0 + 1.1 * r, y0 + 0.6 * r, 0.3 * r, 0.3 * r, 0, 360);
            fl_arc(x0 + 0.6 * r, y0 + 0.6 * r, 0.3 * r, 0.3 * r, 0, 360);
        }
    }

    void hat(const Point& p, int r)
    {
        fl_line(p.x - 0.2 * r, p.y - r, p.x, p.y - 1.5 * r);
        fl_line(p.x, p.y - 1.5 * r, p.x + 0.2 * r, p.y - r);
    }

    void Smiley_hat::draw_lines() const
    {
        Smiley(point(0), radius()).draw_lines();
        hat (point(0), radius());
    }
    void Frowny_hat::draw_lines() const
    {
        Frowny(point(0), radius()).draw_lines();
        hat(point(0), radius());
    }
    
    void error_win(string s)
    {
        int width = 10*s.size() + 100;
        Simple_window alert(Point(300, 300), width, 150, "Error");
        Text t(Point(50, 70), s);
        t.set_color(Color::black);
        alert.attach(t);
        alert.wait_for_button();
    }

    void Immobile_Circle::move(int dx, int dy)
    {
        error_win("Immobile_Circle can't move!");
    }
    void Stripped_Rectangle::draw_lines() const
    {
        fl_color(color().as_int());
        fl_rect(point(0).x, point(0).y, width(), height());
        fl_color(fill_color().as_int());
        fl_line_style(lsf.style(), lsf.width());
        for (int i = 2*lsf.width(); i < height()- 0.5*lsf.width(); i += 2* lsf.width())
            fl_line(point(0).x, point(0).y + i, point(0).x + width(), point(0).y + i);
    }

    

}
