#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <climits>

using namespace std;
const int M = 80;
const int INF = INT_MAX >> 1;

int main() {
    string temp;
    getline(cin, temp);
    stringstream ss(temp);
    vector<string> words;
    vector<int> l;
    while (!ss.eof()) {
        string word;
        ss >> word;
        if (!word.empty()) {
            l.push_back(word.length());
            words.emplace_back(move(word));
        }
    }
    int n = words.size();
    vector<vector<int> > v(n, vector<int>(n, INF));
    vector<vector<int> > s(n, vector<int>(n, INF));
    vector<vector<int> > p(n, vector<int>(n, 0));
    for (int i=0;i<n;i++) {
        int sum = 0;
        for (int j=i;j<n;j++) {
            sum += l[j];
            int temp = M - j + i - sum;
            if (temp >= 0) {
                v[i][j] = temp * temp * temp;
            } else {
                break;
            }
        }
        if (v[i][n-1] != INF) v[i][n-1] = 0;
    }
    for (int i=0;i<n;i++) {
        s[0][i] = v[0][i];
    }
    for (int j=1;j<n;j++) {
        for (int i=j;i>=1;i--) {
            if (v[i][j] == INF) break;
            int min = INF;
            int last;
            for (int k=i-1;k>=0;k--) {
                if (s[k][i-1] == INF) break;
                if (s[k][i-1] < min) {
                    min = s[k][i-1];
                    last = k;
                }
            }
            if (min != INF) {
                s[i][j] = v[i][j] + min; 
                p[i][j] = last;
            }
        }
    }
    int min = INF;
    int begin, end = n-1;
    for (int i=0;i<n;i++) {
        if (s[i][n-1] < min) {
            min = s[i][n-1];
            begin = i;
        }
    }
    list<pair<int, int> > index;
    while (begin > 0) {
        index.push_front({begin, end});
        int temp = end;
        end = begin - 1;
        begin = p[begin][temp];
    }
    index.push_front({begin, end});
    for (const auto &item : index) {
        for (int i=item.first;i<=item.second;i++) {
            cout << words[i] << " ";
        }
        cout << endl;
    }
    cout << min << endl;
}
