//
// Created by qiuyuhang on 24-5-24.
//

#ifndef TICKETSYSTEM_EXTERNALMAP_HPP
#define TICKETSYSTEM_EXTERNALMAP_HPP

#include "BPT/BPT.hpp"
#include <map>

//#define sjtu std

template<typename Key, typename Value>
class externalMap {
private:
#ifdef debug
    public:
#endif
    sjtu::map<Key, int> date;
    ll size = 0;
    ll endOfFile = 100;
    std::string filePath;
    std::fstream file;
    std::fstream file2;

    void getValue(ll pos, Value &rsl) {
        file.seekg(pos, std::ios::beg);
        file.read(reinterpret_cast<char *>(&rsl), sizeof(rsl));
        return rsl;
    }

    Value getValue(ll pos) {
        Value rsl;
        file.seekg(pos, std::ios::beg);
        file.read(reinterpret_cast<char *>(&rsl), sizeof(rsl));
        return rsl;
    }

    void GET() {
        auto *tmp1 = new Key[size];
        auto *tmp2 = new int[size];
        file2.seekg(0, std::ios::beg);
        file2.read(reinterpret_cast<char *>(tmp1), size * sizeof(Key));
        file2.read(reinterpret_cast<char *>(tmp2), size * sizeof(int));
        for (int i = 0; i < size; ++i) {
            date[tmp1[i]] = tmp2[i];
        }
    }

    void PUSH() {
//        typename sjtu::map<Key,int>::value_type *tmp=new typename sjtu::map<Key,int>::value_type[size];
        auto *tmp1 = new Key[size];
        auto *tmp2 = new int[size];
        int i = -1;
        for (auto &itr: date) {
            ++i;
            tmp1[i] = itr.first;
            tmp2[i] = itr.second;
        }
        file2.seekp(0, std::ios::beg);
        file2.write(reinterpret_cast<char *>(tmp1), size * sizeof(Key));
        file2.write(reinterpret_cast<char *>(tmp2), size * sizeof(int));
    }

public:
    externalMap() = delete;

    externalMap(const std::string &_filePath) : filePath(_filePath) {
        file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
        file2.open(filePath + "DATA", std::ios::in | std::ios::out | std::ios::binary);
        if (!file) {
            file.open(filePath, std::ios::out | std::ios::binary);
            file.close();
            file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
            file2.open(filePath + "DATA", std::ios::out | std::ios::binary);
            file2.close();
            file2.open(filePath + "DATA", std::ios::in | std::ios::out | std::ios::binary);
            return;
        }
        if (!file) {
            std::cerr << "open file failed" << std::endl;
            assert(0);
        }
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char *>(&size), sizeof(size));
        file.read(reinterpret_cast<char *>(&endOfFile), sizeof(endOfFile));
        GET();
    }


    ~externalMap() {
        file.seekp(0, std::ios::beg);
        file.write(reinterpret_cast<char *>(&size), sizeof(int));
        file.write(reinterpret_cast<char *>(&endOfFile), sizeof(ll));
        PUSH();
        file.close();
    }

    void insert(Key key, Value value) {
        date[key] = endOfFile;
        file.seekp(endOfFile, std::ios::beg);
        file.write(reinterpret_cast<char *>(&value), sizeof(value));
        endOfFile += sizeof(value);
        size++;
    }

    void delete_(Key key) {
        //todo:优化
        date.erase(key);
#ifdef debug
        assert(pos.size() == 1);
#endif
        size--;
    }

    auto find3(const Key &key) {
        sjtu::vector<Value> rsl;
        if (size == 0)return rsl;
        auto itr = date.find(key);
        if (itr == date.end())return rsl;
        else {
            rsl.push_back(getValue(itr->second));
        }
        return rsl;
    }

    int _size() {
        return size;
    }

    void change(Key key, Value value) {
        file.seekp(date[key], std::ios::beg);
        file.write(reinterpret_cast<char *>(&value), sizeof(value));
    }
};

#endif //TICKETSYSTEM_EXTERNALMAP_HPP
