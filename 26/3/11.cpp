//import std
#include <iostream>
#include <vector>

int main()
{
    //std::println("hellow C++23");
    std::vector<int> tmp(5,4);


    tmp.insert(tmp.begin()+3,6);
    for(auto &iter: tmp)
    {
        std::cout<<iter<<std::endl;
    }

    return 0;
}
