#pragma once

#include "WingedEdgeDataStructure.h"
#include "rg_Point2D.h"

class MyFace : public WingedEdgeDataStructure::Face{

private:
    rg_Point2D m_generator;
    
public:
    MyFace();
    MyFace(rg_Point2D generator);
    MyFace(rg_Point2D generator, int FaceID);
    
    ~MyFace();
    
    rg_Point2D get_generator() const;
    
    void set_generator(rg_Point2D generator);

};