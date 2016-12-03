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

#include "search.hpp"

 // TESTED
bool Search::findPair(vector<int> cards) {

	for (int i = 0; i < cards.size(); i++) {

		if (i >= 1 && cards[i] == cards[i - 1]) {

			return true;
		}
	}
	return false;
}

// TESTED
bool Search::findTwoPair(vector<int> cards) {

	int firstPair = 0;

	for (int i = 0; i < cards.size(); i++) {

		if (i >= 1 && cards[i] == cards[i - 1]) {

			firstPair = cards[i];
			break;

		}
	}

	for (int i = 0; i < cards.size(); i++) {

		if (i >= 1 && cards[i] != firstPair
			&& cards[i] == cards[i - 1]) {

			return true;
		}
	}

	return false;
}

// TESTED
bool Search::findThree(vector<int> cards) {

	for (int i = 0; i < cards.size(); i++) {
		if (i >= 2 && cards[i] == cards[i - 1]
			&& cards[i - 1] == cards[i - 2]) {
			return true;
		}
	}
	return false;
}

// TESTED
bool Search::findStraight(vector<int> cards) {

	vector<int> uniqueHolder;

	for (int i = 0; i < cards.size(); i++) {
		if (find(uniqueHolder.begin(), uniqueHolder.end(), cards[i]) != uniqueHolder.end()) {
			continue;
		}
		else {
			uniqueHolder.push_back(cards[i]);
		}
	}

	for (int i = 0; i < uniqueHolder.size(); i++) {
		if (i >= 4 &&
			uniqueHolder[i] == uniqueHolder[i - 1] + 1 &&
			uniqueHolder[i] == uniqueHolder[i - 2] + 2 &&
			uniqueHolder[i] == uniqueHolder[i - 3] + 3 &&
			uniqueHolder[i] == uniqueHolder[i - 4] + 4) {
			return true;
		}
	}
	return false;
}

// TESTED
bool Search::findFlush(vector<int> colors) {

	int spades = 0;
	int hearts = 0;
	int diams = 0;
	int club = 0;

	for (int i = 0; i < colors.size(); i++) {

		switch (colors[i]) {
		case 0:
			spades += 1;
			break;
		case 1:
			hearts += 1;
			break;
		case 2:
			diams += 1;
			break;
		case 3:
			club += 1;
			break;
		default:
			break;
		}
	}

	if (spades >= 5 || hearts >= 5 || diams >= 5 || club >= 5)
		return true;
	else
		return false;
}

// TESTED
bool Search::findFull(vector<int> cards) {

	bool pairFound = false;
	bool threeFound = false;

	int threeNum = 0;

	for (int i = 0; i < cards.size(); i++) {
		if (i >= 2 && cards[i] == cards[i - 1]
			&& cards[i - 1] == cards[i - 2]) {
			threeNum = cards[i];
			threeFound = true;
			break;
		}
	}

	for (int i = 0; i < cards.size(); i++) {
		if (i >= 1 && cards[i] != threeNum
			&& cards[i] == cards[i - 1]) {
			pairFound = true;
			break;
		}
	}

	if (pairFound && threeFound)
		return true;
	else
		return false;
}

// TESTED
bool Search::findFourKind(vector<int> cards) {

	for (int i = 0; i < cards.size(); i++) {
		if (i >= 3 && cards[i] == cards[i - 1]
			&& cards[i - 1] == cards[i - 2]
			&& cards[i - 2] == cards[i - 3]) {
			return true;
		}
	}
	return false;
}

// TESTED
bool Search::findStraightFlush(vector<int> cards, vector<int> colors) {

	int spades = 0;
	int hearts = 0;
	int diams = 0;
	int club = 0;

	vector<int> spadesCards;
	vector<int> heartsCards;
	vector<int> diamsCards;
	vector<int> clubCards;

	for (int i = 0; i < colors.size(); i++) {

		switch (colors[i]) {
		case 0:
			spades += 1;
			spadesCards.push_back(cards[i]);
			break;
		case 1:
			hearts += 1;
			heartsCards.push_back(cards[i]);
			break;
		case 2:
			diams += 1;
			diamsCards.push_back(cards[i]);
			break;
		case 3:
			club += 1;
			clubCards.push_back(cards[i]);
			break;
		default:
			break;
		}
	}

	if (spades >= 5) {
		if (straigthFlushVerifier(cards, spadesCards))
			return true;
	}
	else if (hearts >= 5) {
		if (straigthFlushVerifier(cards, heartsCards))
			return true;
	}
	else if (diams >= 5) {
		if (straigthFlushVerifier(cards, diamsCards))
			return true;
	}
	else if (club >= 5) {
		if (straigthFlushVerifier(cards, clubCards))
			return true;
	}

	return false;
}

bool Search::straigthFlushVerifier(vector<int> cards, vector<int> colorCards) {
	vector<int> uniqueHolder;

	for (int i = 0; i < cards.size(); i++) {
		if (find(uniqueHolder.begin(), uniqueHolder.end(), colorCards[i]) != uniqueHolder.end()) {
			continue;
		}
		else {
			uniqueHolder.push_back(cards[i]);
		}
	}

	for (int i = 0; i < uniqueHolder.size(); i++) {
		if (i >= 4 &&
			uniqueHolder[i] == uniqueHolder[i - 1] + 1 &&
			uniqueHolder[i] == uniqueHolder[i - 2] + 2 &&
			uniqueHolder[i] == uniqueHolder[i - 3] + 3 &&
			uniqueHolder[i] == uniqueHolder[i - 4] + 4) {
			return true;
		}
	}
}

// TESTED
bool Search::findRoyalFlush(vector<int> cards, vector<int> colors) {

	int spades = 0;
	int hearts = 0;
	int diams = 0;
	int club = 0;

	vector<int> spadesCards;
	vector<int> heartsCards;
	vector<int> diamsCards;
	vector<int> clubCards;

	int resultCounter = 0;

	int royal[5] = { 8,9,10,11,12 };

	for (int i = 0; i < colors.size(); i++) {

		switch (colors[i]) {
		case 0:
			spades += 1;
			spadesCards.push_back(cards[i]);
			break;
		case 1:
			hearts += 1;
			heartsCards.push_back(cards[i]);
			break;
		case 2:
			diams += 1;
			diamsCards.push_back(cards[i]);
			break;
		case 3:
			club += 1;
			clubCards.push_back(cards[i]);
			break;
		default:
			break;
		}
	}

	if (spades >= 5) {
		royalFlushVerifier(royal, resultCounter, cards, spadesCards);
	}
	else if (hearts >= 5) {
		royalFlushVerifier(royal, resultCounter, cards, heartsCards);
	}
	else if (diams >= 5) {
		royalFlushVerifier(royal, resultCounter, cards, diamsCards);
	}
	else if (club >= 5) {
		royalFlushVerifier(royal, resultCounter, cards, clubCards);
	}

	if (resultCounter >= 5)
		return true;
	else
		return false;
}

void Search::royalFlushVerifier(int royal[5], int& resultCounter, vector<int> cards, vector<int> colorCards) {
	vector<int> uniqueHolder;

	for (int i = 0; i < cards.size(); i++) {
		if (find(uniqueHolder.begin(), uniqueHolder.end(), colorCards[i]) != uniqueHolder.end()) {
			continue;
		}
		else {
			uniqueHolder.push_back(cards[i]);
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < uniqueHolder.size(); j++) {
			if (royal[i] == uniqueHolder[j]) {
				resultCounter += 1;
				break;
			}
		}
	}
}