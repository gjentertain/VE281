//
// Created by liu on 2017/9/16.
//

#ifndef PROJECT_STOCK_H
#define PROJECT_STOCK_H

#include <string>
#include <queue>

class Stock {

private:
    std::string name;
    std::priority_queue<int> sell_queue, buy_queue;

    void match();

public:
    Stock();

    void addSeller();

    void addBuyer();
};


#endif //PROJECT_STOCK_H
