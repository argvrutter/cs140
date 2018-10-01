#include "hash140.h"
#include <sstream>
/**
 * Author: Aiden Rutter
 * CS140 Lab4: Hashing Stuff
 * Description: Implement methods in hash140.h
 */

HashTable::HashTable(int table_size, string function, string collision)
{
    Fxn = function == "XOR";
    Coll = collision == "Double";
    keys.resize(table_size);
    vals.resize(table_size);
      
}

int XOR(string &key)
{
    // splits
}

int Last7(string &key)
{
    string last7;
    int h;
    if(key.size() > 7)
    {
        last7 = key.substr(key.size() - 7, 7);
    }
    else
    {
        last7 = key;
    }
    istringstream sin(last7);
    sin >> hex >> h;
    return h;
}

void HashTable::Add_Hash(string &key, string &val)
{
    // Last7: treats last 7 digits of hash string as a number in hexadecimal.
    // if fewer than 7, treat last 7 as hex.
      
}

string HashTable::Find(string &key)
{

}

void HashTable::Print()
{

}

int HashTable::Total_Probes()
{

}

