#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

bool is_char_same(char c_begin,char c_end)
{
    // Compare two characters in a case-insensitive way.
    // Cast to unsigned char to avoid undefined behavior with std::tolower.
    return std::tolower(static_cast<unsigned char>(c_begin)) ==
           std::tolower(static_cast<unsigned char>(c_end));
}


bool palindrome_string(std::string str)
{
    // Base case: an empty string or a single character is always a palindrome.
    if (str.length() <= 1)
        return true;

    // Ignore leading whitespace / punctuation.
    if (!std::isalnum(static_cast<unsigned char>(str.front())))
    {
        str.erase(0, 1);
        return palindrome_string(str);
    }

    // Ignore trailing whitespace / punctuation.
    if (!std::isalnum(static_cast<unsigned char>(str.back())))
    {
        str.erase(str.size() - 1, 1);
        return palindrome_string(str);
    }

    // If the first and last relevant characters match, strip them and recurse.
    if (is_char_same(str.front(), str.back()))
    {
        str.erase(0, 1);
        str.erase(str.size() - 1, 1);
        return palindrome_string(str);
    }

    // Mismatch means it's not a palindrome.
    return false;
}

int main()
{
    std::vector<std::string> str_list={"Radar", "Saddleback College", "CS 1D", "No lemon, no melon",
                                    "A man a plan a canal Panama", "The rain in Spain", "Racecar", "Dad", "Mom", "Was it a cat I saw ?"};

    for(const auto& iter: str_list)
    {
        // Print descriptive output for each input string.
        std::cout << iter << ": ";

        if (palindrome_string(iter))
        {
            std::cout << "Palindrome (True)" << std::endl;
        }
        else
            std::cout << "Not a palindrome (False)" << std::endl;

    }

    //std::string s={"acbasdaca"};
    //std::cout<<palindrome_string(s)<<std::endl;

    return 0;
}
