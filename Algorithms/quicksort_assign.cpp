#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>


template<class RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
    for(RandomIt current = std::next(first); current < last; ++current) {
        auto temp = *current;
        auto it = std::prev(current);
        for(; it >= first && temp < *it; --it)
            *(it+1) = *it;
        *(it+1) = temp;
    }
}


template< typename RandomIt, typename Comp >
void shell_sort(RandomIt first, RandomIt last, Comp comp) {
    static unsigned int gaps[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 };
    
    for( auto d : gaps ) {
        if ( d>= (last - first) )
            continue;
        for( RandomIt i = first + d; i != last; ++i)
            for( RandomIt j = i; j - first >=d && comp( *j, *(j-d)); j-=d )
                std::swap( *j, *(j-d) );
    }
}

template< typename RandomIt >
void shell_sort(RandomIt first, RandomIt last) {
    shell_sort(first, last, std::less<typename RandomIt::value_type>());
}

template<class RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
    if (last - first <= 1) {
        return first;
    }
    
    auto pivot = std::prev(last);
    auto mid = first + (last - first)/2;
    
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
void quick_sort_int(RandomIt first, RandomIt last) {
    if ((last - first) < 16) {
        insertion_sort(first, last);
        return;
    };
    
    while(first < last) {
        auto part = partition(first, last);
        
        if(part-first < last-part) {
            quick_sort_int(first, part);
            first = std::next(part);
        } else {
            quick_sort_int(part+1, last);
            last = part;
        }
    }
}

template<class RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
    quick_sort_int(first, last);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    std::vector<long> a;
    a.reserve(1*1000*1000);
    a.assign(std::istream_iterator<long>(std::cin), std::istream_iterator<long>());
        
    quick_sort(a.begin(), a.end());
    
    unsigned long count = 1;
    std::copy_if(a.begin(), a.end(), std::ostream_iterator<long>(std::cout, " "),
                    [&count](long) { return !(count++ % 10); } );
    
    return 0;
}