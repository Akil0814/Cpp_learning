//异或加密 实现文件读取
#include<vector>
#include<iostream>
#include<string>
#include<sstream>
#include<bitset>
#include <fstream>
#include<istream>

bool into_file(std::string str)
{
	std::string filename = R"(key.dat)";
    std::ofstream fout;
	fout.open(filename, std::ios::trunc | std::ios::binary);

    if (fout.is_open() == false)
	{
		std::cout << "打开文件" << filename << "失败。\n";
        return false;
	}

	fout.write(str.data(), static_cast<std::streamsize>(str.size()));

    fout.close();

    return true;
}

std::string read_file()
{
    std::string filename = R"(key.dat)";

    std::ifstream fin;
	fin.open(filename, std::ios::in | std::ios::binary);

    if (fin.is_open() == false)
	{
		std::cout << "打开文件" << filename << "失败。\n";
        return {};
	}

    std::string key_set((std::istreambuf_iterator<char>(fin)),
                        std::istreambuf_iterator<char>());

	fin.close();

    return key_set;
}

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
    std::string user_name="cs1d";
    std::string pasword="abc";
    char key='A';

    std::vector<std::bitset<8>> b_user_name=str_to_list_of_bit(user_name);
    std::vector<std::bitset<8>> b_pasword=str_to_list_of_bit(pasword);

    auto s_u=encode_decode(b_user_name,key);
    auto s_p=encode_decode(b_pasword,key);

    std::string key_set=list_of_bit_to_str(s_u)+"+"+list_of_bit_to_str(s_p)+key;

    std::cout<<"1:"<<key_set<<std::endl;
    into_file(key_set);

    key_set=read_file();
    std::cout<<"2:"<<key_set<<std::endl;


    return 0;
}

