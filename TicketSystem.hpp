//
// Created by qiuyuhang on 24-5-18.
//

#ifndef TICKETSYSTEM_TICKETSYSTEM_HPP
#define TICKETSYSTEM_TICKETSYSTEM_HPP
#define debug

#include "BPT/BPT.hpp"

#ifdef debug

#include <vector>
#include <map>

template<typename T>
std::vector<T> sjtuVtoStdV(const sjtu::vector<T> &v) {
    std::vector<T> rsl;
    for (auto &i: v) {
        rsl.push_back(i);
    }
    return rsl;
}

#define sjtu std
#endif


void splitString(const std::string &str, sjtu::vector<std::string> &res) {
    res.clear();
    std::string tmp;
    for (int i = 0; i < str.size(); ++i) {
#ifdef debug
        if (str[i] == '\n')assert(i == str.size() - 1);
#endif
        if (str[i] == ' ' || str[i] == '\r' || str[i] == '\t' || str[i] == '\v' || str[i] == '\f') {
            if (tmp.empty())continue;
            res.push_back(tmp);
            tmp.clear();
        } else {//utf-8
            //11110xxx
            if (str[i] >> 3 == (char) 0b11111110) {
//                std::cout<<"11110xxx------------------------------------------------"<<std::endl;
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                tmp.push_back(str[i + 2]);
                tmp.push_back(str[i + 3]);
                i += 3;
            }
                //1110xxxx
            else if (str[i] >> 4 == (char) 0b11111110) {
//                std::cout<<"1110xxxx------------------------------------------------"<<std::endl;
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                tmp.push_back(str[i + 2]);
                i += 2;
            }
                //110xxxxx
            else if (str[i] >> 5 == (char) 0b11111110) {
//                std::cout<<"110xxxxx------------------------------------------------"<<std::endl;
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                i += 1;
            }
                //10xxxxxxx&0xxxxxxx
            else {
//                if (str[i]>>6 == (char)0b11111110)std::cout<<"10xxxxxxx------------------------------------------------"<<std::endl;
//                else std::cout<<"0xxxxxxx------------------------------------------------"<<std::endl;
                tmp.push_back(str[i]);
            }
        }
    }
    if (!tmp.empty())res.push_back(tmp);
}

int timestampStrToInt(const std::string &str) {
#ifdef debug
    assert(str.size() > 2);
    assert(str[0] == '[');
    assert(str[str.size() - 1] == ']');
#endif
    int rsl = 0;
    for (int i = 1; i < str.size() - 1; ++i) {
        rsl = rsl * 10 + str[i] - '0';
    }
    return rsl;
}

int StringToInt(const std::string &str) {
    int rsl = 0;
    for (int i = 0; i < str.size(); ++i) {
#ifdef debug
        assert(str[i] >= '0' && str[i] <= '9');
#endif
        rsl = rsl * 10 + str[i] - '0';
    }
    return rsl;
}

void clearFile() {
    remove("Station_TrainID_ToTrainForQTBlocks");
    remove("Station_TrainID_ToTrainForQTNodes");
    remove("Station_TrainID_ToTrainForQTOlyIDBlocks");
    remove("Station_TrainID_ToTrainForQTOlyIDNodes");
    remove("TrainID_ToTrainBlocks");
    remove("TrainID_ToTrainNodes");
    remove("TrainIDDate_ToPendsBlocks");
    remove("TrainIDDate_ToPendsNodes");
    remove("TrainIDDate_ToReleasedTrainBlocks");
    remove("TrainIDDate_ToReleasedTrainNodes");
    remove("Username_ToOrdersBlocks");
    remove("Username_ToOrdersNodes");
    remove("Username_ToUserBlocks");
    remove("Username_ToUserNodes");
}
//int timeStrToInt(const std::string &str) {
//    int hh = (str[0] - '0') * 10 + (str[1] - '0');
//    int mm = (str[3] - '0') * 10 + (str[4] - '0');
//    return hh * 60 + mm;
//}

class TicketSystem {
private:
#ifdef debug
public:
#endif

private://basic data structure
#ifdef debug
public:
#endif
//    todo：修改price为累计价格
    enum orderStatus {
        success,
        pending,
        refunded
    };

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

    static Time IntToTime(int x) {
        return {x / 60, x % 60};
    }

    static Date IntToDate(int x) {
//        x is from june to august
        if (x <= 30) return {6, x};
        if (31 <= x && x <= 61) return {7, x - 30};
        return {8, x - 61};
    }

