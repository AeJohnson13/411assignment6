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


//debug includes
#include <iostream>
using std::cout;
using std::endl;
// compareNodes
// based on CmpEdgePtrs found here -> https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c
struct compareNodes
{
    bool operator()(const shared_ptr<HuffTree> a, const shared_ptr<HuffTree> b) const
    {
        //cout << "is " << a->_freq << " < " << b->_freq << endl;
        return a->_freq > b->_freq;
    }
};

void HuffCode::setWeights(const unordered_map<char, int> &theweights)
{
    priority_queue<shared_ptr<HuffTree>, vector<shared_ptr<HuffTree>>, compareNodes> HuffQueue;

    for (auto iter = theweights.begin(); iter != theweights.end(); iter++)
    {
        HuffQueue.push(make_shared<HuffTree>(string(1, iter->first), iter->second));
    }

    while (HuffQueue.size() > 1)
    {
        auto left = HuffQueue.top();
        //cout << left->_data << endl;
        HuffQueue.pop();
        auto right = HuffQueue.top();
        //cout << right->_data << endl;
        HuffQueue.pop();

        int newFreq = left->_freq + right->_freq;
        string newData = left->_data + right->_data;

        shared_ptr<HuffTree> parentNode = make_shared<HuffTree>(newData, newFreq);
        parentNode->_left = left;
        parentNode->_right = right;

        //cout << "made parent"<< newFreq << " : "<< newData << endl;
        HuffQueue.push(parentNode);
    }
    auto final = HuffQueue.top();
    _root = final;
}
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
        char key = _data[0];
        //cout << key << " : " << code << endl;
        pair<char, string> newEntry = {key, code};
        dict.insert(newEntry);
    }
}

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
