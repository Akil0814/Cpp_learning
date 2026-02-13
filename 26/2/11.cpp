#include<vector>
#include<iostream>
int main()
{
    std::vector<int> v;
    v.reserve(10);
    v.insert(v.end(),8);
    v.insert(v.end(),2);
    auto p=v.end();
    auto q=p;
    q--;
    v.insert(q,3);
    *q=6;
    v.insert(p,7);
    v.erase(q);


    for(auto &iter:v)
    {
        std::cout<<iter<<" ";
    }

    return 0;
}
