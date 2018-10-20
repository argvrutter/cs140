#include "candyCrush.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h> 
/**
 * Author: Aiden Rutter
 * CS140 Lab6 CandyCrush
 * Description: Implement candyCrush.h
 */
// constructor, 
candyCrush::candyCrush(string inputFile)
{
    string line, word;
    int seed, temp, sum=0, flavor, seqLen;
    vector<string> words;
    ifstream fin; // not a huge fan of C++ file IO, look at this mess
    fin.open(inputFile, std::ifstream::in);
    if(!fin.is_open()) return;
    // parse seed & row length
    getline(fin, line);
    istringstream sin(line);
    while(sin >> word) words.push_back(word);
    if(words.size() != 2) return;
    sin.str(words[0]);
    sin >> seed;
    // pass seed to srand function
    srand(seed);
    sin.str(words[1]);
    sin >> rowLength;
    if(rowLength < 1 || rowLength > 100) return;
    // store flavors
    getline(fin, line);
    sin.str(line);
    words.clear();
    while(sin >> word) flavors.push_back(word);
    // store probabilities into probabilities vector
    // store points into points vector
    while(true) {
        getline(fin, line);
        if(fin.eof()) break;
        if(fin.bad()) return;
        sin.str(line);
        words.clear();
        while(sin >> word) words.push_back(word);
        if(words.size() != 2) return;
        sin.str(words[0]);
        sin >> temp;
        if(temp < 1 || temp > 100) return;
        sum += temp;
        probabilities.push_back(temp);
        sin.str(words[1]);
        sin >> temp;
        if(temp < 1 || temp > 100) return;
        points.push_back(temp);
    }
    // check that probabilities add to 100 
    // & there are rowLength entries
    if(sum != 100) return;
    if(points.size() != rowLength) return;
    if(probabilities.size() != rowLength) return;
    // make probabilies cumulative
    for(int i=1; i<rowLength; i++) probabilities[i] += probabilities[i-1];
    // choose a candy flavor
    flavor = rand() % flavors.size();
    // choose length of candy sequence
    seqLen = rand() % 100;
    for(int i=0; i<rowLength; i++) {
        if(seqLen < probabilities[i]) {
            seqLen = i+1;
            break;
        }
    }
    candy.assign(seqLen, flavors[flavor]);

}
// returns length of candy crush row
int candyCrush::getRowLength()
{
    return rowLength;
}
// prints candy crush row as 8 flavors per row, left justified, 10 chars wide.
void candyCrush::printCandy()
{
    int i=0;
    // BVZ says no more rangies :(
    for(auto lit = candy.begin(); lit !=candy.end(); lit++) {
        cout.width(10);
        cout << left << *lit; 
        if(i == 8) {
            cout << endl;
            i = 0;
            continue;
        }
        i++;
    }
}
/**
 * choice is an int from 0 - rowlength-1 indicating which candy flavor the player
 * selected. 
 */ 
int candyCrush::play(int choice)
{
    
}
// returns the score
int candyCrush::getScore()
{
    return score;
}
