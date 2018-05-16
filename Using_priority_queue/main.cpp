#include <stdio.h>
#include <set>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<long long> que;
    int  M;

    cin >> M;

    for(int i = 0; i < M; ++i){
        int ci;
        cin >> ci;
        que.push(-ci);
    }

    double ans = 0;

    while(que.size() > 1){
        long long val = que.top();
        que.pop();
        val += que.top();
        que.pop();
        ans += val;
        que.push(val);
    }

    cout << -0.01 * ans << endl;

    return 0;
}
