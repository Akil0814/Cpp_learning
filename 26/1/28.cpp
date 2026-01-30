#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<deque>

#include "_print_container.h"
#include "_container_modify.h"

#include "_my_stack.h"
#include "_my_queue.h"
#include "_my_deque.h"
#include "_my_queue_with_deque.h"


// !-----------------------IMPROTANT-----------------------!
// this program only work for C++20 or higher version
// !-----------------------IMPROTANT-----------------------!

bool is_pair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool is_parentheses(char c)
{
    return c == '(' || c == ')' ||
           c == '[' || c == ']' ||
           c == '{' || c == '}';
}

bool valid_parentheses(std::string s)
{
    MTL_A::Deque<char> d;

    for(auto c: s)
    {
        if(is_parentheses(c))
        {
            switch (c)
            {
            case '(':
            case '[':
            case '{':
                d.push_back(c);
                break;
            case ')':
            case ']':
            case '}':
                if(d.empty()||!is_pair(d.back(),c))
                    return false;
                d.pop_back();
                break;
            default:
                break;
            }
        }
    }

    return true;
}

double evaluate(std::string s, char ver, double val)
{
    double r=0;

    for(auto &c: s)
    {
        if (c=='('||c=='['||c=='{')c = '(';
        if (c==')'||c==']'||c=='}') c = ')';
    }


    int time=0;
    int max_time=0;
    char* priority=nullptr;
    int num_of_c=0;
    for(auto &c: s)
    {
        if(c=='(')
        {
            time++;
            if(time>max_time)
            {
                max_time=time;
                priority=&c;
            }
        }
        else if(c==')')
            time=0;
    }
    for()


    std::cout<<s<<" ,"<<std::endl;
    std::cout<<"first num need to op:"<<*(priority+1)<<std::endl;
    std::cout<<"max time (:"<<max_time<<std::endl;


    return r;
}


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

    MTL_A::Queue<double> my_queue_1;
    for (double x : {222.22, 44.44, 789.6, 123.45, 88.64, 123.123})
        my_queue_1.push(x);
    MTL_A::Queue<std::string> my_queue_2;
    for (std::string x : {"Mickey", "Minnie", "Donald", "Daisy", "Pluto", "Goofy"})
        my_queue_2.push(x);

    ct::print_container(my_queue_1);
    ct::print_container(my_queue_2);

    std::cout<<"--------------PART F-----------------"<<std::endl;

    ct::pop_until_removed(my_queue_1,789.6);
    ct::pop_until_removed(my_queue_2,"Daisy");
    ct::print_container(my_queue_1);
    ct::print_container(my_queue_2);

    std::cout<<"--------------PART G-----------------"<<std::endl;

    MTL_A::Deque<double> my_deque_1;
    for (double x : {222.22, 44.44, 789.6, 123.45, 88.64, 123.123})
        my_deque_1.push_front(x);
    MTL_A::Deque<std::string> my_deque_2;
    for (std::string x : {"Mickey", "Minnie", "Donald", "Daisy", "Pluto", "Goofy"})
        my_deque_2.push_front(x);

    ct::print_container(my_deque_1);
    ct::print_container(my_deque_2);

    std::cout<<"--------------PART H-----------------"<<std::endl;

    ct::pop_until_removed(my_deque_2,"Daisy");
    while(!my_deque_1.empty())
    {
        if(my_deque_1.back()==44.44)
        {
            my_deque_1.pop_back();
            break;
        }
        my_deque_1.pop_back();
    }

    ct::print_container(my_deque_2);
    ct::print_container(my_deque_1);

    std::cout<<"-----------PART I AND J--------------"<<std::endl;

    char No='a';
    for(std::string test : {"((12x+3){2x-7})", "{{8x+5)-5x[9x+3]})", "(((4x+8)-x[4x+3])))", "{2x+5}(9x+4)", "[(5x-5)-4x[6x+2]]", "(2x+7}(12x+6)"})
    {
        std::cout<<No++<<":";
        if(valid_parentheses(test))
        {
            std::cout<<"is valid, the answer will be:";
            std::cout<<evaluate(test,'x',-3);
        }
        else
            std::cout<<"is not valid";

        std::cout<<"\n";
    }

    std::cout<<"----------------EX-------------------"<<std::endl;

    std::cout<<"testing my qveue with deque:"<<std::endl;

     MTL_A::Queue_D<double> my_queue_d_1;
    for (double x : {222.22, 44.44, 789.6, 123.45, 88.64, 123.123})
        my_queue_d_1.push(x);
    MTL_A::Queue_D<std::string> my_queue_d_2;
    for (std::string x : {"Mickey", "Minnie", "Donald", "Daisy", "Pluto", "Goofy"})
        my_queue_d_2.push(x);

    ct::print_container(my_queue_d_1);
    ct::print_container(my_queue_d_2);

    return 0;
}
