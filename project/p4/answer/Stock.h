//
// Created by liu on 2017/9/16.
//

#ifndef PROJECT_STOCK_H
#define PROJECT_STOCK_H

#include <string>
#include <queue>
#include <exception>
#include "Client.h"

class Stock
{
private:
    struct trade_t
    {
        Client *client;
        size_t id, price, quantity;
        int expire;

        trade_t &operator=(const trade_t &that)
        {
            if (this == &that) return *this;
            this->client = that.client;
            this->id = that.id;
            this->price = that.price;
            this->quantity = that.quantity;
        }
    };

    struct trade_compare_buy
    {
        bool operator()(const trade_t &a, const trade_t &b) const
        {
            if (a.price == b.price) return a.id > b.id;
            return a.price < b.price;
        }
    };

    struct trade_compare_sell
    {
        bool operator()(const trade_t &a, const trade_t &b) const
        {
            if (a.price == b.price) return a.id > b.id;
            return a.price > b.price;
        }
    };

    class QueueEmptyException : public std::exception
    {
    };

    std::string _name;
    std::priority_queue<trade_t, std::vector<trade_t>, trade_compare_buy> _buyQueue;
    std::priority_queue<trade_t, std::vector<trade_t>, trade_compare_sell> _sellQueue;


public:
    explicit Stock(const std::string &name);

    const std::string &name();

    void addSell(Client *client, size_t id, size_t price, size_t quantity, int duration);

    void addBuy(Client *client, size_t id, size_t price, size_t quantity, int duration);

    void match(size_t timestamp);

    const trade_t &getHighestBuy(size_t timestamp);

    const trade_t &getLowestSell(size_t timestamp);

    void printMidPoint(size_t timestamp);
};


#endif //PROJECT_STOCK_H
