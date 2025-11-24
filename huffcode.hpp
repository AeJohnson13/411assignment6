// huffcode.hpp 
// Alex Johnson
// 2025-11-19
//
// For CS 411 Fall 2025
// Assignment 6, Exercise A
// Header for class HuffCode
// Based on the huffcode.hpp skeleton by Glenn G. Chappell

#ifndef FILE_HUFFCODE_HPP_INCLUDED
#define FILE_HUFFCODE_HPP_INCLUDED

#include <string>
// For std::string
#include <unordered_map>
// For std::unordered_map;
#include <memory> 
// For std::shared_ptr
// For std::enable_shared_from_this


//Forward Decleration so that compareNodes can be declared as friend later;
struct compareNodes;

// Class HuffTree
// class for huffman code tree nodes
class HuffTree
{
public:
    friend struct compareNodes;
    friend class HuffCode;
 // 2-param ctor
	// _data is set to given data
    // _freq is set to give freq
	// _left and _right are set to nullptr
	// No-Throw Guarantee 
	HuffTree(const char & data, const int & freq)             
		:_data(data),
       _freq(freq),
		_left(nullptr),
		_right(nullptr)
    {
        //Left Empty Intentionally 
    }
    
    // default ctor
	// _data is set to empty string
    // _freq is set to zero 
	// _left and _right are set to nullptr
	// No-Throw Guarantee 
    HuffTree()
        :_data(' '),
       _freq(0),
		_left(nullptr),
		_right(nullptr)
    {
        //Left Empty Intentionally 
    }
    
public: 

    void Traverse(std::unordered_map<char, std::string> & dict, std::string code) const;

private:
    char _data;  //Data for node
    int _freq;          //Frequency for node
    std::shared_ptr<HuffTree> _left;    //Ptr to left node 
	std::shared_ptr<HuffTree> _right;   //Ptr to right node
}; // End class HuffTree


// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode
 {
// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated copy ctor, copy =, dctor used
    
// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

// ***** HuffCode: data members *****
private:
    std::shared_ptr<HuffTree> _root;
};  // End class HuffCode

#endif //#ifndef FILE_HUFFCODE_HPP_INCLUDED

