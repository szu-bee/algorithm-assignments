#include <iostream>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <cstdlib>

using namespace std;

#define N 10000

class Point {
public:
    double x, y;

    friend bool operator<(const Point &a, const Point &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    }
};

double distance(const Point a, const Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y));
}

// 蛮力法
double bf(Point *arr, int n) {
//    Point p1, p2;

    double min_dist = FLT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = distance(arr[i], arr[j]);
            if (dist < min_dist) {
                min_dist = dist;
//                p1 = arr[i];
//                p2 = arr[j];
            }
        }
    }
//    cout << "最近点对: (" << p1.x << ", " << p1.y << ") (";
//    cout << p2.x << ", " << p2.y << ")" << endl;

    return min_dist;
}

// 分治法
double divideAndConquer(Point *points, int left, int right) {
    if (left == right) return FLT_MAX;

    if (right == left + 1) {
        return distance(points[left], points[right]);
    }

    int mid = (left + right) / 2;

    double d = min(divideAndConquer(points, left, mid),
                   divideAndConquer(points, mid, right));

    for (int i = mid - 1; i >= left && points[mid].x - points[i].x < d; i--) {
        for (int j = mid + 1; j <= right &&
                              points[j].x - points[mid].x < d &&
                              fabs(points[i].y - points[j].y) < d; j++) {
            double distance_tmp = distance(points[i], points[j]);

            if (distance_tmp < d) {
                d = distance_tmp;
            }
        }
    }

    return d;
}


int main() {
    srand((unsigned int) clock());

    Point *points = new Point[N];
    for (int i = 0; i < N; i++) {
        points[i].x = rand() % 1000000;
        points[i].y = rand() % 1000000;
    }

    cout << "最短距离-------------------" << endl;

    sort(points, points + N);
    cout << "分治法：" << divideAndConquer(points, 0, N - 1) << endl;

    cout << "蛮力法：" << bf(points, N) << endl;

    cout << "耗时-----------------------" << endl;
    long tic, toc;
    const int repeat = 10;

    int cnt = 0;

    sort(points, points + N);
    for (int r = 0; r < repeat; ++r) {
        tic = clock();
        divideAndConquer(points, 0, N - 1);
        toc = clock();

        cnt += toc - tic;
    }
    cout << "分治法耗时： " << cnt / (double) repeat / 1000 << " ms" << endl;

    cnt = 0;
    for (int r = 0; r < repeat; ++r) {
        tic = clock();
        bf(points, N);
        toc = clock();

        cnt += toc - tic;
    }
    cout << "蛮力法耗时： " << cnt / (double) repeat / 1000 << " ms" << endl;

    return 0;
}
