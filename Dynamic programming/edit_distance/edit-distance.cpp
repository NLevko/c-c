#include <iostream>
#include <string>

using namespace std;

int edit_distance[1005][1005];

int main()
{
    string first_word, second_word;
    
    cin >> first_word >> second_word;
    
    int n = first_word.size();
    int m = second_word.size();

    for(int i = 1; i <= n; ++i)
        edit_distance[i][0] = i;
    for(int i = 1; i <= m; ++i)
        edit_distance[0][i] = i;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
    
            if(first_word[i] == second_word[j]){
                edit_distance[i + 1][j + 1] = edit_distance[i][j];
            }else{
                edit_distance[i + 1][j + 1] = min(min(edit_distance[i][j + 1],edit_distance[i][j]),
                                                  edit_distance[i + 1][j]);
                ++edit_distance[i + 1][j + 1];
            }
        }
    }

    cout << edit_distance[n][m] << endl;
    
    return 0;
}
