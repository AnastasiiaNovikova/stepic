#include <iostream>
#include <vector>
#include <iterator>
#include <cstring>

unsigned char get_byte(unsigned long long x, int n) {
    return (x >> (8*n)) & 0xff;
}

void counting_sort1(int* a, int n, int k) {
    int * c = new int[k];
    for( int i = 0; i < k; ++i)
        c[i] = 0;
    for( int i = 0; i < n; ++i)
        ++c[a[i]];
    int pos = 0;
    for( int i = 0; i<k; ++i )
        for( int j = 0; j < c[i]; ++j )
            a[pos++] = i;
    delete[] c;
}

void counting_sort2(unsigned long long* a, unsigned long n, int k, int byte) {
    long * c = new long[k];
    for( int i = 0; i < k; ++i)
        c[i] = 0;
    for( int i = 0; i < n; ++i)
        ++c[get_byte(a[i], byte)];
    int sum = 0;
    for( int i = 0; i < k; ++i) {
        int tmp = c[i];
        c[i] = sum;
        sum += tmp;
    }
    unsigned long long *b = new unsigned long long[n];
    for( int i = 0; i < n; ++i)
        b[c[get_byte(a[i], byte)]++] = a[i];
    memcpy( a, b, n * sizeof( unsigned long long ) );
    delete[] c;
    delete[] b;
}

void lsd_sort(unsigned long long *a, unsigned long n) {
    for (int r = 0; r < sizeof( long long ); ++r)
        counting_sort2( a, n, 256, r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    long n;
    std::cin >> n;
    
    std::vector<unsigned long long> a {std::istream_iterator<long>(std::cin), 
                                       std::istream_iterator<long>() };

    lsd_sort(a.data(), a.size());

    std::copy(a.begin(), a.end(), std::ostream_iterator<long>(std::cout, " "));
}