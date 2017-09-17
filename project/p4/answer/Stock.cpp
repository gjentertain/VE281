//
// Created by liu on 2017/9/16.
//

#include <iostream>
#include "Stock.h"

Stock::Stock(const std::string &name)
{
    this->_name = name;
}

const std::string &Stock::name()
{
    return this->_name;
}

void Stock::addBuy(Client *client, size_t id, size_t price, size_t quantity, int expire)
{
    trade_t trade{client, id, price, quantity, expire};
    this->_buyQueue.push(trade);
}

void Stock::addSell(Client *client, size_t id, size_t price, size_t quantity, int expire)
{
    trade_t trade{client, id, price, quantity, expire};
    this->_sellQueue.push(trade);
}

void Stock::match(size_t timestamp)
{
    try
    {
        auto buy = getHighestBuy(timestamp);
        auto sell = getLowestSell(timestamp);
        if (buy.price >= sell.price)
        {
            
        }
    } catch (QueueEmptyException &e)
    {
    }
}

const Stock::trade_t &Stock::getHighestBuy(size_t timestamp)
{
    while (!this->_buyQueue.empty())
    {
        auto &trade = this->_buyQueue.top();
        if (trade.expire > 0 && trade.expire < timestamp)
        {
            this->_buyQueue.pop();
        } else
        {
            return trade;
        }
    }
    throw QueueEmptyException();
}

const Stock::trade_t &Stock::getLowestSell(size_t timestamp)
{
    while (!this->_sellQueue.empty())
    {
        auto &trade = this->_sellQueue.top();
        if (trade.expire > 0 && trade.expire < timestamp)
        {
            this->_sellQueue.pop();
        } else
        {
            return trade;
        }
    }
    throw QueueEmptyException();
}

void Stock::printMidPoint(size_t timestamp)
{
    std::cout << "Midpoint of " << this->_name << " at time " << timestamp << " is ";
    try
    {
        auto buy = getHighestBuy(timestamp);
        auto sell = getLowestSell(timestamp);
        std::cout << (buy.price + sell.price) / 2;
    } catch (QueueEmptyException &e)
    {
        std::cout << "undefined";
    }
    std::cout << std::endl;
}
