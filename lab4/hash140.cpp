#include "hash140.h"
#include <sstream>
#include <cstdio>
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
    tmp=0;
    nkeys=0;
}

int XOR(string &key)
{
    int i, hk, k;
    vector<string> hkeys;
    istringstream sin;
    // splits key into substrings of length 7
    for(i=0; i<key.size()-7; i+=7)
    {
        hkeys.push_back(key.substr(i, i+7));
    }
    hkeys.push_back(key.substr(i, key.size() - i));
    sin.str(hkeys[0]);
    sin >> hex >> hk;
    for(unsigned int j=1; j<hkeys.size(); j++)
    {
        sin.str(hkeys[i]);
        sin >> hex >> k;
        hk ^= k;
    }
    return hk;   
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
    int hi, hk, ts = keys.size(), i=0, h1, h2;
    if(nkeys >= ts) cerr << "Hash Table Full" << endl;
    if(Coll) // double hashing
    {
        // order of hash functions
        h1 = Fxn ? XOR(key) : Last7(key);
        h2 = Fxn ? Last7(key) : XOR(key);
        // bad double hashing check
        if(h2 % ts == 0)
        {
            // cerr << "Couldn't put " << key << " into the table" << endl;
            h2 = 1;
        }
        while(true)
        {
            tmp++;
            hk = (h1 + i*h2) % ts;
            if(keys[hk].empty()) break;
            i++;
        }
        hi = hk;
        
    }
    else // Linear hashing
    {
        hk = Fxn ? XOR(key) : Last7(key);
        while(true)
        {
            tmp++; // for total_probes
            if(keys[hk % ts].empty()) break;
            hk++;
        }
        hi = hk % ts;
    }
    keys[hi] = key;
    vals[hi] = val;
    nkeys++;
}

string HashTable::Find(string &key)
{

}

void HashTable::Print()
{
    for(int i=0; i<keys.size(); i++)
    {
        if(!(keys[i].empty()))
        {
            printf("%5d %s %s", i, keys[i], vals[i]);             
        }
    }
}

int HashTable::Total_Probes()
{

}

