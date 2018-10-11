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
 * @param row row index (zero indexed)
 * @param col column index
 * @param val value to set, should be 0,1 or '0','1'
 */
void Bitmatrix::Set(int row, int col, char val)
{
  // if row or col are bad, do nothing
  if(row < 0 || col < 0 || row >= Rows() || col >= Cols()) return;
  // val can be 0,1 or '0','1'
  if(val == 0 || val == 1) val+='0';
  if(val == '0' || val == '1') M[row][col] = val;  
}
/**
 * Return the specified value -- '0' should be returned as the integer 
 * 0 and '1' should be returned as the integer 1. Even though Val returns
 * a char, you can have your return statement return the integer 0 or 
 * the integer 1 and it will work properly. This also means that when 
 * you use Val to retrieve a value from a matrix, and you want to store 
 * its return value back into another matrix (e.g., the Copy method will 
 * need to do this), you will need to first convert the return value to 
 * the character '0' or '1'. You can do this by adding '0' to the return 
 * value. Val() should return -1 if given bad input.
 * @param  row zero indexed row
 * @param  col zero indexed column
 * @return     integer 0, 1, or -1, if char desired add +'0' when calling
 */
char Bitmatrix::Val(int row, int col)
{
  if(row < 0 || col < 0 || row >= Rows() || col >= Cols()) return -1;
  return M[row][col]-'0';
}
/**
 *  Print the matrix on standard output. If w is less than or equal to zero,
 *  print each row on its own line with no spaces. Otherwise, print a space
 *  after every w columns and a blank line after every w rows. I've written
 *  this one for you.
 * @param w width
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
 * @param fn the file name
 */
void Bitmatrix::Write(string fn)
{
  ofstream fout;
  fout.open(fn);
  for(const string& row : M) fout << row << endl;
  fout.close();
}
/**
 * Swap the specified rows. This should do nothing if given bad values.
 * @param r1 zero index of row 1
 * @param r2 zero index of row 2
 */
void Bitmatrix::Swap_Rows(int r1, int r2)
{
  if(r1 < 0 || r1 >= Rows() || r2 < 0 || r2 >= Rows()) return;
  M[r1].swap(M[r2]);
}
/**
 * Set row r1 to be the sum of rows r1 and r2. Again, this should do 
 * nothing if given bad values. It's ok for r2 to equal r1. Sum is binary
 * addition w/ carry discarded?
 * @param r1 zero index of row 1
 * @param r2 zero index of row 2
 */
void Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
  if(r1 < 0 || r1 >= Rows() || r2 < 0 || r2 >= Rows()) return;
  for(int i=0; i<Cols(); i++) Set(r1, i, ((Val(r1,i) ^ Val(r2,i))%2)+'0');
}
/**
 * Read a bit-matrix from a file. The file should contain only zeros, ones,
 * spaces and newlines, and each line should either be blank, or it should
 * contain the same number of non-spaces as all other lines. I've written
 * this one for you, so you don't need to sweat about it too much.
 * @param fn filename
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
 * @param fn     filename
 * @param pixels Length of a square representing 1 pixel
 * @param border black border of border pixels
 */
void Bitmatrix::PGM(string fn, int pixels, int border)
{
  if(border < 0) border = 0;
  vector<vector<int> > pgm;
  int pgm_rows = Rows() * pixels + border * (Rows()+1);
  int pgm_cols = Cols() * pixels + border * (Cols()+1);
  FILE* fout = fopen(fn.c_str(), "w");;
  int color;

  fprintf(fout, "P2\n%d %d\n255\n", pgm_cols, pgm_rows);
  // iteration represents a row
  for(const string& row : M)
  {
    // does border at tops of rows
    for(int i=0; i<border; i++)
    {
      for(int j=0; j<pgm_cols; j++) fprintf(fout, "%4d", 0);
      fprintf(fout, "\n");
    }
    // completes a bitmatrix row
    for(int j=0; j<pixels; j++)
    {
      for(const char p : row) // completes pgm row
      {
        // set color
        color = (p == '1') ? 100 : 255;
        //vertical borders
        for(int i=0; i<border; i++) fprintf(fout, "%4d", 0);
        for(int i=0; i<pixels; i++) fprintf(fout, "%4d", color);
      }
      // add vertical border to the end
      for(int i=0; i<border; i++) fprintf(fout, "%4ld", 0);
      fprintf(fout, "\n");
    }
  }
  // Adds border to the end
  for(int i=0; i<border; i++)
  {
    for(int j=0; j<pgm_cols; j++) fprintf(fout, "%4d", 0);
    fprintf(fout, "\n");
  }
  fclose(fout);
}
/**
 * Create a new bit-matrix that is a copy of the given bit-matrix and 
 * return a pointer to it. To do this, you'll have to create a new 
 * empty bit-matrix of the proper size, and then use Set() to set its 
 * elements properly.
 * @return Pointer to a new copy of the bitmatrix.
 */
Bitmatrix *Bitmatrix::Copy()
{
  Bitmatrix* copy = new Bitmatrix(Rows(), Cols());
  for(unsigned int i=0; i<Rows(); i++)
    for(unsigned int j=0; j<Cols(); j++)
      copy->Set(i, j, M[i][j]);

  return copy;
}
/**
 * Notes for BM_HASH:
 * You should not call new or delete on bit-matrices when you implement 
 * any of the hash table methods. You should call new when you create a 
 * new HTE. That is the only time that you will call new in the hash 
 * table methods.
 */
