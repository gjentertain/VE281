//
// Created by liu on 17-9-17.
//

#include "Client.h"

Client::Client(const std::string &name)
{
    this->_name = name;
}

const std::string& Client::name()
{
    return this->_name;
}

