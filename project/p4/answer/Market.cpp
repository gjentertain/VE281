//
// Created by liu on 2017/9/16.
//

#include <iostream>
#include "Market.h"

Market::Market()
{
    this->timestamp = 0;
    this->tradeNum = 0;
}

Client *Market::getClient(const std::string &name)
{
    auto it = this->clients.find(name);
    if (it == this->clients.end())
    {
        auto client = new Client(name);
        this->clients.insert({name, client});
        it = this->clients.find(name);
    }
    return it->second;
}

Stock *Market::getStock(const std::string &name)
{
    auto it = this->stocks.find(name);
    if (it == this->stocks.end())
    {
        auto stock = new Stock(name);
        this->stocks.insert({name, stock});
        it = this->stocks.find(name);
    }
    return it->second;
}

void Market::readLine(const std::string &line)
{
    this->ss.clear();
    this->ss.str(line);
    size_t timestamp, price, quantity;
    int duration;
    std::string clientName, action, stockName, priceStr, quantityStr;
    ss >> timestamp >> clientName >> action >> stockName >> priceStr >> quantityStr >> duration;

    while (timestamp > this->timestamp) nextTick();

    price = strtoul(priceStr.c_str() + 1, NULL, 10);
    quantity = strtoul(quantityStr.c_str() + 1, NULL, 10);

    auto client = this->getClient(stockName);
    auto stock = this->getStock(stockName);

    int expire = duration >= 0 ? (int) (timestamp + duration) : -1;
    if (action == "SELL")
    {
        stock->addSell(client, tradeNum++, price, quantity, expire);
    } else
    {
        stock->addBuy(client, tradeNum++, price, quantity, expire);
    }

}

void Market::nextTick()
{
//    std::cout << this->timestamp << std::endl;
    for (auto &pair:this->stocks)
    {
        pair.second->printMidPoint(this->timestamp);
    }
    this->timestamp++;
}
