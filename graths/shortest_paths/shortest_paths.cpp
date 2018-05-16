#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int main()
{

    int n, m, s;
    
    cin >> n >> m >> s;
    
    int dp[n + 1];

    for(int i = 0; i <= n; ++i){
        dp[i] = int(1e6);
    }

    dp[s] = 0;
    vector<pair<int, int>> edges;
    vector<int> weights;
    bool reachable[n + 1];
    memset(reachable, 0, sizeof(reachable));

    reachable[s] = 1;
    
    for(int i = 0; i < m; ++i){
        int v, u, w;
        cin >> v >> u >> w;
        edges.push_back({v, u});
        weights.push_back(w);
    }

    for(int i = 1; i < n; ++i){
        for(int j = 0; j < m; ++j){
            dp[edges[j].second] = min(dp[edges[j].second], dp[edges[j].first] + weights[j]);
            if(reachable[edges[j].first]){
                reachable[edges[j].second] = 1;
            }
        }
    }

    for(int j = 0; j < m; ++j){
        if(dp[edges[j].second] > dp[edges[j].first] + weights[j]){
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    for(int i = 0; i < n; ++i){
        if(reachable[i]){
            cout << dp[i] << " ";
        }else{
            cout << "UNREACHABLE ";
        }
    }
    return 0;
}
