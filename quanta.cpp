//
// Created by birdpeople on 2020/10/14.
//

#include "quanta.h"
#include "pointset.h"
#include "cmath"
#define pi 3.1415926
Status quanta::walk(pointset *ps)
{
    if(IsCollided(ps))
        return false;
    point pos(random_generator(*q,rg(1e-2,360),steplength));
    this->q->x = pos.x;
    this->q->y = pos.y;
    this ->OutrangeTest();
    setHistory();
    return true;
}

Status quanta::setHistory()
{
    HistoryPos->push_back(point(q->x,q->y));
    walktime ++;
    return true;
}


quanta& quanta::GenerateQuanta(double points_radius){
    double theta = rg(0,360);
    this->q->x = (points_radius + generateR) * cos(theta * pi / 180) ;
    this->q->y = (points_radius + generateR) * sin(theta * pi / 180);
    this ->OutrangeTest();
    setHistory();
    return *this;
}

Status quanta::printHistoryDestory(int number){

    char fp_path[250];
    int i = sprintf(fp_path,rootpath);
    sprintf(fp_path +i ,"point%d.txt",number);

    FILE *fp=fopen(fp_path,"w");
    for(int i = 0 ;i<walktime ;++i)
        fprintf(fp,"%lf,%lf\n",HistoryPos->at(i).x, HistoryPos->at(i).y);
    fclose(fp);
    delete HistoryPos;
    return true;

}

quanta::quanta(){
    HistoryPos = new vector<point>;
    q = new point;
    walktime = 0;
    generateR = R;
    quanta_randius = A;
    critical_distance = 2 * quanta_randius;
    energy = 0 ;
    steplength = 0;
    min_dis = 1e4;
    Range = L;
}
double Abs(double x){return x>0?x:-x;}

Status quanta::OutrangeTest()
{
    if(Abs(q->x) > Range) {
        q->x = (Abs(q->x) - Range) * (q->x > 0 ? -1 : 1);
        return true;
    }
    if(Abs(q->y) > Range) {
        q->y = (Abs(q->y) - Range) * (q->y > 0 ? -1 : 1);
        return true;
    }
    return false;
}