    static DateAndTime IntToDateAndTime(int x) {
        return {IntToDate(x / 1440), IntToTime(x % 1440)};
    }

    struct User {
        int timestamp = 0;//only for debug (createTime)
        char username[21] = {};//unique
        char password[31] = {};
        char name[21] = {};
        char mailAddr[31] = {};
        int privilege = 0;

        //默认构造，从变量构造，拷贝构造，拷贝赋值，< 重载，== 重载，!= 重载
        User() = default;

        User(const std::string &_username, const std::string &_password, const std::string &_name,
             const std::string &_mailAddr, int _privilege, int _timestamp = 0) : timestamp(_timestamp) {
            strcpy(username, _username.c_str());
            strcpy(password, _password.c_str());
            strcpy(name, _name.c_str());
            strcpy(mailAddr, _mailAddr.c_str());
            privilege = _privilege;
        }

        User(const User &other) {
            timestamp = other.timestamp;
            strcpy(username, other.username);
            strcpy(password, other.password);
            strcpy(name, other.name);
            strcpy(mailAddr, other.mailAddr);
            privilege = other.privilege;
        }

        User &operator=(const User &other) {
            if (this == &other)return *this;
            timestamp = other.timestamp;
            strcpy(username, other.username);
            strcpy(password, other.password);
            strcpy(name, other.name);
            strcpy(mailAddr, other.mailAddr);
            privilege = other.privilege;
            return *this;
        }

        bool operator<(const User &other) const {
            return strcmp(username, other.username) < 0;
        }

        bool operator==(const User &other) const {
            return strcmp(username, other.username) == 0;
        }

        bool operator!=(const User &other) const {
            return strcmp(username, other.username) != 0;
        }
    };

    struct Train {
        int timestamp = 0;//only for debug (createTime)
        bool released = false;
        char trainID[21] = {};//unique
        int stationNum = 0;
        char stations[101][31] = {};
        int seatNum = 0;
        int price[101] = {};//0无意义（为0），1为始发站到第一站的价格
        int startTime = 0;
        int travelTime[101] = {};
        int stopoverTime[101] = {};
        int saleDate[2] = {};
        char type = 0;

        //默认构造，从变量构造，拷贝构造，拷贝赋值，< 重载，== 重载，!= 重载
        Train() = default;

