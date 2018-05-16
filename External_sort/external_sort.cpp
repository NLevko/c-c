#include <cstdio>
#include <cstring>

void Merge(char name1[], char name2[], int len, int n) {
    
    FILE *ptr1 = fopen(name1, "r");
    FILE *ptr2 = fopen(name1, "r");
    FILE *out = fopen(name2, "w");

    char str1[10005], str2[10005];

    int am = n / (2 * len);
    int ind = 0;
    
    for(int i = 1; i <= len; ++i) {
        fgets(str2, 10005, ptr2);
        ++ind;
    }
    
    if(n % (2 * len) > len) {
        ++am;
    }
    
    for(int i = 0; i < am; ++i) {
        int len2 = len < n - ind ? len : n - ind;
    
        fgets(str1, 10005, ptr1);
        fgets(str2, 10005, ptr2);
        ++ind;
    
        int cnt1 = 1, cnt2 = 1;
    
        while(cnt1 <= len && cnt2 <= len2) {
    
            int var = strcmp(str1, str2);
    
            if(var <= 0) {
                fputs(str1, out);
                fgets(str1, 10005, ptr1);
                ++cnt1;
            } else {
                fputs(str2, out);
                fgets(str2, 10005, ptr2);
                ++cnt2;
                ++ind;
            }
    
        }
    
        while(cnt1 <= len) {
            fputs(str1, out);
            fgets(str1, 10005, ptr1);
            ++cnt1;
        }
    
        while(cnt2 <= len2) {
            fputs(str2, out);
            fgets(str2, 10005, ptr2);
            ++cnt2;
            ++ind;
        }
    
        for(int j = 1; j < len; ++j) {
            fgets(str1, 10005, ptr1);
            fgets(str2, 10005, ptr2);
            ++ind;
        }

    }
    
    while(fgets(str1, 10005, ptr1) != NULL) {
        fputs(str1, out);
    }
    
    fclose(ptr1);
    fclose(ptr2);
    fclose(out);

}

int FromTo(char from[], char to[]) {

    FILE *in = fopen(from, "r");
    FILE *out = fopen(to, "w");

    int cnt = 0;
    char str[10005];

    while(fgets(str, 10005, in)) {
        ++cnt;
        fputs(str, out);
    }

    fclose(in);
    fclose(out);
    return cnt;
}

int main()
{
    int n = FromTo("input.txt", "tmp1.txt");

    int deg = 0;

    while((1 << deg) < n) {
        if(deg & 1) {
            Merge("tmp2.txt", "tmp1.txt", 1 << deg, n);
        } else {
            Merge("tmp1.txt", "tmp2.txt", 1 << deg, n);
        }
        ++deg;
    }

    if(deg & 1) {
        FromTo("tmp2.txt", "output.txt");
    } else {
        FromTo("tmp1.txt", "output.txt");
    }

    return 0;
}
