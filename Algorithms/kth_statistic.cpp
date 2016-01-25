#include <iostream>
#include <iterator>
#include <algorithm>
#include <array>

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
    std::swap(*(last-1), *pivot);
    
    RandomIt i = first;
    RandomIt j = i;
    while ( j < last-1 ) {
        while ( *j > *pivot ) ++j;
        if (j != (last-1))
            std::swap( *(i++), *(j++) );
    }
    while ( i < (last-2) && *i <= *pivot ) ++i;
    std::swap( *i, *(last-1) );
    return i;
}

template<class RandomIt>
typename RandomIt::value_type kth_statistic(RandomIt first, RandomIt last, long k) {
    auto part = partition(first, last);
    
    debug(first, last);
    std::cout << "part = " << (part - first) << ", k = " << k << std::endl;
    
    if (part - first == k) return *part;
    if (k < (part - first)) return kth_statistic(first, part, k);
    else return kth_statistic(part+1, last, k - (part-first));
}

template<class RandomIt>
void quickSort(RandomIt first, RandomIt last) {
	auto part = partition(first, last);
    /*
	if (part > first) quickSort(first, part);
	if (part != last) quickSort(std::next(part), last);
	*/
    if (part > first) quickSort(first, part);
	if (part != last) quickSort(std::next(part), last);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    long n, k;
    std::cin >> n >> k;    
    std::vector<long> a(std::istream_iterator<long>(std::cin), std::istream_iterator<long>());
    
    //std::cout << kth_statistic(a.begin(), a.end(), k ) << std::endl;
    quickSort(a.begin(), a.end());
	
	std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    return 0;
}