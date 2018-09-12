/*
 * Lab2 CS140
 * Author: Aiden Rutter
 * netid: arutter1
 * program: pgminfo
 * description: Takes pgm file on stdin and reports # of rows, # cols,
 * # pixels, avg pixel value.
 *
 */
#include <cstdio>
#include <vector>
#include <string.h>
typedef unsigned char Pix;

int main()
{
    int pixel;
    char label[5];
    double sum=0.0;
    scanf("%3c", label);
    // checks if label is there & has whitespace after it
    if(strcmp(label,"P2 ") && strcmp(label, "P2\n"))
    {
        fprintf(stderr, "Bad PGM file -- first word is not P2\n");
        return -1;
    }
    int rows, cols, max;
    scanf("%d %d\n%d", &rows, &cols, &max);
    if(rows <= 0)
    {
        fprintf(stderr, "Bad PGM file -- No column specification\n");
        return -1;
    }
    if(cols <= 0)
    {
        fprintf(stderr, "Bad PGM file -- No row specification\n");
        return -1;
    }
    if(max != 255)
    {
        fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
        return -1;
    }
    // loop thru all pixels
    for(int i=0; i<rows * cols; i++)
    {
        // 0 things read
        if(!scanf("%d", &pixel))
        {
            fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i+1);
            return -1;
        }
        // check if value between 0 and 255
        if(pixel < 0 || pixel > 255)
        {
            fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i);
            return -1;
        }
        if(feof(stdin) || ferror(stdin))
        {
            fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i);
            return -1;
        }
        sum += (double)pixel;
    }
    sum /= (double)rows*cols;
    // this scanf should result in eof
    scanf("%d", &pixel);
    if(!(feof(stdin)))
    {
        fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
        return -1;
    }

    printf("# Rows:%*d\n", 12, cols);
    printf("# Columns:%*d\n", 9, rows);
    printf("# Pixels:%*d\n", 10, rows * cols);
    printf("Avg Pixel:%*.3f\n", 9, sum);

    return 0;
}
