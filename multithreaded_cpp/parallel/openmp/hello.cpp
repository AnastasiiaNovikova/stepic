#include <iostream>

int main() {
    #pragma omp parallel num_threads(8)
    {
        std::cout << "Hello, world!" << std::endl;
    }

    return 0;
}
