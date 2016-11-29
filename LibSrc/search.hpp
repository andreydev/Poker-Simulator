/*
 MIT License

 Copyright (c) 2016 Andrey Lopukhov

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef search_hpp
#define search_hpp

#include <vector>
#include <algorithm>

#include "data.hpp"

using namespace std;

class Search
{

public:
	// TODO: This should return a struct instead of using so many methods
	bool findPair(vector<int> cards);
	bool findTwoPair(vector<int> cards);
	bool findThree(vector<int> cards);
	bool findStraight(vector<int> cards);
	bool findFlush(vector<int> colors);
	bool findFull(vector<int> cards);
	bool findFourKind(vector<int> cards);
	bool findStraightFlush(vector<int> cards, vector<int> colors);
	bool findRoyalFlush(vector<int> cards, vector<int> colors);
};

#endif
