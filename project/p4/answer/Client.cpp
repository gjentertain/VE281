//
// Created by liu on 17-9-17.
//

#include <iostream>
#include "Client.h"

Client::Client(const std::string &name) {
    this->_name = name;
}

const std::string &Client::name() const {
    return this->_name;
}

void Client::buy(size_t quantity, size_t price) {
    _buyAmount += quantity;
    _transfer -= quantity * price;
}

void Client::sell(size_t quantity, size_t price) {
    _sellAmount += quantity;
    _transfer += quantity * price;
}

void Client::printTransfer() const {
    std::cout << _name << " bought " << _buyAmount << " and sold "
              << _sellAmount << " for a net transfer of $"
              << _transfer << std::endl;
}
