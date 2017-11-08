//
// Created by liu on 2017/9/16.
//

#include <iostream>
#include "Stock.h"
#include "Market.h"

Stock::Stock(const std::string &name) {
    this->_name = name;
}

Stock::~Stock() {
    for (auto &item : _timeTraveler) {
        delete item;
    }
}

const std::string &Stock::name() const {
    return this->_name;
}

void
Stock::addBuy(Client *client, size_t id, size_t price, size_t quantity, int expire, size_t timestamp, bool verbose) {
    auto trade = new trade_t{client, timestamp, id, price, quantity, this, false};
    _timeTraveler.push_back(trade);
    while (matchBuy(trade, verbose)) {}
    if (expire != 0 && trade->quantity > 0) {
        this->_buySet.insert(trade);
        if (expire > 0) {
            Market::getInstance().addExpiringTrade(trade, (size_t) expire);
        }
    }
}

void
Stock::addSell(Client *client, size_t id, size_t price, size_t quantity, int expire, size_t timestamp, bool verbose) {
    auto trade = new trade_t{client, timestamp, id, price, quantity, this, true};
    _timeTraveler.push_back(trade);
    while (matchSell(trade, verbose)) {}
    if (expire != 0 && trade->quantity > 0) {
        this->_sellSet.insert(trade);
        if (expire > 0) {
            Market::getInstance().addExpiringTrade(trade, (size_t) expire);
        }
    }
}

bool Stock::matchBuy(trade_t *buy, bool verbose) {
    if (buy->quantity == 0) return false;
    auto sell = getLowestSell();
    if (!sell) return false;
    if (buy->price < sell->price) return false;
    size_t price = sell->price;
    size_t quantity;
    if (buy->quantity > sell->quantity) {
        quantity = sell->quantity;
        buy->quantity -= sell->quantity;
        this->removeLowestSell();
    } else if (buy->quantity < sell->quantity) {
        quantity = buy->quantity;
        sell->quantity -= buy->quantity;
        buy->quantity = 0;
    } else {
        quantity = sell->quantity;
        buy->quantity = 0;
        this->removeLowestSell();
    }
    _median.add(price);
    buy->client->buy(quantity, price);
    sell->client->sell(quantity, price);
    Market::getInstance().trade(quantity, price);
    if (verbose) {
        std::cout << buy->client->name() << " purchased " << quantity << " shares of " << this->_name << " from "
                  << sell->client->name() << " for $" << price << "/share" << std::endl;
    }
    return true;
}

bool Stock::matchSell(trade_t *sell, bool verbose) {
    if (sell->quantity == 0) return false;
    auto buy = getHighestBuy();
    if (!buy) return false;
    if (buy->price < sell->price) return false;
    size_t price = buy->price;
    size_t quantity;
    if (buy->quantity > sell->quantity) {
        quantity = sell->quantity;
        buy->quantity -= sell->quantity;
        sell->quantity = 0;
    } else if (buy->quantity < sell->quantity) {
        quantity = buy->quantity;
        sell->quantity -= buy->quantity;
        this->removeHighestBuy();
    } else {
        quantity = sell->quantity;
        sell->quantity = 0;
        this->removeHighestBuy();
    }
    _median.add(price);
    buy->client->buy(quantity, price);
    sell->client->sell(quantity, price);
    Market::getInstance().trade(quantity, price);
    if (verbose) {
        std::cout << buy->client->name() << " purchased " << quantity << " shares of " << this->_name << " from "
                  << sell->client->name() << " for $" << price << "/share" << std::endl;
    }
    return true;
}

Stock::trade_t *Stock::getHighestBuy() const {
    if (_buySet.empty()) return nullptr;
    return *(_buySet.begin());
}

Stock::trade_t *Stock::getLowestSell() const {
    if (_sellSet.empty()) return nullptr;
    return *(_sellSet.begin());
}

void Stock::removeHighestBuy() {
    if (!_buySet.empty()) _buySet.erase(_buySet.begin());
}

void Stock::removeLowestSell() {
    if (!_sellSet.empty()) _sellSet.erase(_sellSet.begin());
}

void Stock::removeExpiredTrade(trade_t *trade) {
    if (trade->isSell) {
        _sellSet.erase(trade);
    } else {
        _buySet.erase(trade);
    }
}

void Stock::printMedian(size_t timestamp) const {
    if (_median.empty()) return;
    std::cout << "Median match price of " << _name << " at time " << timestamp << " is $" << _median.get() << std::endl;
}

void Stock::printMidPoint(size_t timestamp) const {
    std::cout << "Midpoint of " << _name << " at time " << timestamp << " is ";
    auto buy = getHighestBuy();
    auto sell = getLowestSell();
    if (buy && sell) {
        std::cout << "$" << (buy->price + sell->price) / 2;
    } else {
        std::cout << "undefined";
    }
    std::cout << std::endl;
}

void Stock::printTimeTraveler() const {
    int sellPrice = -1, sellTime = -1, buyTime = -1, profit = 0;
    int minSell = -1, minSellTime = -1;
    for (const auto &trade : _timeTraveler) {
        if (trade->isSell) {
            if (minSell < 0 || minSell > trade->price) {
                minSell = (int) trade->price;
                minSellTime = (int) trade->timestamp;
            }
        } else {
            if (minSell < 0) continue;
            int diff = (int) trade->price - minSell;
            if (sellPrice == -1 || diff > profit) {
                sellPrice = minSell;
                sellTime = minSellTime;
                buyTime = (int) trade->timestamp;
                profit = diff;
            }
        }
    }
    // variable name error, won't fix
    std::cout << "Time travelers would buy " << _name << " at time: " << sellTime
              << " and sell it at time: " << buyTime << std::endl;
}

