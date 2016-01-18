#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int x1,x2;

    Segment(int x1, int x2): x1(x1), x2(x2) {}

    bool operator<(const Segment& that) const {
        if(x1 == that.x1)
            return x2 < that.x2;
        return x1 < that.x1;
    }
};

int main() {
    int N;
    vector<Segment> segments;

    cin >> N;
    for(int i=0; i<N; ++i)
    {
        int x1,x2;
        cin >> x1 >> x2;
        segments.emplace_back(x1,x2);
    }
    
    sort(segments.begin(), segments.end());
    
    int sum = 0;
    for(int i=0; i<segments.size()-1; ++i)
    {
        if(segments[i].x1 < segments[i+1].x1) {
            sum += min(segments[i].x2, segments[i+1].x1) - segments[i].x1;
        }
        segments[i+1].x1 = max(segments[i].x2, segments[i+1].x1);
    }
    sum += (segments[segments.size()-1].x2 - segments[segments.size()-1].x1 );
    cout << sum << endl;
    
    return 0;
}
