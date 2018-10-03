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
 */
Bitmatrix::Bitmatrix(int rows, int cols)
{
}
/**
 * Accessor, returns size of row
 * @return [description]
 */
int Bitmatrix::Rows()
{
  return rows;
}
/**
 * [Bitmatrix::Cols description]
 * @return [description]
 */
int Bitmatrix::Cols()
{
  return 0;
}
/**
 * [Bitmatrix::Set description]
 * @param row [description]
 * @param col [description]
 * @param val [description]
 */
void Bitmatrix::Set(int row, int col, char val)
{
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
 * [Bitmatrix::Print description]
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
 * [Bitmatrix::Write description]
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
 * [Bitmatrix::Bitmatrix description]
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
 * [Bitmatrix::PGM description]
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
