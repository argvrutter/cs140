#include <iostream>
#include <stdlib.h> 
/*
 * Author: Aiden Rutter
 * CS140 Lab1: Checkerboard
 * netid: arutter1
 * Description: Reads five inputs from stdin
 * Parameters R, C, SC, CS, width w
 * Starting character sc, read as char, remaining are ints.
 * Example usage: ./checkerboard <rows> <Columns> <starting char>
 * <repititions>
 */

int main(int argc, char** argv)
{
    int rows, cols, cycle_size, width;
    char starting_char, curr_char;
    
    std::cin >> rows >> cols >> starting_char >> cycle_size >> width;
    if(std::cin.fail())
    {
        std::cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W" << std::endl;
        return -1;
    }

    /*
    if(argc != 6)
    {
        std::cerr << "usage: ./checkerboard <rows> <Columns> <starting char> <cycle size> <width>";
        return -1;
    }
    try 
    {
        rows=atoi(argv[1]), cols=atoi(argv[2]), cycle_size=atoi(argv[4]), width=atoi(argv[5]);
        starting_char = argv[3][0];
    }
    catch(...)
    {
        std::cerr << "usage: ./checkerboard <rows> <Columns> <starting char> <cycle size> <width>. Enter 2 integers, a character, and then two more integers.";
        return -1;
    }*/
    if(starting_char + cycle_size > 127)
    {
        return -1;
    }
    if(rows <= 0 || cols <= 0 || cycle_size <=0 || width <= 0 || starting_char <= 0)
    {
        return -1;
    }

    // loops through rows, and is repeated width times per loop.
    for(int i=0; i<rows; i++)
    {
        for(int e=0; e<width; e++)
        {
            // loops through columns, and determines character based on the current row,
            // starting character, and cycle size to make desired "checkerboard" pattern.
            for(int j=0; j<cols; j++)
            {
                curr_char = (char)(starting_char + ((j+i)%cycle_size));
                for(int k=0; k<width; k++)
                {
                    std::cout << curr_char;
                }
            }
            std::cout << std::endl;
        }
    }
}



