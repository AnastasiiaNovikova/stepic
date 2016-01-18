#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template<class RandomIt>
void selection_sort(RandomIt first, RandomIt last) {
    RandomIt current = first;
    while(current != last) {
        RandomIt minIt = current;
        for(RandomIt it = current+1; it != last; ++it)
            if(*minIt > *it) minIt = it;
        swap(*current, *minIt);
        current++;
    }
}

int main()
{
    vector<int> A {4, 2, 1, 3, 5};
    selection_sort(A.begin(), A.end());
    
    copy(A.begin(), A.end(), ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}
