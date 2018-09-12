/*
 * Lab2 CS140
 * Author: Aiden Rutter
 * netid: arutter1
 * program: hflip
 * description: reflects the image across the y axis
 * Use a 1d vector.
 */
#include <cstdio>
#include <vector>
#include <string.h>
typedef unsigned char Pix;

int main()
{
    int pixel;
    std::vector<Pix> pixels;
    char label[5];
    int c;
    scanf("%3c", label);
    // checks if label is there & has whitespace after it
    if(strcmp(label,"P2") && strcmp(label, "P2\n"))
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
    printf("P2\n%d %d \n255\n", rows, cols);
    pixels.reserve(cols);
    // cols + 1 since if statement comes before scan.
    for(int i=0; i<rows * (cols+1); i++)
    {
        // when row is filled
        if(!(i % (rows)) && i != 0)
        {
            // swap: left is right, right is left
            for(unsigned int j=0; j<pixels.size() / 2; j++)
            {
                pixel = pixels.at(j);
                pixels.at(j) = pixels.at(pixels.size() - 1 - j);
                pixels.at(pixels.size() - 1 - j) = pixel;
            }
            // write the swapped row to stdout
            for(unsigned int j=0; j<pixels.size(); j++)
            {
                printf("%d ", pixels.at(j));
            }
            // newline just for readability
            printf("\n");
            // clear the pixel vector for the next row.
            pixels.clear();
            c++;
            // last column is swapped, break
            if(c == cols)
            {
                // this scanf should result in eof
                scanf("%d", &pixel);
                if(!(feof(stdin)))
                {
                    fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
        }
        if(!scanf("%d", &pixel))
        {
            fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i);
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
        pixels.push_back((Pix)pixel);
    }
}
