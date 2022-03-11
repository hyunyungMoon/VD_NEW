#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "WingedEdgeDataStructure.h"
#include "rg_Circle2D.h"
#include "rg_Const.h"
#include "rg_Point2D.h"
#include "MyBoundaryPolygon.h"
#include "MyEdge.h"
#include "MyFace.h"
#include "MyVertex.h"

using std::vector;
using std::string;

class MyVD {

private:
    WingedEdgeDataStructure m_wingededge;    
    
    vector<rg_Point2D> m_generatorList;
    vector<MyFace*> m_faceVector;
    
    int m_faceIndex = 0;
    vector<MyVertex*> m_vertexVector;
    vector<rg_Circle2D> m_circleVector;
    
    int m_circleIndex = 0;
    vector<MyEdge*> m_edgeVector;

    vector<vector<MyEdge*>> m_edgeVectorOfVertexVector;    
    
public: 


private:
    void read_generator_txt_file_and_make_face(string file_name);
    
    void make_face_by_generator_and_ID(rg_Point2D generator, int FaceID);
    
    bool check_valid_circle(rg_Circle2D circle);
    
    bool check_ObtuseTriangle_and_find_component_of_maxLine(int i, int j, int k, int& maxLeft, int& maxRight);
    
    MyVertex* make_vertex_by_valid_circle(rg_Circle2D circle);
    
    bool compare_edge_by_FaceID_and_integrate(MyVertex* currentVertex, int leftFaceID, int rightFaceID);
    
    bool find_direction_of_vector_by_3_point(rg_Point2D vertexPT, rg_Point2D leftPT, rg_Point2D rightPT);
    
    void make_new_edge_by_each_face_and_vertex_information(MyVertex* currentVertex, int leftFaceID, int rightFaceID, bool isObtuse, int maxLeft, int maxRight);
    
    void connect_edge_by_edgeVectorOfVertex();
    
    void make_relationship_of_face();    
    
    void calculate_unboud_with_boundary(MyBoundaryPolygon* boundary, double boundary_value);
        
    void make_vertex_and_edge_by_making_inner_circle();
    
    
    
    
public:
    MyVD();
    
    MyVD(string file_name);
    
    ~MyVD();

    void make_boundary_and_calculate_unbound(double boundary_value);

    void write_edge_output_in_txt_form(string file_name);
    
};