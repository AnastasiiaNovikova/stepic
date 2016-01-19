#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int N, K;
    vector<int> A;

    cin >> N;
	A.reserve(N);
    for(long i=0; i<N; ++i)
    {
        int x;
        cin >> x;
        A.push_back(x);
    }
	cin >> K;
    
    for(std::vector<int>::size_type i=0;i<A.size();i+=K)
		sort(A.begin()+i,A.begin()+min(i+K,A.size()));
		
	copy(A.begin(),A.end(),ostream_iterator<int>(cout, " "));
	cout << endl;
    
    return 0;
}