unsigned int djb_hash(string &s)
{
  int i;
  unsigned int h;
  
  h = 5381;

  for (i = 0; i < s.size(); i++) {
    h = (h << 5) + h + s[i];
  }
  return h;
}

/**
 * The constructor specifies the size of the table.
 * @param size size of the table
 */
BM_Hash::BM_Hash(int size)
{
  table.resize(size);
}
/**
 * Store the given key and bit-matrix in the hash table. If the key is
 * already there, replace the bit-matrix with the given one.
 * @param key string hash key
 * @param bm  Bitmatrix to store
 */
void BM_Hash::Store(string &key, Bitmatrix *bm)
{
  int hi = djb_hash(key)%table.size();
  // check if key already in bucket
  for(auto &entry : table[hi]) {
    if(entry->key == key) {
      entry->bm = bm;
      return;
    }
  }
  HTE* table_entry = new HTE;
  table_entry->bm = bm;
  table_entry->key = key;
  // append table entry to bucket
  table[hi].push_back(table_entry);
}
/**
 * return the bit-matrix corresponding to the given key. If the key is 
 * not in the hash table, then return NULL.
 * @param  key string hash key
 * @return     Corresponding bit matrix or NULL if n/a
 */
Bitmatrix *BM_Hash::Recall(string &key)
{
  unsigned int hi = djb_hash(key)%table.size();
  if(table[hi].empty()) {
    return NULL;
  }
  else {
    for(auto entry : table[hi]) {
      if(entry->key == key) {
        return entry->bm;
      }
    }
  }
  return NULL;
}
/**
 * Return a vector of all hash table entries in the table. The vector 
 * should be ordered just like the hash table. In other words, suppose 
 * "A" hashes to 5, "B" hashes to 1 and "C" hashes to 1. And suppose 
 * that "B" was added to the table before "C". Then All() should return 
 * the HTE's in the order "B", "C", "A".
 * @return vector of all hash table entries in the table
 */
HTVec BM_Hash::All()
{
  HTVec rv;
  for(auto& bucket : table)
  {
    if(!(bucket.empty())) {
      for(auto& entry : bucket) {
        rv.push_back(entry);
      }
    }
  }
  return rv;
}

/**
 * This creates a new bit-matrix which is the sum of a1 and a2. If a1 
 * and a2 are not the same size, return NULL.
 * @param  m1 bitmatrix 1 pointer
 * @param  m2 bitmatrix 2 pointer
 * @return    Bitmatrix pointer that is the sum of a1 and a2
 */
Bitmatrix *Sum(Bitmatrix *m1, Bitmatrix *m2)
{
  // check if m1 and m2 are the same size, assumes pointers are not null
  if((m1->Rows() != m2->Rows()) || (m1->Cols() != m2->Cols())) return NULL;

  Bitmatrix* res = new Bitmatrix(m1->Rows(), m1->Cols());
  for(int j=0; j<res->Rows(); j++)
    for(int i=0; i<res->Cols(); i++) 
      res->Set(j, i, ((m1->Val(j,i) ^ m2->Val(j,i))%2)+'0');
  
  return res;
}
/**
 * This creates a new bit-matrix which is the product of a1 and a2. 
 * This product will have a1->Rows() rows and a2->Cols() columns. If 
 * a1->Cols() and a2->Rows() do not match, then return NULL.
 * @param  m1 bitmatrix 1 pointer
 * @param  m2 bitmatrix 2 pointer
 * @return   bitmatrix pointer that is the product of m2 and m2
 */
Bitmatrix *Product(Bitmatrix *m1, Bitmatrix *m2)
{
  if(m1->Cols() != m2->Rows()) return NULL;
  Bitmatrix* res = new Bitmatrix(m1->Rows(), m2->Cols());
  char temp;
  // matrix multiply is each row of m1 multiplied by every col of m2
  for(int i=0; i<m1->Rows(); i++) {
    for(int j=0; j<m2->Cols(); j++) {
      temp=0;
      for(int k=0; k<m1->Cols(); k++) {
        temp ^= m1->Val(i, k) & m2->Val(k, j);
      }
      res->Set(i, j, temp+'0');
    }
  }
  return res;
}
/**
 * This creates a new bit-matrix composed of the specified rows of the 
 * given bit-matrix. It is ok to repeat entries in rows. However, if 
 * rows is empty or contains bad indices, return NULL.
 * @param  m    bitmatrix pointer
 * @param  rows vector of indices of rows to keep
 * @return      subsection of m, unless empty or bad indices.
 */
Bitmatrix *Sub_Matrix(Bitmatrix *m, vector <int> &rows)
{
  if(rows.empty()) return NULL;
  for(int row : rows)
    if((row < 0) || (row >= m->Rows()))
      return NULL;
  int i=0;
  Bitmatrix *res = new Bitmatrix(rows.size(), m->Cols());
  for(int row : rows) {
    for(int j=0; j<m->Cols(); j++) {
      res->Set(i, j, m->Val(row, j));
    }
    i++;
  }
  return res;
}
/**
 * Create and return the inverse of a1. To do this, you should also use 
 * the Swap_Rows() and R1_Plus_Equals_R2() methods. I'll go into more 
 * detail on how to invert a bit-matrix below. If a1 is not square or 
 * not invertible, return NULL.
 * @param  m bitmatrix pointer
 * @return   inverted bitmatrix or null if there's an issue
 */
Bitmatrix *Inverse(Bitmatrix *m)
{
  // not square or not invertible
  // identity matrix: only one 1 in each row
  return NULL;
}