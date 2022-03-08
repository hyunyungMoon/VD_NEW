#pragma once

#include "WingedEdgeDataStructure.h"
#include "rg_Point2D.h"
#include "rg_Circle2D.h"
#include "MyEdge.h"

class MyVertex : public WingedEdgeDataStructure::Vertex
{
private:    
    rg_Point2D m_point;
    
public:    
    MyVertex();
    MyVertex(rg_Point2D point);
    MyVertex(rg_Circle2D circle);
    
    rg_Point2D get_point() const;
    
    void set_point(rg_Point2D point);
    

private :
    // private function

};