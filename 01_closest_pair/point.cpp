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
// Point: 缺省构造函数
Point::Point() {
    x = 0;
    y = 0;
}

// Point: 构造函数
Point::Point(int x_v, int y_v) {
    x = x_v;
    y = y_v;
}

// Point: 返回点的x值
int Point::getX() {
    return x;
}

// Point: 返回点的y值
int Point::getY() {
    return y;
}

// Point: 设置点的x, y值
void Point::setXY(int x_v, int y_v) {
    x = x_v;
    y = y_v;
}

// Point: 求点到另外一个点 p 的距离
double Point::getDisTo(Point &p) {
    return sqrt(pow(x - p.getX(), 2) + pow(y - p.getY(), 2));
}

/* PGroup 对象 */
// PGroup: 构造函数：初始化点集（规模为n_v)
PGroup::PGroup(int n_v) {
    n = n_v;
    points = new Point[n_v];
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        points[i].setXY(random(1, 100000), random(1, 100000));
    }
}

// PGroup: 拷贝构造函数
PGroup::PGroup(PGroup &pg) {
    n = pg.getN();
    points = new Point[n];
    for (int i = 0; i < n; i++) {
        points[i].setXY(pg.getPoints(i).getX(), pg.getPoints(i).getY());
    }
}

// PGroup: 析构函数
PGroup::~PGroup() {
    delete []points;
}

// PGroup: 设置点集的规模
void PGroup::setN(int n_v) {
    n = n_v;
}

// PGroup: 得到点集的规模
int PGroup::getN() {
    return n;
}

// PGroup: 设置点集中某个点的值
void PGroup::setPoint(int i, int x_v, int y_v) {
    points[i].setXY(x_v, y_v);
}

// PGroup: 根据点的 x 值对点集进行排序
void PGroup::sortX() {
    sort(points, points + n, cmpX);
}

// PGroup: 根据点的 y 值对点集进行排序
void PGroup::sortY() {
    sort(points, points + n, cmpY);
}

// PGroup: 按 x 值升值排序的比较函数
bool cmpX(Point a, Point b) {
    return a.getX() < b.getX();
}

// PGroup: 按 y 值升值排序的比较函数
bool cmpY(Point a, Point b) {
    return a.getY() < b.getY();
}

// PGroup: 打印点集所有点
void PGroup::display() {
    for (int i = 0; i < n; i++) {
        cout<<"("<<points[i].getX()<<", "<<points[i].getY()<<")";
        if (i != n-1) cout<<" ";
    }
    cout<<endl;
}

// PGroup: 返回点集中的某个点
Point PGroup::getPoints(int i) {
    return points[i];
}

// PGroup: 暴力求解
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

// PGroup: 分治法求解
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
        // 在 min_x 之前的点都在 pyLeft 里面
        // 因为不确定 min_x 线上的点属于 pyLeft 还是 pyRight,
        // 所以加入数量检查，超出 pyLeft 的点数的点就归pyRight了
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

    // 对 YL 中的每个点，求 YR 中它上方的3点和下方的3点的 dis
    for (int i = 0; i < mid.getN(); i++) {
        // 只检验 YL 的点， 如果是右边的边，pass
        if (mid.getPoints(i).getX() - mid_x >= 0)
            continue;

        int cmp_cnt = 0;
        for (int j = i - 1; j >= i - 3 - cmp_cnt && j >0; j--) {
            // 如果检验到的点是左点，cmp_cnt++，要往上多检验一个点，直到检验到 YR 的3个点
            if (mid.getPoints(j).getX() - mid_x < 0) {
                cmp_cnt++;
                continue;
            }

            Point tmpPoint = mid.getPoints(j);
            double cur_dis = mid.getPoints(i).getDisTo(tmpPoint);
            if (cur_dis < min_tol) {
                min_tol = cur_dis;
            }
        }

        cmp_cnt = 0;
        for (int j = i + 1; j <= i + 3 + cmp_cnt && j < mid.getN(); j++) {
            // 如果检验到的点是左点，cmp_cnt++，要往下多检验一个点，直到检验到 YR 的3个点
            if (mid.getPoints(j).getX() - mid_x < 0) {
                cmp_cnt++;
                continue;
            }

            Point tmpPoint = mid.getPoints(j);
            double cur_dis = mid.getPoints(i).getDisTo(tmpPoint);
            if (cur_dis < min_tol) {
                min_tol = cur_dis;
            }
        }
    }

    return min_tol;
}

