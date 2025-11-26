#include "VectorC.h"
#include <iostream>

int main()
{
    VectorC<int> v;

    std::cout << sizeof(v) << std::endl;

    v.push_back(10);
    v.push_back(20);

    for(auto i = v.begin(); i != v.end();i++)
          std::cout << *i << " ";

    std::cout << "\n";
}
