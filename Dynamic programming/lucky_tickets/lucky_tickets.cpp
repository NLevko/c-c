#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

typedef long long ll;

int const mod = int(1e9);
vector<ll> dp[2][3005];


void showNum(const vector<ll> &vec) {
    cout << vec[vec.size() - 1];
    for(int i = vec.size() - 2; i >= 0; --i) {
        vector<int> digits;
        ll var = vec[i];
        while(var > 0){
            digits.push_back(var % 10);
            var /= 10;
        }
        while(digits.size() < 9) {
            digits.push_back(0);
        }
        for(int j = digits.size() - 1; j >= 0; --j){
            cout << digits[j];
        }
    }
}

void sumN(vector<ll> &first, const vector<ll> &second){
    while(first.size() < second.size()) {
        first.push_back(0);
    }
    int n = max(first.size(), second.size());
    ll c = 0;
    for(int i = 0; i < n; ++i) {

        if(i < second.size())
            first[i] += second[i];
        first[i] += c;
        c = first[i] / mod;
        first[i] %= mod;
    }
    if(c > 0){
        first.push_back(c);
    }
}

void multN(const vector<ll> &first, const vector<ll> &second, vector<ll> &result){
    for(int i = 0; i < first.size(); ++i) {
        vector<ll> cur;
        for(int j = 0; j < i; ++j)
            cur.push_back(0);
        ll c = 0;
        for(int j = 0; j < second.size(); ++j) {
            ll multd = first[i] * second[j] + c;
            cur.push_back(multd % mod);
            c = multd / mod;
        }
        if(c > 0) {
            cur.push_back(c);
        }
        while(cur.size() > 1 && cur.back() == 0) {
            cur.pop_back();
        }
        sumN(result, cur);
    }

}


int main()
{

    int n, m;
    cin >> n >> m;


    dp[0][0].push_back(1);

    for(int i = 1; i <= n / 2; ++i) {
        for(int j = 0; j <= (m - 1) * i; ++j) {
            dp[1][j].push_back(0);
            for(int k = 0; k < m; ++k) {
                if((i - 1) * (m - 1) >= j - k && j - k >= 0){
                    sumN(dp[1][j], dp[0][j - k]);
                }
            }
        }
        for(int j = 0; j <= (m - 1) * i; ++j) {
            swap(dp[1][j], dp[0][j]);
            dp[1][j].clear();
        }
    }
    vector<ll> result(1, 0);
    for(int i = 0; i <= (m - 1) * (n / 2); ++i) {
        multN(dp[0][i], dp[0][i], result);
    }
    showNum(result);
    cout << endl;


    return 0;
}
