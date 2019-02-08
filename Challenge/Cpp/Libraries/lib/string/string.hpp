#ifndef STRING_H

namespace LJP {
    class String {
    public:
        String() { }
        String(const char*) { }
        String(char*) { }
        char &operator [](int index);
        String &operator =(const char*);
        String &operator =(char*);
        String &operator +(const char*);
        String &operator +(char*);
    private:
        
    };
}

#endif