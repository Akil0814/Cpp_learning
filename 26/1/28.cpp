#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<deque>

#include "_print_container.h"
#include "_my_stack.h"
#include "_container_modify.h"

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

    std::queue<double> queue_1;
    for (double x : {222.22, 44.44, 789.6, 123.45, 88.64, 123.123})
        queue_1.push(x);
    std::queue<std::string> queue_2;
    for (std::string x : {"Mickey", "Minnie", "Donald", "Daisy", "Pluto", "Goofy"})
        queue_2.push(x);

    std::deque<double> deque_1 = {222.22, 44.44, 789.6, 123.45, 88.64, 123.123};
    std::deque<std::string> deque_2 = {"Mickey", "Minnie", "Donald", "Daisy", "Pluto", "Goofy"};

    std::cout<<"--------------PART A-----------------"<<std::endl;
    ct::print_container(stack_1);
    ct::print_container(stack_2);

    std::cout<<"--------------PART B-----------------"<<std::endl;
    ct::pop_until_removed(stack_1,789.6);
    ct::pop_until_removed(stack_2,"Donald");
    ct::print_container(stack_1);
    ct::print_container(stack_2);

    std::cout<<"--------------PART C-----------------"<<std::endl;
    MTL_A::Stack<double> my_stack_1;
    for (double x : {222.22, 44.44, 789.6, 123.45, 88.64, 123.123})
        my_stack_1.push(x);
    MTL_A::Stack<std::string> my_stack_2;
    for (std::string x : {"Mickey", "Minnie", "Donald", "Daisy", "Pluto", "Goofy"})
        my_stack_2.push(x);

    ct::print_container(my_stack_1);
    ct::print_container(my_stack_2);

    std::cout<<"--------------PART D-----------------"<<std::endl;
    ct::pop_until_removed(my_stack_1,789.6);
    ct::pop_until_removed(my_stack_2,"Donald");
    ct::print_container(my_stack_1);
    ct::print_container(my_stack_2);

    std::cout<<"--------------PART E-----------------"<<std::endl;




    return 0;
}
