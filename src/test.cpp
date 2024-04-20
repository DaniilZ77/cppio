
#include "../include/bit_manip.h"
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream file("example.edb", std::ios::binary);

    char x[10] = "Hm";
    std::cout << sizeof(x) << std::endl;
    file >> read_c_str(x, 3);
    std::cout << x << std::endl;

    file.close();
}
