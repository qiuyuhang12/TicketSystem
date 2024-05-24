//
// Created by qiuyuhang on 24-5-20.
//

#ifndef TICKETSYSTEM_HashBPT_HPP
#define TICKETSYSTEM_HashBPT_HPP

#include "BPT/BPT.hpp"
struct Int {
    int val;
    bool isMin;
    char realVal;

    Int() : val(0), isMin(false) {}

    Int(int _val, bool _isMin, int _realVal) : val(_val), isMin(_isMin), realVal(_realVal) {}

    Int(int _val) : val(_val), isMin(false) {}

    Int(int _val, int _realVal) : val(_val), isMin(false), realVal(_realVal) {}

    Int(int val, bool isMin) : val(val), isMin(isMin) {}

    Int(const Int &other) : val(other.val), isMin(other.isMin), realVal(other.realVal) {}

    bool operator<(const Int &other) const {
        return val < other.val;
    }

    bool operator==(const Int &other) const {
        return val == other.val;
    }

    bool operator>(const Int &other) const {
        return val > other.val;
    }

    bool operator<=(const Int &other) const {
        return val <= other.val;
    }

    bool operator>=(const Int &other) const {
        return val >= other.val;
    }

    bool operator!=(const Int &other) const {
        return val != other.val;
    }
//
//    bool operator<(const Int &other) const {
//        if (val != other.val)return val < other.val;
//        return realVal < other.realVal;
//    }
//
//    bool operator==(const Int &other) const {
//        return val == other.val && realVal == other.realVal;
//    }
//
//    bool operator>(const Int &other) const {
//        if (val != other.val)return val > other.val;
//        return realVal > other.realVal;
//    }
//
//    bool operator<=(const Int &other) const {
//        if (val != other.val)return val <= other.val;
//        return realVal <= other.realVal;
//    }
//
//    bool operator>=(const Int &other) const {
//        if (val != other.val)return val >= other.val;
//        return realVal >= other.realVal;
//    }
//
//    bool operator!=(const Int &other) const {
//        return val != other.val || realVal != other.realVal;
//    }
//        return val != other.val;
};
template<HasIsMin Key, typename Value>
class HashBPT {
private:
#ifdef debug
    public:
#endif
    BPT<Int, Value> bpt;
    int size = 0;
//    std::string filePath;

public:
    HashBPT() = delete;

    HashBPT(const std::string &_filePath) :
//    filePath(_filePath),
            bpt(_filePath) {
    }

    ~HashBPT() {
    }

    void insert(Key key, Value value) {
        bpt.insert(key.hash, value);
    }

    void delete_(Key key, Value value) {
        //todo:优化
        bpt.delete_(key.hash, value);
        size--;
    }

    auto find3(const Key &key) {
        return bpt.find3(key.hash);
    }

    int _size() {
        return bpt.size_();
    }

    void change(Key key, Value value) {
        bpt.change(key.hash, value);
    }
};

#endif //TICKETSYSTEM_HashBPT_HPP
