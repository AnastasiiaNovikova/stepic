class StringPointer {
public:
    std::string *operator->() {
        if(!pointer) {
            pointer = new std::string();
            constr = true;
        }
        return pointer;      
    }
    operator std::string*() {
        if(!pointer) {
            pointer = new std::string();
            constr = true;
        }
        return pointer;      
    }
    StringPointer(std::string *Pointer): pointer(Pointer) {}
    ~StringPointer() { 
        if (constr)
            delete pointer;
    }
private:
    std::string *pointer = nullptr;
    bool constr = false;
};

int main() {
    std::string s1 = "Hello, world!";

    StringPointer sp1(&s1);
    StringPointer sp2(NULL);

    std::cout << sp1->length() << std::endl;
    std::cout << *sp1 << std::endl;
    std::cout << sp2->length() << std::endl;
    std::cout << *sp2 << std::endl;
}