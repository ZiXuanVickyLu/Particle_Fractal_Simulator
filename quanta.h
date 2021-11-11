//
// Created by birdpeople on 2020/10/14.
//

#ifndef SEARCH_QUANTA_H
#define SEARCH_QUANTA_H
#include <vector>
#include "pointset.h"
#define Status bool
#define rootpath  "/Users/birdpeople/CLionProjects/search/data/" //please make sure the directory has already exist !
#define  num2(L) L * L

//--------------------------------------- defined in paper -----------------------------------------------
#define L1 100      //map layer
#define L2 10
#define L3 1

#define R 3         // quanta born at Rm + \triangle R
#define A 1         // radius of a quanta ;dr = 2A
#define M 5e4       // number of quanta test
#define L 1000     // L*L

//------------------------------------------ end define ------------------------------------------------------


using namespace std;
struct point{
    double x; double y;
    point(double xx,double yy):x(xx),y(yy){};
    point(){};
};

double Abs(double x);
double rg(double leftRange, double rightRange);
point random_generator(point Pos, double theta, double r);
double dist(point a,point b);

//---------------------------------------------------- class quanta ----------------------------------------------------
class quanta {

    point *q;                    // quanta itself
    vector<point>* HistoryPos;   // position it walk bypass
    int walktime;                // times it walk totally
    int generateR;               // when generated, it will born in area cir(pointset_radius + R) ; R in paper = 3
    int steplength;              // map layer L1,L2,L3
    double min_dis;              // SMD to the pointset
    double quanta_randius;       // quanta radius; a = 1
    double critical_distance;    // critical distance dr = 2a = 2;
    double energy;               // energy it generator
    double Range;

public:
    friend pointset;
    double getx(){return this->q->x;};
    double gety(){return this->q->y;};
    Status walk(pointset *ps);                 // walk a quanta if it is not collided to pointset
    Status setHistory();          // add information to HistoryPos
    bool IsCollided(pointset* ps);// if collided add to pointset, goto printHistoryDestory; others adjust steplength
    quanta& GenerateQuanta(double pointset_radius);     // generate a quanta and initialize it private var
    Status printHistoryDestory(int number); // print the HistoryPos and destory the quanta, used when add to pointset
    Status OutrangeTest();      // test after walk , adjust the pos when out of range, use circulated edge-condition
    quanta();
    ~quanta() = default;

};



#endif //SEARCH_QUANTA_H
