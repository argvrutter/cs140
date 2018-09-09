#include <iostream>

int main(int argc, char** argv)
{
    std::string input;
    int gold_oz = 0;

    while(std::cin >> input)
    {
        for(char& c : input)
        {
            if(c != '.' && c >= 'A' && c <= 'Z')
            {
                gold_oz += (int)c - (int('A')-1);
            }
        }
    }
    std::cout << gold_oz << std::endl;
}