        Train(const std::string &_trainID, int _stationNum, const sjtu::vector<std::string> &_stations, int _seatNum,
              const sjtu::vector<int> &_price, int _startTime, const sjtu::vector<int> &_travelTime,
              const sjtu::vector<int> &_stopoverTime, const sjtu::vector<int> &_saleDate, char _type,
              int _timestamp = 0) : timestamp(_timestamp) {
            strcpy(trainID, _trainID.c_str());
            stationNum = _stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], _stations[i].c_str());
            }
            seatNum = _seatNum;
            for (int i = 0; i < stationNum; i++) {
                price[i] = _price[i];
            }
            startTime = _startTime;
            for (int i = 0; i < stationNum; i++) {
                travelTime[i] = _travelTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                stopoverTime[i] = _stopoverTime[i];
            }
            for (int i = 0; i < 2; i++) {
                saleDate[i] = _saleDate[i];
            }
            type = _type;
        }

        Train(const Train &other) {
            timestamp = other.timestamp;
            released = other.released;
            strcpy(trainID, other.trainID);
            stationNum = other.stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], other.stations[i]);
            }
            seatNum = other.seatNum;
            for (int i = 0; i < stationNum; i++) {
                price[i] = other.price[i];
            }
            startTime = other.startTime;
            for (int i = 0; i < stationNum; i++) {
                travelTime[i] = other.travelTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                stopoverTime[i] = other.stopoverTime[i];
            }
            for (int i = 0; i < 2; i++) {
                saleDate[i] = other.saleDate[i];
            }
            type = other.type;
        }

        Train &operator=(const Train &other) {
            if (this == &other)return *this;
            timestamp = other.timestamp;
            released = other.released;
            strcpy(trainID, other.trainID);
            stationNum = other.stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], other.stations[i]);
            }
            seatNum = other.seatNum;
            for (int i = 0; i < stationNum; i++) {
                price[i] = other.price[i];
            }
            startTime = other.startTime;
            for (int i = 0; i < stationNum; i++) {
                travelTime[i] = other.travelTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                stopoverTime[i] = other.stopoverTime[i];
            }
            for (int i = 0; i < 2; i++) {
                saleDate[i] = other.saleDate[i];
            }
            type = other.type;
            return *this;
        }

        bool operator<(const Train &other) const {
            return strcmp(trainID, other.trainID) < 0;
        }

        bool operator==(const Train &other) const {
            return strcmp(trainID, other.trainID) == 0;
        }

        bool operator!=(const Train &other) const {
            return strcmp(trainID, other.trainID) != 0;
        }
    };

    struct releasedTrain {//先id序 后time序
        int timestamp = 0;//only for debug (releaseTime)
        char trainID[21] = {};//unique
        int date = 0;
        int stationNum = 0;
        char stations[101][31] = {};//0为始发站
        int startTime = 0;
        int travelTime[101] = {};//0无意义（为0），1为始发站到第一站的时间
        int stopoverTime[101] = {};//0无意义（为0），1为第一站停靠时间
        int price[101] = {};
        int restTickets[101] = {};//0为从始发站到第一站的余票
        int seatNum = 0;//only for debug
        char type = 0;//only for debug
        //默认构造，从变量构造，拷贝构造，拷贝赋值，< 重载，== 重载，!= 重载
        releasedTrain() = default;

        releasedTrain(const std::string &_trainID, int _date, int _stationNum,
                      const sjtu::vector<std::string> &_stations,
                      int _startTime, const sjtu::vector<int> &_travelTime, const sjtu::vector<int> &_stopoverTime,
                      const sjtu::vector<int> &_price, const sjtu::vector<int> &_restTickets, int _seatNum, char _type,
                      int _timestamp = 0) : timestamp(_timestamp) {
            strcpy(trainID, _trainID.c_str());
            date = _date;
            stationNum = _stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], _stations[i].c_str());
            }
            startTime = _startTime;
            for (int i = 0; i < stationNum; i++) {
                travelTime[i] = _travelTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                stopoverTime[i] = _stopoverTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                price[i] = _price[i];
            }
            for (int i = 0; i < stationNum; i++) {
                restTickets[i] = _restTickets[i];
            }
            seatNum = _seatNum;
            type = _type;
        }

        releasedTrain &operator=(const releasedTrain &other) {
            if (this == &other)return *this;
            timestamp = other.timestamp;
            strcpy(trainID, other.trainID);
            date = other.date;
            stationNum = other.stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], other.stations[i]);
            }
            startTime = other.startTime;
            for (int i = 0; i < stationNum; i++) {
                travelTime[i] = other.travelTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                stopoverTime[i] = other.stopoverTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                price[i] = other.price[i];
            }
            for (int i = 0; i < stationNum; i++) {
                restTickets[i] = other.restTickets[i];
            }
            seatNum = other.seatNum;
            type = other.type;
            return *this;
        }

        bool operator<(const releasedTrain &other) const {
            if (strcmp(trainID, other.trainID) != 0)return strcmp(trainID, other.trainID) < 0;
            return date < other.date;
        }

        bool operator==(const releasedTrain &other) const {
            return strcmp(trainID, other.trainID) == 0 && date == other.date;
        }

        bool operator!=(const releasedTrain &other) const {
            return strcmp(trainID, other.trainID) != 0 || date != other.date;
        }
    };

    struct Order {
        int timestamp = 0;//only for debug (createTime)
        char username[21] = {};//only for debug
        orderStatus status = success;
        char trainID[21] = {};
        char from[41] = {};
        int leavingDateAndTime = 0;
        char to[41] = {};
        int arrivingDateAndTime = 0;
        int price = 0;
        int num = 0;
    };
    struct Pend {
        char trainID[21] = {};//only for debug
        int leavingDateFromFirstStation = 0;//only for debug
        int timestamp = 0;//only for debug (createTime)
        char username[21] = {};
        char from[41] = {};
        char to[41] = {};
        int price = 0;
        int num = 0;
    };
    struct LogUser {
        int timestamp = 0;//only for debug (logInTime)
//        char username[21] = {};//unique
        int privilege = 0;
    };

    //注意换乘排除同一辆车
    struct TrainForQT {//time序
        char trainID[21] = {};//unique
        int nowStation = 0;//是第几站（0为始发站）
        int nowTime = 0;//到达本站时间（可大于24：00，以发车日0时为准）
        int nowPrice = 0;//当前车票累计价格
        int stationNum = 0;
        char stations[101][31] = {};
        int saleDate[2] = {};
        int travelTime[101] = {};
        int stopoverTime[101] = {};
        int price[101] = {};
        char type = 0;//不需要？
        //默认构造，从变量构造，拷贝构造，拷贝赋值，< 重载，== 重载，!= 重载
        TrainForQT() = default;

        TrainForQT(const std::string &_trainID, int _nowStation, int _nowTime, int _nowPrice, int _stationNum,
                   const sjtu::vector<std::string> &_stations, const sjtu::vector<int> &_saleDate,
                   const sjtu::vector<int> &_travelTime, const sjtu::vector<int> &_stopoverTime,
                   const sjtu::vector<int> &_price, char _type) {
            strcpy(trainID, _trainID.c_str());
            nowStation = _nowStation;
            nowTime = _nowTime;
            nowPrice = _nowPrice;
            stationNum = _stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], _stations[i].c_str());
            }
            for (int i = 0; i < 2; i++) {
                saleDate[i] = _saleDate[i];
            }
            for (int i = 0; i < stationNum; i++) {
                travelTime[i] = _travelTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                stopoverTime[i] = _stopoverTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                price[i] = _price[i];
            }
            type = _type;
        }

        TrainForQT &operator=(const TrainForQT &other) {
            if (this == &other)return *this;
            strcpy(trainID, other.trainID);
            nowStation = other.nowStation;
            nowTime = other.nowTime;
            nowPrice = other.nowPrice;
            stationNum = other.stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], other.stations[i]);
            }
            for (int i = 0; i < 2; i++) {
                saleDate[i] = other.saleDate[i];
            }
            for (int i = 0; i < stationNum; i++) {
                travelTime[i] = other.travelTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                stopoverTime[i] = other.stopoverTime[i];
            }
            for (int i = 0; i < stationNum; i++) {
                price[i] = other.price[i];
            }
            type = other.type;
            return *this;
        }

        bool operator<(const TrainForQT &other) const {
            //1 stations[nowStation] < other.station[nowStation],2 Date[0] , 3Date[1],4 trainid
            int flag = strcmp(stations[nowStation], other.stations[other.nowStation]);
            if (flag != 0)return flag < 0;
            if (saleDate[0] != other.saleDate[0])return saleDate[0] < other.saleDate[0];
            if (saleDate[1] != other.saleDate[1])return saleDate[1] < other.saleDate[1];
            return strcmp(trainID, other.trainID) < 0;
        }

        bool operator==(const TrainForQT &other) const {
            return strcmp(trainID, other.trainID) == 0 && nowStation == other.nowStation;
        }
    };

    struct TrainForQTOnlyId {
        char trainID[21] = {};//unique
        int nowStation = 0;//是第几站（0为始发站）
        int nowTime = 0;//到达本站时间（可大于24：00，以发车日0时为准）
        int nowPrice = 0;//当前车票累计价格
        //默认构造，从变量构造，拷贝构造，拷贝赋值，< 重载，== 重载，!= 重载
        TrainForQTOnlyId() = default;

        TrainForQTOnlyId(const std::string &_trainID, int _nowStation, int _nowTime, int _nowPrice) {
            strcpy(trainID, _trainID.c_str());
            nowStation = _nowStation;
            nowTime = _nowTime;
            nowPrice = _nowPrice;
        }

        TrainForQTOnlyId &operator=(TrainForQTOnlyId const &other) {
            if (this == &other)return *this;
            strcpy(trainID, other.trainID);
            nowStation = other.nowStation;
            nowTime = other.nowTime;
            nowPrice = other.nowPrice;
            return *this;
        }

        bool operator<(TrainForQTOnlyId const &other) const {
            return strcmp(trainID, other.trainID) < 0;
        }

        bool operator==(TrainForQTOnlyId const &other) const {
            return strcmp(trainID, other.trainID) == 0;
        }

        bool operator!=(TrainForQTOnlyId const &other) const {
            return strcmp(trainID, other.trainID) != 0;
        }
    };

    struct UsernameForBPT {
        char val[21] = {};//unique
        bool isMin = false;
        char realVal = 0;

        UsernameForBPT() = default;

        explicit UsernameForBPT(const std::string &_username) {
            strcpy(val, _username.c_str());
        }

        UsernameForBPT(const UsernameForBPT &other) {
            strcpy(val, other.val);
        }

        UsernameForBPT &operator=(const UsernameForBPT &other) {
            if (this == &other)return *this;
            strcpy(val, other.val);
            return *this;
        }

        bool operator<(const UsernameForBPT &other) const {
            return strcmp(val, other.val) < 0;
        }

        bool operator==(const UsernameForBPT &other) const {
            return strcmp(val, other.val) == 0;
        }

        bool operator!=(const UsernameForBPT &other) const {
            return strcmp(val, other.val) != 0;
        }
    };

    struct TrainIDForBPT {
        char val[21] = {};//unique
        bool isMin = false;
        char realVal = 0;

        TrainIDForBPT() = default;

        explicit TrainIDForBPT(const std::string &_trainID) {
            strcpy(val, _trainID.c_str());
        }

        TrainIDForBPT(const TrainIDForBPT &other) {
            strcpy(val, other.val);
        }

        TrainIDForBPT &operator=(const TrainIDForBPT &other) {
            if (this == &other)return *this;
            strcpy(val, other.val);
            return *this;
        }

        bool operator<(const TrainIDForBPT &other) const {
            return strcmp(val, other.val) < 0;
        }

        bool operator==(const TrainIDForBPT &other) const {
            return strcmp(val, other.val) == 0;
        }

        bool operator!=(const TrainIDForBPT &other) const {
            return strcmp(val, other.val) != 0;
        }
    };

    struct ValForTrainIDDateForBPT {
        char val[21] = {};//unique
        int date = 0;

        ValForTrainIDDateForBPT() = default;

        ValForTrainIDDateForBPT(const std::string &_trainID, int _date) : date(_date) {
            strcpy(val, _trainID.c_str());
        }

        ValForTrainIDDateForBPT(const ValForTrainIDDateForBPT &other) {
            strcpy(val, other.val);
            date = other.date;
        }

        ValForTrainIDDateForBPT &operator=(const ValForTrainIDDateForBPT &other) {
            if (this == &other)return *this;
            strcpy(val, other.val);
            date = other.date;
            return *this;
        }

        bool operator<(const ValForTrainIDDateForBPT &other) const {
            if (strcmp(val, other.val) != 0)return strcmp(val, other.val) < 0;
            return date < other.date;
        }

        bool operator==(const ValForTrainIDDateForBPT &other) const {
            return strcmp(val, other.val) == 0 && date == other.date;
        }

        bool operator!=(const ValForTrainIDDateForBPT &other) const {
            return strcmp(val, other.val) != 0 || date != other.date;
        }
    };

    struct TrainIDDateForBPT {
        ValForTrainIDDateForBPT val;
        bool isMin = false;
        char realVal = 0;

        TrainIDDateForBPT() = default;

        TrainIDDateForBPT(const std::string &_trainID, int _date) : val(_trainID, _date) {}

        TrainIDDateForBPT(const TrainIDDateForBPT &other) : val(other.val) {}

        TrainIDDateForBPT &operator=(const TrainIDDateForBPT &other) {
            if (this == &other)return *this;
            val = other.val;
            return *this;
        }

        bool operator<(const TrainIDDateForBPT &other) const {
            return val < other.val;
        }

        bool operator==(const TrainIDDateForBPT &other) const {
            return val == other.val;
        }

        bool operator!=(const TrainIDDateForBPT &other) const {
            return val != other.val;
        }
    };

    struct ValForStation_TrainIDForBPT {
        char station[31] = {};
        char trainID[21] = {};

        ValForStation_TrainIDForBPT() = default;

        ValForStation_TrainIDForBPT(const std::string &_station, const std::string &_trainID) {
            strcpy(station, _station.c_str());
            strcpy(trainID, _trainID.c_str());
        }

        ValForStation_TrainIDForBPT(const ValForStation_TrainIDForBPT &other) {
            strcpy(station, other.station);
            strcpy(trainID, other.trainID);
        }

        ValForStation_TrainIDForBPT &operator=(const ValForStation_TrainIDForBPT &other) {
            if (this == &other)return *this;
            strcpy(station, other.station);
            strcpy(trainID, other.trainID);
            return *this;
        }

        bool operator<(const ValForStation_TrainIDForBPT &other) const {
            int flag = strcmp(station, other.station);
            if (flag != 0)return flag < 0;
            return strcmp(trainID, other.trainID) < 0;
        }

        bool operator==(const ValForStation_TrainIDForBPT &other) const {
            return strcmp(station, other.station) == 0 && strcmp(trainID, other.trainID) == 0;
        }

        bool operator!=(const ValForStation_TrainIDForBPT &other) const {
            return strcmp(station, other.station) != 0 || strcmp(trainID, other.trainID) != 0;
        }
    };

    struct Station_TrainIDForBPT {
        ValForStation_TrainIDForBPT val;
        bool isMin = false;
        char realVal = 0;

        Station_TrainIDForBPT() = default;

        Station_TrainIDForBPT(const std::string &_station, const std::string &_trainID) : val(_station, _trainID) {}

        Station_TrainIDForBPT(const Station_TrainIDForBPT &other) : val(other.val) {}

        Station_TrainIDForBPT &operator=(const Station_TrainIDForBPT &other) {
            if (this == &other)return *this;
            val = other.val;
            return *this;
        }

        bool operator<(const Station_TrainIDForBPT &other) const {
            return val < other.val;
        }

        bool operator==(const Station_TrainIDForBPT &other) const {
            return val == other.val;
        }

        bool operator!=(const Station_TrainIDForBPT &other) const {
            return val != other.val;
        }
    };

    sjtu::map<std::string, LogUser> UserMap;
    BPT<UsernameForBPT, User> Username_ToUser;
    BPT<TrainIDForBPT, Train> TrainID_ToTrain;
    BPT<TrainIDDateForBPT, releasedTrain> TrainIDDate_ToReleasedTrain;
    BPT<Station_TrainIDForBPT, TrainForQT> Station_TrainID_ToTrainForQT;
    BPT<Station_TrainIDForBPT, TrainForQTOnlyId> Station_TrainID_ToTrainForQTOlyId;
    BPT<TrainIDDateForBPT, Pend> TrainIDDate_ToPends;
    BPT<UsernameForBPT, Order> Username_ToOrders;
