//
// Created by liu on 17-11-8.
//

#ifndef PROJECT_MEDIAN_H
#define PROJECT_MEDIAN_H

#include <queue>
#include <functional>

template<typename TYPE>
struct MedianAverage {
    std::plus<TYPE> plus = std::plus<TYPE>();
    std::divides<TYPE> divides = std::divides<TYPE>();
    const TYPE operator()(const TYPE &a, const TYPE &b) const {
        return divides(plus(a, b), TYPE(2));
    }
};

template<typename TYPE, typename AVERAGE = MedianAverage<TYPE>, typename COMP = std::less<TYPE>>
class Median {
public:
    typedef unsigned long size_type;
private:
    size_type size = 0;
    std::priority_queue<TYPE, std::vector<TYPE>, COMP> maxQueue;
    std::priority_queue<TYPE, std::vector<TYPE>, std::binary_negate<COMP> > minQueue;
    AVERAGE average;
public:
    explicit Median(AVERAGE average = AVERAGE(), COMP compare = COMP()) :
            average(average), maxQueue(compare), minQueue(std::binary_negate<COMP>(compare)) {}

    void add(TYPE val) {
        if (size % 2) {
            if (val >= maxQueue.top()) {
                minQueue.push(std::move(val));
            } else {
                TYPE temp = maxQueue.top();
                maxQueue.pop();
                minQueue.push(std::move(temp));
                maxQueue.push(std::move(val));
            }
        } else {
            if (maxQueue.empty()) {
                maxQueue.push(std::move(val));
            } else if (val <= minQueue.top()) {
                maxQueue.push(std::move(val));
            } else {
                TYPE temp = minQueue.top();
                minQueue.pop();
                maxQueue.push(std::move(temp));
                minQueue.push(std::move(val));
            }
        }
        ++size;
    };

    TYPE get() const {
        if (size % 2) {
            return maxQueue.top();
        } else {
            return average(maxQueue.top(), minQueue.top());
        }
    }

    bool empty() const {
        return size == 0;
    }

};

#endif //PROJECT_MEDIAN_H
