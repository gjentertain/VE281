//
// Created by liu on 2017/9/15.
//

#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

#include "binary_heap.h"
#include "unsorted_heap.h"
#include "fib_heap.h"

using namespace std;

class Point {
public:
    size_t x, y;
    size_t weight, cost = 0;
    bool reached = false;
    Point *predecessor = NULL;

    struct ptr_compare_t {
        bool operator()(const Point *a, const Point *b) const {
            if (a->cost != b->cost) return a->cost < b->cost;
            if (a->y != b->y) return a->y < b->y;
            return a->x < b->x;
        }
    };

    friend ostream &operator<<(ostream &out, const Point &p) {
        out << "(" << p.y << ", " << p.x << ")";
        return out;
    }

    Point() = default;

    ~Point() = default;
};

void print_path(ostream &out, const Point &p) {
    if (p.predecessor) print_path(out, *(p.predecessor));
    out << p << endl;
}

int main(int argc, char *argv[]) {
    bool verbose = false;
    string impl;
    while (true) {
        const option long_options[] = {
                {"verbose",        no_argument,       NULL, 'v'},
                {"implementation", required_argument, NULL, 'i'},
                {0, 0, 0,                                   0}
        };
        int c = getopt_long(argc, argv, "vi:", long_options, NULL);
        if (c == -1)break;
        if (c == 'v') {
            verbose = true;
        } else if (c == 'i') {
            impl = optarg;
        }
    }

    priority_queue<Point *, Point::ptr_compare_t> *queue;
    if (impl == "BINARY") queue = new binary_heap<Point *, Point::ptr_compare_t>();
    else if (impl == "UNSORTED") queue = new unsorted_heap<Point *, Point::ptr_compare_t>();
    else if (impl == "FIBONACCI") queue = new fib_heap<Point *, Point::ptr_compare_t>();
    else return 0;

    if (argc < optind) return 0;

    ifstream fin;
    ofstream fout;

    if (argc >= optind + 4) {
        if (string(argv[optind + 2]) == "<") {
            fin.open(argv[optind + 3]);
            cin.rdbuf(fin.rdbuf());
        } else if (string(argv[optind + 2]) == ">") {
            fout.open(argv[optind + 3]);
            cout.rdbuf(fout.rdbuf());
        }
    }
    if (argc >= optind + 2) {
        if (string(argv[optind]) == "<") {
            fin.open(argv[optind + 1]);
            cin.rdbuf(fin.rdbuf());
        } else if (string(argv[optind]) == ">") {
            fout.open(argv[optind + 1]);
            cout.rdbuf(fout.rdbuf());
        }
    }

    size_t m, n, x1, x2, y1, y2;
    cin >> n >> m >> y1 >> x1 >> y2 >> x2;

    Point **grid = new Point *[m];
    for (size_t i = 0; i < m; i++) {
        grid[i] = new Point[n];
        for (size_t j = 0; j < n; j++) {
            auto p = &grid[i][j];
            cin >> p->weight;
            p->cost = p->weight;
            p->x = i;
            p->y = j;
        }
    }

    auto start = &grid[x1][y1];
    auto end = &grid[x2][y2];
    start->reached = true;
    queue->enqueue(start);

    size_t step = 0;
    const int DIR_X[4] = {0, 1, 0, -1};
    const int DIR_Y[4] = {1, 0, -1, 0};

    while (!queue->empty()) {
        auto C = queue->dequeue_min();
        if (verbose) {
            cout << "Step " << step << endl;
            cout << "Choose cell " << *C << " with accumulated length " << C->cost << "." << endl;
        }
        step++;
        for (int i = 0; i < 4; i++) {
            auto x = C->x + DIR_X[i];
            auto y = C->y + DIR_Y[i];
            if (x < 0 || x >= m || y < 0 || y >= n) continue;
            auto N = &grid[x][y];
            if (N->reached) continue;
            N->cost += C->cost;
            N->reached = true;
            N->predecessor = &grid[C->x][C->y];
            if (N->x == x2 && N->y == y2) {
                if (verbose) {
                    cout << "Cell " << *N << " with accumulated length " << N->cost << " is the ending point."
                         << endl;
                }
                cout << "The shortest path from " << *start << " to " << *end << " is " << N->cost << "." << endl;
                cout << "Path:" << endl;
                print_path(cout, *N);
                for (size_t i = 0; i < m; i++) {
                    delete[] grid[i];
                }
                delete[] grid;
                delete queue;
                fin.close();
                fout.close();
                return 0;
            } else {
                queue->enqueue(N);
                if (verbose) {
                    cout << "Cell " << *N << " with accumulated length " << N->cost << " is added into the queue."
                         << endl;
                }
            }
        }
    }
    for (size_t i = 0; i < m; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    delete queue;
    fin.close();
    fout.close();
    return 0;
}


