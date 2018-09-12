/*
 * Lab2 CS140
 * Author: Aiden Rutter
 * netid: arutter1
 * program: neg
 * description: Inverts the PGM values.
 * Ensure that PGM file is valid
 *
 */
#include <cstdio>
#include <vector>
#include <string.h>
typedef unsigned char Pix;

int main()
{
    Pix pixel;
    char label[5];
    scanf("%2s", label);
    if(strcmp(label,"P2"))
    {
        fprintf(stderr, "Bad PGM file -- first word is not P2\n");
        return -1;
    }
    int rows, cols, max;
    scanf("%d %d\n%d", &rows, &cols, &max);
    if(rows <= 0 || cols <= 0)
    {
        fprintf(stderr, "Bad PGM file -- No column specification\n");
        return -1;
    }
    if(max != 255)
    {
        fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
        return -1;
    }
    printf("P2\n%d %d \n255\n", rows, cols);
    // iterate through all pixels and get inverse, 255 - pixel value
    for(int i=0; i<rows * cols; i++)
    {
        scanf("%hhu", &pixel);
        pixel = 255 - pixel;
        printf("%u ",(Pix)pixel);
    }
}
