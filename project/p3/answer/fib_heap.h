#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include <list>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap : public priority_queue<TYPE, COMP> {
public:
    typedef unsigned size_type;

    // EFFECTS: Construct an empty heap with an optional comparison functor.
    //          See test_heap.cpp for more details on functor.
    // MODIFIES: this
    // RUNTIME: O(1)
    fib_heap(COMP comp = COMP());

    // EFFECTS: Add a new element to the heap.
    // MODIFIES: this
    // RUNTIME: O(1)
    virtual void enqueue(const TYPE &val);

    // EFFECTS: Remove and return the smallest element from the heap.
    // REQUIRES: The heap is not empty.
    // MODIFIES: this
    // RUNTIME: Amortized O(log(n))
    virtual TYPE dequeue_min();

    // EFFECTS: Return the smallest element of the heap.
    // REQUIRES: The heap is not empty.
    // RUNTIME: O(1)
    virtual const TYPE &get_min() const;

    // EFFECTS: Get the number of elements in the heap.
    // RUNTIME: O(1)
    virtual size_type size() const;

    // EFFECTS: Return true if the heap is empty.
    // RUNTIME: O(1)
    virtual bool empty() const;

private:
    // Note: compare is a functor object
    COMP compare;

private:
    // Add any additional member functions or data you require here.
    // You may want to define a strcut/class to represent nodes in the heap and a
    // pointer to the min node in the heap.
    struct node {
        TYPE val;
        unsigned depth = 0;
        std::list<node> child;

        explicit node(const TYPE &val) {
            this->val = val;
        }
    };

    typename std::list<node> root;
    typename std::list<node>::iterator min;
    unsigned num_elements = 0;
    const TYPE &default_element = TYPE();
};

// Add the definitions of the member functions here. Please refer to
// binary_heap.h for the syntax.

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP>::fib_heap(COMP comp) {
    compare = comp;
    min = root.begin();
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::enqueue(const TYPE &val) {
    if (root.empty()) {
        root.push_front(std::move(node(val)));
        min = root.begin();
    } else if (compare(val, min->val)) {
        min = root.insert(min, std::move(node(val)));
    } else {
        root.insert(min, std::move(node(val)));
    }
    num_elements++;
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP>::dequeue_min() {
    if (this->empty()) return default_element;
    num_elements--;
    auto temp = min->val;

    if (num_elements == 0) {
        root.clear();
        return temp;
    }

    root.splice(min, min->child);
    min = root.erase(min);
    if (min == root.end()) {
        min = root.begin();
    }

    auto it = min;
    auto size = (unsigned) (log(num_elements) / log(1.618)) + 1;
    bool isset[size] = {0};
    typename std::list<node>::iterator arr[size];

    auto root_size = root.size();
    for (auto i = 0; i < root_size; i++) {
        if (it == root.end()) it = root.begin();
        bool flag = true;
        auto now = it;
        unsigned depth = now->depth;
        while (isset[depth]) {
            if (compare(now->val, arr[depth]->val)) {
                now->child.push_front(std::move(*arr[depth]));
                root.erase(arr[depth]);
            } else {
                arr[depth]->child.push_front(std::move(*now));
                if (now == it) {
                    it = root.erase(now);
                    flag = false;
                } else {
                    root.erase(now);
                }
                now = arr[depth];
            }
            isset[depth] = false;
            depth++;
            now->depth++;
        }
        isset[depth] = true;
        if (now == root.end()) now = root.begin();
        arr[depth] = now;
        if (flag) ++it;
    }
    min = std::min_element(root.begin(), root.end(), [this](const node &a, const node &b) {
        return compare(a.val, b.val);
    });
    return temp;
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP>::get_min() const {
    // Fill in the body.
    if (this->empty()) return default_element;
    return min->val;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP>::empty() const {
    // Fill in the body.
    return this->size() == 0;
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP>::size() const {
    // Fill in the body.
    return this->num_elements;
}

#endif //FIB_HEAP_H
