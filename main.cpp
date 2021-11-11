

#include "pointset.h"
#include "quanta.h"

Status Event(pointset *ps)
{
    auto *quan = new quanta ;
    if(!quan)
        return false;

    quan -> GenerateQuanta(ps -> pointset_radius);
    while (quan -> walk(ps));
    ps -> addQuanta(quan);

    if(FILE_PRINT_ON)
        quan -> printHistoryDestory(ps -> number - 1);

    delete quan;
    return true;
}

int main() {

    srand((int)time(nullptr));
    int event_count = 0;
    auto *ps = new pointset;
    while(Event(ps) && event_count < M) ++event_count;
    ps->PrintPoint();
    delete ps;
   return 0;

}