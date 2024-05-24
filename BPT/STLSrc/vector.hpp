#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

//#include "exceptions.hpp"

//#include <climits>
//#include <cstddef>
#include <iostream>
#ifndef debug

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {
    private:
    public:
        T *data = nullptr;
        size_t _size = 0, max_size = 128;

        void _clear() {
            delete[] data;
            data = new T[128];
            _size = 0;
            max_size = 128;
        }

        void double_size() {
            auto tmp = new T[max_size * 2];
            for (int i = 0; i < _size; ++i) {
                tmp[i] = data[i];
            }
            delete[] data;
            data = tmp;
            tmp = nullptr;
            max_size *= 2;
        }


    public:

        vector() {
            data = new T[128];
        }

        ~vector() {
            delete[]data;
        }

        vector(const vector<T> &other) {
            if (this == &other)return;
            delete []data;
            _size = other._size;
            max_size = other.max_size;
            data = new T[max_size];
            for (int i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
        }

        vector &operator=(const vector &other) {
            if (this == &other)return *this;
            delete []data;
            _size = other._size;
            max_size = other.max_size;
            data = new T[max_size];
            for (int i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
            return *this;
        }

//        vector(vector &&other) noexcept {
////            if (this == &other)return ;
//            delete []data;
//            _size = other._size;
//            max_size = other.max_size;
//            data = new T[max_size];
//            for (int i = 0; i < _size; ++i) {
//                data[i] = other.data[i];
//            }
//        }
        vector(vector &&other) noexcept {
            if (this == &other)return;
            delete []data;
            _size = other._size;
            max_size = other.max_size;
            data = other.data;
            other.data = nullptr;
            other._size = 0;
            other.max_size = 1;
        }

        const T &at(const size_t &pos) const {
            if (pos >= _size || pos < 0) {
                std::cerr << "index_out_of_bound" << std::endl;
                assert(0);
            }
            return data[pos];
        }
        T &at(const size_t &pos){
            if (pos >= _size || pos < 0) {
                std::cerr << "index_out_of_bound" << std::endl;
                assert(0);
            }
            return data[pos];
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T &operator[](const size_t &pos) {
            if (pos >= _size || pos < 0) {
                std::cerr << "index_out_of_bound" << std::endl;
                assert(0);
            }
            return data[pos];
        }

        const T &operator[](const size_t &pos) const {
            return at(pos);
        }


        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T &back() const {
            if (empty()) {
                std::cerr << "container_is_empty" << std::endl;
                assert(0);
            }
            return at(_size - 1);
        }

        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return _size == 0;
        }

        /**
         * returns the number of elements
         */
        size_t size() const {
            return _size;
        }

        /**
         * clears the contents
         */
        void clear() {
            _clear();
        }

        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (_size >= max_size)double_size();
            data[_size++] = value;
        }
        void _push_back(const T &value) {
            if (_size >= max_size)double_size();
            data[_size++] = std::move(value);
        }
    };


}

#endif
#endif
