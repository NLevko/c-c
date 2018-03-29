#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int ui;

void radixSort(vector<ui> &seq){
    
    int blockSize = 8;
    int amountBlocks = 4;
    vector<int> counter(1 << 8, 0);
    vector<ui> tmp(seq.size());

    for(int i = 0; i < amountBlocks; ++i) {
    
        unsigned int mask = (1 << 8) - 1;
        mask <<= (i * 8);

        for(int j = 0; j < (1 << 8); ++j) counter[j] = 0;

        for(int j = 0; j < seq.size(); ++j) {
            ++counter[(seq[j] & mask) >> (8 * i)];
        }

        for(int j = 1; j < (1 << 8); ++j) {
            counter[j] += counter[j - 1];
        }

        for(int j = seq.size() - 1; j >= 0; --j) {
            int blockNumber = (seq[j] & mask) >> (8 * i);
            --counter[blockNumber];
            tmp[counter[blockNumber]] = seq[j];
        }
        for(int j = 0; j < seq.size(); ++j) {
            seq[j] = tmp[j];
        }
    }
}

int main()
{

    unsigned int N;
    unsigned int K;
    unsigned int M;
    unsigned int L;

    cin >> N >> K >> M >> L;

    vector<unsigned int> a(N);
    a[0] = K;

    for(int i = 0; i < N - 1; i++) {
        a[i+1] = (unsigned int)((a[i] * (unsigned long long)M) & 0xFFFFFFFFU) %L;
    }

    radixSort(a);

    long long result = 0;
    for(int i = 0; i < N; ++i) {
        if(!(i & 1)) {
            result += a[i];
            result %= L;
        }
    }
    cout << result;
    return 0;
}
