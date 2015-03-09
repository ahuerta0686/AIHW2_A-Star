#include<iostream>
using namespace std;

class road {
public:
    int distance;
    double quality;
    double risk;
    
    road() {}
    
    // Create a road with the attributes
    // d : distance
    // q : road quality
    // r : risk level
    road(int d, double q, double r) {
        distance = d;
        quality = q;
        risk = r;
    }

    friend ostream& operator<<(ostream& os, const road& rd) {
        os << "Distance: " <<  rd.distance << ", " << "Road quality: " << rd.quality << ", " << "Risk Level: " << rd.risk;
        return os;
    }
};
