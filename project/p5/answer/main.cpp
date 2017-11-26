//
// Created by liu on 17-11-25.
//

#include <list>
#include <vector>
#include <queue>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <algorithm>

struct node {
    std::vector<std::pair<node *, int>> neighbor;
    bool visited = false;
    size_t id;
    int cost = -1;
    node *predecessor = nullptr;
    size_t degree = 0;

    node(size_t id) : id(id) {}

    struct comp {
        bool operator()(const node *a, const node *b) {
            if (a->cost == b->cost) return a->id < b->id;
            return a->cost < b->cost;
        };
    };
};

struct graph {
    std::vector<std::unique_ptr<node> > nodes;
};

void print_path(node *n) {
    if (!n) return;
    print_path(n->predecessor);
    std::cout << n->id << " ";
}

int main(int argc, char *argv[]) {
    std::fstream fin;
    std::istringstream ss;
    if (argc > 1) {
        fin.open(argv[1]);
        if (fin.is_open()) {
            std::cin.rdbuf(fin.rdbuf());
        }
    }
    size_t N, srcId, destId;
    std::cin >> N >> srcId >> destId;

    graph g{};
    g.nodes.reserve(N);
    for (int i = 0; i < N; ++i) {
        g.nodes.emplace_back(std::make_unique<node>(i));
    }

    while (!std::cin.eof()) {
        size_t src, dest, weight;
        std::string str;
        std::getline(std::cin, str);
        if (str.empty()) continue;
        ss.clear();
        ss.str(str);
        ss >> src >> dest >> weight;
        auto srcNode = g.nodes[src].get();
        auto destNode = g.nodes[dest].get();
        srcNode->neighbor.emplace_back(destNode, weight);
        ++destNode->degree;
    }

    std::set<node *, node::comp> set;
    std::queue<node *> queue;

    for (auto &item : g.nodes) {
        std::sort(item->neighbor.begin(), item->neighbor.end(),
                  [](const std::pair<node *, int> &a, std::pair<node *, int> &b) {
                      return a.second < b.second;
                  }
        );
        if (item->degree == 0) {
            queue.push(item.get());
        }
    }


    auto srcNode = g.nodes[srcId].get();
    auto destNode = g.nodes[destId].get();

    srcNode->cost = 0;
    set.emplace(srcNode);
    while (!destNode->visited && !set.empty()) {
        auto now = *(set.begin());
        set.erase(set.begin());
        now->visited = true;
        for (auto &item : now->neighbor) {
            auto neighbor = item.first;
            if (!neighbor->visited) {
                auto newCost = now->cost + item.second;
                if (neighbor->cost < 0) {
                    neighbor->cost = newCost;
                    neighbor->predecessor = now;
                    set.emplace(neighbor);
                } else if (neighbor->cost > newCost) {
                    set.erase(neighbor);
                    neighbor->cost = newCost;
                    neighbor->predecessor = now;
                    set.emplace(neighbor);
                }
            }
        }
    }

    if (destNode->visited && destNode->predecessor) {
        std::cout << "Shortest path length is " << destNode->cost << std::endl;
        std::cout << "Shortest path is ";
        print_path(destNode);
        std::cout << std::endl;
    } else {
        std::cout << "No path exists!" << std::endl;
    }

    std::list<node *> list;
    while (!queue.empty()) {
        auto now = queue.front();
        queue.pop();
        list.emplace_back(now);
        for (auto &item : now->neighbor) {
            auto neighbor = item.first;
            if (neighbor->degree > 0) {
                --neighbor->degree;
            }
            if (neighbor->degree == 0) {
                queue.push(neighbor);
            }
        }
    }

    if (list.size() == N) {
        std::cout << "The graph is a DAG" << std::endl;
    } else {
        std::cout << "The graph is not a DAG" << std::endl;
    }

    return 0;
}
