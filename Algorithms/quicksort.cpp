#include <iostream>
#include <iterator>
#include <algorithm>
#include <array>

template<class RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
	if (std::distance(first,last) <= 1) {
		return first;
	}
	
	auto pivot = *first;
	
	auto i=std::next(first), j = std::prev(last);
	while ( i <= j ) {
		while(i < last && *i <= pivot) ++i;
		while(*j > pivot) --j;
		if( i < j )
			std::swap( *(i++), *(j--) );
	}
	std::swap( *j, *first );
	return j;
}

template<class RandomIt>
void quickSort(RandomIt first, RandomIt last) {
	auto part = partition(first, last);
	if (part > first) quickSort(first, part);
	if (part != last) quickSort(std::next(part), last);
}

int main() {
	std::array<int, 7> a = {0, 3, -2, -5, 1, 10, 4};
	
	quickSort(a.begin(), a.end());
	
	std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
	
	return 0;
}