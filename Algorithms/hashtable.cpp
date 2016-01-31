#include <iostream>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

template< typename T >
struct hashf;

template<>
struct hashf<string>
{
    unsigned int operator()(const string& str ) const {
        unsigned int hash = 0;
        for (auto it = str.begin(); it != str.end(); ++it) {
            hash = (hash * 33 + *it) % std::numeric_limits<unsigned int>::max();
        }
        return hash;
    }
};

template<>
struct hashf<char*>
{
    unsigned int operator()(const char* str) const {
        unsigned int hash = 0;
        for (; str != 0; ++str) {
            hash = (hash * 33 + *str) % std::numeric_limits<unsigned int>::max();
        }
        return hash;
    }
};

template<typename T, typename Hash = hashf<T>>
class hash_set {
public:
    using iterator = T*;
    
    hash_set() {
        reset(capacity_);
    }
    
    iterator find(const T& key) {
        unsigned int h = hashf_(key) % capacity_;
        for(int i=0;i<capacity_;++i) {
            h = (h + i*11) % capacity_;
            if(storage_[h] == nullptr && !deleted_[h])
                return end();
            if(storage_[h] != nullptr && *storage_[h] == key)
                return (iterator)(storage_ + h);
        }
        return end();
    }
    
    size_t erase(const T& key) {
        unsigned int h = hashf_(key) % capacity_;
        for(int i=0;i<capacity_;++i) {
            h = (h + i*11) % capacity_;
            if(storage_[h] == nullptr && !deleted_[h])
                return 0;
            if(storage_[h] != nullptr && *storage_[h] == key) {
                delete storage_[h];
                storage_[h] = nullptr;
                deleted_[h] = true;
                --size_;
                return 1;
            }
        }
        return 0;
    }
    
    std::pair<iterator, bool> insert(const T& key) {
        if( float(size_) / capacity_ >= max_load_factor_ )
            rehash(capacity_*2);
        
        unsigned int h = hashf_(key) % capacity_;
        for(int i=0;i<capacity_;++i) {
            h = (h + i*11) % capacity_;
            if(storage_[h] == nullptr) {
                storage_[h] = new T(key);
                deleted_[h] = false;
                ++size_;
                return std::make_pair((iterator)(storage_ + h), true);
            }
            if(storage_[h] != nullptr && *storage_[h] == key) {
                return std::make_pair((iterator)(storage_ + h), false);
            }
        }
        return std::make_pair(end(), false);;
    }
    
    bool rehash(unsigned int new_capacity) {
        if (new_capacity < size_)
            return false;
        
        unsigned int old_capacity = capacity_;
        T** old_storage = storage_;
        delete deleted_;
        
        reset(new_capacity, false);
        
        for(size_t i = 0; i< old_capacity; ++i) {
            if(old_storage[i]) {
                insert(*old_storage[i]);
                delete old_storage[i];
            }
        }
        
        delete old_storage;
    }
    
    iterator begin() {
        return storage_;
    }
    
    iterator end() {
        return (iterator)(storage_ + capacity_);
    }
    
private:
    void reset(unsigned int capacity, bool clear = false) {
        if (clear) {
            delete deleted_;
            delete storage_;
        }
        capacity_ = capacity;
        deleted_ = new bool[capacity_];
        storage_ = new T*[capacity_];
        std::memset((void*)deleted_,0,capacity_*sizeof(bool));
        std::memset((void*)storage_,0,capacity_*sizeof(T*));
    }
    
    unsigned int capacity_ = 16;
    unsigned int size_ = 0;
    float max_load_factor_ = 0.75;
    
    bool* deleted_ = nullptr;
    T** storage_ = nullptr;
    
    Hash hashf_;
};

int main() {
    hash_set<string> hash_map;
    char c;
    string s;
    while (cin >> c) {
        cin >> s;
        switch( c ) {
            case '+':
                if (hash_map.find(s) != hash_map.end()) {
                    cout << "FAIL\n";
                    continue;
                }
                hash_map.insert(s);
                break;
            case '-':
                if (hash_map.find(s) == hash_map.end()) {
                    cout << "FAIL\n";
                    continue;
                }
                hash_map.erase(s);
                break;
            case '?':
                if (hash_map.find(s) == hash_map.end()) {
                    cout << "FAIL\n";
                    continue;
                }
                break;
        }
        cout << "OK\n";
    }
    return 0;
}