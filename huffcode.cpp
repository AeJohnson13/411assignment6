// huffcode.cpp
// Alex Johnson
// 2025-11-19
//
// For CS 411 Fall 2025
// Assignment 6, Exercise A
// Source for class HuffCode

#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <algorithm>
using std::sort;
#include <memory> 
using std::unique_ptr; 
using std::make_unique;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
#include <queue>
using std::priority_queue;
#include <functional>
using std::greater;

void HuffCode::setWeights(const unordered_map<char, int> & theweights) 
{
     priority_queue<HuffCode, vector<HuffCode>, greater<HuffCode>> HuffQueue;

     for (auto iter = theweights.begin(); iter != theweights.end(); iter++)
     {
        HuffCode newNode = HuffCode(string(1, iter->first), iter-> second);
     }

     while(HuffQueue.size() > 1)
     {
        HuffCode nodeA = HuffQueue.top();
        HuffQueue.pop();
        HuffCode nodeB = 
     }

}


string HuffCode::encode(const string & text) const
{
    // TODO: WRITE THIS!!!
    return "";  // DUMMY
}


string HuffCode::decode(const string & codestr) const
{
    // TODO: WRITE THIS!!!
    return "";  // DUMMY
}

bool HuffCode::operator<(const HuffCode& other) const {
        // Example: sort by x, break ties with y
        return _freq < other._freq;
    }