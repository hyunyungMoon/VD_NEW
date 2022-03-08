#include "MyVD.h"

MyVD::MyVD(){
    
}


MyVD::MyVD(string file_name){

    read_generator_txt_file(file_name);   
}


void MyVD::read_generator_txt_file(string file_name){
    
    ifstream file(file_name);
    
    string tmp;
    
    getline(file, tmp);
    
    while(!file.eof()){
        
        string line;
        string buf;
        double i = 0;
        
        string x,y;
        
        getline(file, line);
        
        stringstream ss(line);
        ss >> i >> x >> y;
                
        rg_Point2D pt = rg_Point2D(stod(x), stod(y));
        
        m_generatorList.push_back(pt);
        
        make_face_by_generator_and_ID(pt, m_faceIndex);
        
        m_faceIndex++;           
    }
}


void MyVD::make_face_by_generator_and_ID(rg_Point2D generator, int FaceID){
    
    MyFace* NewFace = new MyFace(generator, FaceID);
        
    m_wingededge.concatenate_face(NewFace);
}


bool MyVD::check_valid_circle(rg_Circle2D circle){
    
    for(int i=0; i<m_generatorList.size(); i++){
        if(circle.doesContain(m_generatorList[i])==true){
            return false;
        }
    }    
    return true;   
}


bool MyVD::check_ObtuseTriange_and_find_component_of_maxLine(int i, int j, int k, int& maxLeft, int& maxRight){
    
    rg_Point2D pt1 = m_generatorList[i];
    rg_Point2D pt2 = m_generatorList[j];
    rg_Point2D pt3 = m_generatorList[k];
    
    double d1 = pt1.distance(pt2);
    double d2 = pt2.distance(pt3);
    double d3 = pt3.distance(pt1);
    
    int maxFaceLeft = 0;
    int maxFaceRight = 0;
    
    double max = 0.0;
    
    if(d1>max){
        maxFaceLeft = i;
        maxFaceRight = j;
        max = d1;
    }
    if(d2>max){
        maxFaceLeft = j;
        maxFaceRight = k;
        max = d2;
    }
    if(d3>max){
        maxFaceLeft = i;
        maxFaceRight = k;
        max = d3;
    }
        
    if(max*max + max*max >= d1*d1 + d2*d2 + d3*d3){
        maxLeft = maxFaceLeft;
        maxRight = maxFaceRight;    
        return true;
    }
    else{
        return false;
    }
    
}


void MyVD::make_vertex_by_valid_circle(rg_Point2D circle){
    
    MyVertex* NewVertex = new MyVertex(circle);
    
}


void MyVD::make_vertex_by_making_inner_circle(){
    
    bool isObtuseTriangle = false;
    
    for(int i=0; i<m_generatorList.size(); i++){
        for(int j=i+1; j<m_generatorList.size(); j++){
            for(int k=j+1; k<m_generatorList.size(); k++){
                
                rg_Circle2D currentCircle = rg_Circle2D(m_generatorList[i], m_generatorList[j], m_generatorList[k]);
                double r = sqrt(pow((m_generatorList[i].getX() - currentCircle.getCenterPt().getX()), 2) + pow((m_generatorList[i].getY() - currentCircle.getCenterPt().getY()), 2));
                currentCircle.setRadius(r);                
                
                if(check_valid_circle(currentCircle) == false){
                    break;
                }                
                
                else{
                    
                }          
                
            }
        }    
    }
}