private://实现函数
#ifdef debug
public:
#endif

//    void _addUser(User &user) {
//        Username_ToUser.insert(UsernameForBPT(user.username), user);
//    }
    void _getUser(const std::string &username, User &user) {}
//    void _addTrain(Train &train) {
//        TrainID_ToTrain.insert(TrainIDForBPT(train.trainID), train);
//    }
private://主分支函数
#ifdef debug
public:
    //todo WARNING 或许ADDUSER指令不全/重复！
    void addUser(int timestamp, sjtu::vector<std::string> &v) {
        User user;
        user.timestamp = timestamp;
        int flag = 0;
        int curPrivilege = 0;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-c") {
                if (Username_ToUser.size_() == 0) {
                    ++i;
                    continue;
                }
                auto iter = UserMap.find(v[++i]);
                if (iter == UserMap.end()) {
                    std::cout << -1 << std::endl;
                    return;
                }
                curPrivilege = iter->second.privilege;
            } else if (v[i] == "-g") {
                user.privilege = StringToInt(v[++i]);
            } else if (v[i] == "-u") {
                strcpy(user.username, v[++i].c_str());
                flag = i;
            } else if (v[i] == "-p") {
                strcpy(user.password, v[++i].c_str());
            } else if (v[i] == "-n") {
                strcpy(user.name, v[++i].c_str());
            } else if (v[i] == "-m") {
                strcpy(user.mailAddr, v[++i].c_str());
            }
        }
        if (Username_ToUser.size_() == 0) {
            user.privilege = 10;
            Username_ToUser.insert(UsernameForBPT(v[flag]), user);
            std::cout << 0 << std::endl;
        } else {
            if (curPrivilege <= user.privilege) {
                std::cout << -1 << std::endl;
                return;
            }
            Username_ToUser.insert(UsernameForBPT(v[flag]), user);
            std::cout << 0 << std::endl;
        }
    }

    void login(int timestamp, sjtu::vector<std::string> &v) {
        LogUser logUser;
        logUser.timestamp = timestamp;
        char *truePsw;
        std::string *Psw, username;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-u") {
                username = v[++i];
                if (UserMap.find(v[i]) != UserMap.end()) {
                    std::cout << -1 << std::endl;
                    return;
                }
                //考虑move
                auto vec = Username_ToUser.find3(UsernameForBPT(v[i]));
                if (vec.empty()) {
                    std::cout << -1 << std::endl;
                    return;
                }
#ifdef debug
                assert(vec.size() == 1);
#endif
                truePsw = vec[0].password;
                logUser.privilege = vec[0].privilege;
            } else if (v[i] == "-p") {
                Psw = &v[++i];
            }
        }
        if (strcmp(truePsw, Psw->c_str()) == 0) {
            UserMap[username] = logUser;
            std::cout << 0 << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }

    void logout(int timestamp, sjtu::vector<std::string> &v) {
        std::string username;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-u") {
                username = v[++i];
            }
        }
        if (UserMap.find(username) == UserMap.end()) {
            std::cout << -1 << std::endl;
            return;
        }
        UserMap.erase(username);
        std::cout << 0 << std::endl;
    }

    void queryProfile(int timestamp, sjtu::vector<std::string> &v) {
        std::string *curUser, *targetUser;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-c") {
                curUser = &v[++i];
            } else if (v[i] == "-u") {
                targetUser = &v[++i];
            }
        }
        auto itr = UserMap.find(*curUser);
        if (itr == UserMap.end()) {
            std::cout << -1 << std::endl;
            return;
        }
        //考虑move
        auto vec = Username_ToUser.find3(UsernameForBPT(*targetUser));
        if (vec.empty()) {
            std::cout << -1 << std::endl;
            return;
        }
