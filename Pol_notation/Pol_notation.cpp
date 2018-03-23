#include <iostream>
#include <string>
#include <stack>
using namespace std;


bool IsNumber(string str, int &Num){
	Num = 0;
	bool isNegative = false;
	for(int i = 0; i < str.size(); ++i) {
		if(i == 0 && str[i] == '-' && str.size() > 1) {
			isNegative = true;
		} else {
			if('0' <= str[i] && str[i] <= '9') {
				Num *= 10;
				Num += (str[i] - '0');
			} else {
				return false;
			}
		}
	}
	if(isNegative) {
		Num *= -1;
	}
	return true;
}



int main() {

	stack<string> znak;

	int number = 0;
	int itog = 0;

	bool first = false;

	string str;
	
	while(cin >> str) {

		if(IsNumber(str, itog)) {

			int cnt = 0;

			char el;

			while(znak.size() > 1 && IsNumber(znak.top(), number)) {
				znak.pop();
				if(znak.top() == "+") {
					itog = number + itog; 
				}

				if(znak.top() == "-") {
					itog = number - itog; 
				}

				if(znak.top() == "*") {
					itog = number * itog; 
				}

				if(znak.top() == "/") {
					itog = number / itog; 
				}

				znak.pop();
				cnt++;
			}

	        if(cnt == 0) {
	        	znak.push(str);
			} else {
				znak.push(to_string(itog));
			}
		}else {
			znak.push(str);
		}
	}
	
	cout << itog;
}