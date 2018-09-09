/*
 * Lab2 CS140
 * Author: Aiden Rutter
 * netid: arutter1
 * program: vflip
 * description: Flip the file across the x axis.
 * Use a vector.
 */
 #include <cstdio>
 #include <vector>
 #include <string.h>
 typedef unsigned char Pix;

 int main()
 {
     Pix pixel;
     std::vector<std::vector<Pix> > pixels;

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
     pixels.resize(cols);
     for(std::vector<Pix>& pixl : pixels)
     {
         pixl.resize(rows);
     }
     printf("P2\n%d %d \n255\n", rows, cols);
     // read pixels into 2d vector
     // loops through a column
     for(int i=0; i<cols; i++)
     {
        // loops through a row
        for(int j=0; j<rows; j++)
        {
            scanf("%hhu", &pixel);
            pixels.at(i).at(j) = pixel;
        }
     }
     // swap on vertical axis
     for(unsigned int i=0; i<pixels.size() / 2; i++)
     {
         pixels.at(i).swap(pixels.at(pixels.size() - 1 - i));
     }
     // write pixels to stdout
     // loops through a column
     for(int i=0; i<cols; i++)
     {
        // loops through a row
        for(int j=0; j<rows; j++)
        {
            printf("%u ", pixels.at(i).at(j));
        }
     }
 }
