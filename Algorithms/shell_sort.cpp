#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

template< typename RandomIt, typename Comp >
void shell_sort(RandomIt first, RandomIt last, Comp comp) {
    static unsigned int gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
    
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


int main() {
    std::vector<long> a {std::istream_iterator<long>(std::cin), 
                         std::istream_iterator<long>() };

    shell_sort(a.begin(), a.end());

    std::copy(a.begin(), a.end(), std::ostream_iterator<long>(std::cout, " "));
    
    return 0;
}