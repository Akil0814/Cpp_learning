#include<iostream>
class A
{
public:
    A()
    {
        std::cout<<"A"<<std::endl;
    }

};

int main()
{
    A* ta1= new A;
    A* ta2= new A();
    A ta3=A();

    return 0;
}
