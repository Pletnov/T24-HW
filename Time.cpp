#include "Time.h"
#include<ctime>
using namespace std;
#include<iostream>
Time_::Time_()
{
    auto t = time(NULL);
    tm* now = new tm;
    localtime_s(now, &t);
    hour = now->tm_hour;
    minutes = now->tm_min;
    seconds = now->tm_sec;
    format = true; 
}

Time_::Time_(int hour, int minutes, int seconds, bool format)
{
    this->format = format;
    if (format) {
        this->hour = (hour >= 0 && hour < 24) ? hour : 0;
    }
    else {
        this->hour = (hour >= 1 && hour <= 12) ? hour : 12;
    }
    this->minutes = (minutes >= 0 && minutes < 60) ? minutes : 0;
    this->seconds = (seconds >= 0 && seconds < 60) ? seconds : 0;
}

void Time_::setHour(int hour)
{
    if (format) {
        if (hour >= 0 && hour < 24)
            this->hour = hour;
    }
    else {
        if (hour >= 1 && hour <= 12)
            this->hour = hour;
    }
}

int Time_::getHour() const
{
    return hour;
}

void Time_::setMinutes(int minutes)
{
    if (minutes >= 0 && minutes < 60) {
        this->minutes = minutes;
    }
}

int Time_::getMinutes() const
{
    return minutes;
}

void Time_::setSeconds(int seconds)
{
    if (seconds >= 0 && seconds < 60) {
        this->seconds = seconds;
    }
}

int Time_::getSeconds() const
{
    return seconds;
}

void Time_::setFormat(bool format)
{
    this->format = format;
}

bool Time_::getFormat() const
{
    return format;
}

bool Time_::valid() const
{
    if(format) {
        return (hour >= 0 && hour < 24) &&
            (minutes >= 0 && minutes < 60) &&
            (seconds >= 0 && seconds < 60);
    }
    else {
     return (hour >= 1 && hour <= 12) &&
         (minutes >= 0 && minutes < 60) &&
         (seconds >= 0 && seconds < 60);
    }
}

void Time_::tickTime()
{
    seconds++;
    if (seconds == 60) {
        seconds = 0;
        minutes++;
        if (minutes == 60) {
            minutes = 0;
            hour++;
            if (format) {
                if (hour == 24) hour = 0;
            }
            else {
                if (hour > 12) hour = 1;
            }
        }
    }
}

void Time_::untickTime()
{
    seconds--;
    if (seconds < 0) {
        seconds = 59;
        minutes--;
        if (minutes < 0) {
            minutes = 59;
            hour--;
            if (format) {
                if (hour < 0) hour = 23;
            }
            else {
                if (hour < 1) hour = 12;
            }
        }
    }
}

void Time_::showTime() const
{
    if (format) {
        if (hour < 10) cout << "0";
        cout << hour << ":";
        if (minutes < 10) cout << "0";
        cout << minutes << ":";
        if (seconds < 10) cout << "0";
        cout << seconds << "\n";
    }
    else {
        int displayHour = hour % 12;
        if (displayHour == 0) displayHour = 12;
        string ampm = (hour < 12) ? "AM" : "PM";
        if (displayHour < 10) cout << "0";
        cout << displayHour << ":";
        if (minutes < 10) cout << "0";
        cout << minutes << ":";
        if (seconds < 10) cout << "0";
        cout << seconds;
        cout << " " << ampm << "\n";
    }
}

bool Time_::operator==(const Time_& obj) const&
{
    if (this->seconds == obj.seconds && this->minutes == obj.minutes && this->hour == obj.hour) {
        return true;
    }
    else return false;
}

bool Time_::operator!=(const Time_& obj) const&
{
    return !(*this == obj);
}

bool Time_::operator>(const Time_& obj) const&
{
    if (this->hour > obj.hour) {
        return true;
    }
    else if (this->hour == obj.hour && this->minutes > obj.minutes) {
        return true;
    }
    else if (this->hour == obj.hour && this->minutes == obj.minutes && this->seconds > obj.seconds) {
        return true;
    }
    else return false;
}

bool Time_::operator<(const Time_& obj) const&
{
    if (this->hour < obj.hour) {
        return true;
    }
    else if (this->hour == obj.hour && this->minutes < obj.minutes) {
        return true;
    }
    else if (this->hour == obj.hour && this->minutes == obj.minutes && this->seconds < obj.seconds) {
        return true;
    }
    else return false;
}

bool Time_::operator>=(const Time_& obj) const&
{
    return !(*this > obj) || (*this == obj);
}

bool Time_::operator<=(const Time_& obj) const&
{
    return !(*this < obj) || (*this == obj);
}

Time_& Time_::operator+=(float s)
{
    int sec = s; 
    seconds += sec;
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    if (minutes >= 60) {
        hour += minutes / 60;
        minutes %= 60;
    }
    if (format) {
        hour %= 24;
    }
    else {
        hour = 1 + (hour - 1) % 12;
    }
    return *this;
}

Time_& Time_::operator-=(float s)
{
    int sec = s;
    seconds -= sec;
    while (seconds < 0) {
        seconds += 60;
        minutes--;
    }
    while (minutes < 0) {
        minutes += 60;
        hour--;
    }
    if (format) {
        if (hour < 0) hour = (hour % 24 + 24) % 24;
    }
    else {
        while (hour < 1) hour += 12;
    }
    return *this;
}

Time_& Time_::operator+=(int m)
{
    minutes += m;
    if (minutes >= 60) {
        hour += minutes / 60;
        minutes %= 60;
    }
    if (format) {
        hour %= 24;
    }
    else {
        hour = ((hour - 1) % 12) + 1;
    }
    return *this;
}

Time_& Time_::operator-=(int m)
{
    minutes -= m;
    while (minutes < 0) {
        minutes += 60;
        hour--;
    }
    if (format) {
        if (hour < 0) hour = (hour % 24 + 24) % 24;
    }
    else {
        while (hour < 1) hour += 12;
    }
    return *this;
}

Time_& Time_::operator+=(long h)
{
    hour += h;
    if (format) {
        hour = (hour % 24 + 24) % 24;
    }
    else {
        while (hour < 1) hour += 12;
        hour = ((hour - 1) % 12) + 1;
    }
    return *this;
}

Time_& Time_::operator-=(long h)
{
    hour -= h;
    if (format) {
        hour = (hour % 24 + 24) % 24;
    }
    else {
        while (hour < 1) hour += 12;
        hour = ((hour - 1) % 12) + 1;
    }
    return *this;
}

Time_ Time_::operator+(float s) const&
{
    Time_ tmp = *this;
    tmp += s;
    return tmp;
}

Time_ Time_::operator-(float s) const&
{
    Time_ tmp = *this;
    tmp -= s;
    return tmp;
}

Time_ Time_::operator+(int m) const&
{
    Time_ tmp = *this;
    tmp += m;
    return tmp;
}

Time_ Time_::operator-(int m) const&
{
    Time_ tmp = *this;
    tmp -= m;
    return tmp;
}

Time_ Time_::operator+(long h) const&
{
    Time_ tmp = *this;
    tmp += h;
    return tmp;
}

Time_ Time_::operator-(long h) const&
{
    Time_ tmp = *this;
    tmp -= h;
    return tmp;
}
