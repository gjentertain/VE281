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
        string str = name + ": distance = ";
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
        return str;
    }
};

struct edge {
    node *start, *end;
    int weight;
};

void tikz_graph(const vector<node> &graph) {
    cout << R"(
\begin{center}
\begin{tikzpicture}[>/.tip={Latex}]
\draw (-2.5,0) 	node (a) [draw,shape=circle,minimum size=0.8cm] {a};
\draw (-1,1)    node (b) [draw,shape=circle,minimum size=0.8cm] {b};
\draw (-1,-1)   node (c) [draw,shape=circle,minimum size=0.8cm] {c};
\draw (1,1)     node (d) [draw,shape=circle,minimum size=0.8cm] {d};
\draw (1,-1)    node (e) [draw,shape=circle,minimum size=0.8cm] {e};
\draw (2.5,0)   node (f) [draw,shape=circle,minimum size=0.8cm] {f};
\draw[->] (a) edge node [above left] {6} (b);
\draw[->] (a) edge node [below left] {4} (c);
\draw[->] (b) edge node [left] {1} (c);
\draw[->] (b) edge node [above] {5} (d);
\draw[->] (b) edge node [below left] {6} (f);
\draw[->] (c) edge node [below] {3} (e);
\draw[->] (d) edge node [below left] {1} (e);
\draw[->] (e) edge node [below left] {-2} (b);
\draw[->] (e) edge node [below right] {6} (f);
\draw[->] (f) edge node [above right] {-3} (d);
    )" << endl;
    cout << R"(\node [left]  at (a.west)  {)" << graph[0].distance << "};" << endl;
    cout << R"(\node [above] at (b.north) {)" << graph[1].distance << "};" << endl;
    cout << R"(\node [below] at (c.south) {)" << graph[2].distance << "};" << endl;
    cout << R"(\node [above] at (d.north) {)" << graph[3].distance << "};" << endl;
    cout << R"(\node [below] at (e.south) {)" << graph[4].distance << "};" << endl;
    cout << R"(\node [right] at (f.east)  {)" << graph[5].distance << "};" << endl;
    cout << R"(
\end{tikzpicture}
\end{center}
    )" << endl;
}

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
        cout << "\\noindent Iteration " << (i+1) << "\\\\" << endl;
        for (const auto &e : edges) {
            cout << "Edge " << e.start->name << " -> " << e.end->name << " = " << e.weight << "\\\\" << endl;
            cout << e.start->to_string() << "\\\\" << endl;
            cout << e.end->to_string() << "\\\\" << endl;
            if (e.start->distance + e.weight < e.end->distance) {
                e.end->distance = e.start->distance + e.weight;
                e.end->predecessor = e.start;
                cout << "updated: " << e.end->to_string();
            } else {
                cout << "nothing happened";
            }
            cout << "\\\\" << endl;
        }
        tikz_graph(graph);
    }

    cout << "\\noindent Check negative cycle" << "\\\\" << endl;
    for (const auto &e : edges) {
        cout << "Edge " << e.start->name << " -> " << e.end->name << " = " << e.weight << "\\\\" << endl;
        cout << e.start->to_string() << "\\\\" << endl;
        cout << e.end->to_string() << "\\\\" << endl;
        if (e.start->distance + e.weight < e.end->distance) {
            cout << endl << "Graph contains a negative-weight cycle" << "\\\\" << endl;
            return 0;
        } else {
            cout << "nothing happened" << "\\\\" << endl;
        }
    }
    cout << endl << "\\noindent Graph doesn't contain a negative-weight cycle" << endl;
    return 0;
}
