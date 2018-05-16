#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct position {
	int x;
	int y;

	position(const int x, const int y)
		: x(x)
		, y(y)
	{}
};

vector<position> moves_set = {{1,2}, {-1,-2}, {1,-2}, {-1,2}, {2,1}, {-2,-1}, {2,-1}, {-2,1} };

bool operator == (const position &left, const position &right) {
	return left.x == right.x && left.y == right.y;
}

bool operator != (const position &left, const position &right) {
	return !(left == right);
}

int main()
{
	const int UNDEF = -1;
	int n;

	cin >> n;

	position begin(UNDEF, UNDEF);
	position end(UNDEF, UNDEF);

	vector<vector<position>> from(n, vector<position> (n, position(UNDEF, UNDEF)));

	char x_begin;
	char x_end;
	int y_begin;
	int y_end;

	cin >> x_begin >> y_begin >> x_end >> y_end;
	begin.x = x_begin - 'A';
	begin.y = y_begin - 1;
	end.x = x_end - 'A';
	end.y = y_end - 1;

	queue<position> moves;

	moves.push(begin);

	while (!moves.empty()) {
		position cur = moves.front();
		moves.pop();
		for (int i = 0; i < 8; ++i)
		{
			int nx = cur.x + moves_set[i].x;
			int ny = cur.y + moves_set[i].y;
			if(0 <= nx && nx < n && 0 <= ny && ny < n && from[nx][ny].x == UNDEF) {
				moves.push(position(nx,ny));
				from[nx][ny] = cur;
			}
		}
	}
	
	stack<position> ans;
	position cur = end;

	while (cur != begin) {
		ans.push(cur);
		cur = from[cur.x][cur.y];
	}

	cout << ans.size() << endl;
    while(ans.size() > 0){
        cur = ans.top();
        ans.pop();
        cout << char(cur.x + 'A') << cur.y + 1 << endl;
    }
    
    cout << "\n";

	return 0;
}