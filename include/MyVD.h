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
    
    int m_faceIndex = 0;
    vector<MyVertex> m_vertexVector;
    vector<rg_Circle2D> m_circleVector;
    
    int m_circleIndex = 0;
    vector<MyEdge> m_edgeVector;

    vector<vector<MyEdge>> m_edgeVectorOfVertexVector;    
    
public:

private:
    void read_generator_txt_file(string file_name);
    
    void make_face_by_generator_and_ID(rg_Point2D generator, int FaceID);
    
    bool check_valid_circle(rg_Circle2D circle);
    
    bool check_ObtuseTriange_and_find_component_of_maxLine(int i, int j, int k, int& maxLeft, int& maxRight);
    
    void make_vertex_by_valid_circle(rg_Point2D circle);
    
    void make_vertex_by_making_inner_circle();
    
    
    
public:
    MyVD();
    MyVD(string file_name);
    
    
};