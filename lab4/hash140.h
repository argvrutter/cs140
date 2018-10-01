#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HashTable {
  public:
    // function can be either "Last7" or "XOR". collision can be either
    // "Linear" or "Double"
    HashTable(int table_size, string function, string collision);
    // Adds given key/value pair to hash table, assuming key is free
    // Errors if: no more room in hash table, or key can't go into table
    void Add_Hash(string &key, string &val);
    // Finds key and returns value
    string Find(string &key);
    // Prints all non-empty slots in the hash table, one per line, index,
    // right justified, and padded to five characters. Key & value, 
    // separated by a space
    void Print();
    // Calculates how may probes it takes to find for each key in the table.
    int Total_Probes();
  protected:
    vector <string> keys;
    vector <string> vals; 
    int nkeys; // number of keys in the hash table
    int Fxn;   // which hash function is being used
    int Coll;  
    int tmp;
};

