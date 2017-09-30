<<<<<<< Updated upstream
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
=======
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

void Stock::addTrade(bool isSell, trade_t &trade, size_t timestamp)
{
    try
    {
        trade_t buy, sell;
        size_t price;
        if (isSell)
        {
            sell = trade;
            buy = getHighestBuy(timestamp);
            if (buy.price >= sell.price)
            {
                price = buy.price;
                this->_buyQueue.pop();
            } else
            {
                this->_sellQueue.push(trade);
            }
        } else
        {
            buy = trade;
            sell = getLowestSell(timestamp);
            if (buy.price >= sell.price)
            {
                price = sell.price;
                this->_sellQueue.pop();
            } else
            {
                this->_buyQueue.push(trade);
            }
        }
        if (buy.price >= sell.price)
        {
            this->_buyQueue.pop();
            this->_sellQueue.pop();
            size_t price = sell.id > buy.id ? buy.price : sell.price;
            size_t quantity;
            if (buy.quantity > sell.quantity)
            {
                quantity = sell.quantity;
                buy.quantity -= sell.quantity;
                this->_buyQueue.push(buy);
            } else if (buy.quantity < sell.quantity)
            {
                quantity = buy.quantity;
                sell.quantity -= buy.quantity;
                this->_sellQueue.push(sell);
            } else
            {
                quantity = sell.quantity;
            }
            if (verbose)
            {
                std::cout << buy.client->name() << " purchased " << quantity << " shares of " << this->_name << " from "
                          << sell.client->name() << " for $" << price << "/share" << std::endl;
            }
            return true;
        }
        return false;
    } catch (QueueEmptyException &e)
    {
        return false;
    }


}

bool Stock::match(size_t timestamp, bool verbose)
{
    try
    {
        auto buy = getHighestBuy(timestamp);
        auto sell = getLowestSell(timestamp);
        if (buy.price >= sell.price)
        {
            this->_buyQueue.pop();
            this->_sellQueue.pop();
            size_t price = sell.id > buy.id ? buy.price : sell.price;
            size_t quantity;
            if (buy.quantity > sell.quantity)
            {
                quantity = sell.quantity;
                buy.quantity -= sell.quantity;
                this->_buyQueue.push(buy);
            } else if (buy.quantity < sell.quantity)
            {
                quantity = buy.quantity;
                sell.quantity -= buy.quantity;
                this->_sellQueue.push(sell);
            } else
            {
                quantity = sell.quantity;
            }
            if (verbose)
            {
                std::cout << buy.client->name() << " purchased " << quantity << " shares of " << this->_name << " from "
                          << sell.client->name() << " for $" << price << "/share" << std::endl;
            }
            return true;
        }
        return false;
    } catch (QueueEmptyException &e)
    {
        return false;
    }
}

const Stock::trade_t &Stock::getHighestBuy(size_t timestamp)
{
    while (!this->_buyQueue.empty())
    {
        auto &trade = this->_buyQueue.top();
        if (trade.expire > 0 && trade.expire <= timestamp)
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
        if (trade.expire > 0 && trade.expire <= timestamp)
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
>>>>>>> Stashed changes
