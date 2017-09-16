//
// Created by liu on 2017/9/16.
//

#include "Market.h"

Market::Market() {
    this->timestamp = 0;
}

void Market::nextDay() {
    this->timestamp++;

}

void Market::readLine(const std::string &line) {
    this->ss.clear();
    this->ss.str(line);
    int timestamp, price, quantity, duration;
    std::string name, role, price_str, quantity_str;
    ss >> timestamp >> name >> role >> price_str >> quantity_str >> duration;
    price = strtol(price_str.c_str() + 1, NULL, 10);
    duration = strtol(quantity_str.c_str() + 1, NULL, 10);

    while (timestamp > this->timestamp) nextDay();


}

