//
// Created by liu on 17-9-17.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

#include <string>

class Client
{
private:
    std::string _name;
    int _transfer = 0;
    int _buyAmount = 0, _sellAmount = 0;
public:
    explicit Client(const std::string &name);

    const std::string &name();

    void buy(size_t quantity, size_t price);

    void sell(size_t quantity, size_t price);

    void printTransfer() const;
};


#endif //PROJECT_CLIENT_H
