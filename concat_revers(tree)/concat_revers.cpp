#include <iostream>

using namespace std;

void getResult(const string str, int &ind, string &result){
    
    int st = result.size();
    
    while(str[ind] != ')') {
        if(str[ind] == '(') {
            ind++;
            getResult(str, ind, result);
            if(str[ind] == ',') {
                ind++;
            }
        } else {
            result += str[ind];
            ind++;
        }
    }

    ind++;

    if(ind < (int)str.size() && str[ind] == 'R') {
        for(int i = st, j = result.size() - 1; i < j; ++i, --j) {
            swap(result[i], result[j]);
        }
        ind++;
    }
}

int main()
{
    string str;
    cin >> str;

    int ind = 1;

    string result;

    getResult(str, ind, result);

    cout << result;

    return 0;
}
