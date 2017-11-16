//
// Created by liu on 2017/9/16.
//

#ifndef PROJECT_STOCK_H
#define PROJECT_STOCK_H

#include <string>
#include <queue>
#include <exception>
#include <set>
#include <unordered_map>
#include "Median.h"
#include "Client.h"

class Stock {
public:
    struct trade_t {
        Client *client;
        size_t timestamp, id, price, quantity;
        Stock *stock;
        bool isSell;
    };
private:
    struct trade_ptr_compare_buy {
        bool operator()(const trade_t *a, const trade_t *b) const {
            if (a->price == b->price) return a->id < b->id;
            return a->price > b->price;
        }
    };

    struct trade_ptr_compare_sell {
        bool operator()(const trade_t *a, const trade_t *b) const {
            if (a->price == b->price) return a->id < b->id;
            return a->price < b->price;
        }
    };

    std::string _name;

    std::set<trade_t *, trade_ptr_compare_buy> _buySet;
    std::set<trade_t *, trade_ptr_compare_sell> _sellSet;
    std::vector<trade_t *> _timeTraveler;

    Median<size_t> _median;

public:
    struct stock_ptr_compare {
        bool operator()(const Stock *a, const Stock *b) const {
            return a->_name < b->_name;
        }
    };

    explicit Stock(const std::string &name);

    ~Stock();

    const std::string &name() const;

    void addBuy(Client *client, size_t id, size_t price, size_t quantity, int expire, size_t timestamp, bool verbose);

    void addSell(Client *client, size_t id, size_t price, size_t quantity, int expire, size_t timestamp, bool verbose);

    bool matchBuy(trade_t *buy, bool verbose);

    bool matchSell(trade_t *sell, bool verbose);

    trade_t *getHighestBuy() const;

    trade_t *getLowestSell() const;

    void removeHighestBuy();

    void removeLowestSell();

    void removeExpiredTrade(trade_t *trade);

    void printMedian(size_t timestamp) const;

    void printMidPoint(size_t timestamp) const;

    void printTimeTraveler() const;
};


#endif //PROJECT_STOCK_H
