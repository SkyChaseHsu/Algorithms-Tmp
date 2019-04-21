#include <iostream>
#include <time.h>
#include <cmath>
#include <sstream>
#include <fstream>
using namespace std;

#include "point.h"

int main() {
    // 计算程序运行的时间
    time_t begin, end;

    // 点集的规模
    int N_v = 1000;

    // expri_data.csv: 两种方法的数据
    // expri_data_div.csv: 分治法的数据
    // expri_data_vio.csv: 暴力法的数据
    ofstream outcsv;
    outcsv.open("expri_data.csv", ios::out);
    outcsv<<"Type, N, Time(ms)"<<endl;

    ofstream outcsv_div;
    outcsv_div.open("expri_data_div.csv", ios::out);
    outcsv_div<<"Type, N, Time(ms)"<<endl;

    ofstream outcsv_vio;
    outcsv_vio.open("expri_data_vio.csv", ios::out);
    outcsv_vio<<"Type, N, Time(ms)"<<endl;

    // 点集规模从 N_v 到 10 * N_v
    // 分治法的运行时间
    for (int N = N_v; N <= N_v * 3; N += N_v) {
        // 20 次的运行时间总和
        double cost_time = 0;
        for (int i = 0; i < 20; i++) {
            PGroup pg(N);
            PGroup py(pg);
            pg.sortX();
            py.sortY();
            begin = clock();
            pg.dacMin(py);
            end = clock();

            // 运行时间：以 ms 为单位
            cost_time += (double) (end - begin) * 1000 / CLOCKS_PER_SEC;
        }

        // 平均运行时间
        double ave_time = cost_time / 20;

        cout<<"[DIV] | N = "<<N<<" \t| time = "<<ave_time<<" \tms"<<endl;
        outcsv<<"DIV,"<< N <<","<< ave_time <<endl;
        outcsv_div<<"DIV,"<< N <<","<< ave_time <<endl;
    }

    // 点集规模从 N_v 到 10 * N_v
    // 暴力法的运行时间
    for (int N = N_v; N <= N_v * 3; N += N_v) {
        // 20 次的运行时间总和
        double cost_time = 0;
        for (int i = 0; i < 20; i++) {
            PGroup pg(N);
            begin = clock();
            pg.vioMin();
            end = clock();

            // 运行时间：以 ms 为单位
            cost_time += (double) (end - begin) * 1000 / CLOCKS_PER_SEC;
        }

        // 平均运行时间
        double ave_time = cost_time / 20;

        cout<<"[VIO] | N = "<<N<<" \t| time = "<<ave_time<<" \tms"<<endl;
        outcsv<<"VIO,"<< N <<","<< ave_time <<endl;
        outcsv_vio<<"VIO,"<< N <<","<< ave_time <<endl;
    }

    // 关闭 csv 文件的输出
    outcsv.close();
    outcsv_div.close();
    outcsv_vio.close();

    return 0;
}