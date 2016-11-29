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

#define _CRT_SECURE_NO_WARNINGS 1 

#include <thread>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <string>

#include "data.hpp"
#include "gamemech.hpp"
#include "generator.hpp"

using namespace std;

const short numberOfCards = 5;
const short maxRandom = 51;

Score myScore;
Generator generator;
GameMech game;

vector<Card> resultCards;

extern "C" __declspec(dllexport)  void  __cdecl getResults(char* buf) {

	game.clearGameResults();
	resultCards.clear();

	resultCards = generator.rollTable(maxRandom, numberOfCards);

	game.verifyResult(resultCards);

	unsigned int nothing = game.vectorSearch(Combo::Nothing, myScore);
	unsigned int pairs = game.vectorSearch(Combo::Pair, myScore);
	unsigned int twopairs = game.vectorSearch(Combo::TwoPairs, myScore);
	unsigned int three = game.vectorSearch(Combo::ThreeKind, myScore);
	unsigned int straight = game.vectorSearch(Combo::Straight, myScore);
	unsigned int flush = game.vectorSearch(Combo::Flush, myScore);
	unsigned int full = game.vectorSearch(Combo::Full, myScore);
	unsigned int fourkinds = game.vectorSearch(Combo::FourKind, myScore);
	unsigned int straightflush = game.vectorSearch(Combo::StraightFlush, myScore);
	unsigned int royalflush = game.vectorSearch(Combo::RoyalFlush, myScore);

	Score returnSCore = myScore;
	string result = myScore.returnString();

	strcpy(buf, result.c_str());
}

extern "C" __declspec(dllexport)  void  __cdecl gendeck() {

	myScore.clear();
	generator.createDeck();
}

