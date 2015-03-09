#include<fstream>
#include<map>
#include<algorithm>
#include<vector>
#include<sstream>
#include<iostream>
#include<cctype>
#include<string>
#include<iterator>
#include<cstdlib>
using namespace std;

#include "graph.h"
#include "road.h"

class graph_maker {
private:
    string point_to_point_path;
    string straight_line_distance_path;
    
    ifstream paths_input;
    ifstream distance_input;

    bool graph_created;
    bool table_created;

    graph<string, road> paths_graph;
    map<string, int> distances_table;

    // Based on a vector of tokens generate the proper road
    road extract_road(vector<string> t) {
        double risk_level = atof(t[t.size() - 1].c_str());
        double road_quality = atof(t[t.size() - 2].c_str());
        int distance = atoi(t[t.size() - 3].c_str());
        
        return road(distance, road_quality, risk_level);
    }

    // Using vector of tokens return the name of the road
    string extract_road_name(vector<string> t) {
        string destination = "";
        for (int i = 0; i < t.size() - 3; i++) {
            if (i + 1 != t.size() - 3)
                destination += t[i] + " ";
            else
                destination += t[i];
        }

        return destination;
    }

public:
    // Sets paths for input files
    graph_maker(string ptp_path, string sld_path) {
        point_to_point_path = ptp_path;
        straight_line_distance_path = sld_path;
        
        graph_created = false;
        table_created = false;
    }

    // Return a graph representation based on point to point information
    bool create_graph() {
        if (!graph_created) {
            paths_input.open(point_to_point_path.c_str());
            int num_lines = 0;
            string parent_location = "";
            
            // Read in first line
            string line;
            getline(paths_input, line);
            num_lines++;
            while (!paths_input.eof()) {
                // Check if line is a parent location, i.e. in the input
                // the location doesn't have path info but has paths to
                // other locations following it
                if (!isspace(line[0])) {
                    parent_location = line;
                    int num_child_locations = 0;
                    getline(paths_input, line);
                    num_lines++;
                    cout << parent_location << endl << num_child_locations << endl;

                    // Path information from a parent location is noted
                    // by whitespace in front
                    while (isspace(line[0]) and !paths_input.eof()) {
                        num_child_locations++;              

                        // Tokenize path information
                        istringstream iss(line);
                        vector<string> tokens;
                        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
                        
                        road rd = extract_road(tokens);
                        string rd_name = extract_road_name(tokens);
                        cout << rd_name << endl;
                        cout << rd << endl;

                        getline(paths_input, line);
                        num_lines++;
                    }
                    cout << "=======" << endl;
                    parent_location = "";
                }
            }
            cout << num_lines << endl;
            return true;
        }
        else {
            return false;
        }
    }
};
