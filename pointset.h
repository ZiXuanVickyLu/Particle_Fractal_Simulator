//
// Created by birdpeople on 2020/10/14.
//

#ifndef SEARCH_POINTSET_H
#define SEARCH_POINTSET_H

#ifndef Status
#define Status bool
#define rootpath  "/Users/birdpeople/CLionProjects/search/data/"
#define FILE_PRINT_ON 0
#endif

#include<vector>
#include <iostream>
using namespace std;
struct point;
class quanta;

class pointset {
    vector<point> *quantas; // quanta pos
    vector<double> *dis;    // SMD of each quantas at history

public:
    double pointset_radius; // Rm
    int number;             // number
    friend quanta;
    pointset();             // initialize and add the points
    ~pointset() = default;
    Status PrintPoint();    // print each point
    Status addQuanta(quanta *q);
};



#endif //SEARCH_POINTSET_H
