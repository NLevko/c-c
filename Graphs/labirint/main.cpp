#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> gr[10005];
int t1[10005];
int t2[10005];
priority_queue<pair<int, int>> que;

const int UNDEF = int(1e9);

void initGraff(int n, int m, int k) {

    for(int i = 0; i <= n; ++i){
        t1[i] = UNDEF;
        t2[i] = UNDEF;
    }
    
    for(int i = 0; i < k; ++i){
        int v;
        cin >> v;
        t1[v] = 0;
        que.push({0, v});
    }

    for(int i = 0; i < m; ++i){
        int v, u, w;
        cin >> v >> u >> w;
        gr[v].push_back({u, w});
        gr[u].push_back({v, w});
    }
}

void magic() {
    while(que.size() > 0){
    
        int cv = que.top().second;
    
        que.pop();
    
        for(int i = 0; i < (int)gr[cv].size(); ++i){
    
            int u = gr[cv][i].first, w = gr[cv][i].second;
    
            if(t1[cv] + w < t1[u]){
                t1[u] = t1[cv] + w;
                que.push({-t1[u], u});
            }
        }
    }
}

void find_path() {
    while(que.size() > 0){
    
        int cv = que.top().second;
    
        que.pop();
    
        for(int i = 0; i < (int)gr[cv].size(); ++i){
    
            int u = gr[cv][i].first, w = gr[cv][i].second;
            if(t2[cv] + w < t2[u] && t2[cv] + w < t1[u]){
                t2[u] = t2[cv] + w;
                que.push({-t2[u], u});
            }
        }
    }
}

int main()
{
    int n, m, k;
    
    cin >> n >> m >> k;
    
    initGraff(n, m, k);
    magic();
    
    int s, f;
    
    cin >> s >> f;

    t2[s] = 0;
    que.push({0, s});
    
    find_path();

    if(t2[f] == UNDEF){
        cout << -1;
    }else {
        cout << t2[f];
    }
    return 0;
}
