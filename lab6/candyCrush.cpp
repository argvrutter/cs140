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
// constructor 
candyCrush::candyCrush(string inputFile)
{
    string line, word;
    score=0;
    int seed, temp, sum=0, flavor, seqLen, remaining, lineNum=3;
    vector<string> words;
    ifstream fin; // not a huge fan of C++ file IO, look at this mess
    fin.open(inputFile, std::ifstream::in);
    if(!fin.is_open()) {
		cerr << inputFile << ": No such file or directory" << endl;
		exit(-1);
	}
    // parse seed & row length
    getline(fin, line);
    istringstream sin(line);
    while(sin >> word) words.push_back(word);
    if(words.size() != 2) cerr << "x2d";
    sin.clear();
    sin.str(words[0]);
    sin >> seed;
    if(sin.bad() || seed == 0) {
        cerr << "line 1: Bad seed for the random number generator" << endl;
        cerr << "	erroneous input was: " << words[0] << endl;
		exit(-1);
    }
    else if(sin.good()){} // C++ is heretical language confirmed, burn at stake 

    // pass seed to srand function
    srand(seed);
    sin.clear();
    sin.str(words[1]);
    if(!(sin >> rowLength)) {
		cerr << "line 1: Bad row length--must be an integer" << endl;
		cerr << "	erroneous input was: " << words[1] << endl;
		exit(-1);
	}
	
    if(rowLength < 1 || rowLength > 100) {
		cerr << "line 1: The row length you entered, " << rowLength;
		cerr << ", must be from 1-100" << endl;
		exit(-1);
	}
    // store flavors
    getline(fin, line);
    sin.clear();
    sin.str(line);
    words.clear();
    while(sin >> word) flavors.push_back(word);
    // store probabilities into probabilities vector
    // store points into points vector
    while(true) {
        getline(fin, line);
        if(fin.eof()) break;
        if(fin.bad()) cerr << "x4d";
        sin.clear();
        sin.str(line);
        words.clear();
        while(sin >> word) words.push_back(word);
        if(words.size() != 2) cerr << "x5d";
        sin.clear();
        sin.str(words[0]);
        if(!(sin >> temp)) {
			cerr << "line " << lineNum <<  ": Probability and points for this sequence must be non-negative integers" << endl;
			cerr << "	erroneous input was: " << words[0] << endl;
			exit(-1);
		}
        if(temp < 0 || temp > 100) {
			cerr << "Line " << lineNum << ": The probability you entered, " << temp << ", must be 0-100" << endl;
			exit(-1);
		}
        sum += temp;
        probabilities.push_back(temp);
        sin.clear();
        sin.str(words[1]);
		if(!(sin >> temp)) {
			cerr << "line " << lineNum <<  ": Probability and points for this sequence must be non-negative integers" << endl;
			cerr << "	erroneous input was: " << words[1] << endl;
			exit(-1);
		}
		if(temp < 0) {
			cerr << "Line " << lineNum << ": points, " << temp << ", is negative. It must be non-negative" << endl;
			exit(-1);
		}
        points.push_back(temp);
		lineNum++;
    }
    // check that probabilities add to 100 
    // & there are rowLength entries
    if(sum < 100)
    {
        cerr << "The probabilities you entered must sum to 100 but their sum was " << sum << endl;
        exit(-1);
    }
    if(sum > 100) { 
        cerr << "Line 27: The cumulative probability exceeds 100. It must be exactly 100 when all probabilities have been entered" << endl;
        exit(-1);
    }
    if(points.size() != rowLength || probabilities.size() != rowLength) { 
        cerr << "You entered "<< points.size() <<" pairs of probabilities ";
        cerr << "and points. You must enter the same number of pairs as";
        cerr << " the rowLength, which is " << rowLength << endl;
        exit(-1);
    }
    // make probabilies cumulative
    for(int i=1; i<rowLength; i++) probabilities[i] += probabilities[i-1];
    // add the candii ^0^
    // choose a candy flavor
    while(candy.size() < rowLength) {
        flavor = rand() % flavors.size();
        // choose length of candy sequence
        seqLen = rand() % 100;
        for(int i=0; i<rowLength; i++) {
            if(seqLen < probabilities[i]) {
                seqLen = i+1;
                break;
            }
        }
        remaining = rowLength - candy.size();
        if(seqLen < remaining) remaining = seqLen;
        for(int i=0; i<remaining; i++) candy.push_back(flavors[flavor]);
    }
    // generate a flavor and a sequence length, 
    // add that many flavors to the end of the list, 
    // and repeat until the row is full
}
// cerr << "xd"s length of candy crush row
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
        if(i == 7) {
            cout << endl;
            i = 0;
            continue;
        }
        i++;
    }
    cout << endl;
}
/**
 * choice is an int from 0 - rowlength-1 indicating which candy flavor the player
 * selected. 
 */ 
int candyCrush::play(int choice)
{
    int scr, seqLen=0, flavor, remaining, prob;
    string cand;
    // Find the candy list element corresponding to the player's 
    // choice.
    auto lit = candy.begin();
    advance(lit, choice);
    cand = *lit;
    // compute sequence size
    // backwards pass
    while(*lit == cand) lit--;
    lit++;
    auto beg = lit;
    // forward pass
    while(*lit == cand) {
        lit++;
        seqLen++;
    }
    auto end = lit;
    // Delete the strings in that sequence from the candy list
    candy.erase(beg, end);
    // generate and append more candies.
    // add the candii ^0^
    // choose a candy flavor
    while(candy.size() < rowLength) {
        flavor = rand() % flavors.size();
        // choose length of candy sequence
        prob = rand() % 100;
        for(int i=0; i<rowLength; i++) {
            if(prob < probabilities[i]) {
                prob = i+1;
                break;
            }
        }
        // if(!set) seqLen = rowLength;
        remaining = rowLength - candy.size();
        if(prob < remaining) remaining = prob;
        for(int i=0; i<remaining; i++) candy.push_back(flavors[flavor]);
    }
    score += points[seqLen-1];
    return points[seqLen-1];
}
// returns the score
int candyCrush::getScore()
{
    return score;
}
