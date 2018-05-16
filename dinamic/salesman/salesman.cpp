#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int cost[155][1005];
int path[155][1005];

int ans(int n, int m){
    int min = cost[1][m];
    int index = 1;
    for (int i = 2; i <= n; ++i) {
        if (cost[i][m] < min) {
            index = i;
            min = cost[i][m];
        }
    }
    return index;
}

int min(int x, int y, int z)
{
   if (x <= y)
      return (x <= z)? x : z;
   else
      return (y <= z)? y : z;
}

int min_index(int x, int y, int z)
{
   if (x <= y)
      return (x <= z)? -1 : 1;
   else
      return (y <= z)? 0 : 1;
}

int main()
{
    
    int n, m;
    int index = 0;

    const int INF = (int)(1e9);
    
    cin >> n >> m;
    

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> cost[i + 1][j + 1];
            if(i == 0 || j == 0) {
                cost[i][j] = INF;
            }
        }
    }
    cost[n + 1][0] = INF;
    cost[n][0] = INF;

    for (int j = 0; j <= m; ++j)
    {
        cost[n + 1][j] = INF;
    }



    for (int i = 1; i <= n; ++i)
    {
        path[i][1] = i;
    }


    for(int j = 2; j <= m; ++j){
        for(int i = 1; i <= n; ++i){
            cost[i][j] += min(cost[i - 1][j - 1], cost[i][j - 1], cost[i + 1][j - 1]);
            path[i][j] = i + min_index(cost[i - 1][j - 1], cost[i][j - 1], cost[i + 1][j - 1]);
        }
    }

    index = ans(n,m);

    stack<int> queue;
    int ans = cost[index][m];
    queue.push(index);

    for (int j = m; j > 1; --j)
    {
        queue.push(path[index][j]);
        index = path[index][j];
    }


    for(int i = 1; i <= m; ++i){
        index = queue.top();
        queue.pop();
        cout << index << " ";
    }

    cout << endl;
    cout << ans << endl;

    return 0;
}
