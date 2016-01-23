#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

template<class RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
    RandomIt current = first+1;
    while(current < last) {
        auto temp = *current;
        RandomIt it = current-1;
        for(; it >= first && temp < *it; --it)
            *(it+1) = *it;
        *(it+1) = temp;
        current++;
    }
}

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
void quick_sort_int(RandomIt first, RandomIt last) {
	if (std::distance(first,last) < 42) {
		return;
	} else {
		auto part = partition(first, last);
		if (part > first) quick_sort_int(first, part);
		if (part != last) quick_sort_int(std::next(part), last);
	}
}

template<class RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
	quick_sort_int(first, last);
	insertion_sort(first, last);
}

int main() {
	std::vector<long> a {std::istream_iterator<long>(std::cin), 
						std::istream_iterator<long>() };
						
	quick_sort(a.begin(), a.end());
	
	unsigned long count = 1;
	std::copy_if(a.begin(), a.end(), std::ostream_iterator<long>(std::cout, " "),
				 [&count](long) { return !(count++ % 10); } );
	
	return 0;
}