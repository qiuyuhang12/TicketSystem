//
// Created by qiuyuhang on 24-5-20.
//

#ifndef TICKETSYSTEM_DATEANDTIMESTRUCT_HPP
#define TICKETSYSTEM_DATEANDTIMESTRUCT_HPP

#include <iostream>

struct Time {//without =
    int hh = 0;
    int mm = 0;

    Time() = default;

    Time(int _hh, int _mm) : hh(_hh), mm(_mm) {}

    Time(Time const &other) = default;
};

struct Date {//without =
    int mm = 0;
    int dd = 0;

    Date() = default;

    Date(int _mm, int _dd) : mm(_mm), dd(_dd) {}

    Date(Date const &other) = default;
};

struct DateAndTime {
    Date date;
    Time time;

    DateAndTime() = default;

    DateAndTime(Date _date, Time _time) : date(_date), time(_time) {}
};

Time IntToTime(int x) {
    return {x / 60, x % 60};
}

Date IntToDate(int x) {
//        x is from june to august
    if (x <= 30) return {6, x};
    if (31 <= x && x <= 61) return {7, x - 30};
    if (x >= 62 && x <= 92)return {8, x - 61};
    return {9, x - 92};
}

DateAndTime IntToDateAndTime(int x) {
    return {IntToDate(x / 1440), IntToTime(x % 1440)};
}

std::ostream &operator<<(std::ostream &os, const Time &time) {
    if (time.hh < 10)os << '0';
    os << time.hh << ':';
    if (time.mm < 10)os << '0';
    os << time.mm;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    if (date.mm < 10)os << '0';
    os << date.mm << '-';
    if (date.dd < 10)os << '0';
    os << date.dd;
    return os;
}

std::ostream &operator<<(std::ostream &os, const DateAndTime &dateAndTime) {
    os << dateAndTime.date << ' ' << dateAndTime.time;
    return os;
}

DateAndTime makeDateAndTime(int day, int time) {
    DateAndTime res;
    res.time = IntToTime(time);
    if (res.time.hh >= 24) {
        day += res.time.hh / 24;
        res.time.hh %= 24;
    }
    res.date = IntToDate(day);
    return res;
}

#endif //TICKETSYSTEM_DATEANDTIMESTRUCT_HPP
