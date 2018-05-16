#include <iostream>
#include <vector>
#include <queue>


using namespace std;

int depth[10001];
int ancestor[10001];

int find_root(int a){
    if(a == ancestor[a]){
        return a;
    }
    return ancestor[a] = find_root(ancestor[a]);
}

void merge_trees(int r1, int r2){
    if(depth[r1] < depth[r2]){
        swap(r1, r2);
    }
    ancestor[r2] = r1;
    depth[r1] = max(depth[r1], depth[r2] + 1);
}

int main()
{
    int n;
    cin >> n;

    priority_queue<pair<int, pair<int, int>>> q;

    for(int i = 0; i < n; ++i) {

        ancestor[i] = i;

        for(int j = 0; j < n; ++j) {

            int lenth;
            cin >> lenth;

            if(lenth > 0){
                q.push({lenth, {i, j}});
            }
        }
    }

    int result = 0;

    while(q.size() > 0) {

        int lenth = q.top().first;
        int a = q.top().second.first;
        int b = q.top().second.second;
        int r1 = find_root(a);
        int r2 = find_root(b);
        q.pop();

        if(r1 != r2){

            result += lenth;
            merge_trees(r1, r2);
        }
    }

    cout << result;
    return 0;
}
