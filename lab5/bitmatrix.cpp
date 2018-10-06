#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.h"
/**
 * Author: Aiden Rutter
 * CS140 Lab5
 * Description: implement bitmatrix.h
 * For week 1, cases 1-28 and 101-120 must work
 * Implement all methods in BM_Hash and Bitmatrix by partial deadline
 */
/**
 * Create a bitmatrix of the specified size whose entries are all zeros.
 * If rows or cols is less than or equal to zero, print an error message,
 * but still create a 1 X 1 bit-matrix whose entry is zero.
 * @param rows # of rows
 * @param cols # of columns
 */
Bitmatrix::Bitmatrix(int rows, int cols)
{
  if(rows <= 0 || cols <= 0)
  {
    cerr << "Rows or columns less than 0" << endl;
    M.resize(1, "0");
  }
  else
  {
    M.resize(rows);
    for(string& row : M) row.resize(cols, '0');
  }
}
/**
 * Accessor, returns size of row
 * @return # of rows
 */
int Bitmatrix::Rows()
{
  return M.size();
}
/**
 * Return the number of columns in the bit-matrix.
 * @return # of columns
 */
int Bitmatrix::Cols()
{
  return M[0].size();
}
/**
 * Set the element in the specified row and column (zero-indexed, 
 * of course) to the given value. Val can be either 0 or '0' to specify 
 * zero, and either 1 or '1' to specify one. The character your program 
 * actually stores should be a '0' or a '1'. Hence if val is either the 
 * integer 0 or 1, as opposed to the integer 48 or 49, which represent 
 * '0' and '1', then you need to convert it to '0' or '1'. You can do
 * so by adding '0' to val. If row or col are bad, simply do nothing 
 * -- your code should not be erroneous if given bad values.
 * @param row [description]
 * @param col [description]
 * @param val [description]
 */
void Bitmatrix::Set(int row, int col, char val)
{
  // if row or col are bad, do nothing
  if(row <= 0 || col <= 0 || row >= Rows() || col >= Cols()) return;
  // val can be 0,1 or '0','1'
  if(val == 0 || val == 1) val+='0';
  if(val == '0' || val == '1') M[row][col] = val;  
}
/**
 * [Bitmatrix::Val description]
 * @param  row [description]
 * @param  col [description]
 * @return     [description]
 */
char Bitmatrix::Val(int row, int col)
{
  return -1;
}
/**
 *  Print the matrix on standard output. If w is less than or equal to zero,
 *  print each row on its own line with no spaces. Otherwise, print a space
 *  after every w columns and a blank line after every w rows. I've written
 *  this one for you.
 * @param w [description]
 */
void Bitmatrix::Print(int w)
{
  int i, j;

  for (i = 0; i < M.size(); i++) {
    if (w > 0 && i != 0 && i%w == 0) printf("\n");
    if (w <= 0) {
      cout << M[i] << endl;
    } else {
      for (j = 0; j < M[i].size(); j++) {
        if (j % w == 0 && j != 0) printf(" ");
        printf("%c", M[i][j]);
      }
      cout << endl;
    }
  }
}
/**
 *  Write the bit-matrix to a file. Here, just write out the zeros and
 *  ones with no spaces. Each row of the bit-matrix gets one row of output.
 * @param fn [description]
 */
void Bitmatrix::Write(string fn)
{
}
/**
 * [Bitmatrix::Swap_Rows description]
 * @param r1 [description]
 * @param r2 [description]
 */
void Bitmatrix::Swap_Rows(int r1, int r2)
{
}
/**
 * [Bitmatrix::R1_Plus_Equals_R2 description]
 * @param r1 [description]
 * @param r2 [description]
 */
void Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
}
/**
 * Read a bit-matrix from a file. The file should contain only zeros, ones,
 * spaces and newlines, and each line should either be blank, or it should
 * contain the same number of non-spaces as all other lines. I've written
 * this one for you, so you don't need to sweat about it too much.
 * @param fn [description]
 */
Bitmatrix::Bitmatrix(string fn)
{
  ifstream f;
  int i, j;
  string s, row;

  f.open(fn.c_str());
  if (f.fail()) { perror(fn.c_str()); M.resize(1); M[0].resize(1), M[0][0] = '0'; return; }

  while (getline(f, s)) {
    row.clear();
    for (i = 0; i < s.size(); i++) {
      if (s[i] == '0' || s[i] == '1') {
        row.push_back(s[i]);
      } else if (s[i] != ' ') {
        fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
        M.resize(1); M[0].resize(1), M[0][0] = '0';
        f.close();
        return;
      }
    }
    if (s.size() > 0 && M.size() > 0 && row.size() != M[0].size()) {
      fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
      M.resize(1); M[0].resize(1), M[0][0] = '0';
      f.close();
      return;
    }
    if (s.size() > 0) M.push_back(row);
  }
  f.close();
}
/**
 * Create a PGM file from the bit-matrix. This is how I made the pictures above.
 * The zero entries are white (255) and the one entries are gray (100).
 * Each entry is a pixels by pixels square. If border is greater than zero,
 * then there should be a black border of that many pixels separating each
 * square and around the whole matrix.
 * @param fn     [description]
 * @param pixels [description]
 * @param border [description]
 */
void Bitmatrix::PGM(string fn, int pixels, int border)
{
}
/**
 * [Bitmatrix::Copy description]
 * @return [description]
 */
Bitmatrix *Bitmatrix::Copy()
{
  return NULL;
}
/**
 * [BM_Hash::BM_Hash description]
 * @param size [description]
 */
BM_Hash::BM_Hash(int size)
{
}
/**
 * [BM_Hash::Store description]
 * @param key [description]
 * @param bm  [description]
 */
void BM_Hash::Store(string &key, Bitmatrix *bm)
{
}
/**
 * [BM_Hash::Recall description]
 * @param  key [description]
 * @return     [description]
 */
Bitmatrix *BM_Hash::Recall(string &key)
{
  return NULL;
}
/**
 * [BM_Hash::All description]
 * @return [description]
 */
HTVec BM_Hash::All()
{
  HTVec rv;
  return rv;
}

/**
 * [Sum description]
 * @param  m1 [description]
 * @param  m2 [description]
 * @return    [description]
 */
Bitmatrix *Sum(Bitmatrix *m1, Bitmatrix *m2)
{
  return NULL;
}
/**
 * [Product description]
 * @param  m1 [description]
 * @param  m2 [description]
 * @return    [description]
 */
Bitmatrix *Product(Bitmatrix *m1, Bitmatrix *m2)
{
  return NULL;
}
/**
 * [Sub_Matrix description]
 * @param  m    [description]
 * @param  rows [description]
 * @return      [description]
 */
Bitmatrix *Sub_Matrix(Bitmatrix *m, vector <int> &rows)
{
  return NULL;
}
/**
 * [Inverse description]
 * @param  m [description]
 * @return   [description]
 */
Bitmatrix *Inverse(Bitmatrix *m)
{
  return NULL;
}
