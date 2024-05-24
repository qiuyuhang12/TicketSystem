//
// Created by qiuyuhang on 24-5-18.
//

#ifndef TICKETSYSTEM_TICKETSYSTEM_HPP
#define TICKETSYSTEM_TICKETSYSTEM_HPP
//#define debug
//#define timetest
#ifdef timetest

#include "timer.hpp"

#endif

#ifdef debug


#include <vector>
#include <map>

//template<typename T>
//std::vector<T> sjtuVtoStdV(const sjtu::vector<T> &v) {
//    std::vector<T> rsl;
////    for (auto &i: v) {
//    for (int i = 0; i < v.size(); ++i) {
//        rsl.push_back(v[i]);
//    }
//    return rsl;
//}

#define sjtu std


#endif

#include "BPT/BPT.hpp"
#include "HashBPT.hpp"
#include "BigBlockBpt.hpp"
#include "StringFunction.hpp"
#include "DateAndTimeStruct.hpp"
#include "externalMap.hpp"


void clearFile() {
    remove("Station_TrainID_ToTrainForQT");
    remove("Station_TrainID_ToTrainForQTBlocks");
    remove("Station_TrainID_ToTrainForQTNodes");
    remove("Station_TrainID_ToTrainForQTOlyIDBlocks");
    remove("Station_TrainID_ToTrainForQTOlyIDNodes");
    remove("TrainID_ToTrain");
    remove("TrainID_ToTrainBlocks");
    remove("TrainID_ToTrainNodes");
    remove("TrainID_ToTrainDATA");
    remove("TrainIDDate_ToPendsBlocks");
    remove("TrainIDDate_ToPendsNodes");
    remove("TrainIDDate_ToReleasedTrain");
    remove("TrainIDDate_ToReleasedTrainBlocks");
    remove("TrainIDDate_ToReleasedTrainNodes");
    remove("Username_ToOrdersBlocks");
    remove("Username_ToOrdersNodes");
    remove("Username_ToUserBlocks");
    remove("Username_ToUserNodes");
}

class TicketSystem {
private:
#ifdef debug
    public:
#endif

#ifdef timetest
    Timer timerqt,timerpt;
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
        int price[101] = {};
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

        void print(int date) {
            std::cout << trainID << " " << type << std::endl;
            int time = startTime;
            for (int i = 0; i < stationNum; ++i) {
                std::cout << stations[i] << " ";
                if (i == 0) {
                    std::cout << "xx-xx xx:xx -> ";
                } else {
                    std::cout << makeDateAndTime(date, time += travelTime[i]) << " -> ";
                }
                if (i != stationNum - 1) {
                    std::cout << makeDateAndTime(date, time += stopoverTime[i]) << " ";
                } else {
                    std::cout << "xx-xx xx:xx ";
                }
                std::cout << price[i] << " ";
                if (i == stationNum - 1) {
                    std::cout << "x" << std::endl;
                } else {
                    std::cout << seatNum << std::endl;
                }
            }
        }
    };

