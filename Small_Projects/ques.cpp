#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include<cmath>
//#include<number>

using namespace std;
constexpr double e=2.71828182845904523536;
constexpr double pi=3.141592653589793238462643383;


long double func(long double x)
{
    //double e=std::numbers::e;
    long double Y=0;

    //Y=pow(e,(x*x));
    //Y=pow(x,2);
    Y=pow(sin(x),3)*pow(cos(x),2);
    //Y=1/x;

    return Y;
}

void intrgart(double start,double end)
{
    long double Area=0;
    long long part=1000000;
    long double interval=(end-start)/part;
    long double current_pos=start;
    long double next_pos=start+interval;

    while(part>0)
    {
        Area=Area+(func(current_pos)+func(next_pos))*interval/2;
        current_pos=next_pos;
        next_pos=next_pos+interval;
        part--;
    }

    std::cout<<"Area="<<Area<<std::endl;
}

void intrgart_2(double start,double end)
{
    long double Area=0;
    long long part=10;
    long double interval=(end-start)/part;
    long double current_pos=start+interval;

    Area=func(start);

    while(part-1>0)
    {
        Area=Area+4*func(current_pos);
        current_pos=start+interval;
        part--;

        if(part-1<=0)
        break;

        Area=Area+2*func(current_pos);
        current_pos=start+interval;
        part--;

    }

    Area=Area+func(end);
    Area=Area*interval/3;
    std::cout<<"Area="<<Area<<std::endl;
}


int main()
{
    intrgart(0,pi/3);

    //std::cout<<__cplusplus<<std::endl;
    return 0;
}
