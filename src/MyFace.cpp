#include "MyFace.h"

MyFace::MyFace(){

}


MyFace::MyFace(rg_Point2D generator){
    m_generator = generator;
}


MyFace::MyFace(rg_Point2D generator, int FaceID){
    m_generator = generator;
    m_ID = FaceID;
}


MyFace::~MyFace(){
    
}


rg_Point2D MyFace::get_generator() const{
    return m_generator;
}

void MyFace::set_generator(rg_Point2D generator){
    m_generator = generator;
}