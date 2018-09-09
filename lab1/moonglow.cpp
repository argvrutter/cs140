#include <iostream>
#include <string>
#include <sstream>
/*
 * Author: Aiden Rutter
 * CS140 Lab1: Moonglow
 * netid: arutter1
 * Description: read a file in Moonglow's format via stdin, 
 * and prints a simple output. If a word is a number, then that
 * is a students score on a question, so add it to exam score. 
 * if the word is NAME, then the next word is the name.
 * AVERAGE -> read numbers until a word that is not a number, 
 * avg all those numbers and add to score. Number does not neccesarily
 * follow "average".
 *
 * output is <name> <score>
 */

int main()
{
    double exam_score = 0;
    std::string curr_input, name;
    unsigned int pos;

    // searches for either: NAME, AVERAGE, or #
    while(std::cin >> curr_input)
    {
        // Checks for average while numbers follow 
        if(curr_input == "AVERAGE")
        {
            double num_eric = 0.0, curr_val;
            double sum = 0.0;
            while(std::cin >> curr_input)
            {
                // checks if numeric
                if(!std::isdigit(static_cast<unsigned char>(curr_input[0]))) break;
                num_eric ++;
                std::istringstream op(curr_input);
                op >> curr_val;
                sum += curr_val;
            }
            if(num_eric != 0) sum /= num_eric;
            exam_score += sum;
        }        
        // Checks for name
        if(curr_input == "NAME")
        {
            std::cin >> name;
        }
        // checks for stray numbers
        else if(std::isdigit(static_cast<unsigned char>(curr_input[0])))
        {
            double temp;
            std::istringstream op(curr_input);
            op >> temp;
            exam_score += temp;
        }
    }
    std::cout << name << " " << exam_score << std::endl;
}
