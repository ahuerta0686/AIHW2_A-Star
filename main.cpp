#include "graph_maker.h"

int main() {
    graph_maker generator("input_files/point_to_point.lotr", "input_files/straight_line_distances.lotr");
    
    //generator.create_graph();
    //graph<string, road> paths_graph = generator.get_graph();
    
    generator.create_table();

    map<string, int> distance_table = generator.get_table();
    

    for (map<string, int>::const_iterator it = distance_table.begin(); it != distance_table.end(); ++it) {
        cout << it->first << " :: " << it->second << endl;
    }
    //paths_graph.print();
    return 0;
}
