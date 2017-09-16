//
// Created by liu on 2017/9/16.
//

#ifndef PROJECT_MARKET_H
#define PROJECT_MARKET_H

#include <unordered_map>
#include <string>
#include <sstream>
#include "Stock.h"

class Market {

private:
    std::unordered_map<std::string, Stock> stocks;
    std::stringstream ss;
    size_t timestamp;

    void nextDay();

public:
    Market();

    void readLine(const std::string &line);

};


#endif //PROJECT_MARKET_H
