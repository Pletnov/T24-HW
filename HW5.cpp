#include <iostream>
#include "Time.h"
#include"Shedule.h"
using namespace std;
int main() {
    Time_ start(13, 20, 0, true);
    Schedule schedule(start, 45, 10, 20, 3, 4);
    schedule.generateSchedule();
    return 0;
}