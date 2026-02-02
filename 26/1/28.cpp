#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include <cctype>

#include "_print_container.h"
#include "_container_modify.h"

#include "_my_stack.h"
#include "_my_queue.h"
#include "_my_deque.h"
#include "_my_queue_with_deque.h"


// !-----------------------IMPROTANT-----------------------!
// this program only work for C++20 or higher version
// !-----------------------IMPROTANT-----------------------!


//result shoud be:
//a 468
//d 23
//e -212

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

long long read_number(MTL_A::Deque<char>& q, char ver, double val)
{
    int sign = 1;
    bool has_digit = false;
    long long x = 0;

    while (!q.empty() && (q.front() == '+' || q.front() == '-'))
    {
        if (q.front() == '-')
            sign = -sign;
        q.pop_front();
    }

    while (!q.empty())
    {
        char c = q.front();

        if (std::isdigit(static_cast<unsigned char>(c)))
        {
            has_digit = true;
            x = x * 10 + (c - '0');
            q.pop_front();
        }
        else if (c == ver)
        {
            x = static_cast<long long>(x * val);
            q.pop_front();
        }
        else
            break;
    }

    if (!has_digit)
        throw std::runtime_error("Expected a number");

    return sign * x;
}

long long calculate_multi(MTL_A::Deque<char> cdp, char ver, double val)
{
    if (cdp.empty()) throw std::runtime_error("Empty expression");

    long long result = 0;
    long long term = read_number(cdp, ver, val);

    while (!cdp.empty())
    {
        char op = cdp.front();
        cdp.pop_front();

        if (op!='+' && op!='-' && op!='*' && op!='/')
            throw std::runtime_error(std::string("Unexpected operator: '") + op + "'");

        long long rhs = read_number(cdp, ver, val);

        if (op == '*')
        {
            term = term * rhs;
        }
        else if (op == '/')
        {
            if (rhs == 0)
                throw std::runtime_error("Division by zero");
            term = term / rhs;
        }
        else if (op == '+')
        {
            result += term;
            term = rhs;
        }
        else if (op == '-')
        {
            result += term;
            term = -rhs;
        }
    }

    result += term;
    return result;
}


int calculate(MTL_A::Deque<char> cdp,char ver, double val)
{
    //确保第一个数字的正负性被记录
    bool is_oper1_neg=false;
    bool is_oper2_neg=false;
    bool do_multiplication=false;

    MTL_A::Deque<int> operand_1;
    MTL_A::Deque<int> operand_2;

    MTL_A::Deque<int>* current_input=&operand_1;

    char tmp_c;
    int res1=0;
    int res2=0;
    int res=0;

    if(cdp.front()=='-')
    {
        is_oper1_neg=true;
        cdp.pop_front();
    }


    while(!cdp.empty())
    {
        tmp_c=cdp.front();

        if (std::isdigit(static_cast<unsigned char>(tmp_c)))
        {
            current_input->push_back(tmp_c - '0');
        }
        else if(tmp_c=='+')
        {
            current_input=&operand_2;
        }
        else if(tmp_c=='-')
        {
            current_input=&operand_2;
            is_oper2_neg=true;
        }
        else if(tmp_c=='*')
        {
            current_input=&operand_2;
            do_multiplication=true;
        }
        else if(tmp_c==ver)
        {
            int tmp_n=0;
            while(!current_input->empty())
            {
               tmp_n=tmp_n+operand_1.front();
                current_input->pop_front();
                if(!current_input->empty())
                    tmp_n=tmp_n*10;
            }
            current_input->push_back(tmp_n*val);
        }
        else
            throw std::runtime_error(std::string("Unexpected character: '") + tmp_c + "'");

        cdp.pop_front();
    }
    ct::print_container(cdp);

    ct::print_container(operand_1);
    ct::print_container(operand_2);


    while(!operand_1.empty())
    {
        res1=res1+operand_1.front();
        operand_1.pop_front();
        if(!operand_1.empty())
            res1=res1*10;
    }

    while(!operand_2.empty())
    {
        res2=res2+operand_2.front();
        operand_2.pop_front();
        if(!operand_1.empty())
            res1=res1*10;
    }

    if(is_oper1_neg)
        res1=(0-res1);

    if(is_oper2_neg)
        res2=(0-res2);

    if(do_multiplication)
        res=res1*res2;
    else
        res=res1+res2;

    return res;

}

