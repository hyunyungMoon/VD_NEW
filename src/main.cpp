#include "MyVD.h"

int main(int, char**) {
    MyVD VD100 = MyVD("./../../data/input/voronoi_test5000.txt");

    VD100.make_boundary_and_calculate_unbound(6000.0);

    VD100.write_edge_output_in_txt_form("./../../data/output/voronoi_output5000.txt");

    // VoronoiDiagram2D VD_D2;
    // VD_D2.construct(fileName, 6000);
    // //VD_D2.construct(list<rg_Point>);
    // VD_D2.write_edge(fileNameForEdges);

    std::cout << "finish" << std::endl;
    return 0;
}
