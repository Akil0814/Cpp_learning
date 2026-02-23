//XOR Cipher
//异或加密
#include<vector>
#include<iostream>
#include<string>
#include<sstream>
#include<bitset>

std::vector<std::bitset<8>> str_to_list_of_bit(std::string str)
{
    std::vector<std::bitset<8>> bits;

    for(int i=0;i<str.size();++i)
    {
        bits.push_back(std::bitset<8>(str[i]));

    }

    return bits;
}

std::string list_of_bit_to_str(std::vector<std::bitset<8>> bits)
{
    std::stringstream ss;
    for(int i=0;i<bits.size();++i)
    {
        ss<<char(bits[i].to_ulong());
    }

    return  ss.str();
}

std::vector<std::bitset<8>> encode_decode(std::vector<std::bitset<8>> bits, char char_key)
{
    auto result=bits;
    std::bitset<8> key(char_key);
    for(int i=0; i<result.size(); ++i)
    {
        result[i]^=key;
    }

    return result;
}

int main()
{
    //原文
    std::string s="樱岛麻衣";
    std::vector<std::bitset<8>> b=str_to_list_of_bit(s);
    std::cout<<"1:"<<s<<std::endl;

    //加密后
    auto b2=encode_decode(b,'a');
    std::string s2=list_of_bit_to_str(b2);
    std::cout<<"2:"<<s2<<std::endl;


    //正确解密
    auto b3=encode_decode(b2,'a');
    std::string s3=list_of_bit_to_str(b3);
    std::cout<<"3:"<<s3<<std::endl;

    //错误解密
    auto b4=encode_decode(b2,'s');
    std::string s4=list_of_bit_to_str(b4);
    std::cout<<"4:"<<s4<<std::endl;

    return 0;
}
