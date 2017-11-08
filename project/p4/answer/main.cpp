//
// Created by liu on 2017/9/16.
//

#include <string>
#include <iostream>
#include <fstream>
#include <getopt.h>
#include "Market.h"

int main(int argc, char *argv[]) {
    //std::ifstream fin("test.txt");
    //std::cin.rdbuf(fin.rdbuf());

    Market &market = Market::getInstance();

    bool verbose = false;
    bool median = false;
    bool midpoint = false;
    bool transfers = false;

    std::string impl;
    while (true) {
        const option long_options[] = {
                {"verbose",   no_argument,       NULL, 'v'},
                {"median",    no_argument,       NULL, 'm'},
                {"midpoint",  no_argument,       NULL, 'p'},
                {"transfers", no_argument,       NULL, 't'},
                {"ttt",       required_argument, NULL, 'g'},
                {0, 0, 0,                              0}
        };
        int c = getopt_long(argc, argv, "vmptg:", long_options, NULL);
        if (c == -1) break;
        switch (c) {
        case 'v':
            verbose = true;
            break;
        case 'm':
            median = true;
            break;
        case 'p':
            midpoint = true;
            break;
        case 't':
            transfers = true;
            break;
        case 'g':
            market.initTimeTraveler(optarg);
            break;
        default:
            break;
        }
    }

    market.initOptions(verbose, median, midpoint, transfers);

    std::string str;
    while (!std::cin.eof()) {
        std::getline(std::cin, str);
        if (!str.empty()) market.readLine(str);
    }
    market.printTickSummary();
    market.printDaySummary();
    return 0;
}
