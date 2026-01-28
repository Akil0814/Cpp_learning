#include<iostream>
#include<vector>
#include<stack>

#include <type_traits>
#include <utility>

//IMplment  a Qveue with a deque ! Adapter//

template<typename T>
void print_container(const T& container)
{
    for(auto &iter:container)
        std::cout<<iter<<" "<<std::endl;
    std::cout<<std::endl;
}

int main()
{
    std::stack<double> stack_1;
    for (double x : {222.22, 44.44, 789.6, 123.45, 88.64, 123.123})
        stack_1.push(x);

    std::vector<double> _1={222.22, 44.44, 789.6, 123.45, 88.64, 123.123};
    print_container(_1);
        std::cout << __cplusplus << "\n";


    return 0;
}
