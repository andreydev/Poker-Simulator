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

#include "gamemech.hpp"

void GameMech::verifyResult(vector<Card> cardResults, Score& score) {

	vector<int> colors;
	vector<int> cards;

	for (auto i = 0; i < cardResults.size(); i++) {
		colors.push_back(cardResults.at(i).suit);
		cards.push_back(cardResults.at(i).num);
	}

	sort(begin(colors), end(colors));
	sort(begin(cards), end(cards));

	if (search.findRoyalFlush(cards, colors)) {
		score.royal += 1;
	}

	else if (search.findStraightFlush(cards, colors)) {
		score.straightflush += 1;
	}

	else if (search.findFourKind(cards)) {
		score.four += 1;
	}

	else if (search.findFull(cards)) {
		score.full += 1;
	}

	else if (search.findFlush(colors)) {
		score.flush += 1;
	}

	else if (search.findStraight(cards)) {
		score.straight += 1;
	}

	else if (search.findThree(cards)) {
		score.three += 1;
	}

	else if (search.findTwoPair(cards)) {
		score.twopair += 1;
	}

	else if (search.findPair(cards)) {
		score.pair += 1;
	}

	else {
		score.nothing += 1;
	}
}

