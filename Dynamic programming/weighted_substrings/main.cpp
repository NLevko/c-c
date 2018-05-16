#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

int Weigt(const string &s) {

    int weigt = 0;
    vector<int> base(s.size());
    vector<int> cnt(s.size() + 1);
    int l = 0, r = 0;

    for(int i = 1; i < s.size(); ++i) {
        
        if(i <= r) base[i] = min(base[i - l], r - i);
        
        while(i + base[i] < s.size() && s[base[i]] == s[i + base[i]]) ++base[i];
        
        ++cnt[base[i]];

        if(i + base[i] - 1 > r){
            l = i;
            r = base[i] + i - 1;
        }
    }

    for(int i = s.size() - 1; i >= 0; --i) cnt[i] += cnt[i + 1];

    for(int i = 0; i <= s.size(); ++i) weigt = max(weigt, (cnt[i] + 1) * i);

    return weigt;
}

int max_Weigt(const string &s) {
	
	int ans;
	
	for (int i = 0; i < s.size(); ++i) {
	
		string cur_string;
	
		for (int j = i; j < s.size(); ++j) cur_string += s[j];
	
		ans = max(ans, Weigt(cur_string));

	}
	return ans;
}

int main()
{
    string str;

    cin >> str;
    
    cout << Weigt(str) << endl;

    return 0;
}
