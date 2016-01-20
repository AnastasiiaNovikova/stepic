#include <iostream>

template <class Type>
class SmartPointer {
private:
    Type* pointer = nullptr;
public:
    SmartPointer(Type* p): pointer(p) {};
    
    ~SmartPointer() {
        delete pointer;
    }
    
    operator Type*() {
        if(!pointer)
            pointer = new Type();
        return pointer;        
    };
    
    Type* operator->() {
        if(!pointer)
            pointer = new Type();
        return pointer;
    }
    
    std::ptrdiff_t operator-(SmartPointer<Type> p) {
        return pointer - p;
    }
    
    std::ptrdiff_t operator-(void *p) {
        return pointer - p;
    }
};

class Foo {
private:
    int a,b;
public:
    Foo(): a(0), b(0) {};
    Foo(int a,int b): a(a), b(b) {};
    int Sum() { return a+b; }
};

int main(int argc, char **argv) {
    SmartPointer<Foo> sp(nullptr);
    std::cout << sp->Sum() << std::endl;
    return 0;
}