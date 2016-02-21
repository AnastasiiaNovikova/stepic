#include <iostream>

int main() {
    #pragma omp parallel
    {
        std::cout << 1 << std::endl;
        #pragma omp single nowait
        {
            std::cout << 2 << std::endl;
        }
        std::cout << 3 << std::endl;
    }
}
