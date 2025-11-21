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
using std::move;
using std::pair;
#include <queue>
using std::priority_queue;

void HuffCode::setWeights(const unordered_map<char, int> & theweights) 
{
     priority_queue<unique_ptr<HuffCode>, vector<unique_ptr<HuffCode>>, compareNodes> HuffQueue;

     for (auto iter = theweights.begin(); iter != theweights.end(); iter++)
     {
      
        HuffQueue.push(make_unique<HuffCode>(string(1, iter->first), iter-> second));
     }

     while(HuffQueue.size() > 1)
     {
        auto left = move(HuffQueue.top()); 
        HuffQueue.pop();
        auto right = move(HuffQueue.top()); 
        HuffQueue.pop();

        int newFreq = nodeA->_freq + nodeB ->_freq;
        string newData = nodeA->_data + nodeB ->_data;

        unique_ptr<HuffCode> parentNode = make_unique<HuffCode>(newData, newFreq);
        //parentNode->_left = nodeA;
        //parentNode->_right = nodeB;

        HuffQueue.push(parentNode);
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



// compareNodes
// based on CmpEdgePtrs found here -> https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c
struct compareNodes
{
    bool operator()(const unique_ptr<HuffCode> a, const unique_ptr<HuffCode> b) const
    {
        return a->_freq > b->_freq;
    }
};