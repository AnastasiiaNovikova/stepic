#include <iostream>
#include <cmath>

double f(long x) {
    return std::sqrt(x);
}


int main()
{
    double sum = 0;
    long i=0;
    long N = 1e7;
    #pragma omp parallel for reduction(+:sum)
    for(i=0; i<N; ++i) {
        sum = sum + f(i);
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
