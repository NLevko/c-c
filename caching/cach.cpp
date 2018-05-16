#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h> 
#include <iterator> 
using namespace std;

template<class InputIterator, class T>
  InputIterator find1 (InputIterator first_1, InputIterator first, InputIterator last, const T& val)
{
  while (first!=last) {
    if (*first==val) return first;
    ++first;
  }
  return first_1;
}

int find_maximal (vector<pair<unsigned long, int>> &cash) {
	int m = cash[0].second;
	int k = 0;
	for(int i = 1; i < (int)cash.size(); i++)
	{	
		if (cash[i].second > m) {
			k = i;
			m = cash[i].second;
		}
	}
	return k;			
}

int find_in_vec (unsigned long x, vector<pair<unsigned long, int>> &M) {
	for (int i = 0; i < (int)M.size(); ++i)
	{
		if (x == M[i].first) {
			return i;
		}
	}
	return -2;
}

int main()
{
	int N;
	int M;
	scanf ("%d", &M);
    scanf ("%d", &N);
    int s = 0;
	int count = 0;
	int k =0;

	vector<pair<unsigned long, int>> cash;
	vector<unsigned long> date(N);

	for (int i = 0; i < N; ++i)
	{
		scanf( "%lu", &date[i]);
	}


	for (int i = 0; i < N; ++i)
	{	
		if ((int)cash.size() < M && find_in_vec(date[i], cash) < 0) {
			k = distance(date.begin(), find1(date.begin(), date.begin() + i + 1, date.end(), date[i]));
			if (k != 0 ) cash.push_back({date[i], k});
			count ++;	
		} else if ((s = find_in_vec(date[i], cash)) >= 0 ) {
			k = distance(date.begin(), find1(date.begin(), date.begin() + i + 1, date.end(), cash[s].first));
			cash[s].second = k;
			if (k == 0) {
				cash.erase(cash.begin() + s);
			}
		} else {
			k = find_maximal(cash);
			cash.erase(cash.begin() + k);
			k = distance(date.begin(), find1(date.begin(), date.begin() + i + 1, date.end(), date[i]));
			if (k != 0 ) cash.push_back({date[i], k});
			count ++;	
		}
	}
	printf("%d", count);
	return 0;
}