std::string evaluate(std::string s, char ver, double val)
{
    double r=0;
    for(auto &c: s)
    {
        if (c=='('||c=='['||c=='{')
            c = '(';
        if (c==')'||c==']'||c=='}')
            c = ')';
    }

    std::cout<<"string"<<s<<" ,"<<std::endl;

    while((s.find('(') != std::string::npos)
        ||(s.find(')') != std::string::npos)
        ||(s.find('*') != std::string::npos))
    {

    int time=0;
    int max_time=0;
    char* priority=nullptr;
    int num_of_c=0;
    MTL_A::Deque<char> chars;

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

    if((s.find('(') == std::string::npos)&&(s.find(')') == std::string::npos))
    {
        priority=&s[0];
    }

    size_t pos = static_cast<size_t>(priority - s.data());

    if(s[pos]=='(')
    {
        std::cout<<"can find ()"<<std::endl;
        s.erase(pos, 1);
        while (pos < s.size() && s[pos] != ')')
        {
            chars.push_back(s[pos]);
            s.erase(pos, 1);
        }
        s.erase(pos, 1);
    }
    else
    {
        std::cout<<"can't find ()"<<std::endl;
        while (!s.empty())
        {
            chars.push_back(s[pos]);
            s.erase(pos, 1);
        }

    }


    std::cout<<"string of priority:"<<std::endl;
    ct::print_container(chars);

    std::cout<<"string after take out priority:"<<s<<" ,"<<std::endl;

    char next = s[pos];
    char prev = (pos > 0) ? s[pos - 1] : '\0';

    if(std::isdigit(static_cast<unsigned char>(next))||next=='('||next==ver)
    {
        std::cout<<"next pos is:"<<next<<" ,"<<std::endl;
        s.insert(pos,"*");
    }

    if(std::isdigit(static_cast<unsigned char>(prev))||prev==')'||prev==ver)
    {
        std::cout<<"prev pos is:"<<prev<<" ,"<<std::endl;
        s.insert(pos-1,"*");
    }

    s.insert(pos,std::to_string(calculate_multi(chars,ver,val)));//传入一串式子（3x+3）


    std::cout<<"string after put back calculation results:"<<s<<" ,"<<std::endl;

    }

    //if((s.find('+') != std::string::npos)||(s.find('*') != std::string::npos)((s.find('/') != std::string::npos)))


//if string have more than one - or have +or *


    return s;
}


int main()
{
    std::cout<<"Current C++ ver:"<<__cplusplus<<std::endl;

/*
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

*/

    std::cout<<"-----------PART I AND J--------------"<<std::endl;

    char No='a';
    for(std::string test : {"((12x+3){2x-7})", "{{8x+5)-5x[9x+3]})", "(((4x+8)-x[4x+3])))", "{2x+5}(9x+4)", "[(5x-5)-4x[6x+2]]", "(2x+7}(12x+6)"})
    {
        std::cout<<No++<<":";
        if(valid_parentheses(test))
        {
            std::cout<<"-----------------------------------"<<std::endl;

            evaluate(test,'x',-3);
            //std::cout<<"is valid, the answer will be:";
            //std::cout<<evaluate(test,'x',-3);
            std::cout<<"-----------------------------------"<<std::endl;
        }
        else
            std::cout<<"is not valid"<<std::endl;

        std::cout<<"\n";
    }

    return 0;
}
