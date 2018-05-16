#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main()
{
    string word;
    string pattern;
    cin >> word >> pattern;
    int n = word.size(), m = pattern.size();
    bool dp[n + 1][m + 1];

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(pattern[j] == '*'){
                if(dp[i][j + 1] || dp[i][j] || dp[i + 1][j])
                    dp[i + 1][j + 1] = 1;
            }else if(pattern[j] == '?' || word[i] == pattern[j]){
                dp[i + 1][j + 1] = dp[i][j];
            }
        }
    }
    if(dp[n][m]){
        cout << "YES";
    }else{
        cout << "NO";
    }
    return 0;
}
