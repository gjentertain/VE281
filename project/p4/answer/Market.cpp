//
// Created by liu on 2017/9/16.
//

#include <iostream>
#include "Market.h"

Market::~Market() {
    for (auto &stock:this->stocks) {
        delete stock;
    }
    for (auto &client:this->clients) {
        delete client;
    }
}

Market &Market::getInstance() {
    static Market market;
    return market;
}

void Market::initOptions(bool verbose, bool median, bool midpoint, bool transfers) {
    this->verbose = verbose;
    this->median = median;
    this->midpoint = midpoint;
    this->transfers = transfers;
}

void Market::initTimeTraveler(std::string name) {
    timeTravelers.push_back(std::move(name));
}

Client *Market::getClient(const std::string &name) {
    auto it = this->clientsMap.find(name);
    if (it == this->clientsMap.end()) {
        auto client = new Client(name);
        this->clients.insert(client);
        it = this->clientsMap.insert({name, client}).first;
    }
    return it->second;
}

Stock *Market::getStock(const std::string &name) {
    auto it = this->stocksMap.find(name);
    if (it == this->stocksMap.end()) {
        auto stock = new Stock(name);
        this->stocks.insert(stock);
        it = this->stocksMap.insert({name, stock}).first;
    }
    return it->second;
}

void Market::readLine(const std::string &line) {
    this->ss.clear();
    this->ss.str(line);
    size_t timestamp, price, quantity;
    int duration;
    std::string clientName, action, stockName, priceStr, quantityStr;
    ss >> timestamp >> clientName >> action >> stockName >> priceStr >> quantityStr >> duration;

    if (timestamp > this->timestamp) nextTick(timestamp);

    price = strtoul(priceStr.c_str() + 1, NULL, 10);
    quantity = strtoul(quantityStr.c_str() + 1, NULL, 10);

    auto client = this->getClient(clientName);
    auto stock = this->getStock(stockName);

    /**
     * The expire time of stock
     * -1 : forever
     * 0  : instant
     * >0 : expire time
     */
    int expire = duration > 0 ? (int) (timestamp + duration) : duration;
    if (action == "SELL") {
        stock->addSell(client, tradeNum++, price, quantity, expire, this->timestamp, verbose);
    } else {
        stock->addBuy(client, tradeNum++, price, quantity, expire, this->timestamp, verbose);
    }
}

void Market::trade(size_t quantity, size_t price) {
    ++tradeComplete;
    shareTrade += quantity;
    auto temp = quantity * price;
    transferMoney += temp;
    commission += (temp / 100) * 2;
}

void Market::addExpiringTrade(Stock::trade_t *trade, size_t expire) {
    this->_expireMap.emplace(expire, trade);
}

void Market::removeExpiredTrade(size_t timestamp) {
    auto end = _expireMap.upper_bound(timestamp);
    for (auto it = _expireMap.begin(); it != end; ++it) {
        auto trade = it->second;
        trade->stock->removeExpiredTrade(trade);
    }
    _expireMap.erase(_expireMap.begin(), end);
}

void Market::printTickSummary() const {
    if (median) {
        for (auto &stock:this->stocks) {
            stock->printMedian(this->timestamp);
        }
    }
    if (midpoint) {
        for (auto &stock:this->stocks) {
            stock->printMidPoint(this->timestamp);
        }
    }
}

void Market::nextTick(size_t newTimestamp) {
    printTickSummary();
    removeExpiredTrade(newTimestamp);
    this->timestamp = newTimestamp;
}

void Market::printDaySummary() {
    std::cout << "---End of Day---" << std::endl;
    std::cout << "Commission Earnings: $" << commission << std::endl;
    std::cout << "Total Amount of Money Transferred: $" << transferMoney
              << std::endl;
    std::cout << "Number of Completed Trades: " << tradeComplete << std::endl;
    std::cout << "Number of Shares Traded: " << shareTrade << std::endl;
    if (transfers) {
        for (auto &client:this->clients) {
            client->printTransfer();
        }
    }
    for (auto &name: this->timeTravelers) {
        this->getStock(name)->printTimeTraveler();
    }
}

