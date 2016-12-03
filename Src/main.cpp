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

	auto dTime = static_cast<DWORD>(time);

#ifdef __linux__
	usleep(dTime * 1000);
#elif __APPLE__
	usleep(dTime * 1000);
#elif _WIN32
	Sleep(dTime);
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

		game.vectorSearch(myScore);

		auto tmpScore = myScore;

		auto nothingPrc = tmpScore.nothing / static_cast<float>(tmpScore.getTotal()) * 100;
		auto pairsPrc = tmpScore.pair / static_cast<float>(tmpScore.getTotal()) * 100;
		auto twoPairPrc = tmpScore.twopair / static_cast<float>(tmpScore.getTotal()) * 100;
		auto threePrc = tmpScore.three / static_cast<float>(tmpScore.getTotal()) * 100;
		auto straightPrc = tmpScore.straight / static_cast<float>(tmpScore.getTotal()) * 100;
		auto flushPrc = tmpScore.flush / static_cast<float>(tmpScore.getTotal()) * 100;
		auto fullPrc = tmpScore.full / static_cast<float>(tmpScore.getTotal()) * 100;
		auto fourKindsPrc = tmpScore.four / static_cast<float>(tmpScore.getTotal()) * 100;
		auto straightFlushPrc = tmpScore.straightflush / static_cast<float>(tmpScore.getTotal()) * 100;
		auto royalFlushPrc = tmpScore.royal / static_cast<float>(tmpScore.getTotal()) * 100;

		auto total = nothingPrc + pairsPrc + twoPairPrc + threePrc + straightPrc + flushPrc + fullPrc + fourKindsPrc + straightFlushPrc + royalFlushPrc;

		cout << "[?] Game #" << tmpScore.getTotal() << " Done ->" << setiosflags(ios::fixed) << setprecision(0) << total << "%" << endl;
		cout << "[?] Nothing ->" << tmpScore.nothing << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << nothingPrc << "%" << endl;
		cout << "[?] Pairs ->" << tmpScore.pair << " ->" << pairsPrc << "%" << endl;
		cout << "[?] TwoPairs ->" << tmpScore.twopair << " ->" << twoPairPrc << "%" << endl;
		cout << "[?] ThreeKinds ->" << tmpScore.three << " ->" << threePrc << "%" << endl;
		cout << "[?] Straights ->" << tmpScore.straight << " ->" << straightPrc << "%" << endl;
		cout << "[?] Flushes ->" << tmpScore.flush << " ->" << flushPrc << "%" << endl;
		cout << "[?] Fulls ->" << tmpScore.full << " ->" << fullPrc << "%" << endl;
		cout << "[?] FourKinds ->" << tmpScore.four << " ->" << fourKindsPrc << "%" << endl;
		cout << "[?] StraightFlushes ->" << tmpScore.straightflush << " ->" << straightFlushPrc << "%" << endl;
		cout << "[?] RoyalFlushes ->" << tmpScore.royal << " ->" << royalFlushPrc << "%" << endl;

		while (!done) {
			crossSleep(0.01f);
		}

		game.clearGameResults();
	}
}


void play() {
	while (true) {

		done = false;

		resultCards.clear();

		resultCards = generator.rollTable(maxRandom, numberOfCards);

		game.verifyResult(resultCards);

		done = true;

		crossSleep(0.1f);
	}
}