//#define cutRelease
    struct releasedTrain {//先id序 后time序
        int timestamp = 0;//only for debug (releaseTime)
#ifndef cutRelease
        char trainID[21] = {};//unique
#endif
        int date = 0;
        int stationNum = 0;
//        char stations[101][31] = {};//0为始发站
        int startTime = 0;
//        int travelTime[101] = {};//0无意义（为0），1为始发站到第一站的时间
//        int stopoverTime[101] = {};//0无意义（为0），1为第一站停靠时间
//        int price[101] = {};//0无意义（为0），1为始发站到第一站的累计价格
        int restTickets[101] = {};//0为从始发站到第一站的余票,i：第i站到第i+1站的余票
        int seatNum = 0;//only for debug
        char type = 0;//only for debug
        //默认构造，从变量构造，拷贝构造，拷贝赋值，< 重载，== 重载，!= 重载
        releasedTrain() = default;

        releasedTrain(char *_trainID, int _date, int _stationNum,
//                      char(*_stations)[31],
                      int _startTime,
//                      const int *_travelTime, const int *_stopoverTime,
//                      const int *_price,
                      int _seatNum, char _type,
                      int _timestamp = 0) : timestamp(_timestamp) {
#ifndef cutRelease
            strcpy(trainID, _trainID);
#endif
            date = _date;
            stationNum = _stationNum;
//            for (int i = 0; i < stationNum; i++) {
//                strcpy(stations[i], _stations[i]);
//            }
            startTime = _startTime;
//            for (int i = 0; i < stationNum; i++) {
//                travelTime[i] = _travelTime[i];
//            }
//            for (int i = 0; i < stationNum; i++) {
//                stopoverTime[i] = _stopoverTime[i];
//            }
//            for (int i = 0; i < stationNum; i++) {
//                price[i] = _price[i];
//            }
            for (int i = 0; i < stationNum; i++) {
                restTickets[i] = _seatNum;
            }
            seatNum = _seatNum;
            type = _type;
        }

        releasedTrain &operator=(const releasedTrain &other) {
            if (this == &other)return *this;
            timestamp = other.timestamp;
#ifndef cutRelease
            strcpy(trainID, other.trainID);
#endif
            date = other.date;
            stationNum = other.stationNum;
//            for (int i = 0; i < stationNum; i++) {
//                strcpy(stations[i], other.stations[i]);
//            }
            startTime = other.startTime;
//            for (int i = 0; i < stationNum; i++) {
//                travelTime[i] = other.travelTime[i];
//            }
//            for (int i = 0; i < stationNum; i++) {
//                stopoverTime[i] = other.stopoverTime[i];
//            }
//            for (int i = 0; i < stationNum; i++) {
//                price[i] = other.price[i];
//            }
            for (int i = 0; i < stationNum; i++) {
                restTickets[i] = other.restTickets[i];
            }
            seatNum = other.seatNum;
            type = other.type;
            return *this;
        }

        bool operator<(const releasedTrain &other) const {
#ifndef cutRelease
            if (strcmp(trainID, other.trainID) != 0)return strcmp(trainID, other.trainID) < 0;
#endif
            return date < other.date;
        }

        bool operator==(const releasedTrain &other) const {
#ifndef cutRelease
            return strcmp(trainID, other.trainID) == 0 && date == other.date;
#else
            return date == other.date;
#endif
        }

        bool operator!=(const releasedTrain &other) const {
#ifndef cutRelease
            return strcmp(trainID, other.trainID) != 0 || date != other.date;
#else
            return date != other.date;
#endif
        }

#ifndef cutRelease

        void print(const Train &train) {
            std::cout << trainID << " " << type << std::endl;
#else
            void print(const Train &train,const char * trainID) {
            std::cout << trainID << " " << type << std::endl;
#endif
            int time = startTime;
            for (int i = 0; i < stationNum; ++i) {
                std::cout << train.stations[i] << " ";
                if (i == 0) {
                    std::cout << "xx-xx xx:xx -> ";
                } else {
                    std::cout << makeDateAndTime(date, time += train.travelTime[i]) << " -> ";
                }
                if (i != stationNum - 1) {
                    std::cout << makeDateAndTime(date, time += train.stopoverTime[i]) << " ";
                } else {
                    std::cout << "xx-xx xx:xx ";
                }
                std::cout << train.price[i] << " ";
                if (i == stationNum - 1) {
                    std::cout << "x" << std::endl;
                } else {
                    std::cout << restTickets[i] << std::endl;
                }
            }
        }
    };

    struct Order {
        int timestamp = 0;//not only for debug! (createTime)
        char username[21] = {};//not only for debug!
        orderStatus status = success;
        char trainID[21] = {};//unique
        char from[41] = {};//火车出发站
        int leavingDateAndTime = 0;//火车出发时间
        char to[41] = {};//火车到达站
        int arrivingDateAndTime = 0;//火车到达时间
        int price = 0;//车票单价
        int num = 0;//车票数量
        int dateOfTrain = 0;//火车始发日期
        int fNum = 0;//出发站序号
        int tNum = 0;//到达站序号
        Order() {}

        Order(const char *_username, const char *_trainID, const char *_from, int _leavingDateAndTime, const char *_to,
              int _arrivingDateAndTime, int _price, int _num, int _dateOfTrain, int _fNum, int _tNum, orderStatus od,
              int _timestamp = 0) {
            strcpy(username, _username);
            strcpy(trainID, _trainID);
            strcpy(from, _from);
            leavingDateAndTime = _leavingDateAndTime;
            strcpy(to, _to);
            arrivingDateAndTime = _arrivingDateAndTime;
            price = _price;
            num = _num;
            dateOfTrain = _dateOfTrain;
            fNum = _fNum;
            tNum = _tNum;
            status = od;
            timestamp = _timestamp;
        }

        Order(const Order &other) {
            timestamp = other.timestamp;
            strcpy(username, other.username);
            status = other.status;
            strcpy(trainID, other.trainID);
            strcpy(from, other.from);
            leavingDateAndTime = other.leavingDateAndTime;
            strcpy(to, other.to);
            arrivingDateAndTime = other.arrivingDateAndTime;
            price = other.price;
            num = other.num;
            dateOfTrain = other.dateOfTrain;
            fNum = other.fNum;
            tNum = other.tNum;
        }

        Order &operator=(const Order &other) {
            if (this == &other)return *this;
            timestamp = other.timestamp;
            strcpy(username, other.username);
            status = other.status;
            strcpy(trainID, other.trainID);
            strcpy(from, other.from);
            leavingDateAndTime = other.leavingDateAndTime;
            strcpy(to, other.to);
            arrivingDateAndTime = other.arrivingDateAndTime;
            price = other.price;
            num = other.num;
            dateOfTrain = other.dateOfTrain;
            fNum = other.fNum;
            tNum = other.tNum;
            return *this;
        }

        bool operator<(const Order &other) const {
            return timestamp < other.timestamp;
        }

        bool operator==(const Order &other) const {
            return timestamp == other.timestamp;
        }

        bool operator!=(const Order &other) const {
            return timestamp != other.timestamp;
        }

        void print() {
//一行表示一个订单，格式为 [<STATUS>] <trainID> <FROM> <LEAVING_TIME> -> <TO> <ARRIVING_TIME> <PRICE> <NUM>，其中 <NUM> 为购票数量， <STATUS> 表示该订单的状态，可能的值为：success（购票已成功）、pending（位于候补购票队列中）和 refunded（已经退票）。
            std::cout << "[" << (status == success ? "success" : (status == pending ? "pending" : "refunded")) << "] "
                      << trainID << " " << from << " " << IntToDateAndTime(leavingDateAndTime) << " -> "
                      << to << " " << IntToDateAndTime(arrivingDateAndTime) << " " << price << " " << num << std::endl;
        }
    };

    // struct Pend {
    //     int timestamp = 0;//only for debug (createTime)
    //     char username[21] = {};
    //     char trainID[21] = {};//only for debug
    //     char from[41] = {};
    //     char to[41] = {};
    //     int price = 0;
    //     int num = 0;
    //     int leavingDateFromFirstStation = 0;//only for debug
    //     int dateOfTrain = 0;//火车始发日期
    //     int fNum = 0;//出发站序号
    //     int tNum = 0;//到达站序号
    // };
    struct LogUser {
//        int timestamp = 0;//only for debug (logInTime)
//        char username[21] = {};//unique
        int privilege = 0;
    };

    class TrainForQTOnlyId;

    //注意换乘排除同一辆车
    struct TrainForQT {//time序
        char trainID[21] = {};//unique
        int nowStation = 0;//是第几站（0为始发站）
        int nowTime = 0;//到达本站时间（可大于24：00，以发车日0时为准）
        int thisOver = 0;//本站停靠时间
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

        TrainForQT(const char *_trainID, int _nowStation, int _nowTime, int _nowPrice, int _stationNum,
                   const char (*_stations)[31], const int *_saleDate,
                   const int *_travelTime, const int *_stopoverTime,
                   const int *_price, char _type, int _thisOver) {
            strcpy(trainID, _trainID);
            nowStation = _nowStation;
            nowTime = _nowTime;
            thisOver = _thisOver;
            nowPrice = _nowPrice;
            stationNum = _stationNum;
            for (int i = 0; i < stationNum; i++) {
                strcpy(stations[i], _stations[i]);
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
            thisOver = other.thisOver;
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

        TrainForQT(const TrainForQT &other) {
            strcpy(trainID, other.trainID);
            nowStation = other.nowStation;
            nowTime = other.nowTime;
            thisOver = other.thisOver;
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
        }

        TrainForQT(const Train &other, const TrainForQTOnlyId &other2) {
            strcpy(trainID, other.trainID);
            nowStation = other2.nowStation;
            nowTime = other2.nowTime;
            thisOver = other2.thisOver;
            nowPrice = other2.nowPrice;
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

    class TrainForQTOnlyId {
    public:
        //可以删除TRAINID
        char trainID[21] = {};//unique
        int nowStation = 0;//是第几站（0为始发站）
        int nowTime = 0;//到达本站时间（可大于24：00，以发车日0时为准）
        int thisOver = 0;//本站停靠时间
        int nowPrice = 0;//当前车票累计价格
        int saleDate[2] = {};

        //默认构造，从变量构造，拷贝构造，拷贝赋值，< 重载，== 重载，!= 重载
        TrainForQTOnlyId() = default;

        TrainForQTOnlyId(const char *_trainID, int _nowStation, int _nowTime, int _thisOver, int _nowPrice,
                         const int _saleDate[2]) {
            strcpy(trainID, _trainID);
            nowStation = _nowStation;
            nowTime = _nowTime;
            thisOver = _thisOver;
            nowPrice = _nowPrice;
            for (int i = 0; i < 2; i++) {
                saleDate[i] = _saleDate[i];
            }
        }

        TrainForQTOnlyId(const TrainForQTOnlyId &other) {
            strcpy(trainID, other.trainID);
            nowStation = other.nowStation;
            nowTime = other.nowTime;
            nowPrice = other.nowPrice;
            thisOver = other.thisOver;
            for (int i = 0; i < 2; i++) {
                saleDate[i] = other.saleDate[i];
            }
        }

        explicit TrainForQTOnlyId(const TrainForQT &other) {
            strcpy(trainID, other.trainID);
            nowStation = other.nowStation;
            nowTime = other.nowTime;
            nowPrice = other.nowPrice;
            thisOver = other.thisOver;
            for (int i = 0; i < 2; i++) {
                saleDate[i] = other.saleDate[i];
            }
        }

        TrainForQTOnlyId &operator=(TrainForQTOnlyId const &other) {
            if (this == &other)return *this;
            strcpy(trainID, other.trainID);
            nowStation = other.nowStation;
            nowTime = other.nowTime;
            nowPrice = other.nowPrice;
            thisOver = other.thisOver;
            for (int i = 0; i < 2; i++) {
                saleDate[i] = other.saleDate[i];
            }
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
        int realVal = 0;

        int hash() const {
            int rsl = 0;
            for (int i = 0; i < 21; i++) {
                rsl = rsl * 131 + val[i];
            }
            rsl % 1000000007;
            return rsl;
        }

        UsernameForBPT() = default;

        explicit UsernameForBPT(const std::string &_username) {
            strcpy(val, _username.c_str());
        }

        explicit UsernameForBPT(const char *_username) {
            strcpy(val, _username);
        }

        UsernameForBPT(const char *_username, int real) {
            strcpy(val, _username);
            realVal = real;
        }

        UsernameForBPT(const UsernameForBPT &other) {
            strcpy(val, other.val);
            realVal = other.realVal;
        }

        UsernameForBPT &operator=(const UsernameForBPT &other) {
            if (this == &other)return *this;
            strcpy(val, other.val);
            realVal = other.realVal;
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

        ValForTrainIDDateForBPT(const char *_trainID, int _date) : date(_date) {
            strcpy(val, _trainID);
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
        int realVal = 0;

        TrainIDDateForBPT() = default;

        TrainIDDateForBPT(const std::string &_trainID, int _date) : val(_trainID, _date) {}

        TrainIDDateForBPT(const char *_trainID, int _date) : val(_trainID, _date) {}

        TrainIDDateForBPT(const char *_trainID, int _date, int real) : val(_trainID, _date), realVal(real) {}

        TrainIDDateForBPT(const TrainIDDateForBPT &other) : val(other.val), realVal(other.realVal) {}

        TrainIDDateForBPT &operator=(const TrainIDDateForBPT &other) {
            if (this == &other)return *this;
            val = other.val;
            realVal = other.realVal;
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
//        char trainID[21] = {};

        ValForStation_TrainIDForBPT() = default;

        explicit ValForStation_TrainIDForBPT(const char *_station) {
            strcpy(station, _station);
//            strcpy(trainID, _trainID);
        }

        ValForStation_TrainIDForBPT(const ValForStation_TrainIDForBPT &other) {
            strcpy(station, other.station);
//            strcpy(trainID, other.trainID);
        }

        ValForStation_TrainIDForBPT &operator=(const ValForStation_TrainIDForBPT &other) {
            if (this == &other)return *this;
            strcpy(station, other.station);
//            strcpy(trainID, other.trainID);
            return *this;
        }

        bool operator<(const ValForStation_TrainIDForBPT &other) const {
            int flag = strcmp(station, other.station);
//            if (flag != 0)
            return flag < 0;
//            return strcmp(trainID, other.trainID) < 0;
        }

        bool operator==(const ValForStation_TrainIDForBPT &other) const {
            return strcmp(station, other.station) == 0;
//            && strcmp(trainID, other.trainID) == 0;
        }

        bool operator!=(const ValForStation_TrainIDForBPT &other) const {
            return strcmp(station, other.station) != 0;
//            || strcmp(trainID, other.trainID) != 0;
        }
    };

    struct realValForStation_TrainIDForBPT {
        char trainID[21] = {};

        realValForStation_TrainIDForBPT() = default;

        explicit realValForStation_TrainIDForBPT(const char *_trainID) {
            strcpy(trainID, _trainID);
        }

        realValForStation_TrainIDForBPT(const realValForStation_TrainIDForBPT &other) {
            strcpy(trainID, other.trainID);
        }

        realValForStation_TrainIDForBPT &operator=(const realValForStation_TrainIDForBPT &other) {
            if (this == &other)return *this;
            strcpy(trainID, other.trainID);
            return *this;
        }

        bool operator<(const realValForStation_TrainIDForBPT &other) const {
            return strcmp(trainID, other.trainID) < 0;
        }

        bool operator==(const realValForStation_TrainIDForBPT &other) const {
            return strcmp(trainID, other.trainID) == 0;
        }

        bool operator!=(const realValForStation_TrainIDForBPT &other) const {
            return strcmp(trainID, other.trainID) != 0;
        }
    };

    struct Station_TrainIDForBPT {
        ValForStation_TrainIDForBPT val;
        bool isMin = false;
        realValForStation_TrainIDForBPT realVal;

        Station_TrainIDForBPT() = default;

        Station_TrainIDForBPT(const char *_station, const char *_trainID) : val(_station), isMin(false),
                                                                            realVal(_trainID) {}

        Station_TrainIDForBPT(const Station_TrainIDForBPT &other) : val(other.val), realVal(other.realVal) {}

        Station_TrainIDForBPT &operator=(const Station_TrainIDForBPT &other) {
            if (this == &other)return *this;
            val = other.val;
            realVal = other.realVal;
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
    BPT<UsernameForBPT, User> Username_ToUser;//28(key) 112(value) 10000(数据量) 读SF

    externalMap<TrainIDForBPT, Train> TrainID_ToTrain;//23 10000 读SF
    BPT<TrainIDDateForBPT, releasedTrain> TrainIDDate_ToReleasedTrain;//36 10000*90 读写SF
//    BigBlockBpt<Station_TrainIDForBPT, TrainForQT> Station_TrainID_ToTrainForQT;
    BPT<Station_TrainIDForBPT, TrainForQTOnlyId> Station_TrainID_ToTrainForQTOlyId;//53 10000*90*100 读SF
    BPT<TrainIDDateForBPT, Order> TrainIDDate_ToPends;//36 1000000
    BPT<UsernameForBPT, Order> Username_ToOrders;//28 1000000 读F 写SF

    struct IntAndString {
        int num;
        char *str;

        IntAndString() {}

        IntAndString(int _num, char *_str) : num(_num) {
            strcpy(str, _str);
        }

        IntAndString(const IntAndString &other) : num(other.num) {
            strcpy(str, other.str);
        }

        IntAndString &operator=(const IntAndString &other) {
            if (this == &other)return *this;
            num = other.num;
            strcpy(str, other.str);
            return *this;
        }

        bool operator<(const IntAndString &other) const {
            return num < other.num || (num == other.num && strcmp(str, other.str) < 0);
        }

        bool operator==(const IntAndString &other) const {
            return num == other.num && strcmp(str, other.str) == 0;
        }

        bool operator!=(const IntAndString &other) const {
            return num != other.num || strcmp(str, other.str) != 0;
        }
    };

    struct String {
        char str[100] = {};

        String() {}

        String(char *_str) {
            strcpy(str, _str);
        }

        String(const String &other) {
            strcpy(str, other.str);
        }

        String &operator=(const String &other) {
            if (this == &other)return *this;
            strcpy(str, other.str);
            return *this;
        }

        bool operator<(const String &other) const {
            return strcmp(str, other.str) < 0;
        }

        bool operator==(const String &other) const {
            return strcmp(str, other.str) == 0;
        }

        bool operator!=(const String &other) const {
            return strcmp(str, other.str) != 0;
        }
    };

private://实现函数
#ifdef debug
    public:
#endif

    LogUser *_getLoggedUser(const std::string &username) {
        auto iter = UserMap.find(username);
        if (iter == UserMap.end())return nullptr;
        return &iter->second;
    }

    void _getUser(const std::string &username, User &user) {}

    sjtu::vector<Train> _getTrainVec(const std::string &trainID) {
//#ifndef debug
        return TrainID_ToTrain.find3(TrainIDForBPT(trainID));
//#endif
//        return sjtuVtoStdV(TrainID_ToTrain.find3(TrainIDForBPT(trainID)));
    }

    bool exitTrain(const std::string &trainID) {
        return !TrainID_ToTrain.find3(TrainIDForBPT(trainID)).empty();
    }

    bool raw(const std::string &trainID) {
        auto vec = std::move(TrainID_ToTrain.find3(TrainIDForBPT(trainID)));
        return !(vec.empty() || vec[0].released);
    }

//    void _getReleasedTrain(const char *trainID, int date, releasedTrain &train) {
//#ifdef debug
//        auto vec = TrainIDDate_ToReleasedTrain.find3(TrainIDDateForBPT(trainID, date));
//        assert(vec.size() == 1);
//        train = vec[0];
//#else
//        train = TrainIDDate_ToReleasedTrain.find3(TrainIDDateForBPT(trainID, date))[0];
//#endif
//    }

    void
    printTicket(std::string *start, std::string *to, TrainForQTOnlyId *sT, TrainForQTOnlyId *tT, const char *trainID,
                int date) {
        std::cout << trainID << ' ' << *start << ' ' << makeDateAndTime(date, sT->nowTime + sT->thisOver) << ' '
                  << "-> " << *to << ' '
                  << makeDateAndTime(date, tT->nowTime) << ' ' << tT->nowPrice - sT->nowPrice;
        auto vec = std::move(TrainIDDate_ToReleasedTrain.find3(TrainIDDateForBPT(trainID, date)));
#ifdef debug
        assert(vec.size() == 1);
#endif
        releasedTrain &train = vec[0];
        int ticketNum = 1e5;
        for (int i = sT->nowStation; i < tT->nowStation; ++i) {
            ticketNum = std::min(ticketNum, train.restTickets[i]);
        }
        std::cout << ' ' << ticketNum << std::endl;
    }

    bool hasLogIn(const char *username) {
        return UserMap.find(std::string(username)) != UserMap.end();
    }

    bool hasLogIn(const std::string &username) {
        return UserMap.find(username) != UserMap.end();
    }

    void addOrder(const char *username, const Order &od) {
        Username_ToOrders.insert(UsernameForBPT(username, od.timestamp), od);
    }

    void Queue(const char *trainID, int date, const Order &od) {
        TrainIDDate_ToPends.insert(TrainIDDateForBPT(trainID, date, od.timestamp), od);
    }

    void tryBuy(Order &od, releasedTrain *train) {
        for (int i = od.fNum; i < od.tNum; ++i) {
            if (train->restTickets[i] < od.num) {
                return;
            }
        }
        for (int i = od.fNum; i < od.tNum; ++i) {
            train->restTickets[i] -= od.num;
        }
        //od移除pendlist
        TrainIDDate_ToPends.delete_(TrainIDDateForBPT(od.trainID, od.dateOfTrain, od.timestamp), od);
        //改变od在orderlist中的状态
        od.status = success;
//        Username_ToOrders.change(UsernameForBPT(od.username, od.timestamp), od);
        Username_ToOrders.changeHard(UsernameForBPT(od.username, od.timestamp), od);
    }

    enum QT_type {
        normal,
        after
    };

    //date是出发日期
    void queryTicket(const std::string *start, const std::string *toward, int date, int pri,
                     sjtu::vector<TrainForQTOnlyId *> &ans, sjtu::vector<TrainForQTOnlyId *> &ans2,
                     sjtu::map<int, sjtu::map<int, sjtu::map<String, int> > > &costToIndex,
                     sjtu::vector<int> &firstStainDateVec,
                     QT_type type, sjtu::vector<TrainForQTOnlyId> &sTrains, sjtu::vector<TrainForQTOnlyId> &tTrains,
                     int afterTime = 0, int firstStationdate = 0, TrainForQT *firstTrain = nullptr, int k = 0,
                     sjtu::vector<int> *ks = nullptr) {
        if (sTrains.empty() || tTrains.empty()) {
            throw 0;
            return;
        }
//        sjtu::vector<int> IndexToAnotherCost;
        for (int i = 0; i < sTrains.size(); ++i) {
            int firstStainDate = date - (sTrains[i].nowTime + sTrains[i].thisOver) / (24 * 60);
            if (type == after) {
                if (afterTime > (sTrains[i].nowTime + sTrains[i].thisOver) % (24 * 60))++firstStainDate;
            }
            if (firstStainDate > sTrains[i].saleDate[1])continue;
            if (sTrains[i].saleDate[0] > firstStainDate) {
                if (type == normal)continue;
                firstStainDate = sTrains[i].saleDate[0];
            }
            for (int j = 0; j < tTrains.size(); ++j) {
                if (strcmp(sTrains[i].trainID, tTrains[j].trainID) == 0) {
                    if (sTrains[i].nowStation < tTrains[j].nowStation) {
                        ans.push_back(&(sTrains[i]));
                        ans2.push_back(&(tTrains[j]));
//                        ans.push_back(sTrains.data + i);
//                        ans2.push_back(tTrains.data + j);
                        firstStainDateVec.push_back(firstStainDate);
                        int price = 0, time = 0;
                        char *id = id = sTrains[i].trainID;
                        if (type == normal) {
                            price = tTrains[j].nowPrice - sTrains[i].nowPrice;
                            time = tTrains[j].nowTime - sTrains[i].nowTime - sTrains[i].thisOver;
                        } else {
                            ks->push_back(k);
                            price = tTrains[j].nowPrice - sTrains[i].nowPrice + firstTrain->price[k] -
                                    firstTrain->price[firstTrain->nowStation];
                            time = (firstStainDateVec.back() - firstStationdate) * 24 * 60 + ans2.back()->nowTime -
                                   firstTrain->nowTime - firstTrain->thisOver;
                        }
                        if (pri == _price) {
                            if (type == normal) costToIndex[price][0][id] = ans.size() - 1;
                            else costToIndex[price][time][id] = ans.size() - 1;
                        }
//                            costToIndex[tTrains[j].nowPrice - sTrains[i].nowPrice][sTrains[i].trainID] = ans.size() - 1;
                        else if (pri == _time) {
                            if (type == normal)costToIndex[time][0][id] = ans.size() - 1;
                            else costToIndex[time][price][id] = ans.size() - 1;
                        }
//                            costToIndex[tTrains[j].nowTime - sTrains[i].nowTime -
//                                        sTrains[i].thisOver][sTrains[i].trainID] = ans.size() - 1;
                    }
                }
            }
        }
        if (ans.empty()) {
            throw 0;
            return;
        }
    }

//#ifndef debug
//    void _queryTicket(const std::string *start, const std::string *toward, int date, int pri,
//                     std::vector<TrainForQTOnlyId *> &ans, std::vector<TrainForQTOnlyId *> &ans2,
//                     sjtu::map<int, sjtu::map<int, sjtu::map<String, int> > > &costToIndex,
//                     std::vector<int> &firstStainDateVec,
//                     QT_type type, sjtu::vector<TrainForQTOnlyId> &sTrains, sjtu::vector<TrainForQTOnlyId> &tTrains,
//                     int afterTime = 0, int firstStationdate = 0, TrainForQT *firstTrain = nullptr, int k = 0,
//                     std::vector<int> *ks = nullptr) {
//        if (sTrains.empty() || tTrains.empty()) {
//            throw 0;
//            return;
//        }
////        sjtu::vector<int> IndexToAnotherCost;
//        for (int i = 0; i < sTrains.size(); ++i) {
//            int firstStainDate = date - (sTrains[i].nowTime + sTrains[i].thisOver) / (24 * 60);
//            if (type == after) {
//                if (afterTime > (sTrains[i].nowTime + sTrains[i].thisOver) % (24 * 60))++firstStainDate;
//            }
//            if (firstStainDate > sTrains[i].saleDate[1])continue;
//            if (sTrains[i].saleDate[0] > firstStainDate) {
//                if (type == normal)continue;
//                firstStainDate = sTrains[i].saleDate[0];
//            }
//            for (int j = 0; j < tTrains.size(); ++j) {
//                if (strcmp(sTrains[i].trainID, tTrains[j].trainID) == 0) {
//                    if (sTrains[i].nowStation < tTrains[j].nowStation) {
//                        ans.push_back(&(sTrains[i]));
//                        ans2.push_back(&(tTrains[j]));
////                        ans.push_back(sTrains.data + i);
////                        ans2.push_back(tTrains.data + j);
//                        firstStainDateVec.push_back(firstStainDate);
//                        int price = 0, time = 0;
//                        char *id = id = sTrains[i].trainID;
//                        if (type == normal) {
//                            price = tTrains[j].nowPrice - sTrains[i].nowPrice;
//                            time = tTrains[j].nowTime - sTrains[i].nowTime - sTrains[i].thisOver;
//                        } else {
//                            ks->push_back(k);
//                            price = tTrains[j].nowPrice - sTrains[i].nowPrice + firstTrain->price[k] -
//                                    firstTrain->price[firstTrain->nowStation];
//                            time = (firstStainDateVec.back() - firstStationdate) * 24 * 60 + ans2.back()->nowTime -
//                                   firstTrain->nowTime - firstTrain->thisOver;
//                        }
//                        if (pri == _price) {
//                            if (type == normal) costToIndex[price][0][id] = ans.size() - 1;
//                            else costToIndex[price][time][id] = ans.size() - 1;
//                        }
////                            costToIndex[tTrains[j].nowPrice - sTrains[i].nowPrice][sTrains[i].trainID] = ans.size() - 1;
//                        else if (pri == _time) {
//                            if (type == normal)costToIndex[time][0][id] = ans.size() - 1;
//                            else costToIndex[time][price][id] = ans.size() - 1;
//                        }
////                            costToIndex[tTrains[j].nowTime - sTrains[i].nowTime -
////                                        sTrains[i].thisOver][sTrains[i].trainID] = ans.size() - 1;
//                    }
//                }
//            }
//        }
//        if (ans.empty()) {
//            throw 0;
//            return;
//        }
//    }
//#endif
    int getTime(int k, const TrainForQT &train) {
        int time = train.nowTime;
        for (int i = train.nowStation + 1; i <= k; ++i) {
            time += train.travelTime[i];
        }
        for (int i = train.nowStation; i < k; ++i) {
            time += train.stopoverTime[i];
        }
        return time;
    }


private://主分支函数
#ifdef debug
    public:
#endif

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
//        logUser.timestamp = timestamp;
        char *truePsw;
        std::string *Psw, username;
        sjtu::vector<User> vec;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-u") {
                username = v[++i];
                if (UserMap.find(v[i]) != UserMap.end()) {
                    std::cout << -1 << std::endl;
                    return;
                }
                //考虑move
#ifdef debug
                //                vec = sjtuVtoStdV(Username_ToUser.find3(UsernameForBPT(v[i])));
                                vec = Username_ToUser.find3(UsernameForBPT(v[i]));
#else
                vec = std::move(Username_ToUser.find3(UsernameForBPT(v[i])));
#endif
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
        auto vec = std::move(Username_ToUser.find3(UsernameForBPT(*targetUser)));
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
        auto vec = std::move(Username_ToUser.find3(UsernameForBPT(*targetUser)));
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
                auto ptr = _getLoggedUser(*targetUser);
                if (ptr)ptr->privilege = privilege;
            }
        }
        Username_ToUser.insert(UsernameForBPT(*targetUser), vec[0]);
        std::cout << vec[0].username << " " << vec[0].name << " " << vec[0].mailAddr << " " << vec[0].privilege
                  << std::endl;
    }

    void addTrain(int timestamp, sjtu::vector<std::string> &v) {
        Train train;
        train.timestamp = timestamp;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-i") {
                if (exitTrain(v[++i])) {
                    std::cout << -1 << std::endl;
                    return;
                }
                strcpy(train.trainID, v[i].c_str());
            } else if (v[i] == "-n") {
                train.stationNum = StringToInt(v[++i]);
            } else if (v[i] == "-m") {
                train.seatNum = StringToInt(v[++i]);
            } else if (v[i] == "-s") {
                sjtu::vector<std::string> stations;
                splitSplitString(v[++i], stations);
//#ifdef debug
//                You cannot use assert here, because the number of stations can be 0.
//                assert(stations.size() == train.stationNum);
//#endif
                for (int j = 0; j < stations.size(); j++) {
                    strcpy(train.stations[j], stations[j].c_str());
                }
            } else if (v[i] == "-p") {
                sjtu::vector<std::string> vec;
                splitSplitString(v[++i], vec);
//#ifdef debug
//                assert(vec.size() == train.stationNum - 1);
//#endif
                for (int j = 1; j < vec.size() + 1; j++) {
                    train.price[j] = train.price[j - 1] + StringToInt(vec[j - 1]);
                }
            } else if (v[i] == "-x") {
                train.startTime = timeToInt(v[++i]);
            } else if (v[i] == "-t") {
                sjtu::vector<std::string> vec;
                splitSplitString(v[++i], vec);
//#ifdef debug
//                assert(vec.size() == train.stationNum - 1);
//#endif
                for (int j = 1; j < vec.size() + 1; j++) {
                    train.travelTime[j] = StringToInt(vec[j - 1]);
                }
            } else if (v[i] == "-o") {
                sjtu::vector<std::string> vec;
                splitSplitString(v[++i], vec);
//#ifdef debug
//                assert(vec.size() == train.stationNum - 2);
//#endif
                for (int j = 1; j <= vec.size(); j++) {
                    train.stopoverTime[j] = StringToInt(vec[j - 1]);
                }
            } else if (v[i] == "-d") {
                sjtu::vector<std::string> vec;
                splitSplitString(v[++i], vec);
                train.saleDate[0] = dateToInt(vec[0]);
                train.saleDate[1] = dateToInt(vec[1]);
            } else if (v[i] == "-y") {
                train.type = v[++i][0];
            }
        }
        auto vec = std::move(TrainID_ToTrain.find3(TrainIDForBPT(train.trainID)));
        if (!vec.empty()) {
            std::cout << -1 << std::endl;
            return;
        }
        TrainID_ToTrain.insert(TrainIDForBPT(train.trainID), train);
        std::cout << 0 << std::endl;
    }

    void deleteTrain(int timestamp, sjtu::vector<std::string> &v) {
        std::string *trainID;
        trainID = &v[1];
        if (!raw(*trainID)) {
            std::cout << -1 << std::endl;
            return;
        }
        TrainID_ToTrain.delete_(TrainIDForBPT(*trainID));
        std::cout << 0 << std::endl;
    }

    void releaseTrain(int timestamp, sjtu::vector<std::string> &v) {
        std::string *trainID;
        trainID = &v[1];
        auto vec = std::move(TrainID_ToTrain.find3(TrainIDForBPT(*trainID)));
        if (vec.empty() || vec[0].released) {
            std::cout << -1 << std::endl;
            return;
        }
        Train &train = vec[0];
        train.released = true;
        //todo:优化:不删除，只修改！CHANGE TO FUNCTION
//        TrainID_ToTrain.delete_(TrainIDForBPT(*trainID));
//        TrainID_ToTrain.insert(TrainIDForBPT(*trainID), train);
        TrainID_ToTrain.change(TrainIDForBPT(*trainID), train);
        std::cout << 0 << std::endl;
//    BigBlockBpt<TrainIDDateForBPT, releasedTrain> TrainIDDate_ToReleasedTrain;
//    BigBlockBpt<Station_TrainIDForBPT, TrainForQT> Station_TrainID_ToTrainForQT;
//    BPT<Station_TrainIDForBPT, TrainForQTOnlyId> Station_TrainID_ToTrainForQTOlyId;
        releasedTrain rt(train.trainID, train.saleDate[0], train.stationNum,
//                         train.stations,
                         train.startTime,
//                         train.travelTime, train.stopoverTime, train.price,
                         train.seatNum, train.type,
                         timestamp);
        for (int i = train.saleDate[0]; i <= train.saleDate[1]; ++i) {
            rt.date = i;
            TrainIDDate_ToReleasedTrain.insert(TrainIDDateForBPT(*trainID, i), rt);
        }

        TrainForQT tfq(train.trainID, 0, train.startTime, 0, train.stationNum, train.stations, train.saleDate,
                       train.travelTime, train.stopoverTime, train.price, train.type, 0);
        TrainForQTOnlyId tfqoi(train.trainID, 0, train.startTime, train.stopoverTime[0], 0, train.saleDate);
//        Station_TrainID_ToTrainForQT.insert(Station_TrainIDForBPT(train.stations[0], train.trainID), tfq);
        Station_TrainID_ToTrainForQTOlyId.insert(Station_TrainIDForBPT(train.stations[0], train.trainID), tfqoi);
        for (int i = 1; i < tfq.stationNum; ++i) {
            tfq.nowStation++;
            tfq.nowTime += tfq.travelTime[i] + tfq.stopoverTime[i - 1];
            tfq.nowPrice = tfq.price[i];
            tfq.thisOver = tfq.stopoverTime[i];
            tfqoi.nowStation++;
            tfqoi.nowTime += tfq.travelTime[i] + tfq.stopoverTime[i - 1];
            tfqoi.nowPrice = tfq.price[i];
            tfqoi.thisOver = tfq.stopoverTime[i];
            Station_TrainIDForBPT stfb(train.stations[i], train.trainID);
//            Station_TrainID_ToTrainForQT.insert(stfb, tfq);
            Station_TrainID_ToTrainForQTOlyId.insert(stfb, tfqoi);
        }
    }

    void queryTrain(int timestamp, sjtu::vector<std::string> &v) {
        std::string *trainID;
        int date;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == "-i") {
                trainID = &v[++i];
            } else if (v[i] == "-d") {
                try { date = dateToInt(v[++i]); } catch (int) {
                    std::cout << -1 << std::endl;
                    return;
                }
            }
        }
        auto vec2 = std::move(TrainIDDate_ToReleasedTrain.find3(TrainIDDateForBPT(*trainID, date)));
        if (vec2.empty()) {
            auto vec3 = std::move(TrainID_ToTrain.find3(TrainIDForBPT(*trainID)));
            if (vec3.empty() || vec3[0].saleDate[0] > date || vec3[0].saleDate[1] < date) {
                std::cout << -1 << std::endl;
                return;
            }
            assert(vec3.size() == 1);
            Train &train = vec3[0];
            train.print(date);
            return;
        }
        releasedTrain &rt = vec2[0];
        auto vec = std::move(TrainID_ToTrain.find3(TrainIDForBPT(*trainID)));
#ifdef debug
        assert(vec.size() == 1);
        assert(vec[0].released == true);
#endif
#ifndef cutRelease
        rt.print(vec[0]);
#else
        rt.print(vec[0],trainID->c_str());
#endif
    }

    void queryTicket(int timestamp, sjtu::vector<std::string> &v) {
//    BigBlockBpt<TrainIDDateForBPT, releasedTrain> TrainIDDate_ToReleasedTrain;
//    BigBlockBpt<Station_TrainIDForBPT, TrainForQT> Station_TrainID_ToTrainForQT;
//    BPT<Station_TrainIDForBPT, TrainForQTOnlyId> Station_TrainID_ToTrainForQTOlyId;
        std::string *start = nullptr, *toward = nullptr;
        int date = 0;
        priority pri = _time;
        try { parserForQT(start, toward, pri, v, date); } catch (int) {
            std::cout << 0 << std::endl;
            return;
        }


        sjtu::vector<TrainForQTOnlyId *> ans, ans2;//ans是出发站车次，ans2是到达站的车次
        sjtu::vector<int> firstStainDateVec;//第一站的发车日期
        sjtu::map<int, sjtu::map<int, sjtu::map<String, int> > > costToIndex;//costToIndex[price][trainID]=index//costToIndex 价格或时间->索引  索引->ans的下标

        sjtu::vector<TrainForQTOnlyId> sTrains, tTrains;
#ifdef debug
        //        sTrains = sjtuVtoStdV(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(start->c_str(), "")));
        //        tTrains = sjtuVtoStdV(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(toward->c_str(), "")));
                sTrains = Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(start->c_str(), ""));
                tTrains = Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(toward->c_str(), ""));
#endif
#ifndef debug
        sTrains = std::move(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(start->c_str(), "")));
        tTrains = std::move(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(toward->c_str(), "")));
#endif

        try {
#ifdef timetest
            timerqt.start();
#endif
            queryTicket(start, toward, date, pri, ans, ans2, costToIndex, firstStainDateVec, normal, sTrains, tTrains);
        } catch (int) {
#ifdef timetest
            timerqt.stop();
#endif
            std::cout << 0 << std::endl;
            return;
        }
#ifdef timetest
        timerqt.stop();
#endif


#ifdef timetest
        timerpt.start();
#endif
        std::cout << ans.size() << std::endl;
        for (auto iter = costToIndex.begin(); iter != costToIndex.end(); ++iter) {
            for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2) {
                for (auto iter3 = iter2->second.begin(); iter3 != iter2->second.end(); ++iter3) {
                    printTicket(start, toward, ans[iter3->second], ans2[iter3->second], iter3->first.str,
                                firstStainDateVec[iter3->second]);
                }
//                printTicket(start, toward, ans[iter2->second], ans2[iter2->second], iter2->first.str,
//                            firstStainDateVec[iter2->second]);
            }
        }