#ifdef debug
        assert(vec.size() == 1);
#endif
        bool f1 = (itr->second.privilege > vec[0].privilege);
        bool f2 = (*curUser == *targetUser);
        if (!f1 && !f2) {
            std::cout << -1 << std::endl;
            return;
        }
        User &user = vec[0];
        std::cout << user.username << " " << user.name << " " << user.mailAddr << " " << user.privilege << std::endl;
    }

    void modifyProfile(int timestamp, sjtu::vector<std::string> &v) {
        std::string *curUser, *targetUser;
        int privilege = 0;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-c") {
                curUser = &v[++i];
            } else if (v[i] == "-u") {
                targetUser = &v[++i];
            } else if (v[i] == "-g") {
                privilege = StringToInt(v[++i]);
            } else ++i;
        }
        auto itr = UserMap.find(*curUser);
        if (itr == UserMap.end() || itr->second.privilege <= privilege) {
            std::cout << -1 << std::endl;
            return;
        }
        //考虑move
        auto vec = Username_ToUser.find3(UsernameForBPT(*targetUser));
        if (vec.empty()) {
            std::cout << -1 << std::endl;
            return;
        }
#ifdef debug
        assert(vec.size() == 1);
#endif
        bool f1 = (itr->second.privilege > vec[0].privilege);
        bool f2 = (*curUser == *targetUser);
        if (!f1 && !f2) {
            std::cout << -1 << std::endl;
            return;
        }
