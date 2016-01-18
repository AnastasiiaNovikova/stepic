#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

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

int main()
{
    vector<int> A;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(A));

    insertion_sort(A.begin(), A.end());
    
    copy(A.begin(), A.end(), ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}
