//
// Created by liu on 17-9-3.
//

#ifndef P3_BENCHMARK_WRAPPER_H
#define P3_BENCHMARK_WRAPPER_H

#include <algorithm>
#include <memory>
#include <vector>
#include <queue>
#include "../answer/priority_queue.h"
#include "../answer/binary_heap.h"
#include "../answer/unsorted_heap.h"
#include "../answer/fib_heap.h"

template<typename TYPE, typename COMP = std::less<TYPE> >
class stl_heap : public priority_queue<TYPE, COMP> {
private:
    struct REVERSE_COMP {
        COMP compare;
        bool operator()(const TYPE &a, const TYPE &b) {
            return compare(b, a);
        }
    };

    std::priority_queue<TYPE, std::vector<TYPE>, REVERSE_COMP> queue;
    COMP compare;
public:
    typedef unsigned size_type;
    explicit stl_heap(COMP comp = COMP()) {
        queue = std::priority_queue<TYPE, std::vector<TYPE>, REVERSE_COMP>(REVERSE_COMP{comp});
    }
    virtual void enqueue(const TYPE &val) { queue.push(val); }
    virtual TYPE dequeue_min() {
        auto val = queue.top();
        queue.pop();
        return val;
    }
    virtual const TYPE &get_min() const { return queue.top(); }
    virtual size_type size() const { return queue.size(); }
    virtual bool empty() const { return queue.empty(); }
};

class Point {
public:
    typedef std::unique_ptr<Point> Ptr;

    size_t x = 0, y = 0;
    size_t weight = 0, cost = 0;
    bool reached = false;
    Point *predecessor = nullptr;

    struct ptr_compare_t {
        bool operator()(const Point *a, const Point *b) const {
            if (a->cost != b->cost) return a->cost < b->cost;
            if (a->y != b->y) return a->y < b->y;
            return a->x < b->x;
        }
    };

    Point() = default;
    ~Point() = default;
};

long path_test(int32_t type, int32_t n, int32_t m, const int32_t *data) {
    std::unique_ptr<priority_queue<Point *, Point::ptr_compare_t> > queue;
    switch (type) {
    case 0:
        queue = std::make_unique<binary_heap<Point *, Point::ptr_compare_t> >();
        break;
    case 1:
        queue = std::make_unique<unsorted_heap<Point *, Point::ptr_compare_t> >();
        break;
    case 2:
        queue = std::make_unique<fib_heap<Point *, Point::ptr_compare_t> >();
        break;
    case 3:
        queue = std::make_unique<stl_heap<Point *, Point::ptr_compare_t> >();
        break;
    default:
        return 0;
    }

    std::vector<std::vector<Point::Ptr> > grid(m);
    int k = 0;
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            auto p = std::make_unique<Point>();
            p->x = i;
            p->y = j;
            p->cost = p->weight = (size_t) data[k++];
            grid[i].push_back(std::move(p));
        }
    }

    const size_t x1 = 0, y1 = 0;
    const size_t x2 = m - 1, y2 = n - 1;

    const int DIR_X[4] = {0, 1, 0, -1};
    const int DIR_Y[4] = {1, 0, -1, 0};

    auto clock1 = clock();
    auto start = grid[x1][y1].get();
    start->reached = true;
    queue->enqueue(start);

    while (!queue->empty()) {
        auto C = queue->dequeue_min();
        for (int i = 0; i < 4; i++) {
            auto x = (int) C->x + DIR_X[i];
            auto y = (int) C->y + DIR_Y[i];
            if (x < 0 || x >= m || y < 0 || y >= n) continue;
            auto N = grid[x][y].get();
            if (N->reached) continue;
            N->cost += C->cost;
            N->reached = true;
            N->predecessor = grid[C->x][C->y].get();
            if (N->x == x2 && N->y == y2) {
                return clock() - clock1;
            } else {
                queue->enqueue(N);
            }
        }
    }
    return clock() - clock1;
}

#endif //P3_BENCHMARK_WRAPPER_H
