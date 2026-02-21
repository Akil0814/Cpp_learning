#include<iostream>

template<typename T>
void printArray(T list[], int arraySize)
{
  for (int i = 0; i < arraySize; i++)
  {
    std::cout << list[i] << " ";
  }
  std::cout << std::endl;
}

int main()
{
    std::string s("abcd");
    std::cout << s.size() << std::endl;
    //int list[] = {1, 2.5, 3, 4};
    //printArray(list, 4);

}
