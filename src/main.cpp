#include "MyVD.h"

int main(int, char**) {
    
    MyVD VD100 = MyVD("./../../data/input/voronoi_test5000.txt");
    
    VD100.make_boundary_and_calculate_unbound(6000.0);
    
    VD100.write_edge_output_in_txt_form("./../../data/output/voronoi_output5000.txt");
    
    std::cout << "finish" << std::endl;
    return 0;
    
}
