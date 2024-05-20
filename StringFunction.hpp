//
// Created by qiuyuhang on 24-5-20.
//

#ifndef TICKETSYSTEM_STRINGFUNCTION_HPP
#define TICKETSYSTEM_STRINGFUNCTION_HPP

#include "BPT/BPT.hpp"

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

#ifndef debug
void splitString(const std::string &str, std::vector<std::string> &res) {
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
#endif

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

int timeToInt(const std::string &str) {
    int hh = (str[0] - '0') * 10 + (str[1] - '0');
    int mm = (str[3] - '0') * 10 + (str[4] - '0');
    return hh * 60 + mm;
}

int dateToInt(const std::string &str) {
    int mm = (str[0] - '0') * 10 + (str[1] - '0');
    int dd = (str[3] - '0') * 10 + (str[4] - '0');
    if (mm == 6)return dd;
    if (mm == 7)return dd + 30;
    if (mm == 8)return dd + 61;
#ifdef debug
    assert(0);
#endif
}

//将一个含|的string分解成小string
void splitSplitString(const std::string &str, sjtu::vector<std::string> &res) {
    res.clear();
    std::string tmp;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '|') {
            res.push_back(tmp);
            tmp.clear();
        } else {
            if (str[i] >> 3 == (char) 0b11111110) {
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                tmp.push_back(str[i + 2]);
                tmp.push_back(str[i + 3]);
                i += 3;
            }
                //1110xxxx
            else if (str[i] >> 4 == (char) 0b11111110) {
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                tmp.push_back(str[i + 2]);
                i += 2;
            }
                //110xxxxx
            else if (str[i] >> 5 == (char) 0b11111110) {
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                i += 1;
            }
                //10xxxxxxx&0xxxxxxx
            else {
                tmp.push_back(str[i]);
            }
        }
    }
    if (!tmp.empty())res.push_back(tmp);
}

#ifndef debug
void splitSplitString(const std::string &str, std::vector<std::string> &res) {
    res.clear();
    std::string tmp;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '|') {
            res.push_back(tmp);
            tmp.clear();
        } else {
            if (str[i] >> 3 == (char) 0b11111110) {
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                tmp.push_back(str[i + 2]);
                tmp.push_back(str[i + 3]);
                i += 3;
            }
                //1110xxxx
            else if (str[i] >> 4 == (char) 0b11111110) {
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                tmp.push_back(str[i + 2]);
                i += 2;
            }
                //110xxxxx
            else if (str[i] >> 5 == (char) 0b11111110) {
                tmp.push_back(str[i]);
                tmp.push_back(str[i + 1]);
                i += 1;
            }
                //10xxxxxxx&0xxxxxxx
            else {
                tmp.push_back(str[i]);
            }
        }
    }
    if (!tmp.empty())res.push_back(tmp);
}
#endif

//int timeStrToInt(const std::string &str) {
//    int hh = (str[0] - '0') * 10 + (str[1] - '0');
//    int mm = (str[3] - '0') * 10 + (str[4] - '0');
//    return hh * 60 + mm;
//}
#endif //TICKETSYSTEM_STRINGFUNCTION_HPP
