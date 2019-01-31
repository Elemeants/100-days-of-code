#ifndef LIST_H

#include <functional>
#include <exception>

namespace Exceptions {
    struct IndexArrayException : public std::exception
    {
        const char * what () const throw ()
        {
            return "IndexArrayException";
        }
    };
    struct NotImplementedException : public std::exception
    {
        const char * what () const throw ()
        {
            return "NotImplementedException";
        }
    };
}

template <typename T> 
struct List {
private:
    size_t _len;
    T *arr_data;
public:
    List(size_t _Size) {
        this->_len = _Size;
        this->arr_data = new T[this->_len];
        for (int i = 0; i < _Size; i++) {
            this->arr_data[i] = T();
        }
    }
    List() {
        this->_len = 0;
        this->arr_data = new T[this->_len];
        this->arr_data[0] = T();
    }
    ~List() {
        this->_len = 0;
        delete this->arr_data;
    }
    int length() const { 
        return this->_len;
    }
    void clear() {
        delete this->arr_data;
        this->arr_data = new T[0];
        this->_len = 0;
        this->arr_data[0] = T();
    }
    void push(T data) {
        T *tempData = this->arr_data;
        this->_len ++;
        this->arr_data = new T[this->_len];
        this->arr_data[0] = data;
        for (int x = 1; x < this->_len; x++) {
            this->arr_data[x] = tempData[x - 1];
        }
        delete tempData;
    }
    void push_back(T data) {
        T *tempData = this->arr_data;
        this->_len ++;
        this->arr_data = new T[this->_len];
        for (int x = 0; x < (this->_len - 1); x++) {
            this->arr_data[x] = tempData[x];
        }
        delete tempData;
        this->arr_data[this->_len - 1] = data;
    }
    T pop_front() {
        T *tempData = this->arr_data;
        T data = this->arr_data[0];
        this->_len --;
        this->arr_data = new T[this->_len];
        for (int x = 0; x < this->_len; x++) {
            this->arr_data[x] = tempData[x + 1];
        }
        delete tempData;
        return data;
    }
    T pop() {
        T *tempData = this->arr_data;
        this->_len --;
        T data = this->arr_data[this->_len];

        this->arr_data = new T[this->_len];
        for (int x = 0; x < this->_len; x++) {
            this->arr_data[x] = tempData[x];
        }
        delete tempData;
        return data;
    }
    void forEach(std::function<void(int, T&)> function) {
        for (int index = 0; index < this->_len; index++) {
            function(index, this->arr_data[index]);
        }
    }
    T &operator[](int n) {
        if (this->_len < n || this->_len > 0) {
            return this->arr_data[n];
        } else {
            throw new Exceptions::IndexArrayException();
        }
    }
    template <typename Result>
    List<Result> map(std::function<Result(int, T&)> function) {
        List<Result> output = List<Result>();
        for(int index = 0; index < this->_len; index++) {
            Result data = function(index, this->arr_data[index]);
            output.push_back(data);
        }
        return output;
    };
};

#endif