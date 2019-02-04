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
  template <typename N>
  struct Node {
    N data;
    Node *next;
    Node()
    : data(N()), next(NULL) { }
    Node(N _data)
    : data(_data), next(NULL) { }
    ~Node() { }
  };
  size_t _len;
  struct Node<T> *arr_data;
  struct Node<T> *GetIter() { return this->arr_data; }
public:
  // Constructor with specifict list size
  List(size_t _Size) {
    this->_len = 0;
    this->arr_data = new Node<T>[_Size];
    for (int i = 0; i < _Size; i++) {
      this[i] = 0;
    }
  }

  // Constructor with zero values
  List() {
    this->_len = 0;
    this->arr_data = NULL;
  }

  // Destructor of the structure
  ~List() {
    this->_len = 0;
    delete this->arr_data;
  }
  
  // Operator overloading to get/set values of the list
  T &operator[](int index) {
    if (this->_len < index || this->_len > 0) {
      Node<T> *iter = this->GetIter();
      for (int i = 0; iter->next != NULL && i < index; i++) {
        iter = iter->next;
      }
      return iter->data;
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
    while(this->arr_data != NULL) {
      Node<T> *iter = this->GetIter();
      this->arr_data = iter->next;
      delete iter;
    }
    this->_len = 0;
    this->arr_data = NULL;
  }

  // Adds a value into the front of the list
  void push(T data) {
    Node<T> *new_node = new Node<T>(data);
    if (this->arr_data == NULL) {
      this->arr_data = new_node;
    } else {
      new_node->next = this->arr_data;
      this->arr_data = new_node;
    }
    this->_len ++;
  }

  // Adds a value into the last of the list
  void push_back(T data) {
    Node<T> *new_node = new Node<T>(data);
    Node<T> *iter = this->GetIter();
    if (this->arr_data == NULL) {
      this->arr_data = new_node;
    } else {
      while (iter->next != NULL) {
        iter = iter->next;
      }
      iter->next = new_node;
    }
    this->_len ++;
  }

  // Deletes the last value
  T pop() {
    Node<T> *iter = this->GetIter();
    Node<T> *aux_node = this->arr_data;
    while(iter->next != NULL) {
      aux_node = iter;
      iter = iter->next;
    }
    aux_node->next = NULL;
    T data = iter->data;
    this->_len --;
    delete iter;
    return data;
  }

  // Deletes the firsh value
  T pop_front() {
    Node<T> *iter = this->GetIter();
    this->arr_data = iter->next;
    T data = iter->data;
    delete iter;
    this->_len --;
    return data;
  }

  // Executes a function to every value
  void forEach(std::function<void(int, T&)> function) {
    Node<T> *iter = this->GetIter();
    for (int index = 0; iter != NULL && index < this->_len; index++) {
      function(index, iter->data);
      iter = iter->next;
    }
  }

  template <typename Result>
  // Maps the actual List into other List
  List<Result> map(std::function<Result(T&)> function) {
    List<Result> output = List<Result>();
    Node<T> *iter = this->GetIter();
    for(int index = 0; iter != NULL && index < this->_len; index++) {
      Result data = function(iter->data);
      output.push_back(data);
      iter = iter->next;
    }
    return output;
  }

  // Returns a list with the values filtered
  List<T> filter(std::function<bool(T&)> function) {
    List<T> output = List<T>();
    Node<T> *iter = this->GetIter();
    for(int index = 0; iter != NULL && index < this->_len; index++) {
      if(function(this[index])) {
        output.push_back(this[index]);
      }
      iter = iter->next;
    }
    return output;
  }
};

#endif
