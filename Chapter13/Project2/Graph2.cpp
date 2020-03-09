#include "Graph.h"
#include "Graph2.h"
#include <cmath>


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

}
