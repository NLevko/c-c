#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int intersect (vector<int> &vector_i, vector<int> &vector_j) {
    
    unsigned int itetator_1 = 0;
    unsigned int itetator_2 = 0;
    int res = 0;

    while(itetator_1 < vector_i.size() && itetator_2 < vector_j.size()) {
        if(vector_i[itetator_1] < vector_j[itetator_2]){
            itetator_1++;
        } else if(vector_i[itetator_1] > vector_j[itetator_2]) {
            itetator_2++;
        } else {
            itetator_1++;
            itetator_2++;
            res++;
        }
    }
    return res;
}


int func (vector<vector<int>> &Matrix, int N) {
    int ans = 0;
    int a = 0;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            a = intersect(Matrix[i], Matrix[j]);
            ans = max(a, ans);
        }
    }
    return ans;
}

int main()
{

    int N;
    int M;

    cin >> N >> M;

    vector<vector<int>> Matrix(N, vector<int>(M));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> Matrix[i][j];
        }
        sort(Matrix[i].begin(), Matrix[i].end());
    }

    int ans = 0;

    ans = func(Matrix, N);

    cout << ans;

    return 0;
}
