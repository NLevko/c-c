#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <iostream>


using namespace std;

struct Point {
    int x;
    int y;
};

vector<Point> points;
int baseI;
vector<int> orderOfInd;

double dist(int i, int j) {
    double dx = points[i].x - points[j].x;
    double dy = points[i].y - points[j].y;
    return sqrt(dx * dx + dy * dy);
}

bool cmp(int i, int j) {
    long long dx1 = points[i].x - points[baseI].x;
    long long dy1 = points[i].y - points[baseI].y;

    long long dx2 = points[j].x - points[baseI].x;
    long long dy2 = points[j].y - points[baseI].y;
    if(dy1 * dx2 == dy2 * dx1) {
        return dist(i, baseI) < dist(j, baseI);
    }
    return dy1 * dx2 < dy2 * dx1;
}

bool check(int i, int j, int k) {
    int dx1 = points[i].x - points[j].x;
    int dy1 = points[i].y - points[j].y;

    int dx2 = points[k].x - points[j].x;
    int dy2 = points[k].y - points[j].y;

    return dx2 * (long long)dy1 <= dy2 * (long long)dx1;
}


int main()
{
    int N;
    cin >> N;
    Point base;
    Point point;

    cin >> point.x >> point.y;

    baseI = 0;
    base.x = point.x;
    base.y = point.y;
    points.push_back(point);
    orderOfInd.push_back(0);

    for(int i = 1; i < N; i++) {
        cin >> point.x >> point.y;
        if(point.x < base.x || (point.x == base.x && point.y > base.y)){
            baseI = i;
            base.x = point.x;
            base.y = point.y;
        }
        points.push_back(point);
        orderOfInd.push_back(i);
    }
    swap(orderOfInd[0], orderOfInd[baseI]);
    sort(orderOfInd.begin() + 1, orderOfInd.end(), cmp);

    vector<int> convex;
    convex.push_back(orderOfInd[0]);

    for(int i = 1; i < N; ++i) {
        int m = convex.size();
        while(m > 1 && check(convex[m - 2], convex[m - 1], orderOfInd[i])) {
            convex.pop_back();
            --m;
        }
        convex.push_back(orderOfInd[i]);
    }

    double p = 0.;
    convex.push_back(convex[0]);
    for(unsigned int i = 1; i < convex.size(); ++i) {
        p += dist(convex[i], convex[i - 1]);
    }
    printf("%.2lf", p);
    return 0;
}