#ifdef timetest
        timerpt.stop();
#endif
    }

    void queryTransfer(int timestamp, sjtu::vector<std::string> &v) {
        std::string *start, *to;
        int date = 0;
        priority pri = _time;
        try { parserForQT(start, to, pri, v, date); } catch (int) {
            std::cout << 0 << std::endl;
            return;
        }

        //经过第一站的所有火车
        auto tempe = std::move(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(start->c_str(), "")));







//        //经过第一站的所有火车的全部信息
//        sjtu::vector<TrainForQT> sTrains;
////        for (auto &i: tempe) {
//        for (int i_ = 0; i_ < tempe.size(); ++i_) {
//            auto &i = tempe[i_];
//            auto temp = std::move(TrainID_ToTrain.find3(TrainIDForBPT(i.trainID)));
//#ifdef debug
//            assert(temp.size() == 1);
//#endif
//            sTrains.push_back(TrainForQT(temp[0], i));
//        }
////        = Station_TrainID_ToTrainForQT.find3(
////                Station_TrainIDForBPT(start->c_str(), ""));
        sjtu::vector<TrainForQTOnlyId> tTrains;
#ifdef debug
        //        tTrains = sjtuVtoStdV(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(to->c_str(), "")));
                tTrains = Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(to->c_str(), ""));
