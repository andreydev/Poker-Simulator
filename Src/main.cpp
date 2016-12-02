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

#ifdef __linux__
#include <unistd.h>
#elif __APPLE__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>

#include "data.hpp"
#include "gamemech.hpp"
#include "generator.hpp"

using namespace std;

const short numberOfCards = 5;
const short maxRandom = 52;
const short precPoint = 5;

void play();
void displayResult();

bool done = false;

Score myScore;
Generator generator;
GameMech game;

vector<Card> resultCards;

void crossSleep(float time) {
#ifdef __linux__
	usleep(time * 1000);
#elif __APPLE__
	usleep(time * 1000);
#elif _WIN32
	Sleep(time);
#endif
}

void crossClear() {
#ifdef __linux__
	system("clear");
#elif __APPLE__
	system("clear");
#elif _WIN32
	system("CLS");
#endif
}

int main() {
	generator.createDeck();

	thread t(displayResult);
	t.detach();

	cout << "[^] Started with " << numberOfCards << " cards!" << endl;

	play();

	return 0;
}

void displayResult() {
	while (true) {
		crossSleep(1000);

		crossClear();

		try {
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

			float nothingPrc = nothing / static_cast<float>(myScore.getTotal()) * 100;
			float pairsPrc = pairs / static_cast<float>(myScore.getTotal()) * 100;
			float twoPairPrc = twopairs / static_cast<float>(myScore.getTotal()) * 100;
			float threePrc = three / static_cast<float>(myScore.getTotal()) * 100;
			float straightPrc = straight / static_cast<float>(myScore.getTotal()) * 100;
			float flushPrc = flush / static_cast<float>(myScore.getTotal()) * 100;
			float fullPrc = full / static_cast<float>(myScore.getTotal()) * 100;
			float fourKindsPrc = fourkinds / static_cast<float>(myScore.getTotal()) * 100;
			float straightFlushPrc = straightflush / static_cast<float>(myScore.getTotal()) * 100;
			float royalFlushPrc = royalflush / static_cast<float>(myScore.getTotal()) * 100;

			float total = nothingPrc + pairsPrc + twoPairPrc + threePrc + straightPrc + flushPrc + fullPrc + fourKindsPrc + straightFlushPrc + royalFlushPrc;

			cout << "[?] Game #" << myScore.getTotal() << " Done ->" << setiosflags(ios::fixed) << setprecision(0) << total << "%" << endl;
			cout << "[?] Nothing ->" << nothing << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << nothingPrc << "%" << endl;
			cout << "[?] Pairs ->" << pairs << " ->" << pairsPrc << "%" << endl;
			cout << "[?] TwoPairs ->" << twopairs << " ->"  << twoPairPrc << "%" << endl;
			cout << "[?] ThreeKinds ->" << three << " ->" << threePrc << "%" << endl;
			cout << "[?] Straights ->" << straight << " ->" << straightPrc << "%" << endl;
			cout << "[?] Flushes ->" << flush << " ->" << flushPrc << "%" << endl;
			cout << "[?] Fulls ->" << full << " ->" << fullPrc << "%" << endl;
			cout << "[?] FourKinds ->" << fourkinds << " ->" << fourKindsPrc << "%" << endl;
			cout << "[?] StraightFlushes ->" << straightflush << " ->" << straightFlushPrc << "%" << endl;
			cout << "[?] RoyalFlushes ->" << royalflush << " ->" << royalFlushPrc << "%" << endl;

			while (!done) {
				crossSleep(0.01);
			}

			game.clearGameResults();
		}
		catch (const std::overflow_error& e) {
			cout << e.what();
		}
		catch (const std::runtime_error& e) {
			cout << e.what();
		}
		catch (const std::exception& e) {
			cout << e.what();
		}
	}
}

void play() {
	while (true) {
		done = false;

		try {
			resultCards.clear();

			resultCards = generator.rollTable(maxRandom, numberOfCards);

			game.verifyResult(resultCards);

			done = true;

		}
		catch (const std::overflow_error& e) {
			cout << e.what();
		}
		catch (const std::runtime_error& e) {
			cout << e.what();
		}
		catch (const std::exception& e) {
			cout << e.what();
		}

		crossSleep(0.1);
	}
}
