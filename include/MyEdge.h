#pragma once

#include "WingedEdgeDataStructure.h"
#include "rg_Point2D.h"
#include "MyVertex.h"

class MyEdge : public WingedEdgeDataStructure::Edge {
    
private:      
    rg_Point2D m_vector;
    bool m_direction;
   
public:    
    MyEdge();
    MyEdge(rg_Point2D vector);
    MyEdge(bool m_direction, rg_Point2D vector);
    
    ~MyEdge();
            
    rg_Point2D get_vector() const;
    bool get_direction() const;   
    
    void set_vector(rg_Point2D vector);
    void set_direction(bool direction);
        
};