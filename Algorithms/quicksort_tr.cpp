#include <iostream>
#include <iterator>
#include <algorithm>
#include <array>

template<class RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
    if (std::distance(first,last) <= 1) {
        return first;
    }
    
    auto pivot = std::prev(last);
    auto mid = first;
    std::advance(mid, std::distance(first,last)/2);
    
    if (*pivot > *first && *pivot > *mid) {
        if (*first > *mid)
            pivot = first;
        else
            pivot = mid;
    }
    else if (*pivot < *first && *pivot < *mid) {
        if (*first < *mid)
            pivot = first;
        else
            pivot = mid;
    }
    
    std::swap(*first, *pivot);
    
    auto i=std::next(first), j = std::prev(last);
    while ( i <= j ) {
        while(i < last && *i <= *first) ++i;
        while(*j > *first) --j;
        if( i < j )
            std::swap( *(i++), *(j--) );
    }
    std::swap( *j, *first );
    return j;
}

template<class RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
    while(first < last) {
        auto part = partition(first, last);
        
        if(part-first < last-part) {
            quick_sort(first, part);
            first = std::next(part);
        } else {
            quick_sort(part+1, last);
            last = part;
        }
    }
}

int main() {
    std::vector<long> a {std::istream_iterator<long>(std::cin), 
                        std::istream_iterator<long>() };

    quick_sort(a.begin(), a.end());

    std::copy(a.begin(), a.end(), std::ostream_iterator<long>(std::cout, " "));
    
    return 0;
}