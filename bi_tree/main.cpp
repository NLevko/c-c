#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>


using namespace std;

vector<int> arr;
vector<int> seg;
int endS;

void build(int v = 1, int l = 0, int r = endS){
    if(l == r){
        seg[v] = arr[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    seg[v] = seg[v << 1] ^ seg[v << 1 | 1];
}

void update(int ind, int val, int v = 1, int l = 0, int r = endS){
    if(l == r){
        seg[v] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(l <= ind && ind <= mid){
        update(ind, val, v << 1, l, mid);
    }else{
        update(ind, val, v << 1 | 1, mid + 1, r);
    }
    seg[v] = seg[v << 1] ^ seg[v << 1 | 1];
}

int query(int lq, int rq, int v = 1, int l = 0, int r = endS){
    if(lq <= l && r <= rq){
        return seg[v];
    }
    if(r < lq || rq < l){
        return 0;
    }
    int mid = (l + r) >> 1;
    return query(lq, rq, v << 1, l, mid) ^ query(lq, rq, v << 1 | 1, mid + 1, r);
}

int main()
{

    int n, m;
    cin >> n >> m;
    arr.resize(n);
    seg.resize(4 * n);
    endS = n - 1;
    for(int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }
    build();
    for(int i = 0; i < m; ++i){
        int t;
        cin >> t;
        if(t == 1){
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d \n", query(l, r));
        }else{
            int ind, val;
            scanf("%d %d", &ind, &val);
            update(ind, val);
        }
    }
    return 0;
}
