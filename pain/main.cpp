#include <iostream>

int main() {
    int* p = new int[3];
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    std::cout << *(&p[0]) << *(&p[1]) << *(&p[2]) << std::endl;
    return 0;
}