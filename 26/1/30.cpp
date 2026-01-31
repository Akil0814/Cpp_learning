#include "_my_queue_with_deque.h"
#include "_print_container.h"
#include "_container_modify.h"

#include<iostream>

int main()
{
    MTL_A::Queue_D<std::string> my_queue;

    std::string s1 ="A man, a plan, a canal, Panama";
    std::string s2 = "Was it a car or a cat I saw?";
    std::string s3 = "Sit on a potato pan, Otis";
    std::string s4 = "No lemon, no melon";


    std::cout<<"--------------"<<std::endl;

    std::cout<<"Size of new queue:"<<my_queue.size()<<std::endl;
    std::cout<<"Is queue empty:"<<my_queue.empty()<<std::endl;

    std::cout<<"Start loading..."<<std::endl;
    for(std::string s:{"A man, a plan, a canal, Panama","Was it a car or a cat I saw?","Sit on a potato pan, Otis","No lemon, no melon"})
    {
        my_queue.enqueue(s);
    }
    std::cout<<"Finsh loading:"<<std::endl;
    ct::print_container(my_queue);
    std::cout<<"Size of queue:"<<my_queue.size()<<std::endl;
    std::cout<<"Is queue empty:"<<my_queue.empty()<<std::endl;
    std::cout<<"front of queue:"<<my_queue.front()<<std::endl;


    std::cout<<"Dequeue one..."<<std::endl;
    my_queue.dequeue();
    ct::print_container(my_queue);

    return 0;

}
