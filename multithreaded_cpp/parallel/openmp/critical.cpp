#include <iostream>
#include <cmath>


int main()
{
    long i=0;
    long j=0;
    long N = 1e7;
    #pragma omp parallel for 
    for(i=0; i<N; ++i) {
        if((i % 1000000) == 0) {
            #pragma omp critical 
            {
                std::cout << i << std::endl;
            }
            #pragma omp atomic
            j++;
        }
    }
    #pragma omp sections
    {
        #pragma omp section
        {
            std::cout << "733" << std::endl;
        }
        #pragma omp section
        {
            std::cout << "1024" << std::endl;
        }
    }


    return 0;
}
