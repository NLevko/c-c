#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int max_lenth(string str1, string str2, vector<vector<int>> &dp) {

	int n = str1.size();
    int m = str2.size();
    int max_len = 0;

    for(int i = 0; i < n; ++i) {

    	for(int j = 0; j < m; ++j) {

       		dp[1][j] = 0;

        	if(str1[i] == str2[j]) {

            	dp[1][j] = 1;
            	if(i > 0 && j > 0) dp[1][j] += dp[0][j - 1];
        	}
        max_len = max(max_len, dp[1][j]);
    	}

    for(int j = 0; j < m; ++j) dp[0][j] = dp[1][j];

	}

	return max_len;
}

string Max_substr (string str1, string str2, int max_len, vector<vector<int>> &dp) {

	vector<string> ans;
	int n = str1.size();
    int m = str2.size();

	    for(int i = 0; i < n; ++i) {

        	for(int j = 0; j < m; ++j) {

            	dp[1][j] = 0;

            	if(str1[i] == str2[j]) {

                	dp[1][j] = 1;

                	if(i > 0 && j > 0) dp[1][j] += dp[0][j - 1];
                }

            if(max_len == dp[1][j]) {

                string tmp;

                for(int k = i - max_len + 1; k <= i; ++k) tmp += str1[k];

                ans.push_back(tmp);
            }

        }

        for(int j = 0; j < m; ++j) dp[0][j] = dp[1][j];
        	
    }

    sort(ans.begin(), ans.end());

    return ans[0];
}


int main()
{
    string str1, str2;
    string ans;

    cin >> str1 >> str2;

    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(2, vector<int>(m));

    int max_len = max_lenth(str1, str2, dp);

    ans = Max_substr(str1, str2, max_len, dp);

    cout << ans;

    return 0;
}
