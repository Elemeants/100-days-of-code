// ---------------------------------------------------------------------------
// Dinamic array library - v1.0 - 31/01/2019
//
// AUTHOR:
// Created by Daniel Polanco - Jdanypa@gmail.com
//
// CONSTRUCTOR:
//    List<Type>(Size)
//        - Type: Define the kind of var of the List
//        - Size: Specifies the initial size of the list
//                if is empty the default size is 0
//                
// METHODS:
//    length() : Returns the length 
//    clear()  : Deletes all the values from the List
//    push(T)  : Adds a value to the front
//    push_back(T) : Adds a value to the back
//    pop()    : Deletes the last value
//    pop_front()  : Deletes the first value
//    forEach(std::function<void(int, T&)>) 
//             : Executes a function to every value
//    map(std::function<Result(T&)>)
//             : Maps the actual List into other List
//    filter(std::function<bool(T&)> function)
//            : Returns a list with the values filtered
//
// Examples:  
//    Create a new List of kind T:
//      [1]-. List<int> integerList = List<int>();
//      [2]-. List<int> integerList = List<int>(40);
//    
//    Push values into a List:
//      [1]-. integerList.push(20);
//       -> [ ] <- [1], [2], [3] 
//           0      1    2    3
//         Is inserted in the start of the list
//      [2]-. integerList.push_back(20);
//          [1], [2], [3] -> [ ] <-
//           0    1    2      3
//         Is inserted in the end of the list
//
//    Pop values from List:
//      [1]-. integerList.push_back(20) -> T;
//          [1], [2], [3] -> [ ] <-
//           0    1    2      3
//         The last value is deleted and is returned
//      [2]-. integerList.pop_front() -> T;
//       -> [ ] <- [1], [2], [3] 
//           0      1    2    3
//         The first value is deleted and is returned
//
//     Get/Set a value from the List:
//       [GET]-. int value = integerList[3];
//          [1], [2], [3] -> [4] <-
//           0    1    2      3
//          So 'value' is going to be '4'
//       [SET]-. integerList[3] = 3;
//          [1], [2], [3] -> [4 -> 3] <-
//           0    1    2        3
//          The value of the index 3 is changed to 3
//
//      Clean the List:
//        [1] integerList.clean();
//          [1], [2], [3], [4]  -> [0]
//           0    1    2    3   ->  0
//          Deletes all the values and returns a empty List
//
//      
//
// HISTORY:
// 31/01/2019 v1.0 - First version
// ---------------------------------------------------------------------------

#ifndef LIST_H

#include <functional>
#include <exception>
namespace Exceptions {
  struct IndexArrayException : public std::exception
  {
  private:
    const char* error_log;
  public:
    IndexArrayException(const char* error_log): error_log((char*)error_log) { }
    IndexArrayException(): error_log("IndexArrayException") { }
    char const* what() const throw()
    {
      return error_log;
    }
  };
  struct NotImplementedException : public std::exception
  {
  private:
    const char* error_log;
  public:
    NotImplementedException(const char* error_log): error_log((char*)error_log) { }
    NotImplementedException(): error_log("NotImplementedException") { }
    char const* what() const throw()
    {
      return error_log;
    }
  };
}

template <typename T>
struct List {
private:
  size_t _len;
  T *arr_data;
public:
  // Constructor with specifict list size
  List(size_t _Size) {
    this->_len = _Size;
    this->arr_data = new T[this->_len];
    for (int i = 0; i < _Size; i++) {
        this->arr_data[i] = T();
    }
  }
  // Constructor with zero values
  List() {
    this->_len = 0;
    this->arr_data = new T[this->_len];
    this->arr_data[0] = T();
  }
  // Destructor of the structure
  ~List() {
    this->_len = 0;
    delete this->arr_data;
  }
  
  // Operator overloading to get/set values of the list
  T &operator[](int index) {
    if (this->_len < index || this->_len > 0) {
      return this->arr_data[index];
    } else {
      throw new Exceptions::IndexArrayException();
    }
  }

  // Get the length of the list
  int length() const { 
    return this->_len;
  }

  // Deletes all the values
  void clear() {
    delete this->arr_data;
    this->arr_data = new T[0];
    this->_len = 0;
    this->arr_data[0] = T();
  }

  // Adds a value into the front of the list
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

  // Adds a value into the last of the list
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

  // Deletes the last value
  T pop() {
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

  // Deletes the firsh value
  T pop_front() {
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

  // Executes a function to every value
  void forEach(std::function<void(int, T&)> function) {
    for (int index = 0; index < this->_len; index++) {
      function(index, this->arr_data[index]);
    }
  }

  template <typename Result>
  // Maps the actual List into other List
  List<Result> map(std::function<Result(T&)> function) {
    List<Result> output = List<Result>();
    for(int index = 0; index < this->_len; index++) {
      Result data = function(index, this->arr_data[index]);
      output.push_back(data);
    }
    return output;
  }

  // Returns a list with the values filtered
  List<T> filter(std::function<bool(T&)> function) {
    List<T> output = List<T>(this->_len);
    for(int index = 0; index < this->_len; index++) {
      if(function(this[index])) {
        output.push_back(this[index]);
      }
    }
    return output;
  }
};

#endif
