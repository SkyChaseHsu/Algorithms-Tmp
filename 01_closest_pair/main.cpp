#include <iostream>
#include <time.h>
#include <cmath>
#include <sstream>
#include <fstream>
using namespace std;

#include "point.h"

int main() {
    time_t begin, end;

    int N_v = 1000; // basic N value

    ofstream outcsv;
    outcsv.open("expri_data.csv", ios::out);
    outcsv<<"Type, N, Time(ms)"<<endl;

    ofstream outcsv_div;
    outcsv_div.open("expri_data_div.csv", ios::out);
    outcsv_div<<"Type, N, Time(ms)"<<endl;

    ofstream outcsv_vio;
    outcsv_vio.open("expri_data_vio.csv", ios::out);
    outcsv_vio<<"Type, N, Time(ms)"<<endl;

    for (int N = N_v; N <= N_v * 10; N += N_v) {
        double cost_time = 0;
        for (int i = 0; i < 20; i++) {
            PGroup pg(N);
            begin = clock();
            pg.dacMin();
            end = clock();
            cost_time += (double) (end - begin) * 1000 / CLOCKS_PER_SEC;
        }

        double ave_time = cost_time / 20;

        cout<<"[DIV] | N = "<<N<<" \t| time = "<<ave_time<<" \tms"<<endl;
        outcsv<<"DIV,"<< N <<","<< ave_time <<endl;
        outcsv_div<<"DIV,"<< N <<","<< ave_time <<endl;
    }

    for (int N = N_v; N <= N_v * 10; N += N_v) {
        double cost_time = 0;
        for (int i = 0; i < 20; i++) {
            PGroup pg(N);
            begin = clock();
            pg.vioMin();
            end = clock();
            cost_time += (double) (end - begin) * 1000 / CLOCKS_PER_SEC;
        }

        double ave_time = cost_time / 20;

        cout<<"[VIO] | N = "<<N<<" \t| time = "<<ave_time<<" \tms"<<endl;
        outcsv<<"VIO,"<< N <<","<< ave_time <<endl;
        outcsv_vio<<"VIO,"<< N <<","<< ave_time <<endl;
    }

    outcsv.close();
    outcsv_div.close();
    outcsv_vio.close();

    return 0;
}