#include "graph_maker.h"

bool astar(graph<string, road> paths, map<string, int> distances, string start_location = "Blue Mountains");
vector<graph<string, road>::vertex*>::iterator get_min_vector(vector<graph<string, road>::vertex*> v);
string get_path(string start_location, graph<string, road> paths_graph);

int main() {
    graph_maker generator("input_files/point_to_point.lotr", "input_files/straight_line_distances.lotr");
    
    generator.create_graph();
    graph<string, road> paths_graph = generator.get_graph();
    
    generator.create_table();
    map<string, int> distance_table = generator.get_table();
    
    astar(paths_graph, distance_table);
    
    cout << get_path("Blue Mountains", paths_graph) << endl;

    return 0;
}

// A* Algorithm, requires a graph of the locations and distances to the final point
bool astar(graph<string, road> paths, map<string, int> distances, string start_location) {
    const string destination = "Iron Hills";    

    vector<graph<string, road>::vertex*> visited_vertices;
    vector<graph<string, road>::vertex*> open_vertices;
    
    graph<string, road>::vertex* start_vertex = paths.find_vertex(start_location);
    open_vertices.push_back(start_vertex);

    while (!open_vertices.empty()) {
        // Find the smallest estimated_cost vertex
        vector<graph<string, road>::vertex*>::iterator current = open_vertices.begin();
        for (vector<graph<string, road>::vertex*>::iterator it = open_vertices.begin(); it != open_vertices.end(); ++it) {
            if ((*it)->estimated_cost < (*current)->estimated_cost)
                current = it;
        }

        if ((*current)->data == destination) {
            return true;
        }

        // Mark as visited
        graph<string, road>::vertex* current_vertex = *current;
        visited_vertices.push_back(current_vertex);
        open_vertices.erase(current);        
        
        for (list<graph<string, road>::edge>::iterator it = current_vertex->neighbors.begin(); it != current_vertex->neighbors.end(); ++it) {
            graph<string, road>::edge e = *it;

            // If edge end is in visited vertices ignore
            bool skip_edge = false;
            for (vector<graph<string, road>::vertex*>::iterator it2 = visited_vertices.begin(); it2 != visited_vertices.end(); ++it2) {
                graph<string, road>::vertex* v = *it2;
                if (e.end->data == v->data)
                    skip_edge = true;
            }
            if (skip_edge)
                continue;

            double temp_cost = current_vertex->cost + e.cost.distance;
            double temp_estimated_cost = temp_cost + distances[e.end->data];
            
            // If not in open_vertices insert
            bool in_open_vertices = false;
            for (vector<graph<string, road>::vertex*>::iterator it2 = open_vertices.begin(); it2 != open_vertices.end(); ++it2) {
                if ((*it2)->data == (*it).end->data)
                    in_open_vertices = true;
            }
            if (!in_open_vertices) {
                e.end->cost = temp_cost;
                e.end->estimated_cost = temp_estimated_cost;
                e.end->pred = current_vertex;
                open_vertices.push_back(e.end);
            }

            // If new estimated cost lower than current in list replace it
            if (temp_estimated_cost < e.end->estimated_cost) {
                e.end->cost = temp_cost;
                e.end->estimated_cost = temp_estimated_cost;
                e.end->pred = current_vertex;
            }
                
        }
    }
}

// Return a string with the shortest path according to A*
string get_path(string start_location, graph<string, road> paths_graph) {
    string the_path = "";
    graph<string, road>::vertex* tracing_vertex = paths_graph.find_vertex("Iron Hills");
    while (tracing_vertex->pred != NULL) {
        the_path = tracing_vertex->data + "->" + the_path;
        tracing_vertex = tracing_vertex->pred;
    }
    return start_location + "->" + the_path;
}
