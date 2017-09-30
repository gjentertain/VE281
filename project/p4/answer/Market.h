//
// Created by liu on 2017/9/16.
//

#ifndef PROJECT_MARKET_H
#define PROJECT_MARKET_H

#include <unordered_map>
#include <string>
#include <sstream>
#include "Stock.h"
#include "Client.h"

class Market
{

private:
    std::unordered_map<std::string, Stock*> stocks;
    std::unordered_map<std::string, Client*> clients;
    std::stringstream ss;
    size_t timestamp, tradeNum;

public:
    Market();

    Client* getClient(const std::string &name);

    Stock* getStock(const std::string &name);

    void readLine(const std::string &line);

    void nextTick();
};


#endif //PROJECT_MARKET_H