//todo:优化:不删除，只修改！
        Username_ToUser.delete_(UsernameForBPT(*targetUser), vec[0]);
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-p") {
                strcpy(vec[0].password, v[++i].c_str());
            } else if (v[i] == "-n") {
                strcpy(vec[0].name, v[++i].c_str());
            } else if (v[i] == "-m") {
                strcpy(vec[0].mailAddr, v[++i].c_str());
            } else if (v[i] == "-g") {
                vec[0].privilege = privilege;
            }
        }
        Username_ToUser.insert(UsernameForBPT(*targetUser), vec[0]);
        std::cout << vec[0].username << " " << vec[0].name << " " << vec[0].mailAddr << " " << vec[0].privilege
                  << std::endl;
    }

    void addTrain(int timestamp, sjtu::vector<std::string> &v) {}

    void deleteTrain(int timestamp, sjtu::vector<std::string> &v) {}

    void releaseTrain(int timestamp, sjtu::vector<std::string> &v) {}

    void queryTrain(int timestamp, sjtu::vector<std::string> &v) {}

    void queryTicket(int timestamp, sjtu::vector<std::string> &v) {}

    void queryTransfer(int timestamp, sjtu::vector<std::string> &v) {}

    void buyTicket(int timestamp, sjtu::vector<std::string> &v) {}

    void queryOrder(int timestamp, sjtu::vector<std::string> &v) {}

    void refundTicket(int timestamp, sjtu::vector<std::string> &v) {}

    void clean() {}

    void exit() {
        std::cout << "bye" << std::endl;
    }

