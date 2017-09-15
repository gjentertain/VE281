//
// Created by liu on 2017/9/15.
//

#include <iostream>
#include <getopt.h>
#include "binary_heap.h"

using namespace std;

class Point {
public:
    size_t x, y;
    size_t weight, cost = 0;
    bool reached = false;
    Point *predecessor = NULL;

    struct compare_t {
        bool operator()(const Point &a, const Point &b) const {
            return a.cost < b.cost;
        }
    };

    friend ostream &operator<<(ostream &out, const Point &p) {
        out << "(" << p.y << ", " << p.x << ")";
        return out;
    }
};

void print_path(const Point &p) {
    if (p.predecessor) print_path(*(p.predecessor));
    cout << p << endl;
}

int main(int argc, char *argv[]) {

    const char *short_options = "iv";
    const option long_options[] = {
            {"implementation", no_argument, NULL, 'i'},
            {"verbose",        no_argument, NULL, 'v'},
            {0,                0, 0,              0}
    };
    cout << argc << endl;
    while (true) {
        char c = getopt_long(argc, argv, short_options, long_options, NULL);
        if (c == -1)break;
        cout << c << "\t" << optarg << endl;
    }

    size_t m, n, x1, x2, y1, y2;
    bool verbose = true;
    cin >> n >> m >> y1 >> x1 >> y2 >> x2;

    Point **grid = new Point *[m];
    for (size_t i = 0; i < m; i++) {
        grid[i] = new Point[n];
        for (size_t j = 0; j < n; j++) {
            auto &p = grid[i][j];
            cin >> p.weight;
            p.cost = p.weight;
            p.x = i;
            p.y = j;
        }
    }

    priority_queue<Point, Point::compare_t> *queue = new binary_heap<Point, Point::compare_t>();
    auto &start = grid[x1][y1];
    auto &end = grid[x2][y2];
    start.reached = true;
    queue->enqueue(start);

    size_t step = 0;
    const int DIR_X[4] = {0, 1, 0, -1};
    const int DIR_Y[4] = {1, 0, -1, 0};

    while (!queue->empty()) {
        auto C = queue->dequeue_min();
        if (verbose) {
            cout << "Step " << step << endl;
            cout << "Choose cell " << C << " with accumulated length " << C.cost << "." << endl;
        }
        step++;
        for (int i = 0; i < 4; i++) {
            auto x = C.x + DIR_X[i];
            auto y = C.y + DIR_Y[i];
            if (x < 0 || x >= m || y < 0 || y >= n) continue;
            auto &N = grid[x][y];
            if (N.reached) continue;
            N.cost += C.cost;
            N.reached = true;
            N.predecessor = &grid[C.x][C.y];
            if (N.x == x2 && N.y == y2) {
                if (verbose) {
                    cout << "Cell " << N << " with the accumulated length " << N.cost << " is the ending point."
                         << endl;
                }
                cout << "The shortest path from " << start << " to " << end << " is " << N.cost << "." << endl;
                cout << "Path:" << endl;
                print_path(N);
                return 0;
            } else {
                queue->enqueue(N);
                if (verbose) {
                    cout << "Cell " << N << " with the accumulated length " << N.cost << " is added into the queue."
                         << endl;
                }
            }
        }
    }

    for (size_t i = 0; i < m; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}


