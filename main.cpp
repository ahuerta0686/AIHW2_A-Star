#include "graph_maker.h"

int main() {
    graph_maker generator("input_files/point_to_point.lotr", "input_files/straight_line_distances.lotr");
    
    generator.create_graph();
    graph<string, road> paths_graph = generator.get_graph();
    
    paths_graph.print();
    return 0;
}
