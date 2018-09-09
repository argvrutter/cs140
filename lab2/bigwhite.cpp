/*
 * Lab2 CS140
 * Author: Aiden Rutter
 * netid: arutter1
 * program: bigwhite
 * description: Takes two numbers as command line arguments,
 * num rows & num cols, and makes a pgm of all white pixels
 * with specified dimensions.
 *
 */
#include <cstdio>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "usage: \n");
        return -1;
    }
    // convert command line args to ints with atoi
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    if(rows < 0 || cols < 0)
    {
        fprintf(stderr, "usage: bigwhite rows cols\n");
        return -1;
    }
    // write header
    fprintf(stdout, "P2\n%d %d \n255\n", rows, cols);

    // write rows * cols 255's, whitespace doesn't really matter
  
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            fprintf(stdout, "255 ");
        }
        fprintf(stdout, "\n");
    }
}