#endif
#ifndef debug
        tTrains = std::move(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(to->c_str(), "")));
#endif
        if (tempe.empty() || tTrains.empty()) {
            std::cout << 0 << std::endl;
            return;
        }


        TrainForQT startS;
//        将startS.trainID制成最大
        strcpy(startS.trainID, "\127\127\127\127\127\127\127\0");
        TrainForQTOnlyId tranS1, tranS2, toS;
        strcpy(tranS2.trainID, "\127\127\127\127\127\127\127\0");
        int firstTrain_firstStainDate = 0;
        int secondTrain_firstStainDate = 0;
        int cost = 1 << 29, secondCost = 1 << 29;
        bool flag = false;
        std::string trans;


        for (int i = 0; i < tempe.size(); ++i) {



//
//            //第i趟经过第一站的所有火车的全部信息
//            sjtu::vector<TrainForQT> sTrains;
////        for (auto &i: tempe) {
//            for (int i_ = i; i_ < i + 1; ++i_) {
//                auto &i11 = tempe[i_];
//                auto temp = std::move(TrainID_ToTrain.find3(TrainIDForBPT(i11.trainID)));
//#ifdef debug
//                assert(temp.size() == 1);
//#endif
//                sTrains.push_back(TrainForQT(temp[0], i11));
//            }
////        = Station_TrainID_ToTrainForQT.find3(
////                Station_TrainIDForBPT(start->c_str(), ""));
//

            Train tmp = TrainID_ToTrain.find3(TrainIDForBPT(tempe[i].trainID))[0];
            TrainForQT sTrains = TrainForQT(tmp, tempe[i]);


            int firstStainDate = date - (sTrains.nowTime + sTrains.thisOver) / (24 * 60);
            if (sTrains.saleDate[0] > firstStainDate || firstStainDate > sTrains.saleDate[1])continue;
            int start_timeOfFirstTrain = sTrains.nowTime + sTrains.thisOver;
            int arrive_TimeOfFirstTrain = start_timeOfFirstTrain;


            sjtu::vector<TrainForQTOnlyId *> nd_ans, nd_ans2;//ans是出发站车次，ans2是到达站的车次
            sjtu::vector<int> nd_firstStainDateVec;//第一站的发车日期
            sjtu::map<int, sjtu::map<int, sjtu::map<String, int> > > nd_costToIndex;//costToIndex[price][trainID]=index//costToIndex 价格或时间->索引  索引->ans的下标
            sjtu::vector<sjtu::vector<TrainForQTOnlyId> > sTrains2, tTrains2;
            sjtu::vector<int> ks;
            std::string tranStation;


            for (int k = sTrains.nowStation + 1; k < sTrains.stationNum; ++k) {
                int k0 = k - sTrains.nowStation - 1;
                arrive_TimeOfFirstTrain += sTrains.travelTime[k];
                int arrive_DATOfFirstTrain = firstStainDate * 24 * 60 + arrive_TimeOfFirstTrain;
                int arrive_day1 = firstStainDate + arrive_TimeOfFirstTrain / (24 * 60);
                int arrive_time1 = arrive_TimeOfFirstTrain % (24 * 60);
                tranStation = sTrains.stations[k];

#ifdef debug
                //                sTrains2.push_back(sjtuVtoStdV(
                //                        Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(tranStation.c_str(), ""))));
                //                tTrains2.push_back(
                //                        sjtuVtoStdV(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(to->c_str(), ""))));
                                sTrains2.push_back(
                                        Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(tranStation.c_str(), "")));
                                tTrains2.push_back(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(to->c_str(), "")));
