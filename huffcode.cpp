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

bool greaterThan(const pair<char, int>& a,
                 const pair<char, int>& b)
{
    return a.second > b.second;
}

void HuffCode::setWeights(const unordered_map<char, int> & theweights)
{
    vector<pair<char, int>> characters;
     for (auto iter = theweights.begin(); iter != theweights.end(); iter++)
     {
        characters.push_back(*iter);
     }
    sort(characters.begin(), characters.end(), greaterThan);
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

