#include <iostream>
#include <vector>

using namespace std;

bool check(int x, vector<vector<int>> M) {

	int n = M[0].size();
	int i = 0;
	int j = 0;

	while (i < n && j < n) {
		if (M[i][j] == x) return true;
		if (M[i][j] > x) i++;
		else j++;
	}

	return false;
}


int main() {
	int N;

	cin >> N;

    vector<vector<int>> Matrix(N, vector<int>(N));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> Matrix[i][j];
        }
    }

    int x;
    cin >> x;

    if(check(x, Matrix)) {
    	cout << "yes" << endl;
    } else {
    	cout << "no" << endl;
    }

	return 0;
}
