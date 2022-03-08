#include "MyEdge.h"

MyEdge::MyEdge(){
        
}


MyEdge::MyEdge(rg_Point2D vector){
    
    m_direction = true;
    m_vector = vector;
}


MyEdge::MyEdge(bool direction, rg_Point2D vector){
        
    m_direction = direction;
    m_vector = vector;
}

MyEdge::~MyEdge(){
    
}


rg_Point2D MyEdge::get_vector() const{
    
    return m_vector;
}


bool MyEdge::get_direction() const{
    
    return m_direction;
}


void MyEdge::set_vector(rg_Point2D vector){
    
    m_vector = vector;
}


void MyEdge::set_direction(bool direction){
    
    m_direction = direction;
}

