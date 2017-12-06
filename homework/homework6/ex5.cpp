#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

struct node {
    string name;
    long distance = INT_MAX;
    node *predecessor = nullptr;
    
    string to_string() {
        string str = name + " = {distance = ";
        if (distance < INT_MAX) {
            str += std::to_string(distance);
        } else {
            str += "inf";
        }
        str += ", predecessor = ";
        if (predecessor) {
            str += predecessor->name;
        } else {
            str += "null";
        }
        str += "}";
        return str;
    }
};

struct edge {
    node *start, *end;
    int weight;
};

int main() {
    vector<node> graph;
    for (int i=0;i<6;i++) {
        node temp;
        temp.name += 'a'+i;
        graph.emplace_back(move(temp));
    }
    vector<edge> edges = {
        {&graph[0], &graph[1], 6},
        {&graph[0], &graph[2], 4},
        {&graph[1], &graph[2], 1},
        {&graph[1], &graph[3], 5},
        {&graph[1], &graph[5], 6},
        {&graph[2], &graph[4], 3},
        {&graph[3], &graph[4], 1},
        {&graph[4], &graph[1], -2},
        {&graph[4], &graph[5], 6},
        {&graph[5], &graph[3], -3},        
    };
    
    int src = 0;
    graph[src].distance = 0;
    
    for (int i=0;i<graph.size();i++) {
        cout << "Iteration " << (i+1) << endl;
        for (const auto &e : edges) {
            cout << "Edge " << e.start->name << " -> " << e.end->name << " = " << e.weight << ", ";
            cout << e.start->to_string() << ", ";
            cout << e.end->to_string() << ", ";
            if (e.start->distance + e.weight < e.end->distance) {
                e.end->distance = e.start->distance + e.weight;
                e.end->predecessor = e.start;
                cout << "updated " << e.end->to_string();
            } else {
                cout << "nothing happened";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    cout << "Check negative cycle" << endl;
    for (const auto &e : edges) {
        cout << "Edge " << e.start->name << " -> " << e.end->name << " = " << e.weight << ", ";
        cout << e.start->to_string() << ", ";
        cout << e.end->to_string();
        if (e.start->distance + e.weight < e.end->distance) {
            cout << endl << "Graph contains a negative-weight cycle" << endl;
            return 0;
        } else {
            cout << ", nothing happened" << endl;
        }
    }
    cout << endl << "Graph doesn't contain a negative-weight cycle" << endl;
    return 0;
}
