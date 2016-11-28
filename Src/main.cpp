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

#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <iomanip>

#include "data.hpp"
#include "gamemech.hpp"
#include "generator.hpp"

using namespace std;

const int numberOfCards = 5;
const int maxRandom = 51;
const int precPoint = 5;

long long gameCounter = 0;

void play();
void displayResult();

bool done = false;

Score myScore;
Generator generator;
GameMech game;

vector<Card> resultCards;

int main() {

	generator.createDeck();

	thread t(displayResult);
	t.detach();

	cout << "[^] Started with " << numberOfCards << " cards!" << endl << endl;

	play();

	return 0;
}

void displayResult() {
	while (true) {
		Sleep(1000);

		system("CLS");

		int nothing = game.vectorSearch(Combo::Nothing, myScore);
		int pairs = game.vectorSearch(Combo::Pair, myScore);
		int twopairs = game.vectorSearch(Combo::TwoPairs, myScore);
		int three = game.vectorSearch(Combo::ThreeKind, myScore);
		int straight = game.vectorSearch(Combo::Straight, myScore);
		int flush = game.vectorSearch(Combo::Flush, myScore);
		int full = game.vectorSearch(Combo::Full, myScore);
		int fourkinds = game.vectorSearch(Combo::FourKind, myScore);
		int straightflush = game.vectorSearch(Combo::StraightFlush, myScore);
		int royalflush = game.vectorSearch(Combo::RoyalFlush, myScore);

		double nothingPrc = nothing / static_cast<double>(myScore.getTotal()) * 100;
		double pairsPrc = pairs / static_cast<double>(myScore.getTotal()) * 100;
		double twoPairPrc = twopairs / static_cast<double>(myScore.getTotal()) * 100;
		double threePrc = three / static_cast<double>(myScore.getTotal()) * 100;
		double straightPrc = straight / static_cast<double>(myScore.getTotal()) * 100;
		double flushPrc = flush / static_cast<double>(myScore.getTotal()) * 100;
		double fullPrc = full / static_cast<double>(myScore.getTotal()) * 100;
		double fourKindsPrc = fourkinds / static_cast<double>(myScore.getTotal()) * 100;
		double straightFlushPrc = straightflush / static_cast<double>(myScore.getTotal()) * 100;
		double royalFlushPrc = royalflush / static_cast<double>(myScore.getTotal()) * 100;

		float total = nothingPrc + pairsPrc + twoPairPrc + threePrc + straightPrc + flushPrc + fullPrc + fourKindsPrc + straightFlushPrc + royalFlushPrc;

		cout << "[?] Game #" << myScore.getTotal() << " Done \t->" << setiosflags(ios::fixed) << setprecision(0) << total << "%" << endl;
		cout << "[?] Nothing ->" << nothing << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << nothingPrc << "%" << endl;
		cout << "[?] Pairs ->" << pairs << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << pairsPrc << "%" << endl;
		cout << "[?] TwoPairs ->" << twopairs << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << twoPairPrc << "%" << endl;
		cout << "[?] ThreeKinds ->" << three << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << threePrc << "%" << endl;
		cout << "[?] Straights ->" << straight << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << straightPrc << "%" << endl;
		cout << "[?] Flushes ->" << flush << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << flushPrc << "%" << endl;
		cout << "[?] Fulls ->" << full << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << fullPrc << "%" << endl;
		cout << "[?] FourKinds ->" << fourkinds << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << fourKindsPrc << "%" << endl;
		cout << "[?] StraightFlushes ->" << straightflush << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << straightFlushPrc << "%" << endl;
		cout << "[?] RoyalFlushes ->" << royalflush << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << royalFlushPrc << "%" << endl << endl;

		while (!done) {
			Sleep(0.0001f);
			continue;
		}

		game.clearGameResults();
	}
}

void play() {
	while (true) {

		done = false;

		Sleep(0.001f);

		resultCards.clear();

		resultCards = generator.rollTable(maxRandom, numberOfCards);

		game.verifyResult(resultCards);

		done = true;
	}
}
