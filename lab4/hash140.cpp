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

unsigned int XOR(string &key)
{
    unsigned int i, hk, k;
    vector<string> hkeys;
    istringstream sin;
    // splits key into substrings of length 7
    for(int i=0; i<key.size() / 7; i++)
    {
        hkeys.push_back(key.substr(i*7, 7));
    }
    if(key.size() % 7 != 0)
    {
        hkeys.push_back(key.substr(7 * (key.size() / 7)));
    }

    sin.str(hkeys.at(0));
    sin >> hex >> hk;
    for(unsigned int j=1; j<hkeys.size(); j++)
    {
        sin.clear();
        sin.str(hkeys.at(j));
        sin >> hex >> k;
        hk ^= k;
    }
    return hk;
}

unsigned int Last7(string &key)
{
    string last7;
    unsigned int h;
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
    // if double hash prime, guarenteed within ts probes
    int hi, hk, ts = keys.size(), i=0, h1, h2;
    // check to see if table is full by searching whole thing
    if(nkeys >= ts) cerr << "Hash Table Full" << endl;
    h1 = Fxn ? XOR(key) : Last7(key);

    if(Coll) // double hashing
    {
        // order of hash functions
        // TODO: Don't calculate unless probe miss
        h2 = Fxn ? Last7(key) : XOR(key);
        // bad double hashing check
        if(h2 % ts == 0)
        {
            // cerr << "Couldn't put " << key << " into the table" << endl;
            h2 = 1;
        }
        while(true)
        {
            hk = (h1 + i*h2) % ts;
            if(keys.at(hk).empty()) break;
            i++;
        }
        hi = hk;

    }
    else // Linear hashing
    {
        hk = h1;
        while(true)
        {
            if(keys.at(hk % ts).empty()) break;
            hk++;
        }
        hi = hk % ts;
    }
    keys[hi] = key;
    vals[hi] = val;
    nkeys++;
}
// Broke :(
string HashTable::Find(string &key)
{
    unsigned long hk, ts = keys.size(), i=0, h1, h2;
    if(key.empty()) return "";
    if(Coll) // double hashing
    {
        // order of hash functions
        h1 = Fxn ? XOR(key) : Last7(key);
        // TODO: Don't calculate h2 unless probe miss
        h2 = Fxn ? Last7(key) : XOR(key);
        // bad double hashing check
        if(h2 % ts == 0)
        {
            cerr << "Couldn't put " << key << " into the table" << endl;
            h2 = 1;
        }
        for(int j=0; j<ts; j++)
        {
            hk = (h1 + i*h2) % ts;
            if(keys.at(hk).empty()) return "";
            if(keys.at(hk) == key) return vals.at(hk);
            i++;
            tmp++;
        }
        return "";
    }
    else // Linear hashing
    {
        hk = Fxn ? XOR(key) : Last7(key);
        for(int j=0; j<ts; j++)
        {
            if(keys.at(hk % ts).empty()) return "";
            if(keys.at(hk % ts) == key) return vals.at(hk % ts);
            hk++;
            tmp++;
        }
        return "";
    }
}

void HashTable::Print()
{
    for(unsigned int i=0; i<keys.size(); i++)
    {
        if(!(keys.at(i).empty()))
        {
            printf("%5d %s %s\n", i, keys.at(i).c_str(), vals.at(i).c_str());
        }
    }
}

int HashTable::Total_Probes()
{
    tmp =0;
    for(unsigned int i=0; i<keys.size(); i++)
    {
        Find(keys.at(i));
    }
    return tmp;
}