#endif
#ifndef debug
                sTrains2._push_back(
                        Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(tranStation.c_str(), "")));
                tTrains2._push_back(Station_TrainID_ToTrainForQTOlyId.find3(Station_TrainIDForBPT(to->c_str(), "")));
#endif
                try {
                    queryTicket(&tranStation, to, arrive_day1, pri, nd_ans, nd_ans2, nd_costToIndex,
                                nd_firstStainDateVec,
                                after, sTrains2[k0], tTrains2[k0], arrive_time1, firstStainDate, &sTrains, k, &ks);
                } catch (int) {
                    arrive_TimeOfFirstTrain += sTrains.stopoverTime[k];
                    continue;
                }
                arrive_TimeOfFirstTrain += sTrains.stopoverTime[k];
            }
            bool little_flag = false;
            for (auto iter: nd_costToIndex) {
                for (auto iter2: iter.second) {
                    for (auto iter3: iter2.second) {
                        if (strcmp(sTrains.trainID, iter3.first.str) == 0)continue;
                        int index = iter3.second;
                        int k = ks[index];
                        //如果车次一样就跳过
                        int nowCost = 0, nowsecondCost = 0;
                        nowCost = iter.first;
                        nowsecondCost = iter2.first;
//                        if (pri == _price) {
//                    nowCost = sTrains[i].price[k] - sTrains[i].price[sTrains[i].nowStation] +
//                              iter.first;
//                    nowsecondCost = (nd_firstStainDateVec[iter.second.begin()->second.begin()->second] -
//                                     firstStainDate) * 24 * 60 +
//                                    nd_ans2[iter.second.begin()->second.begin()->second]->nowTime -
//                                    sTrains[i].nowTime;
//                        } else if (pri == _time) {
//                            nowCost = (nd_firstStainDateVec[iter.second.begin()->second.begin()->second] -
//                                       firstStainDate) * 24 * 60 +
//                                      nd_ans2[iter.second.begin()->second.begin()->second]->nowTime -
//                                      sTrains[i].nowTime;
//                            nowsecondCost = sTrains[i].price[k] - sTrains[i].price[sTrains[i].nowStation] +
//                                            iter.second.begin()->first;
//                        }
                        bool change = false;
                        int b1 = nowCost - cost;
                        if (b1 < 0)change = true;
                        else if (b1 == 0) {
                            int b2 = nowsecondCost - secondCost;
                            if (b2 < 0)change = true;
                            else if (b2 == 0) {
                                int b3 = strcmp(sTrains.trainID, startS.trainID);
                                if (b3 < 0)change = true;
                                else if (b3 == 0) {
                                    int b4 = strcmp(iter3.first.str,
                                                    tranS2.trainID);
                                    if (b4 < 0)change = true;
                                }
                            }
                        }
                        if (change) {
                            cost = nowCost;
                            secondCost = nowsecondCost;
                            startS = sTrains;
//                        TicketSystem::TrainForQTOnlyId::TrainForQTOnlyId(const char *_trainID, int _nowStation, int _nowTime, int _thisOver, int _nowPrice, const int *_saleDate)
                            tranS1 = TrainForQTOnlyId(sTrains.trainID, k, getTime(k, sTrains),
                                                      sTrains.stopoverTime[k], sTrains.price[k],
                                                      sTrains.saleDate);
                            tranS2 = *nd_ans[index];
                            trans = sTrains.stations[k];
                            toS = *nd_ans2[index];
//                            toS = **(nd_ans2.data + index);
                            firstTrain_firstStainDate = firstStainDate;
                            secondTrain_firstStainDate = nd_firstStainDateVec[index];
                            cost = nowCost;
                            flag = true;
                            little_flag = true;
#ifdef debug
                            //                        assert(tranS2);
                            //                        assert(toS);
                            //                        assert(*tranS2==*toS);
#endif
                        }
                        if (little_flag)break;
                    }
                    if (little_flag)break;
                }
                if (little_flag)break;
            }
        }
        if (flag == false) {
            std::cout << 0 << std::endl;
            return;
        }
