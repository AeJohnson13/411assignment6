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
#include <memory> 
using std::shared_ptr;
using std::make_shared; 
#include <vector>
using std::vector;
#include <utility>
using std::pair;
#include <queue>
using std::priority_queue;


// compareNodes
// based on CmpEdgePtrs found here -> https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c
struct compareNodes
{
    bool operator()(const shared_ptr<HuffCode> a, const shared_ptr<HuffCode> b) const
    {
        return a->_freq > b->_freq;
    }
};

void HuffCode::setWeights(const unordered_map<char, int> & theweights) 
{
     priority_queue<shared_ptr<HuffCode>, vector<shared_ptr<HuffCode>>, compareNodes> HuffQueue;

     for (auto iter = theweights.begin(); iter != theweights.end(); iter++)
     {
      
        HuffQueue.push(make_shared<HuffCode>(string(1, iter->first), iter-> second));
     }

     while(HuffQueue.size() > 1)
     {
        auto left = HuffQueue.top();
        HuffQueue.pop();
        auto right = HuffQueue.top();
        HuffQueue.pop();

        int newFreq = left->_freq + right ->_freq;
        string newData = left->_data + right ->_data;

        shared_ptr<HuffCode> parentNode = make_shared<HuffCode>(newData, newFreq);
        parentNode->_left = left;
        parentNode->_right = right;

        HuffQueue.push(parentNode);
    }

    auto final = HuffQueue.top();
    _data = final->_data,
    _freq = final->_freq,
    _left = final->_left,
	_right = final->_right;
}

void HuffCode::Traverse(unordered_map<char, string> & dict, string code) const
{
    if(_left != nullptr)
    {
        code = code + "0";
        _left->Traverse(dict, code);
    }
    if(_right != nullptr)
    {
        code = code + "1";
        _right->Traverse(dict, code);
    }
    if(_right == nullptr && _left == nullptr){
        char key = _data[0];
        pair<char, string> newEntry = {key, code};
        dict.insert(newEntry);
    }
}

string HuffCode::encode(const string & text) const
{
    unordered_map<char, string> dict;
    Traverse(dict, "");

    string fullCode = "";
    for(auto key : text){
        auto charCode = dict.find(key)->second;
        fullCode = fullCode + charCode;
    }
    return fullCode;
}


string HuffCode::decode(const string & codestr) const
{
auto root = *this;
string decodedString = "";
auto currNode = root;

for(auto codeBit : codestr)
    if(currNode._left == nullptr && currNode._right == nullptr)
    {
        decodedString = decodedString + currNode._data;
        currNode = root;
    }
    else if(codeBit == '0')
    {
        currNode = *currNode._left;
    }
     else if(codeBit == '1')
    {
        currNode = *currNode._right;
    }
    return decodedString;
}
