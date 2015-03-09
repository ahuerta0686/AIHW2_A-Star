#include <iostream>
#include <list>
using namespace std;

template<typename T, typename C>
class graph {
private:
    class vertex;
    class edge;    

    class vertex {
    public:
        T data;
        list<edge> neighbors;
    };

    class edge {
    public:
        vertex* start;
        vertex* end;
        C cost;

        // Create a new edge from a to b with weight w
        edge(vertex* a, vertex* b, C c) {
            start = a;
            end = b;
            cost = c;
        }
    };

    list<vertex*> vertices;

public:
    graph() {
        vertices = list<vertex*>();
    }

    // Add a vertex with data value x to the graph
    // Each vertex's data value must be unique
    bool add_vertex(T x) {
        // Check that vertex is not in graph already
        for (typename list<vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
            vertex* v = *it;
            if (v->data == x)
                return false;
        }

        // Add new vertex to graph
        vertex* v = new vertex();
        v->data = x;
        vertices.push_back(v);
        return true; 
    }

    // Add an edge between two existing vertices with a weight
    bool add_edge(T a, T b, C c) {
        // Disallow edges to self
        if (a == b)
            return false;

        //Find vertices in graph with data a and b
        vertex* s = NULL;
        vertex* e = NULL;
        for (typename list<vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
            vertex* v = *it;
            if (v->data == a)
                s = v;
            else if (v->data == b)
                e = v;
        }
        
        if (s != NULL && e != NULL) {
            edge e1 = edge(s, e, c);
            edge e2 = edge(e, s, c);
            s->neighbors.push_back(e1);
            e->neighbors.push_back(e2);
            return true;
        }
        else
            return false;
    }

    void print() {
        for (typename list<vertex*>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
            vertex* v = *it;
            cout << v->data << endl;
            for (typename list<edge>::const_iterator it2 = v->neighbors.begin(); it2 != v->neighbors.end(); ++it2) {
                edge e = *it2;
                cout << e.end->data << " : " << e.cost << endl;
            }
        }
    }
};
