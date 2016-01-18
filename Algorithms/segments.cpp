#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long N;
    vector<pair<int,bool>> segments;

    cin >> N;
    for(long i=0; i<N; ++i)
    {
        long x1,x2;
        cin >> x1 >> x2;
        segments.emplace_back(x1,false);
		segments.emplace_back(x2,true);
    }
    
    sort(segments.begin(), segments.end());
    
    long count = 1;
	long long sum = 0;
    for(long i=1; i<segments.size(); ++i)
    {
		if( count == 1) sum+= (segments[i].first - segments[i-1].first);
		segments[i].second ? count-- : count++;
	}
    cout << sum << endl;
    
    return 0;
}
