#include "MyBoundaryPolygon.h"

MyBoundaryPolygon::MyBoundaryPolygon(){
	m_ContanerSize = -1;
}


MyBoundaryPolygon::MyBoundaryPolygon(list<rg_Line2D*> list, double size){
    m_linelist = list;
    m_ContanerSize = size;       
}


MyBoundaryPolygon::~MyBoundaryPolygon(){
	
}


bool MyBoundaryPolygon::find_intersect(const MyEdge* edge, rg_Point2D& intersect_point){
    
	//make virtual point by making extension of edge to get intersect point with boundary
	
	rg_Point2D existPoint;
    rg_Point2D endPoint;
	
	
    if(edge->end_vertex() == nullptr){
		MyVertex * vertex = (MyVertex*)edge->start_vertex();
		existPoint = vertex->get_point();        
    }
    else if (edge->start_vertex() == nullptr) {
		MyVertex* vertex = (MyVertex*)edge->end_vertex();
		existPoint = vertex->get_point();
	}
	
	if (edge->get_direction() == true) {
		endPoint = edge->get_vector() * m_ContanerSize + existPoint ;
	}
	else if (edge->get_direction() == false) {
		endPoint = edge->get_vector() * -m_ContanerSize + existPoint;
	}
    
    rg_Line2D curr_line = rg_Line2D(existPoint,endPoint);
	bool doesIntersect = true;
	rg_Line2D::IntersectionPointPosition position;

	std::list<rg_Line2D*>::iterator it;
	for (it = m_linelist.begin(); it != m_linelist.end(); it++) {
		intersect_point = (*it)->compute_intersection_btw_two_line_segments(curr_line, doesIntersect, position);
		if (doesIntersect)
			break;
	}

	if (it == m_linelist.end()){
		return false;
	}
		
	return true;
}


