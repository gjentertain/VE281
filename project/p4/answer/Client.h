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
public:
    explicit Client(const std::string &name);

    const std::string &name();
};


#endif //PROJECT_CLIENT_H
