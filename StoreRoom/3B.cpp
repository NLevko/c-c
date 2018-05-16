#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> store_time;

    for(int i = 0; i < N; i++) {
        
	int duration;
        char colon;
        int hours;
        int minutes;

        cin >> hours >> colon >> minutes;

        duration = hours * 60 + minutes;
        store_time.push_back({duration, -1});

        cin >> hours >> colon >> minutes;

        duration = hours * 60 + minutes;
        store_time.push_back({duration, 1});
    }

    sort(store_time.begin(), store_time.end());

    int answer = 0;
    int counter = 0;

    for(int i = 0; i < 2 * N; i++) {
        counter -= store_time[i].second;
        answer = max(answer, counter);
    }

    cout << answer;
    
    return 0;
}
