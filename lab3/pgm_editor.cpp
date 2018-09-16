/**
 * Author: Aiden Rutter
 * CS140 Lab3: more fun with PGMs!
 * Description: Implement a number of PGM manipulation procedures.
 * User can specify the name of an operation. No vector erase.
 */
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;
typedef vector <int> IVec;

// Write your code here:
/**
 * @brief Write vectorized pgm file to stdout.
 * @param p vector of vector of ints.
 */
void pgm_write(const vector<IVec>& p)
{
    int rows = p.size();
    int cols = p[0].size();
    int i,j;
    printf("P2\n%d %d \n255\n", rows, cols);

    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            if((i * rows + j) % 20 == 0 && (i * rows + j) != 0)
            {
                printf("%4d\n", p.at(i).at(j));
            }
            else
            {
                printf("%4d", p.at(i).at(j));
            }
        }
    }
    // newline at the end, if there already is one, then don't add another
    if((i * rows + j) % 20 != 0)
    {
        printf("\n");
    }
}
/**
 * @brief Creates a pgm file with (r)ows, (c)ols, & pgm value
 * @param  r  rows
 * @param  c  columns
 * @param  pv all pixels will have this value. [0-255]
 * @return    Vector vector of ints representing pixel values
 */
vector<IVec> pgm_create(int r, int c, uint8_t pv)
{
    // Allocate space to vector & set all elements = pv using resize
    vector<IVec> p;
    p.resize(r);
    for(IVec& r : p)
    {
        r.resize(c, pv);
    }
    return p;
}
/**
 * @brief Rotates pgm 90 deg cw.
 * @param p pixel array by reference
 */
void pgm_cw(vector<IVec>& p)
{

}
/**
 * @brief Rotate pgm 90 deg ccw. Can't just cw 3 times either
 * @param p pixel array by reference.
 */
void pgm_ccw(vector<IVec>& p)
{

}
/**
 * @brief adds w pixels around the border of p. All pixels will have value pv.
 * Cannot declare another 2d vector. Required for partial
 * @param p  2d pixel vector
 * @param w  witdth of padding
 * @param pv value of pixel to pad with
 */
void pgm_pad(vector<IVec>& p, int w, int pv)
{
    // Adds padding on the left & right of image
    for(IVec& r : p)
    {
        r.insert(r.begin(), pv, w);
        r.insert(r.end(), pv, w);
    }
    // Adds padding to top & bottom of image
    IVec r(p[0].size(), pv);
    p.insert(p.begin(), r, w);
    p.insert(p.end(), r, w);
}
/**
 * @brief Changes p so that it has r*c copies of PGM file, laid out in a r*c grid.
 * Cannot declare another 2d vector. Required for partial
 * @param p 2d pixel vector by reference
 * @param r number of rows of panels
 * @param c number of columns of panels
 */
void pgm_panel(vector<IVec>& p, int r, int c)
{
    // duplicates each row, so that we now have 1 row of panes.
    for(IVec& row : p) r.insert(r.end(), row, c-1);
    // Populate columns
    p.insert(p.end(), p, r-1);
}
/**
 * @brief Change p to a rectangular subset of the original picture, starting at row r,
 * col c,and extending rows by columns
 * @param p    2d pixel vector by reference
 * @param r    starting row
 * @param c    starting column
 * @param rows number of rows to keep, starting from r
 * @param cols number of columns to keep, starting from c
 */
void pgm_crop(vector<IVec>& p, int r, int c, int rows, int cols)
{

}
// DO NOT CHANGE ANYTHING BELOW THIS LINE

void bad_pgm(string s)
{
  cerr << "Bad PGM file: " << s << endl;
  exit(1);

}

vector <IVec> pgm_read()
{
  string s;
  int r, c, i, j, v;
  vector <IVec> p;

  if (!(cin >> s)) bad_pgm("Empty file.");
  if (s != "P2") bad_pgm("First word is not P2.");
  if (!(cin >> c) || c <= 0) bad_pgm("Bad column spec.");
  if (!(cin >> r) || r <= 0) bad_pgm("Bad column spec.");
  if (!(cin >> i) || i != 255) bad_pgm("Bad spec of 255.");
  p.resize(r);
  for (i = 0; i < r; i++) for (j = 0; j < c; j++) {
    if (!(cin >> v) || v < 0 || v > 255) bad_pgm("Bad pixel.");
    p[i].push_back(v);
  }
  if (cin >> s) bad_pgm("Extra stuff at the end of the file.");
  return p;
}

void usage()
{
  cerr << "usage: pgm_editor command....\n\n";
  cerr << "        CREATE rows cols pixvalue\n";
  cerr << "        CW\n";
  cerr << "        CCW\n";
  cerr << "        PAD pixels pixvalue\n";
  cerr << "        PANEL r c\n";
  cerr << "        CROP r c rows cols\n";
  exit(1);
}

main(int argc, char **argv)
{
  istringstream ss;
  int r, c, i, j, p, w, rows, cols;
  vector <IVec> pgmf;
  string a1;

  if (argc < 2) usage();
  a1 = argv[1];

  if (a1 == "CREATE") {
    if (argc != 5) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c <= 0) usage();
    ss.clear(); ss.str(argv[4]); if (!(ss >> p) || p < 0 || p > 255) usage();
    pgmf = pgm_create(r, c, p);
  } else if (a1 == "PAD") {
    if (argc != 4) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> w) || w <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> p) || p < 0 || p > 255) usage();
    pgmf = pgm_read();
    pgm_pad(pgmf, w, p);
  } else if (a1 == "CCW") {
    if (argc != 2) usage();
    pgmf = pgm_read();
    pgm_ccw(pgmf);
  } else if (a1 == "CW") {
    if (argc != 2) usage();
    pgmf = pgm_read();
    pgm_cw(pgmf);
  } else if (a1 == "PANEL") {
    if (argc != 4) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r <= 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c <= 0) usage();
    pgmf = pgm_read();
    pgm_panel(pgmf, r, c);
  } else if (a1 == "CROP") {
    if (argc != 6) usage();
    ss.clear(); ss.str(argv[2]); if (!(ss >> r) || r < 0) usage();
    ss.clear(); ss.str(argv[3]); if (!(ss >> c) || c < 0) usage();
    ss.clear(); ss.str(argv[4]); if (!(ss >> rows) || rows <= 0) usage();
    ss.clear(); ss.str(argv[5]); if (!(ss >> cols) || cols <= 0) usage();
    pgmf = pgm_read();
    if (r + rows > pgmf.size() || c + cols > pgmf[0].size()) {
      fprintf(stderr, "CROP - Bad params for the pictures size (r=%d, c=%d)\n",
           (int) pgmf.size(), (int) pgmf[0].size());
      exit(1);
    }
    pgm_crop(pgmf, r, c, rows, cols);
  } else {
    usage();
  }
  pgm_write(pgmf);
}
