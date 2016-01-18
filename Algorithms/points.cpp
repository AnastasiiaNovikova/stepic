#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x,y;

    Point(int x, int y): x(x), y(y) {}

    bool operator<(const Point& that) const {
        if(x == that.x)
            return y < that.y;
        return x < that.x;
    }
};

int main() {
    int N;
    vector<Point> points;

    cin >> N;
    for(int i=0; i<N; ++i)
    {
        int x,y;
        cin >> x >> y;
        points.emplace_back(x,y);
    }
    
    sort(points.begin(), points.end());
    
    for(auto point: points)
    {
        cout << point.x << " " << point.y << endl;
    }
    
    return 0;
}
