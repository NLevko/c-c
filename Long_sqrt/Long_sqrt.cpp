#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>
 
using namespace std;

typedef unsigned char uchar;
typedef unsigned short ushort;
 
#define MAX_LEN 10000
#define bigint ushort *
#define base 10
 
bigint tmp = new ushort[MAX_LEN];
bigint prr = new ushort[MAX_LEN];
bigint tmp1 = new ushort[MAX_LEN];
bigint tmp2 = new ushort[MAX_LEN];
 
int cmp(bigint a, bigint b){
    if(a[0] != b[0]) return (int)a[0] - b[0];
    for(int i = a[0]; i > 0; i--)
        if(a[i] != b[i]) return (int)a[i] - b[i];
    return 0;
}
 

void smul(bigint a, ushort b, bigint c) {
    long i;
    long temp;
    ushort carry = 0; 
    for (i = 1; i <= a[0]; i++) {
        temp = a[i] * b + carry;
        carry = temp / base;
        c[i] = temp - carry * base;
    }
    if (carry) {
        c[i] = carry;
        c[0] = a[0] + 1;
    } 
    else c[0] = a[0];
    while(c[0] > 0 && c[c[0]] == 0) c[0]--;
}
 
void shift(bigint a, int s) {
    for(int i = a[0]; i > 0; i--)
        a[i+s] = a[i];
    for(int i = 1; i <= s; i++) a[i] = 0;
    a[0] += s;
}
 
void summ(bigint a, bigint b, bigint c) {
    long i;
    long temp;
    ushort carry = 0;
    if ( a[0] < b[0] ) {
        summ(b, a, c);
        return;
    }
    for (i = 1; i <= b[0]; i++) {
        temp = a[i] + b[i] + carry;
        if (temp >= base) {
            c[i] = temp - base;
            carry = 1;
        } else {
            c[i] = temp;
            carry = 0;
        }
    }
    for (; i <= a[0]; i++) {
        temp = a[i] + carry;
        if (temp >= base) {
            c[i] = temp - base;
            carry = 1;
        } else {
            c[i] = temp;
            carry = 0;
        }
    }
    if (carry) {
        c[i] = carry;
        c[0] = a[0]+1;
    } 
    else c[0] = a[0];
    while(c[0]>0 && c[c[0]]==0) c[0]--;
}
 
ushort findBin(bigint a, bigint r, int cur) {
    short res = base - 1;
    while(res > 0) {
        smul(r, 2, tmp1);
        smul(tmp1, res, tmp2);
        shift(tmp2, cur - 1);
        summ(prr, tmp2, tmp);
        tmp1[0] = 1; 
        tmp1[1] = res;
        smul(tmp1, res, tmp2);
        shift(tmp2, cur * 2 - 2);
        summ(tmp, tmp2, tmp1);
        if(cmp(tmp1, a) <= 0) { 
            break;
        }
        res--;
    }
    while(res >= base) res--;
    smul(r, 2, tmp1);
    smul(tmp1, res, tmp2);
    shift(tmp2, cur - 1);
    summ(prr, tmp2, tmp);
    tmp1[0] = 1; tmp1[1] = res;
    smul(tmp1, res, tmp2);
    shift(tmp2, cur * 2 - 2);
    summ(tmp, tmp2, prr); 
    return r[cur] = res;
}
 
bigint sqrt(bigint a){
    bigint r = new ushort[MAX_LEN];
    r[0] = (a[0] + 1) >> 1;

    for(int i = 1; i <= r[0]; i++)
        r[i] = 0;
    
    int cur = r[0];
    
    while(cur){
        r[0] = (a[0] + 1) >> 1;
        r[cur] = findBin(a, r, cur);
        cur--;
    }
    
    return r;
}
 

int main() {

    bigint r = new ushort[MAX_LEN];
    char s[MAX_LEN];

    cin >> s;

    int c = 0, l = strlen(s);
    
    if(l > 1) {
        for(int i = 0; i < l; i++, c++) {
            if(s[i] != '0') break;
        }
    }

    r[0] = l - c;

    for(int i = l - 1; i >= c; i--) r[l-i] = s[i]-'0';

    bigint a;

    prr[0] = 0;

    a = sqrt(r);

    for(int i = a[0]; i > 0; i--) cout << a[i];
 
    return 0;
}