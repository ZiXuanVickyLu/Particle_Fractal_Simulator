//
// Created by birdpeople on 2020/10/14.
//

#include "pointset.h"
#include "quanta.h"
#include "ctime"
#include "cmath"

#define pi 3.1415926

double dist(point a,point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool quanta::IsCollided(pointset* ps)
{
    double stepl = 1e8;
    double dis = 0;
    for(int i = 0 ;i< ps->number; i++)
    {
        dis = dist(*(this->q), ps->quantas->at(i));
        stepl = stepl > dis? dis : stepl;
        if (dis <= num2(critical_distance)) {
            steplength = 0 ;
            min_dis = stepl;
            return true;
        }
    }

    min_dis = stepl;
    if(stepl >= num2(L1))
        steplength = L1 ;
    if (stepl < num2(L2))
        steplength = L3;
    else
        steplength = L2;

    return false;
}

pointset::pointset()
{
    pointset_radius = 0;
    quantas = new vector<point>;
    dis = new vector<double>;
    quantas->push_back(point(0,0));
    dis->push_back(0);
    number = 0;
    number ++;
}


Status pointset::PrintPoint()
{
    for(int i =0;i< this->number;i++)
        printf("Point %d: %lf%lf\n",i+1,this->quantas->at(i).x,this->quantas->at(i).y);
    printf("Finish Printf!");

    char fp_path[250];
     int i = sprintf(fp_path,rootpath);
     sprintf(fp_path + i,"pointset2.txt");

    FILE *fp=fopen(fp_path,"w");
    for(int i = 0 ;i<number ;++i)
        fprintf(fp,"%lf,%lf,%lf\n",quantas->at(i).x, quantas->at(i).y, dis->at(i));
    fclose(fp);
    cout << "Finished and Success !!!" << endl;
    return true;
}

double rg(double leftRange, double rightRange)//RANDOM_GENERATOR_EASY_VERSION
{
    return rand()% (int)(leftRange-rightRange)+ rand()/double(RAND_MAX);
}

point random_generator(point Pos, double theta, double range_r)
{
    point ans;
    ans.x = Pos.x + range_r * cos(theta/180.0 * pi);
    ans.y = Pos.y + range_r * sin(theta/180.0 * pi);
    return ans;
}

Status pointset::addQuanta(quanta *q)
{
    if(!q)
        return false;
    quantas->push_back(point(q->getx(),q->gety()));
    dis ->push_back(sqrt(q->min_dis));
    double r = sqrt(dist(point(0,0),*q->q)) + q->quanta_randius;
    pointset_radius = pointset_radius > r ? pointset_radius : r;
    ++ number;
    printf("add point %d: %lf, %lf \t\t at min_distance %lf \t\t ps_radius: %lf \n",number-1,q->getx(),q->gety(),sqrt(q->min_dis),pointset_radius);
    return true;
}
