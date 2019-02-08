#ifndef NODE_H

namespace LJP{
    template <typename T>
    struct Node {
        T data;
        Node *next;
        Node()
        : data(T()), next(NULL) { }
        Node(T _data)
        : data(_data), next(NULL) { }
        ~Node() { }
    };
}

#endif