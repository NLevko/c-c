#include <iostream>
#include <algorithm>    
#include <vector>
#include <unordered_set>

using namespace std;

struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    unordered_set<vector<int>, VectorHash> sets;

    for(int i = 0; i < n; ++i){
        vector<int> v(m);
        for(int j = 0; j < m; ++j){
            cin >> v[j];
        }
        sort(v.begin(), v.end());
        sets.insert(v);
    }

    for(int i = 0; i < k; ++i){
        vector<int> example(m);
        for(int j = 0; j < m; ++j){
            cin >> example[j];
        }
        sort(example.begin(), example.end());
        if(sets.find(example) != sets.end()){
            cout << "1\n";
        }else{
            cout << "0\n";
        }
    }
    return 0;
}
