#include "graph.h"

int main() {
    graph test = graph();
    test.add_vertex(10);
    test.add_vertex(20);
    test.add_edge(10, 20, 7);
    test.print();
}
