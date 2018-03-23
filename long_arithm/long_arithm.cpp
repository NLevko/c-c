#include<iostream>
#include<string>
#include<algorithm>
#include<random>

using namespace std;

string SumPositive(string &firstNumber, string &secondNumber) {
	string result;
	reverse(firstNumber.begin(), firstNumber.end());
	reverse(secondNumber.begin(), secondNumber.end());
	
	int remainder = 0;
	int maxL = max(firstNumber.size(), secondNumber.size());
	for(int i = 0; i < maxL; ++i) {
		int cdigit = remainder;
		if(i < firstNumber.size()) {
			cdigit += (firstNumber[i] - '0');
		}
		if(i < secondNumber.size()) {
			cdigit += (secondNumber[i] - '0');
		}
		remainder = cdigit / 10;
		cdigit %= 10;
		result += ('0' + cdigit);
		
	}
	
	if(remainder > 0) {
		result += (remainder + '0');
	}
	reverse(result.begin(), result.end());
	return result;
}

string SubtractionPositive(string &firstNumber, string &secondNumber){
	string result;
	reverse(firstNumber.begin(), firstNumber.end());
	reverse(secondNumber.begin(), secondNumber.end());
	
	int maxL = max(firstNumber.size(), secondNumber.size());
	bool flag = false;
	if(firstNumber.size() < secondNumber.size()) {
		flag = true;
	}
	if(firstNumber.size() == secondNumber.size()) {
		for(int i = maxL - 1; i >= 0; --i){
			if(firstNumber[i] < secondNumber[i]) {
				flag = true;
				break;
			}
			if(firstNumber[i] > secondNumber[i]) {
				break;
			}
		}
	}
	if(flag) {
		swap(firstNumber, secondNumber);
	}
	int rem = 0;
	for(int i = 0; i < maxL; ++i) {
		int a = 0, b = 0;
		if(i < firstNumber.size()) {
			a = (firstNumber[i] - '0');
		}
		if(i < secondNumber.size()) {
			b = (secondNumber[i] - '0');
		}
		if(a >= b + rem) {
			a -= b + rem;
			rem = 0;
		} else {
			a += 10 - b - rem;
			rem = 1;
		}
		result += ('0' + a);
	}
	
	while(result.back() == '0' && result.size() > 1) {
		result.pop_back();
	}
	if(flag) {
		if(result.size() > 1 || result[0] != '0')
		    result += '-';
	}
	reverse(result.begin(), result.end());
	return result;
}

string MultPos(string &firstNumber, string &secondNumber) {
	reverse(firstNumber.begin(), firstNumber.end());
	reverse(secondNumber.begin(), secondNumber.end());
	string mult;

	for (int i = 0; i < secondNumber.size(); ++i) {
		int current = secondNumber[i] - '0';
		string curmult;
		int rem = 0;
		for (int j = 0; j < firstNumber.size(); ++j) {
			int tmp = (firstNumber[j] - '0')*current + rem;
			curmult += '0' + (tmp % 10);
			rem = tmp / 10;
		}
		if(rem > 0) {
			curmult += '0' + rem;
		}
		if(curmult.back() == '0') {
			curmult = "0";
		}
		reverse(curmult.begin(),curmult.end());
		for (int k = 0; k < i && curmult[0] > '0'; ++k)	{
			curmult += '0';
		}
		mult = SumPositive(mult, curmult);
	}
	return mult;
}

string operator+(string &firstNumber, string &secondNumber) {
	if(firstNumber[0] == '-' && secondNumber[0] == '-') {
		string first = firstNumber.substr(1, firstNumber.size() - 1);
		string second = secondNumber.substr(1, secondNumber.size() - 1);
		return '-' + SumPositive(first, second);
	}
	
	if(firstNumber[0] == '-') {
		string first = secondNumber;
		string second = firstNumber.substr(1, firstNumber.size() - 1);
		return SubtractionPositive(first, second);
	}
	
	if(secondNumber[0] == '-') {
		string first = firstNumber;
		string second = secondNumber.substr(1, secondNumber.size() - 1);
		return SubtractionPositive(first, second);
	}
	return SumPositive(firstNumber, secondNumber);
}

string operator-(string &firstNumber, string &secondNumber) {
	if(firstNumber[0] == '-' && secondNumber[0] == '-') {
		string first = secondNumber.substr(1, secondNumber.size() - 1);
		string second = firstNumber.substr(1, firstNumber.size() - 1);
		return SubtractionPositive(first, second);
	}
	
	if(firstNumber[0] == '-') {
		string first = secondNumber;
		string second = firstNumber.substr(1, firstNumber.size() - 1);
		return '-' + SumPositive(first, second);
	}
	
	if(secondNumber[0] == '-') {
		string first = firstNumber;
		string second = secondNumber.substr(1, secondNumber.size() - 1);
		return SumPositive(first, second);
	}
	return SubtractionPositive(firstNumber, secondNumber);
}

string operator*(string &firstNumber, string &secondNumber) {
	bool f_neg = false;
	bool s_neg = false;
	if(firstNumber[0] == '-') {
		f_neg = true;
		firstNumber = firstNumber.substr(1,firstNumber.size() - 1);
	}
	if(secondNumber[0] == '-') {
		s_neg = true;
		secondNumber = secondNumber.substr(1,secondNumber.size() - 1);
	}
	string result = MultPos(firstNumber,secondNumber);
	if((f_neg != s_neg) && result[0] > '0') {
		return "-" +result;
	}
	return result;
}

int main() {
	string firstNumber, secondNumber;
	
	char oper;
	
	cin >> firstNumber >> oper >> secondNumber;
		
	if(oper == '+') {
		cout << firstNumber + secondNumber;
	}
	if(oper == '-') {
		cout << firstNumber - secondNumber;
	}

	if(oper == '*') cout << firstNumber * secondNumber;

	return 0;
}
