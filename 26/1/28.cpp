#include<iostream>
#include<vector>
#include<stack>

#include <type_traits>
#include <utility>

#include "_print_container.h"

//IMplment  a Qveue with a deque ! Adapter//

int main()
{
    std::cout<<"Current C++ ver:"<<__cplusplus<<std::endl;
    std::stack<double> stack_1;
    for (double x : {222.22, 44.44, 789.6, 123.45, 88.64, 123.123})
        stack_1.push(x);
    std::stack<std::string> stack_2;
    for (std::string x : {"Mickey", "Minnie", "Donald", "Daisy", "Pluto", "Goofy"})
        stack_2.push(x);

    print_container(stack_2);
    print_container(stack_1);

    return 0;
}