// printTicket(std::string *start, std::string *to, TrainForQTOnlyId *sT, TrainForQTOnlyId *tT, const char *trainID,
//                int date) {

        TrainForQTOnlyId tem_startS(startS);
        printTicket(start, &trans, &tem_startS, &tranS1, startS.trainID, firstTrain_firstStainDate);
        printTicket(&trans, to, &tranS2, &toS, toS.trainID, secondTrain_firstStainDate);
    }

    void buyTicket(int timestamp, sjtu::vector<std::string> &v) {
        std::string *username, *trainID, *start, *to;
        int num = 0, date = 0;
        queue q = no;
        try { parserForBuy(username, trainID, date, num, start, to, v, q); } catch (int) {
            std::cout << -1 << std::endl;
            return;
        }
        if (!hasLogIn(*username)) {
            std::cout << -1 << std::endl;
            return;
        }

        auto sbasicInfo = Station_TrainID_ToTrainForQTOlyId.findHard(
                Station_TrainIDForBPT(start->c_str(), trainID->c_str()));
        auto tbasicInfo = Station_TrainID_ToTrainForQTOlyId.findHard(
                Station_TrainIDForBPT(to->c_str(), trainID->c_str()));
        try { checkV(sbasicInfo), checkV(tbasicInfo); } catch (int) { return; }
        int sNum = sbasicInfo[0].nowStation, tNum = tbasicInfo[0].nowStation;
        if (sNum >= tNum) {
            std::cout << -1 << std::endl;
            return;
        }
        date -= (sbasicInfo[0].nowTime + sbasicInfo[0].thisOver) / (24 * 60);
        Order order(username->c_str(), trainID->c_str(), start->c_str(),
                    sbasicInfo[0].nowTime + sbasicInfo[0].thisOver + date * 24 * 60, to->c_str(),
                    tbasicInfo[0].nowTime + date * 24 * 60, tbasicInfo[0].nowPrice - sbasicInfo[0].nowPrice, num, 0,
                    sNum, tNum, success, timestamp);
        order.dateOfTrain = date;
        auto vec = std::move(TrainIDDate_ToReleasedTrain.find3(TrainIDDateForBPT(*trainID, date)));
        try { checkV(vec); } catch (int) { return; }
        releasedTrain *rt = &vec[0];

        if (rt->seatNum < num) {
            std::cout << -1 << std::endl;
            return;
        }

        for (int i = sNum; i < tNum; ++i) {
            if (rt->restTickets[i] < num) {
                if (q == yes) {
                    std::cout << "queue" << std::endl;
                    order.status = pending;
                    addOrder(username->c_str(), order);
                    Queue(trainID->c_str(), date, order);
                    return;
                } else {
                    std::cout << -1 << std::endl;
                    return;
                }
            }
        }
        for (int i = sNum; i < tNum; ++i) {
            rt->restTickets[i] -= num;
        }
        //输出总价格
        auto vec2 = std::move(TrainID_ToTrain.find3(TrainIDForBPT(*trainID)));
        Train *t = &vec2[0];
#ifdef debug
        assert(vec2.size() == 1);
        assert(vec2[0].released == true);
#endif
        std::cout << (t->price[tNum] - t->price[sNum]) * num << std::endl;
        TrainIDDate_ToReleasedTrain.changeHard(TrainIDDateForBPT(*trainID, date), *rt);
        addOrder(username->c_str(), order);
    }

    void queryOrder(int timestamp, sjtu::vector<std::string> &v) {
        std::string *username = &v[1];
        if (!hasLogIn(*username)) {
            std::cout << -1 << std::endl;
            return;
        }
        auto vec = std::move(Username_ToOrders.find3(UsernameForBPT(*username)));
        std::cout << vec.size() << std::endl;
//        for (int i = 0; i < vec.size(); ++i) {
        for (int i = vec.size() - 1; i >= 0; --i) {
            vec[i].print();
        }
    }

    void refundTicket(int timestamp, sjtu::vector<std::string> &v) {
        std::string *username;
        int n = 0;
        parserForRefund(username, n, v);
        if (!hasLogIn(*username)) {
            std::cout << -1 << std::endl;
            return;
        }
        auto vec = std::move(Username_ToOrders.find3(UsernameForBPT(*username)));
#ifdef debug
        //vec的timestamp递增
        for (int i = 1; i < vec.size(); ++i) {
            assert(vec[i].timestamp > vec[i - 1].timestamp);
        }
#endif
        if (vec.size() < n) {
            std::cout << -1 << std::endl;
            return;
        }
        auto &od = vec[vec.size() - n];

        if (od.status == pending) {
            auto vec2 = TrainIDDate_ToPends.findHard(TrainIDDateForBPT(od.trainID, od.dateOfTrain, od.timestamp));
            try { checkV(vec2); } catch (int) { return; }
            TrainIDDate_ToPends.delete_(TrainIDDateForBPT(od.trainID, od.dateOfTrain, od.timestamp), vec2[0]);
            od.status = refunded;
            Username_ToOrders.changeHard(UsernameForBPT(username->c_str(), od.timestamp), od);
            std::cout << 0 << std::endl;
        } else if (od.status == success) {
            auto vec2 = std::move(TrainIDDate_ToReleasedTrain.find3(TrainIDDateForBPT(od.trainID, od.dateOfTrain)));
            try { checkV(vec2); } catch (int) { return; }
            releasedTrain *rt = &vec2[0];
            for (int i = od.fNum; i < od.tNum; ++i) {
                rt->restTickets[i] += od.num;
            }
            auto pds = std::move(TrainIDDate_ToPends.find3(TrainIDDateForBPT(od.trainID, od.dateOfTrain)));
#ifdef debug
            //timestamp 递增
            for (int i = 1; i < pds.size(); ++i) {
                assert(pds[i].timestamp > pds[i - 1].timestamp);
            }
#endif
            for (int i = 0; i < pds.size(); ++i) {
                tryBuy(pds[i], rt);
            }
            TrainIDDate_ToReleasedTrain.changeHard(TrainIDDateForBPT(od.trainID, od.dateOfTrain), *rt);
            od.status = refunded;
            Username_ToOrders.changeHard(UsernameForBPT(username->c_str(), od.timestamp), od);
            std::cout << 0 << std::endl;
        } else if (od.status == refunded) {
            std::cout << -1 << std::endl;
            return;
        }
//        }
//        std::cout << sum << std::endl;
//        for (int i = 0; i < n; ++i) {
//            Username_ToOrders.delete_(UsernameForBPT(*username), vec[i]);
//        }
    }

    void clean() {}

    void exit() {
        std::cout << "bye" << std::endl;
    }

