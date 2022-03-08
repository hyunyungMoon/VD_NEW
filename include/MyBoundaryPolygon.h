#pragma once

#include <list>

#include "rg_Point2D.h"
#include "rg_Line2D.h"
#include "MyEdge.h"
#include "MyVertex.h"

class MyBoundaryPolygon{

private :
    std::list<rg_Line2D*> m_linelist;
    double m_ContanerSize;
    
public :
    MyBoundaryPolygon();
    MyBoundaryPolygon(list<rg_Line2D*> list, double size);
    
    ~MyBoundaryPolygon();
    
    bool find_intersect(const MyEdge* edge, rg_Point2D& intersect_point);
    
};
