#include<iostream>
#include<vector>

int mian()
{
    std::vector<int> v1={1,2,3,4,5};
    //int* p=v1.end();
    if (!v1.empty())
        std::cout << *(v1.end() - 1) << "\n";

    //std::cout<<"p="<<p<<std::endl;
    //std::cout<<"*P="<<*p<<std::endl;

    return 0;
}
