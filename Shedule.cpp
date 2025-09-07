#include "Shedule.h"
#include<iostream>
using namespace std;

Schedule::Schedule(Time_ start, int lessonDur, int shortBr, int longBr, int longAfter, int lessons)
{
    startTime = start;
    lessonDuration = (lessonDur > 0) ? lessonDur : 45;
    shortBreak = (shortBr >= 0) ? shortBr : 5;
    longBreak = (longBr >= 0) ? longBr : 15;
    longBreakAfter = (longAfter > 0) ? longAfter : 3;
    totalLessons = (lessons > 0) ? lessons : 6;
}

void Schedule::generateSchedule() const
{
    Time_ current = startTime;
    for (int i = 1; i <= totalLessons; i++)
    {
        cout << "Lesson " << i << ": ";
        current.showTime();
        Time_ endLesson = current + lessonDuration;
        cout << "   until ";
        endLesson.showTime();
        current = endLesson;
        if (i < totalLessons)
        {
            if (i == longBreakAfter)
            {
                cout << "   Long break: ";
                current.showTime();
                current += longBreak;
                cout << " - ";
                current.showTime();
            }
            else
            {
                cout << "   Short break: ";
                current.showTime();
                current += shortBreak;
                cout << " - ";
                current.showTime();
            }
        }
        cout << "------------------------\n";
    }
}
