#include <MyVertex.h>

MyVertex::MyVertex(){
        
}


MyVertex::MyVertex(rg_Point2D point){
    
    m_point = point;    
}


MyVertex::MyVertex(rg_Circle2D circle){
    
    m_point = circle.getCenterPt();    
}


rg_Point2D MyVertex::get_point() const{
    
    return m_point;
}


void MyVertex::set_point(rg_Point2D point){
    
    m_point = point;
}