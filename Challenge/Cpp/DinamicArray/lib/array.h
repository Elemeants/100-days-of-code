#ifndef ARRAY_H

#include "exceptions.h"
#include <functional>

// Interface
template <typename T> 
struct IList {
    virtual T getValue(int) = 0;
    virtual void setValue(int, T) = 0;
    virtual int length() const = 0; 
    virtual void push_front(T) = 0;
    virtual void push_last(T) = 0;
    virtual T pop_front() = 0;
    virtual T pop_last() = 0;
    virtual void forEach(std::function<void(T&)> function) = 0;
    virtual void forEach(std::function<void(int, T&)> function) = 0;
};

template <typename T> 
struct List : IList<T> {
private:
    size_t __len__;
    T *array;
public:
    List(size_t _Size) {
        this->__len__ = _Size;
        this->array = new T[this->__len__];
        for (int i = 0; i < 1; i++) {
            this->array[i] = T();
        }
    }
    List() {
        this->__len__ = 0;
        this->array = new T[this->__len__];
        this->array[0] = T();
    }
    T getValue(int index) {
        if (this->__len__ < index) {
            return this->array[index];
        } else {
            throw new IndexArrayException();
        }
    }
    int length() const { 
        return this->__len__;
    }
    void setValue(int index, T data) {
        if (this->__len__ < index) {
            this->array[index] = data;
        } else {
            throw new IndexArrayException();
        }
    }
    void push_front(T data) {
        T *tempData = this->array;
        this->__len__ ++;
        this->array = new T[this->__len__];
        this->array[0] = data;
        for (int x = 1; x < this->__len__; x++) {
            this->array[x] = tempData[x - 1];
        }
        delete tempData;
    }
    void push_last(T data) {
        T *tempData = this->array;
        this->__len__ ++;
        this->array = new T[this->__len__];
        for (int x = 0; x < (this->__len__ - 1); x++) {
            this->array[x] = tempData[x];
        }
        delete tempData;
        this->array[this->__len__ - 1] = data;
    }
    T pop_front() {
        throw new NotImplementedException();
    }
    T pop_last() {
        throw new NotImplementedException();
    }
    void forEach(std::function<void(T&)> function) {
        for (int index = 0; index < this->__len__; index++) {
            function(this->array[index]);
        }
    }
    void forEach(std::function<void(int, T&)> function) {
        for (int index = 0; index < this->__len__; index++) {
            function(index, this->array[index]);
        }
    }
};

#endif