#endif
public:
    TicketSystem() : Username_ToUser("Username_ToUser"), Username_ToOrders("Username_ToOrders"),
                     TrainID_ToTrain("TrainID_ToTrain"),
                     TrainIDDate_ToReleasedTrain("TrainIDDate_ToReleasedTrain"),
                     Station_TrainID_ToTrainForQT("Station_TrainID_ToTrainForQT"),
                     Station_TrainID_ToTrainForQTOlyId("Station_TrainID_ToTrainForQTOlyID"),
                     TrainIDDate_ToPends("TrainIDDate_ToPends") {
    }

    void run() {
        while (true) {
            std::string timestampStr, cmd;
            std::cin >> timestampStr >> cmd;
            std::cout<<timestampStr<<' ';
            if (cmd == "clean") {
                clean();
            }
            if (cmd == "exit") {
                exit();
                return;
            }
            int timestamp = timestampStrToInt(timestampStr);
            sjtu::vector<std::string> v;
            std::string message;
            getline(std::cin, message);
            splitString(message, v);
            if (cmd == "add_user") {
                addUser(timestamp, v);
            }
            if (cmd == "login") {
                login(timestamp, v);
            }
            if (cmd == "logout") {
                logout(timestamp, v);
            }
            if (cmd == "query_profile") {
                queryProfile(timestamp, v);
            }
            if (cmd == "modify_profile") {
                modifyProfile(timestamp, v);
            }
            if (cmd == "add_train") {
                addTrain(timestamp, v);
            }
            if (cmd == "delete_train") {
                deleteTrain(timestamp, v);
            }
            if (cmd == "release_train") {
                releaseTrain(timestamp, v);
            }
            if (cmd == "query_train") {
                queryTrain(timestamp, v);
            }
            if (cmd == "query_ticket") {
                queryTicket(timestamp, v);
            }
            if (cmd == "query_transfer") {
                queryTransfer(timestamp, v);
            }
            if (cmd == "buy_ticket") {
                buyTicket(timestamp, v);
            }
            if (cmd == "query_order") {
                queryOrder(timestamp, v);
            }
            if (cmd == "refund_ticket") {
                refundTicket(timestamp, v);
            }
        }
#ifdef debug
        std::cerr << "error command" << std::endl;
#endif
    }

    ~TicketSystem() {}

};

