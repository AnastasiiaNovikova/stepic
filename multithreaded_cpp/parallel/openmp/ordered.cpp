#include <iostream>
#include <cmath>


int main()
{
    long i=0;
    long N = 1e7;
    #pragma omp parallel for ordered
    for(i=0; i<N; ++i) {
        if((i % 1000000) == 0) {
            #pragma omp ordered
            {
                std::cout << i << std::endl;
            }
        }
    }


    return 0;
}
