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
// For std::unique_ptr, std::make_unique

// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used
    
    
    // 2-param ctor
	// _data is set to given data
	// _left and _right are set to nullptr
	// No-Throw Guarantee 
	HuffCode(const std::string & data, const int & freq)             
		:_data(data),
        _freq(freq),
		_left(nullptr),
		_right(nullptr)
    {}
// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

    bool operator<(const HuffCode& other) const;

// ***** HuffCode: data members *****
private:
    std::string _data;  //Data for node
    int _freq;          //Frequency for node
    std::unique_ptr<HuffCode> _left;    //Ptr to left node 
	std::unique_ptr<HuffCode> _right;   //Ptr to right node
};  // End class HuffCode

#endif //#ifndef FILE_HUFFCODE_HPP_INCLUDED

