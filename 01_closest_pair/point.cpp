//
// Created by xukexin on 2019/4/15.
//

#include "point.h"

#include <iostream>
using namespace std;
#include <cmath>
#include <cfloat>

#define random(a,b) (rand()%(b-a+1)+a)

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x_v, int y_v) {
    x = x_v;
    y = y_v;
}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

void Point::setXY(int x_v, int y_v) {
    x = x_v;
    y = y_v;
}

double Point::getDisTo(Point &p) {
    return sqrt(pow(x - p.getX(), 2) + pow(y - p.getY(), 2));
}

PGroup::PGroup(int n_v) {
    n = n_v;
    points = new Point[n_v];
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        points[i].setXY(random(1, 100000), random(1, 100000));
    }
}
PGroup::~PGroup() {
    delete []points;
}

void PGroup::sortX() {
    sort(points, points + n, cmpX);
}

void PGroup::sortY() {
    sort(points, points + n, cmpY);
}

double PGroup::vioMin() {
    if (n < 2){
        return DBL_MAX;
    } else if (n == 2) {
        return points[0].getDisTo(points[1]);
    }

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

double PGroup::dacMin() {
    if (n < 2){
        return DBL_MAX;
    } else if (n == 2) {
        return points[0].getDisTo(points[1]);
    }

    sortX();
    int mid_x = points[n/2].getX();

    PGroup left(n/2);
    PGroup right(n - n/2);


    for (int i = 0; i < n/2; i++) {
        left.setPoint(i, points[i].getX(),points[i].getY());
    }

    for(int i = n/2, j = 0; i < n; i++, j++) {
        right.setPoint(j, points[i].getX(),points[i].getY());
    }

    double left_min = left.dacMin();
    double right_min = right.dacMin();
    double tol_min = left_min < right_min? left_min : right_min;

    PGroup mid(n);

    int mid_cnt = 0;
    for(int i = 0; i < n; i++) {
        if (abs(points[i].getX() - mid_x) <= tol_min) {
            mid.setPoint(mid_cnt++, points[i].getX(), points[i].getY());
        }
    }
    mid.setN(mid_cnt);
    mid.sortY();

    for (int i = 0; i < mid.getN(); i++) {
        if (mid.getPoints(i).getX() - mid_x >= 0)
            continue;
        int cmp_cnt = 0;
        for (int j = i + 1; j <= i + 6 + cmp_cnt && j < mid.getN(); j++) {
            if (mid.getPoints(j).getX() - mid_x < 0) {
                cmp_cnt++;
                continue;
            }

            Point tmp = mid.getPoints(j);
            double cur_dis = mid.getPoints(i).getDisTo(tmp);
            if (cur_dis < tol_min) {
                tol_min = cur_dis;
            }
        }
    }

    return tol_min;
}

void PGroup::setN(int n_v) {
    n = n_v;
}

void PGroup::setPoint(int i, int x_v, int y_v) {
    points[i].setXY(x_v, y_v);
}

void PGroup::display() {
    for (int i = 0; i < n; i++) {
        cout<<"("<<points[i].getX()<<", "<<points[i].getY()<<")";
        if (i != n-1) cout<<" ";
    }
    cout<<endl;
}

Point PGroup::getPoints(int i) {
    return points[i];
}

int PGroup::getN() {
    return n;
}

bool cmpX(Point a, Point b) {
    return a.getX() < b.getX();
}

bool cmpY(Point a, Point b) {
    return a.getY() < b.getY();
}