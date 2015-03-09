#include "graph.h"
#include "road.h"

int main() {
    graph<string, road> test = graph<string, road>();
    test.add_vertex("Doghouse");
    test.add_vertex("Shipyard");
    road rd(10, 7.5, 3.5);
    test.add_edge("Doghouse", "Shipyard", rd);
    test.print();
}
