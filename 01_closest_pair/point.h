//
// Created by xukexin on 2019/4/15.
//

#ifndef CLOSESTPOINTS_POINT_H
#define CLOSESTPOINTS_POINT_H

class Point;
class PGroup;

class Point {
    int x, y;
public:
    Point();
    Point(int x_v, int y_v);
    int getX();
    int getY();
    void setXY(int x_v, int y_v);
    double getDisTo(Point &p);
    int inside (PGroup pg);
};

class PGroup {
    int n;
    Point * points;
public:
    PGroup() {}
    PGroup(int n);
    PGroup(PGroup &pg);
    ~PGroup();
    void sortX();
    void sortY();
    double vioMin();
    double dacMin(PGroup py);
    void setN(int n_v);
    void setPoint(int i, int x_v, int y_v);
    void display();
    Point getPoints(int i);
    int getN();
};

bool cmpX(Point a, Point b);
bool cmpY(Point a, Point b);


#endif //CLOSESTPOINTS_POINT_H