#endif //TICKETSYSTEM_TICKETSYSTEM_HPP
//    struct Time{
//        int hh=0;
//        int mm=0;
//        Time()=default;
//        Time(int _hh,int _mm):hh(_hh),mm(_mm){}
//        Time(Time const &other):hh(other.hh),mm(other.mm){}
//        bool operator<(Time const &other) const{
//            if(hh!=other.hh)return hh<other.hh;
//            return mm<other.mm;
//        }
//        bool operator==(Time const &other) const{
//            return hh==other.hh&&mm==other.mm;
//        }
//        bool operator>(Time const &other) const{
//            if(hh!=other.hh)return hh>other.hh;
//            return mm>other.mm;
//        }
//        bool operator<=(Time const &other) const{
//            if(hh!=other.hh)return hh<other.hh;
//            return mm<=other.mm;
//        }
//        bool operator>=(Time const &other) const{
//            if(hh!=other.hh)return hh>other.hh;
//            return mm>=other.mm;
//        }
//        bool operator!=(Time const &other) const{
//            return hh!=other.hh||mm!=other.mm;
//        }
//        Time operator+(int const &other) const{
//            Time res=*this;
//            res.hh+=other/60;
//            res.mm+=other%60;
//            if(res.mm>=60){
//                res.hh++;
//                res.mm-=60;
//            }
//            return res;
//        }
//        Time& operator+=(int const &other){
//            hh+=other/60;
//            mm+=other%60;
//            if(mm>=60){
//                hh++;
//                mm-=60;
//            }
//            return *this;
//        }
//        Time operator+(Time const &other) const{
//            Time res=*this;
//            res.hh+=other.hh;
//            res.mm+=other.mm;
//            if(res.mm>=60){
//                res.hh++;
//                res.mm-=60;
//            }
//            return res;
//        }
//        Time& operator+=(Time const &other){
//            hh+=other.hh;
//            mm+=other.mm;
//            if(mm>=60){
//                hh++;
//                mm-=60;
//            }
//            return *this;
//        }
//    };
//    struct Date{
//        int mm=0;
//        int dd=0;
//        Date()=default;
//        Date(int _mm,int _dd):mm(_mm),dd(_dd){}
//        Date(Date const &other):mm(other.mm),dd(other.dd){}
//        bool operator<(Date const &other) const{
//            if(mm!=other.mm)return mm<other.mm;
//            return dd<other.dd;
//        }
//        bool operator==(Date const &other) const{
//            return mm==other.mm&&dd==other.dd;
//        }
//        bool operator>(Date const &other) const{
//            if(mm!=other.mm)return mm>other.mm;
//            return dd>other.dd;
//        }
//        bool operator<=(Date const &other) const{
//            if(mm!=other.mm)return mm<other.mm;
//            return dd<=other.dd;
//        }
//        bool operator>=(Date const &other) const{
//            if(mm!=other.mm)return mm>other.mm;
//            return dd>=other.dd;
//        }
//        bool operator!=(Date const &other) const{
//            return mm!=other.mm||dd!=other.dd;
//        }
//    };