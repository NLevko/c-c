#include <iostream>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    char lab[n][m];
    int ix, iy;
    int ox, oy;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> lab[i][j];
            if(lab[i][j] == '@'){
                ix = i;
                iy = j;
            }
            if(lab[i][j] == '#'){
                ox = i;
                oy = j;
            }
        }
    }

    long long prev[n][m];
    long long next[n][m];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            prev[i][j] = next[i][j] = 0;
        }
    }
    prev[ix][iy] = 1;

    int sx[] = {0, 0, 1, -1};
    int sy[] = {1, -1, 0, 0};
    for(int it = 0; it < k; ++it){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(lab[i][j] != '+'){
                    for(int l = 0; l < 4; ++l){
                        int x = i + sx[l];
                        int y = j + sy[l];
                        if(0 <= x && x < n && 0 <= y && y < m &&
                           lab[x][y] != '+'){
                            next[x][y] += prev[i][j];
                        }
                    }
                }
            }
        }

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                prev[i][j] = next[i][j];
                next[i][j] = 0;
            }
        }
    }
    cout << prev[ox][oy];
    return 0;
}
