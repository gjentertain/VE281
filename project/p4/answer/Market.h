//
// Created by liu on 2017/9/16.
//

#ifndef PROJECT_MARKET_H
#define PROJECT_MARKET_H

#include <map>
#include <string>
#include <sstream>
#include "Stock.h"
#include "Client.h"

class Market {
private:
    std::map<std::string, Stock *> stocks;
    std::map<std::string, Client *> clients;
    std::multimap<size_t, Stock::trade_t *> _expireMap;
    std::stringstream ss;
    size_t timestamp = 0, tradeNum = 0;
    size_t commission = 0, transferMoney = 0;
    size_t tradeComplete = 0, shareTrade = 0;
    bool verbose = false;
    bool median = false;
    bool midpoint = false;
    bool transfers = false;
    std::vector<std::string> timeTravelers;
    Market() {};
public:
    ~Market();

    static Market &getInstance();

    void initOptions(bool verbose, bool median, bool midpoint, bool transfers);

    void initTimeTraveler(std::string name);

    Client *getClient(const std::string &name);

    Stock *getStock(const std::string &name);

    void readLine(const std::string &line);

    void trade(size_t quantity, size_t price);

    void addExpiringTrade(Stock::trade_t *trade, size_t expire);

    /**
     * Remove all expired trade before timestamp
     * @param timestamp
     */
    void removeExpiredTrade(size_t timestamp);

    void printTickSummary();

    void nextTick(size_t newTimestamp);

    void printDaySummary();
};


#endif //PROJECT_MARKET_H
