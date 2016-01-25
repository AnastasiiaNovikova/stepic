#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

template<class RandomIt>
RandomIt debug(RandomIt first, RandomIt last) {
    std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template<class RandomIt>
RandomIt median_pivot(RandomIt first, RandomIt last) {
    RandomIt pivot = std::prev(last);
    RandomIt mid = first + (last-first)/2;
    
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
    
    return pivot;
}


template<class RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
    if ((last - first) <= 1) {
        return first;
    }
    
    RandomIt pivot = median_pivot(first, last);
    
    std::iter_swap(first, pivot);
    
    RandomIt i = first + 1;
    for(RandomIt j = first + 1; j != last; ++j) {
        if( *j < *first )
            std::iter_swap(i++,j);
    }
    std::iter_swap( --i, first );

    return i;
}

template<class RandomIt>
typename RandomIt::value_type kth_statistic(RandomIt first, RandomIt last, long k) {
    auto part = partition(first, last);
    
    if (part - first == k) return *part;
    if (k < (part - first)) return kth_statistic(first, part, k);
    else return kth_statistic(part+1, last, k - (part-first) - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    long n, k;
    std::cin >> n >> k;
    std::vector<long> a(n);
    a.assign(std::istream_iterator<long>(std::cin), std::istream_iterator<long>());
    
    std::cout << kth_statistic(a.begin(), a.end(), k ) << std::endl;
    
    return 0;
}