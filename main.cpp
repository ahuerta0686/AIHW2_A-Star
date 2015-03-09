#include "graph_maker.h"

int main() {
    graph_maker generator("input_files/point_to_point.lotr", "input_files/straight_line_distances.lotr");
    
    generator.create_graph();
    return 0;
}
