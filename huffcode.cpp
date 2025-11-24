// huffcode.cpp
// Alex Johnson
// 2025-11-19
//
// For CS 411 Fall 2025
// Assignment 6, Exercise A
// Source for class HuffCode

#include "huffcode.hpp" // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <memory>
using std::make_shared;
using std::shared_ptr;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
#include <queue>
using std::priority_queue;


// compareNodes
// based on CmpEdgePtrs found here -> https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c
// Stand-alone functor class
//  implements > operator for HuffTree._freq   
//  used for putting shared_ptr<HuffTree> into a min heap priority queue   
struct compareNodes
{
    bool operator()(const shared_ptr<HuffTree> a, const shared_ptr<HuffTree> b) const
    {
        return a->_freq > b->_freq;
    }
};

// setWeigts
// member function for HuffCode
// builds a HuffTree using the chars
// and weights given in theweights
void HuffCode::setWeights(const unordered_map<char, int> &theweights)
{
    priority_queue<shared_ptr<HuffTree>, vector<shared_ptr<HuffTree>>, compareNodes> HuffQueue;

    for (auto iter = theweights.begin(); iter != theweights.end(); iter++)
    {
        HuffQueue.push(make_shared<HuffTree>(iter->first, iter->second));
    }

    while (HuffQueue.size() > 1)
    {
        auto left = HuffQueue.top();
        HuffQueue.pop();
        auto right = HuffQueue.top();
        HuffQueue.pop();

        int newFreq = left->_freq + right->_freq;

        shared_ptr<HuffTree> parentNode = make_shared<HuffTree>(' ', newFreq);
        parentNode->_left = left;
        parentNode->_right = right;

        HuffQueue.push(parentNode);
    }
    auto final = HuffQueue.top();
    _root = final;
}
// Traverse
// member function for HuffTree
// does an inorder traverse of a hufftree
// stores codes in given unordered map dict
// 
// used in HuffCode::encode 
//
void HuffTree::Traverse(unordered_map<char, string> &dict, string code) const
{
    if (_left != nullptr)
    {
        _left->Traverse(dict, code + "0");
    }
    if (_right != nullptr)
    {
        _right->Traverse(dict, code + "1");
    }
    if (_right == nullptr && _left == nullptr)
    {
        char key = _data;
        pair<char, string> newEntry = {key, code};
        dict[key] = code;
    }
}


// encode 
// member function for HuffCode
// takes a string and turns it into a
// bitstring encoded with HuffTree stored in HuffCode
string HuffCode::encode(const string &text) const
{
    unordered_map<char, string> dict;
    _root->Traverse(dict, "");

    string fullCode = "";
    for (auto key : text)
    {
        auto charCode = dict.find(key)->second;
        fullCode = fullCode + charCode;
    }
    return fullCode;
}


// decode 
// member function for HuffCode
// takes a bitstring and turns it into a
// string decoded with HuffTree with root stored in HuffCode
string HuffCode::decode(const string &codestr) const
{

    auto currNode = _root;

    string decodedString = "";

    for (auto codeBit : codestr)
    {
        if (codeBit == '0')
        {
            currNode = currNode->_left;
        }
        else if (codeBit == '1')
        {
            currNode = currNode->_right;
        }
        if (currNode->_left == nullptr && currNode->_right == nullptr)
        {
            decodedString = decodedString + currNode->_data;
            currNode = _root;
        }
    }
    return decodedString;
}
