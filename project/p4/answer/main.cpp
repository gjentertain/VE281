//
// Created by liu on 2017/9/16.
//

#include <string>
#include <iostream>
#include "Market.h"

int main()
{
    Market market;
    std::string str;
    while (!std::cin.eof())
    {
        std::getline(std::cin, str);
        if (!str.empty()) market.readLine(str);
    }
    return 0;
}
