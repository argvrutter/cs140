#include <iostream>
#include <vector>
#include <string>
int main()
{
    std::string foo = "";
    int len;
    char start_char, curr_char;
    std::cin >> len >> start_char;
    if(std::cin.fail())
        return -1;

    for(int i=0; i<len; i++)
    {
        if(start_char == 'z')
            start_char = 'a';
        else
            start_char++;
    
        foo.push_back(curr_char);
    }
}