public:
    TicketSystem() : Username_ToUser("Username_ToUser", 30000), Username_ToOrders("Username_ToOrders", 30000),
                     TrainID_ToTrain("TrainID_ToTrain"),
                     TrainIDDate_ToReleasedTrain("TrainIDDate_ToReleasedTrain", 600, 500),
//                     Station_TrainID_ToTrainForQT("Station_TrainID_ToTrainForQT"),
                     Station_TrainID_ToTrainForQTOlyId("Station_TrainID_ToTrainForQTOlyID", 600, 500),
                     TrainIDDate_ToPends("TrainIDDate_ToPends", 600, 500)
#ifdef timetest
,timerpt("timerpt"), timerqt("timerqt")
#endif
                     {
//        std::cout << "User_Size:  " << sizeof(User) << std::endl <<
//                  "Train_Size:  " << sizeof(Train) << std::endl <<
//                  "releasedTrain_Size:  " << sizeof(releasedTrain) << std::endl <<
//                  "Order_Size:  " << sizeof(Order) << std::endl <<
//                  "Pend_Size:  " << sizeof(Pend) << std::endl <<
//                  "LogUser_Size:  " << sizeof(LogUser) << std::endl <<
//                  "TrainForQT_Size:  " << sizeof(TrainForQT) << std::endl <<
//                  "TrainForQTOnlyId_Size:  " << sizeof(TrainForQTOnlyId) << std::endl;
//        std::cout << "keys--------------------" << std::endl;
//        std::cout << "UsernameForBPT_Size:  " << sizeof(UsernameForBPT) << std::endl <<
//                  "TrainIDForBPT_Size:  " << sizeof(TrainIDForBPT) << std::endl <<
//                  "ValForTrainIDDateForBPT_Size:  " << sizeof(ValForTrainIDDateForBPT) << std::endl <<
//                  "TrainIDDateForBPT_Size:  " << sizeof(TrainIDDateForBPT) << std::endl <<
//                  "ValForStation_TrainIDForBPT_Size:  " << sizeof(ValForStation_TrainIDForBPT) << std::endl <<
//                  "Station_TrainIDForBPT_Size:  " << sizeof(Station_TrainIDForBPT) << std::endl;
    }

    void run() {
#ifdef timetest
        Timer timer("clean");
        Timer timer2("exit");
        Timer timer3("add_user");
        Timer timer4("login");
        Timer timer5("logout");
        Timer timer6("query_profile");
        Timer timer7("modify_profile");
        Timer timer8("add_train");
        Timer timer9("delete_train");
        Timer timer10("release_train");
        Timer timer11("query_train");
        Timer timer12("query_ticket");
        Timer timer13("query_transfer");
        Timer timer14("buy_ticket");
        Timer timer15("query_order");
        Timer timer16("refund_ticket");
#endif
        while (true) {
            std::string timestampStr, cmd;
            std::cin >> timestampStr >> cmd;
            std::cout << timestampStr << ' ';
            if (cmd == "clean") {
                clean();
            }
            if (cmd == "exit") {
#ifdef timetest
                timer2.start();
#endif
                exit();
#ifdef timetest
                timer2.stop();
#endif
                return;
            }
            int timestamp = timestampStrToInt(timestampStr);
            sjtu::vector<std::string> v;
            std::string message;
            getline(std::cin, message);
            splitString(message, v);
            if (cmd == "add_user") {
#ifdef timetest
                timer3.start();
#endif
                addUser(timestamp, v);
#ifdef timetest
                timer3.stop();
#endif
            }
            if (cmd == "login") {
#ifdef timetest
                timer4.start();
#endif
                login(timestamp, v);
#ifdef timetest
                timer4.stop();
#endif
            }
            if (cmd == "logout") {
#ifdef timetest
                timer5.start();
#endif
                logout(timestamp, v);

#ifdef timetest
                timer5.stop();
#endif
            }
            if (cmd == "query_profile") {
#ifdef timetest
                timer6.start();
#endif
                queryProfile(timestamp, v);
#ifdef timetest
                timer6.stop();
#endif
            }
            if (cmd == "modify_profile") {
#ifdef timetest
                timer7.start();
#endif
                modifyProfile(timestamp, v);
#ifdef timetest
                timer7.stop();
#endif
            }
            if (cmd == "add_train") {
#ifdef timetest
                timer8.start();
#endif
                addTrain(timestamp, v);
#ifdef timetest
                timer8.stop();
#endif
            }
            if (cmd == "delete_train") {
#ifdef timetest
                timer9.start();
#endif
                deleteTrain(timestamp, v);
#ifdef timetest
                timer9.stop();
#endif
            }
            if (cmd == "release_train") {
#ifdef timetest
                timer10.start();
#endif
                releaseTrain(timestamp, v);
#ifdef timetest
                timer10.stop();
#endif
            }
            if (cmd == "query_train") {
#ifdef timetest
                timer11.start();
#endif
                queryTrain(timestamp, v);
#ifdef timetest
                timer11.stop();
#endif
            }
            if (cmd == "query_ticket") {
#ifdef timetest
                timer12.start();
#endif
                queryTicket(timestamp, v);
#ifdef timetest
                timer12.stop();
#endif
            }
            if (cmd == "query_transfer") {
#ifdef timetest
                timer13.start();
#endif
//                continue;
                queryTransfer(timestamp, v);
#ifdef timetest
                timer13.stop();
#endif
            }
            if (cmd == "buy_ticket") {
#ifdef timetest
                timer14.start();
#endif
                buyTicket(timestamp, v);
#ifdef timetest
                timer14.stop();
#endif
            }
            if (cmd == "query_order") {
#ifdef timetest
                timer15.start();
#endif
                queryOrder(timestamp, v);
#ifdef timetest
                timer15.stop();
#endif
            }
            if (cmd == "refund_ticket") {
#ifdef timetest
                timer16.start();
#endif
                refundTicket(timestamp, v);
#ifdef timetest
                timer16.stop();
#endif
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