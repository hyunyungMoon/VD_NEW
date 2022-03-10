#include "MyVD.h"

MyVD::MyVD(){
    
}


MyVD::MyVD(string file_name){

    read_generator_txt_file(file_name);
    
    make_vertex_and_edge_by_making_inner_circle();
    
    connect_edge_by_edgeVectorOfVertex();
    
    make_relationship_of_face();
    
    //make boundary and calculate unboud
    
    //
       
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
    
    m_faceVector.push_back(NewFace);
        
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


bool MyVD::check_ObtuseTriangle_and_find_component_of_maxLine(int i, int j, int k, int& maxLeft, int& maxRight){
    //tell is obtusetrangle or not and which point is the component of max line
    
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


MyVertex* MyVD::make_vertex_by_valid_circle(rg_Circle2D circle){
    
    MyVertex* NewVertex = new MyVertex(circle);
    
    m_circleIndex++;
    
    m_vertexVector.push_back(NewVertex);
        
    m_wingededge.concatenate_vertex(NewVertex);
    
    vector<MyEdge*> m_edgeVectorOfThisVertex;
    
    m_edgeVectorOfVertexVector.push_back(m_edgeVectorOfThisVertex);
    
    return NewVertex;
        
}


bool MyVD::compare_edge_by_FaceID_and_integrate(MyVertex* currentVertex, int leftFaceID, int rightFaceID){
    
    for(int i = 0; i < m_edgeVector.size(); i++){
        MyEdge* compareEdge = m_edgeVector[i];
        if(compareEdge->left_face()->getID() == leftFaceID && compareEdge->right_face()->getID() == rightFaceID){
            if(compareEdge->end_vertex() == nullptr){
                compareEdge->set_end_vertex(currentVertex);
            }
            if(compareEdge->start_vertex() == nullptr){
                compareEdge->set_start_vertex(currentVertex);
            }            
            currentVertex->set_first_edge(compareEdge);
            m_edgeVectorOfVertexVector[m_circleIndex].push_back(compareEdge);
            return false;
        }        
    }
    
    return true;    
}


bool find_direction_of_vector_by_3_point(rg_Point2D vertexPT, rg_Point2D leftPT, rg_Point2D rightPT){
    double x1 = leftPT.getX() - vertexPT.getX();
    double y1 = leftPT.getY() - vertexPT.getY();
    
    double x2 = rightPT.getX() - vertexPT.getX();
    double y2 = rightPT.getY() - vertexPT.getY();
    
    double direction = x1 * y2 - y1 * x2;
    
    if (direction <0){
        return false;
    }
    else{
        return true;
    }
}


void MyVD::make_new_edge_by_each_face_and_vertex_information(MyVertex* currentVertex, int leftFaceID, int rightFaceID, bool isObtuse, int maxLeft, int maxRight){
    MyEdge* NewEdge = new MyEdge();
    NewEdge->set_left_face(m_faceVector[leftFaceID]);
    NewEdge->set_right_face(m_faceVector[rightFaceID]);        
    
    if(find_direction_of_vector_by_3_point(currentVertex->get_point(), m_faceVector[leftFaceID]->get_generator(), m_faceVector[rightFaceID]->get_generator()) == false){
        NewEdge->set_start_vertex(currentVertex);
    }
    else{
        NewEdge->set_end_vertex(currentVertex);
    }
    m_edgeVector.push_back(NewEdge);
    currentVertex->set_first_edge(NewEdge);
    m_edgeVectorOfVertexVector[m_circleIndex].push_back(NewEdge);
    NewEdge->set_vector( (m_faceVector[leftFaceID]->get_generator() + m_faceVector[rightFaceID]->get_generator() / 2 - currentVertex->get_point()).getUnitVector() );
    
    if(isObtuse && leftFaceID == maxLeft && rightFaceID == maxRight){
        NewEdge->set_direction(false);
        
        MyVertex* temp = (MyVertex*)NewEdge->end_vertex();
        NewEdge->set_end_vertex(NewEdge->start_vertex());
        NewEdge->set_start_vertex(temp);        
    }        
}


void MyVD::connect_edge_by_edgeVectorOfVertex(){
    for(int i = 0; i < m_edgeVectorOfVertexVector.size(); i++){
        vector<MyEdge*> currentVectorOfEdge = m_edgeVectorOfVertexVector[i];
        
        MyEdge* currentEdge1 = currentVectorOfEdge[0];
        MyEdge* currentEdge2 = currentVectorOfEdge[1];
        MyEdge* currentEdge3 = currentVectorOfEdge[2];
        
        if (currentEdge1->is_start_vertex(currentEdge2->start_vertex())) {
            if (currentEdge1->right_face() == currentEdge2->left_face()) {
                currentEdge1->set_right_leg_edge(currentEdge2);
                currentEdge2->set_left_leg_edge(currentEdge1);
            }

            if (currentEdge1->left_face() == currentEdge2->right_face()) {
                currentEdge1->set_left_leg_edge(currentEdge2);
                currentEdge2->set_right_leg_edge(currentEdge1);
            }
        }

        if (currentEdge1->is_start_vertex(currentEdge2->end_vertex())) {
            if (currentEdge1->right_face() == currentEdge2->right_face()) {
                currentEdge1->set_right_leg_edge(currentEdge2);
                currentEdge2->set_right_hand_edge(currentEdge1);
            }

            if (currentEdge1->left_face() == currentEdge2->left_face()) {
                currentEdge1->set_left_leg_edge(currentEdge2);
                currentEdge2->set_left_hand_edge(currentEdge1);
            }
        }

        if (currentEdge1->is_end_vertex(currentEdge2->start_vertex())) {
            if (currentEdge1->right_face() == currentEdge2->right_face()) {
                currentEdge1->set_right_hand_edge(currentEdge2);
                currentEdge2->set_right_leg_edge(currentEdge1);
            }

            if (currentEdge1->left_face() == currentEdge2->left_face()) {
                currentEdge1->set_left_hand_edge(currentEdge2);
                currentEdge2->set_left_leg_edge(currentEdge1);
            }
        }

        if (currentEdge1->is_end_vertex(currentEdge2->end_vertex())) {
            if (currentEdge1->left_face() == currentEdge2->right_face()) {
                currentEdge1->set_left_hand_edge(currentEdge2);
                currentEdge2->set_right_hand_edge(currentEdge1);
            }

            if (currentEdge1->right_face() == currentEdge2->left_face()) {
                currentEdge1->set_right_hand_edge(currentEdge2);
                currentEdge2->set_left_hand_edge(currentEdge1);
            }
        }

        if (currentEdge1->is_start_vertex(currentEdge3->start_vertex())) {
            if (currentEdge1->right_face() == currentEdge3->left_face()) {
                currentEdge1->set_right_leg_edge(currentEdge3);
                currentEdge3->set_left_leg_edge(currentEdge1);
            }

            if (currentEdge1->left_face() == currentEdge3->right_face()) {
                currentEdge1->set_left_leg_edge(currentEdge3);
                currentEdge3->set_right_leg_edge(currentEdge1);
            }
        }

        if (currentEdge1->is_start_vertex(currentEdge3->end_vertex())) {
            if (currentEdge1->right_face() == currentEdge3->right_face()) {
                currentEdge1->set_right_leg_edge(currentEdge3);
                currentEdge3->set_right_hand_edge(currentEdge1);
            }

            if (currentEdge1->left_face() == currentEdge3->left_face()) {
                currentEdge1->set_left_leg_edge(currentEdge3);
                currentEdge3->set_left_hand_edge(currentEdge1);
            }
        }

        if (currentEdge1->is_end_vertex(currentEdge3->start_vertex())) {
            if (currentEdge1->right_face() == currentEdge3->right_face()) {
                currentEdge1->set_right_hand_edge(currentEdge3);
                currentEdge3->set_right_leg_edge(currentEdge1);
            }

            if (currentEdge1->left_face() == currentEdge3->left_face()) {
                currentEdge1->set_left_hand_edge(currentEdge3);
                currentEdge3->set_left_leg_edge(currentEdge1);
            }
        }

        if (currentEdge1->is_end_vertex(currentEdge3->end_vertex())) {
            if (currentEdge1->left_face() == currentEdge3->right_face()) {
                currentEdge1->set_left_hand_edge(currentEdge3);
                currentEdge3->set_right_hand_edge(currentEdge1);
            }

            if (currentEdge1->right_face() == currentEdge3->left_face()) {
                currentEdge1->set_right_hand_edge(currentEdge3);
                currentEdge3->set_left_hand_edge(currentEdge1);
            }
        }

        if (currentEdge2->is_start_vertex(currentEdge3->start_vertex())) {
            if (currentEdge2->right_face() == currentEdge3->left_face()) {
                currentEdge2->set_right_leg_edge(currentEdge3);
                currentEdge3->set_left_leg_edge(currentEdge2);
            }

            if (currentEdge2->left_face() == currentEdge3->right_face()) {
                currentEdge2->set_left_leg_edge(currentEdge3);
                currentEdge3->set_right_leg_edge(currentEdge2);
            }
        }

        if (currentEdge2->is_start_vertex(currentEdge3->end_vertex())) {
            if (currentEdge2->right_face() == currentEdge3->right_face()) {
                currentEdge2->set_right_leg_edge(currentEdge3);
                currentEdge3->set_right_hand_edge(currentEdge2);
            }

            if (currentEdge2->left_face() == currentEdge3->left_face()) {
                currentEdge2->set_left_leg_edge(currentEdge3);
                currentEdge3->set_left_hand_edge(currentEdge2);
            }
        }

        if (currentEdge2->is_end_vertex(currentEdge3->start_vertex())) {
            if (currentEdge2->right_face() == currentEdge3->right_face()) {
                currentEdge2->set_right_hand_edge(currentEdge3);
                currentEdge3->set_right_leg_edge(currentEdge2);
            }

            if (currentEdge2->left_face() == currentEdge3->left_face()) {
                currentEdge2->set_left_hand_edge(currentEdge3);
                currentEdge3->set_left_leg_edge(currentEdge2);
            }
        }

        if (currentEdge2->is_end_vertex(currentEdge3->end_vertex())) {
            if (currentEdge2->left_face() == currentEdge3->right_face()) {
                currentEdge3->set_right_hand_edge(currentEdge2);
            }

            if (currentEdge2->right_face() == currentEdge3->left_face()) {
                currentEdge2->set_right_hand_edge(currentEdge3);
                currentEdge3->set_left_hand_edge(currentEdge2);
            }
        }        
    }
}


void MyVD::make_relationship_of_face(){
    for(int i = 0; i < m_edgeVector.size(); i++){
        MyEdge* currentEdge = m_edgeVector[i];
        currentEdge->left_face()->set_first_edge(currentEdge);
        currentEdge->right_face()->set_first_edge(currentEdge);
        m_wingededge.concatenate_edge(currentEdge);
    }
}


void MyVD::make_boundary_and_calculate_unboud(double boundary_value){
    rg_Point2D boundaryPoint1 = rg_Point2D(boundary_value, boundary_value);
    rg_Point2D boundaryPoint2 = rg_Point2D(-boundary_value, boundary_value);
    rg_Point2D boundaryPoint3 = rg_Point2D(-boundary_value, -boundary_value);
    rg_Point2D boundaryPoint4 = rg_Point2D(boundary_value, -boundary_value);

    list<rg_Line2D*> lineList;
    rg_Line2D* BoundaryLine1 = new rg_Line2D(boundaryPoint1, boundaryPoint2);
    rg_Line2D* BoundaryLine2 = new rg_Line2D(boundaryPoint2, boundaryPoint3);
    rg_Line2D* BoundaryLine3 = new rg_Line2D(boundaryPoint3, boundaryPoint4);
    rg_Line2D* BoundaryLine4 = new rg_Line2D(boundaryPoint4, boundaryPoint1);
    lineList.push_back(BoundaryLine1);
    lineList.push_back(BoundaryLine2);
    lineList.push_back(BoundaryLine3);
    lineList.push_back(BoundaryLine4);
    
    MyBoundaryPolygon* boundary = new MyBoundaryPolygon(lineList, 2 * boundary_value);
    
    
}


void MyVD::calculate_unboud_with_boundary(MyBoundaryPolygon* boundary, double boundary_value){
    for(int i = 0; i < m_edgeVector.size(); i++){
        MyEdge* unboundedEdge = m_edgeVector[i];
        if(unboundedEdge->end_vertex() == nullptr || unboundedEdge->start_vertex() == nullptr){
            std::cout<<i<<endl;
            rg_Point2D* newPoint = new rg_Point2D();
            
            if(boundary->find_intersect(unboundedEdge, *newPoint)){
                MyVertex* newVertex = new MyVertex(*newPoint);
                
                if(unboundedEdge->end_vertex() == nullptr){
                    unboundedEdge->set_end_vertex(newVertex);
                }
                else if(unboundedEdge->start_vertex() == nullptr){
                    unboundedEdge->set_start_vertex(newPoint);
                }                
            }
            
            else{
                std::cout <<"gg"<<endl;
                
                
                
            }
        }
    }
}


void MyVD::make_vertex_and_edge_by_making_inner_circle(){    
    
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
                    MyVertex* currentVertex = make_vertex_by_valid_circle(currentCircle);

                    int maxLeft = 0;
                    int maxRight = 0;
                    
                    bool isObtuse = check_ObtuseTriangle_and_find_component_of_maxLine(i, j, k, maxLeft, maxRight);
                    
                    
                    bool isnew1 = compare_edge_by_FaceID_and_integrate(currentVertex, i, j);                    
                    if(isnew1){
                        make_new_edge_by_each_face_and_vertex_information(currentVertex, i, j, isObtuse, maxLeft, maxRight);                        
                    } 
                                       
                    bool isnew2 = compare_edge_by_FaceID_and_integrate(currentVertex, j, k);                    
                    if(isnew2){
                        make_new_edge_by_each_face_and_vertex_information(currentVertex, j, k, isObtuse, maxLeft, maxRight);                        
                    }   
                                     
                    bool isnew3 = compare_edge_by_FaceID_and_integrate(currentVertex, i, k);                    
                    if(isnew3){
                        make_new_edge_by_each_face_and_vertex_information(currentVertex, i, k, isObtuse, maxLeft, maxRight);                        
                    } 
                    
                    
                }         
                
                
            }
        }    
    }   
    
}