//
// Created by liu on 17-8-31.
//

#include <fstream>
#include <sstream>
#include <functional>

using namespace std;

void generate(const string &filename, const size_t n)
{
    hash<string> str_hash;
    auto seed = str_hash(filename);
    ofstream out(filename, ios::binary);
    srand48(seed);
    for (int i = 0; i < n; i++)
    {
        auto num = (int) mrand48();
        out.write((char *) &num, sizeof(int));
    }
    out.close();
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        ostringstream ss;
        ss << "./data/" << i << ".bin";
        generate(ss.str(), 10000);
    }
    return 0;
}