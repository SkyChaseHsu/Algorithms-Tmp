//
// Created by xukexin on 2019/4/15.
//

#include "point.h"

#include <iostream>
using namespace std;
#include <cmath>
#include <cfloat>

#define random(a,b) (rand()%(b-a+1)+a)

/* Point 对象 */
// 缺省构造函数
Point::Point() {
    x = 0;
    y = 0;
}

// 构造函数
Point::Point(int x_v, int y_v) {
    x = x_v;
    y = y_v;
}

// 返回点的x值
int Point::getX() {
    return x;
}

// 返回点的y值
int Point::getY() {
    return y;
}

// 设置点的x, y值
void Point::setXY(int x_v, int y_v) {
    x = x_v;
    y = y_v;
}

// 求点到另外一个点 p 的距离
double Point::getDisTo(Point &p) {
    return sqrt(pow(x - p.getX(), 2) + pow(y - p.getY(), 2));
}

// Point：判断点是否在点集 pg 里面
int Point::inside (PGroup pg) {
    for (int i = 0; i < pg.getN(); i++) {
        if (x == pg.getPoints(i).getX() && y == pg.getPoints(i).getY())
            return 1;
    }
    return 0;
}

/* PGroup 对象 */
// 构造函数：初始化点集（规模为n_v)
PGroup::PGroup(int n_v) {
    n = n_v;
    points = new Point[n_v];
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        points[i].setXY(random(1, 100000), random(1, 100000));
    }
}

PGroup::PGroup(PGroup &pg) {
    n = pg.getN();
    points = new Point[n];
    for (int i = 0; i < n; i++) {
        points[i].setXY(pg.getPoints(i).getX(), pg.getPoints(i).getY());
    }
}

// 析构函数
PGroup::~PGroup() {
    delete []points;
}

// 设置点集的规模
void PGroup::setN(int n_v) {
    n = n_v;
}

// 得到点集的规模
int PGroup::getN() {
    return n;
}

// 设置点集中某个点的值
void PGroup::setPoint(int i, int x_v, int y_v) {
    points[i].setXY(x_v, y_v);
}

// 根据点的 x 值对点集进行排序
void PGroup::sortX() {
    sort(points, points + n, cmpX);
}

// 根据点的 y 值对点集进行排序
void PGroup::sortY() {
    sort(points, points + n, cmpY);
}

// 按 x 值升值排序的比较函数
bool cmpX(Point a, Point b) {
    return a.getX() < b.getX();
}

// 按 y 值升值排序的比较函数
bool cmpY(Point a, Point b) {
    return a.getY() < b.getY();
}

// 打印点集所有点
void PGroup::display() {
    for (int i = 0; i < n; i++) {
        cout<<"("<<points[i].getX()<<", "<<points[i].getY()<<")";
        if (i != n-1) cout<<" ";
    }
    cout<<endl;
}

// 返回点集中的某个点
Point PGroup::getPoints(int i) {
    return points[i];
}

// 暴力求解
double PGroup::vioMin() {

    // 如果点数小于2，则返回无限； 如果点数是2，就返回它们的距离
    if (n < 2){
        return DBL_MAX;
    } else if (n == 2) {
        return points[0].getDisTo(points[1]);
    }

    // 设置最小点距 minDis 为DBL_MAX （浮点数最大值）
    // 当前计算点距 curDis 初始化为0
    double minDis = DBL_MAX;
    double curDis = 0;

    for (int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++){
            curDis = points[i].getDisTo(points[j]);
            if (curDis < minDis) {
                minDis = curDis;
            }
        }
    }

    return minDis;
}

// 分治法求解
double PGroup::dacMin(PGroup py) {
    // 如果点数小于2，则返回无限； 如果点数是2，就返回它们的距离
    if (n < 2){
        return DBL_MAX;
    } else if (n == 2) {
        return points[0].getDisTo(points[1]);
    }

    // 将点集按照 x 值进行排序， 取中位数作为分隔线
    int mid_x = points[n/2].getX();

    // 将点集分为左右两个子集
    PGroup pgLeft(n/2);
    PGroup pgRight(n - n/2);

    for (int i = 0; i < n/2; i++) {
        pgLeft.setPoint(i, points[i].getX(), points[i].getY());
    }

    for (int i = n/2, j = 0; i < n; i++, j++) {
        pgRight.setPoint(j, points[i].getX(),points[i].getY());
    }

    // 将点集 py 分为左右个子集
    PGroup pyLeft(n);
    PGroup pyRight(n);
    int left_cnt = 0, right_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (points[i].getX() <= mid_x && left_cnt < n/2)
            pyLeft.setPoint(left_cnt++, points[i].getX(), points[i].getY());
        else
            pyRight.setPoint(right_cnt++, points[i].getX(), points[i].getY());
    }
    pyLeft.setN(left_cnt);
    pyRight.setN(right_cnt);

    // 分别递归求出左右两个点集的函数，求出最小值为点集的最小点距
    double min_left = pgLeft.dacMin(pyLeft);
    double min_right =pgRight.dacMin(pyRight);
    double min_tol = min_left < min_right? min_left : min_right;

    // 求出出 mid - min 到 mid + min 之前的点
    PGroup mid(n);
    int mid_cnt = 0;
    for(int i = 0; i < n; i++) {
        if (abs(py.getPoints(i).getX() - mid_x) <= min_tol) {
            mid.setPoint(mid_cnt++, py.getPoints(i).getX(), py.getPoints(i).getY());
        }
    }
    mid.setN(mid_cnt);

    // 对 mid 点集中线左边的每个点
    // 依次求解右边的往下的 6 个点的点距
    for (int i = 0; i < mid.getN(); i++) {
        for (int j = i + 1; j <= i + 7 && j < mid.getN(); j++) {
            Point tmp = mid.getPoints(j);
            double cur_dis = mid.getPoints(i).getDisTo(tmp);
            if (cur_dis < min_tol) {
                min_tol = cur_dis;
            }
        }
    }

    return min_tol;
}

