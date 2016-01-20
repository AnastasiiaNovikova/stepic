#include <iostream>
#include <cstring>
#include <list>

class SmallAllocator {
private:
        char Memory[1048576];
        // Free list <offset,size>
        std::list<std::pair<unsigned long,unsigned long>> freeList;    
public:
        SmallAllocator() {
            freeList.push_back(std::make_pair(0,sizeof(Memory)));
        };
        
        void *Alloc(unsigned int Size)
        {
            for(auto it = freeList.begin();
                it != freeList.end();
                ++it)
            {
                if(it->second > Size+2) {
                    unsigned long start = it->first;
                    it->first += Size+2;
                    it->second -= Size+2;
                    *((int*)(Memory + start)) = Size;
                    return (void *)(Memory+start+2);
                }
            }
            std::cerr << "Error allocating!" << std::endl;
            return NULL;
        };
        
        void *ReAlloc(void *Pointer, unsigned int Size) {
            unsigned long start = (char*)Pointer-Memory-2;
            unsigned int oldsize = *(int*)(Memory + start);
            
            if (oldsize == Size) {
                return Pointer;
            }
            else if (oldsize > Size) {
                unsigned long offset = start + Size + 2;
                *((int*)(Memory + start)) = Size + 2;
                
                free_internal(offset, oldsize - Size);
                return Pointer;
            }
            else {
                void *newPointer = Alloc(Size);
                std::memcpy(newPointer,Pointer,oldsize);
                
                free_internal(start, oldsize);
                return newPointer;
            }
        };
        
        void Free(void *Pointer)
        {
            unsigned long start = (char*)Pointer-Memory-2;
            unsigned int size = *(int*)(Memory + start);
            
            free_internal(start,size);
        };
private:
    void free_internal(unsigned long start, unsigned long size) {
        auto lower = std::lower_bound(freeList.begin(),
                                        freeList.end(),
                                        std::make_pair(start,size));
        auto current = freeList.insert(lower,std::make_pair(start, size));
        if(current != freeList.begin()) {
            auto prev = std::prev(current);
            if(prev->first + prev->second == start) {
                freeList.erase(current);
                prev->second += size;
                current = prev;
            }
        }
        auto next = std::next(current);
        if(next != freeList.end()) {            
            if(start + size == next->first) {
                freeList.erase(current);
                next->first -= size;
                current = next;
            }
        }
    }
};