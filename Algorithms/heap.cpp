#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Heap {
public:
	Heap()	{ }
	
	void add(int elem) { 
		a.push_back(elem);
		siftUp(a.size() - 1);
	}
	
	int get_max() {
		assert(!a.empty());
		
		int result = a[0];
		
		a[0] = a.back();
		a.pop_back();
		
		if(!a.empty())
			siftDown(0);
		
		return result;
	}
	
	int max() {
		assert(!a.empty());	
		return a[0];
	}
	
	int size() {
		return a.size();
	}
private:
	void siftDown(int i) {
		int left = 2*i +1;
		int right = 2*i +2;
		//look for a bigger child
		int largest = i;
		if (left < a.size() && a[left]>a[largest] )
			largest = left;
		if (right < a.size() && a[right]>a[largest] )
			largest = right;
		//if found bigger son, shift elem down
		if (largest != i) {
			std::swap( a[i], a[largest] );
			siftDown( largest );
		}
	}
	
	void siftUp(int i) {
		while( i > 0 ) {
			int parent = ( i - 1 ) / 2;
			if( a[i] <= a[parent] )
				return;
			std::swap( a[i], a[parent] );
			i = parent;
		}
	}
	
	void makeHeap(int i) {
		for(int i = a.size() / 2 - 1; i>=0; --i) {
			siftDown(i);
		}
	}
	
	vector<int> a;
};

int main() {
	Heap h;
	
	int n, k, x;
	cin >> n;
	for(int i=0; i< n; ++i) {
		cin >> x;
		h.add(x);
	}
	cin >> k;
	
	int result = 0;
	
	while(h.size() > 0)
	{
		int sum = 0;
		vector<int> elements;
		while(sum<=k) {
			if(h.size() == 0)
				break;
			if (sum + h.max() <= k) {
				elements.push_back(h.get_max());
				sum += elements.back();
			}
			else
				break;
		}
		
		for(int i=0;i<elements.size(); ++i) {
			if(elements[i] != 1)
				h.add(elements[i]/2);
		}
		
		++result;
	}
	
	std::cout << result << std::endl;
	return 0;
}