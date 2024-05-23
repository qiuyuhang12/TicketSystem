//
// Created by qiuyuhang on 24-5-20.
//

#ifndef TICKETSYSTEM_BIGBLOCKBPT_HPP
#define TICKETSYSTEM_BIGBLOCKBPT_HPP

#include "BPT/BPT.hpp"

template<HasIsMin Key, typename Value>
class BigBlockBpt {
private:
#ifdef debug
public:
#endif
    BPT<Key, ll> bpt;
    int size = 0;
    ll endOfFile = 100;
    std::string filePath;
    std::fstream file;

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

public:
    BigBlockBpt() = delete;

    BigBlockBpt(const std::string &_filePath,int ln,int lb) : filePath(_filePath), bpt(_filePath,ln,lb) {
        file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
        if (!file) {
            file.open(filePath, std::ios::out | std::ios::binary);
            file.close();
            file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
            return;
        }
        if (!file) {
            std::cerr << "open file failed" << std::endl;
            assert(0);
        }
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char *>(&size), sizeof(size));
        file.read(reinterpret_cast<char *>(&endOfFile), sizeof(endOfFile));
    }

    ~BigBlockBpt() {
        file.seekp(0, std::ios::beg);
        file.write(reinterpret_cast<char *>(&size), sizeof(int));
        file.write(reinterpret_cast<char *>(&endOfFile), sizeof(ll));
        file.close();
    }

    void insert(Key key, Value value) {
        bpt.insert(key, endOfFile);
        file.seekp(endOfFile, std::ios::beg);
        file.write(reinterpret_cast<char *>(&value), sizeof(value));
        endOfFile += sizeof(value);
        size++;
    }

    void delete_(Key key) {
        //todo:优化
        auto pos = bpt.find3(key);
#ifdef debug
        assert(pos.size() == 1);
#endif
        bpt.delete_(key, pos[0]);
        size--;
    }

    auto find3(const Key &key) {
        sjtu::vector<Value> rsl;
        if (size==0)return rsl;
        auto pos = bpt.find3(key);
//        for (auto &i: pos) {
        for (ll i0=0; i0<pos.size();++i0) {
            rsl.push_back(getValue(pos[i0]));
        }
        return rsl;
    }

    int _size() {
        return size;
    }

    void change(Key key, Value value) {
        auto pos = bpt.find3(key);
#ifdef debug
        assert(pos.size() == 1);
#endif
        file.seekp(pos[0], std::ios::beg);
        file.write(reinterpret_cast<char *>(&value), sizeof(value));
    }

//    void clear() {
//        bpt.clear();
//        size = 0;
//        endOfFile = 100;
//    }
};

#endif //TICKETSYSTEM_BIGBLOCKBPT_HPP
