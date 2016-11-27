/*
 The MIT License (MIT)
 Copyright (c) 2016 Andrey Lopukhov
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef data_hpp
#define data_hpp

struct Card{
    int suit;
    int num;
};

struct Score {
    int nothing = 0;
    int pair = 0;
    int twopair = 0;
    int three = 0;
    int straight = 0;
    int flush = 0;
    int full = 0;
    int four = 0;
    int straightflush = 0;
    int royal = 0;
};

enum class Combo { Nothing, Pair, TwoPairs, ThreeKind, Straight, Flush, Full, FourKind, StraightFlush, RoyalFlush };

#endif
