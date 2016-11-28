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

void GameMech::clearGameResults() {
	_gameResults.clear();
}

vector<Combo> GameMech::getGameResults() {
	return _gameResults;
}

void GameMech::verifyResult(vector<Card> cardResults) {

	vector<int> colors;
	vector<int> cards;

	for (int i = 0; i < cardResults.size(); i++) {
		colors.push_back(cardResults.at(i).suit);
		cards.push_back(cardResults.at(i).num);
	}

	sort(begin(colors), end(colors));
	sort(begin(cards), end(cards));

	if (search.findRoyalFlush(cards, colors)) {
		_gameResults.push_back(Combo::RoyalFlush);
	}

	else if (search.findStraightFlush(cards, colors)) {
		_gameResults.push_back(Combo::StraightFlush);
	}

	else if (search.findFourKind(cards)) {
		_gameResults.push_back(Combo::FourKind);
	}

	else if (search.findFull(cards)) {
		_gameResults.push_back(Combo::Full);
	}

	else if (search.findFlush(colors)) {
		_gameResults.push_back(Combo::Flush);
	}

	else if (search.findStraight(cards)) {
		_gameResults.push_back(Combo::Straight);
	}

	else if (search.findThree(cards)) {
		_gameResults.push_back(Combo::ThreeKind);
	}

	else if (search.findTwoPair(cards)) {
		_gameResults.push_back(Combo::TwoPairs);
	}

	else if (search.findPair(cards)) {
		_gameResults.push_back(Combo::Pair);
	}

	else {
		_gameResults.push_back(Combo::Nothing);
	}
}

int GameMech::vectorSearch(Combo target, Score& myScore) {

	int counter = 0;

	auto results = _gameResults;

	for (auto& i : results) {
		if (i == target) {
			counter++;
		}
	}

	switch (target) {
	case Combo::Nothing:
		myScore.nothing += counter;
		return myScore.nothing;

	case Combo::Pair:
		myScore.pair += counter;
		return myScore.pair;

	case Combo::TwoPairs:
		myScore.twopair += counter;
		return myScore.twopair;

	case Combo::ThreeKind:
		myScore.three += counter;
		return myScore.three;

	case Combo::Flush:
		myScore.flush += counter;
		return myScore.flush;

	case Combo::Full:
		myScore.full += counter;
		return myScore.full;

	case Combo::StraightFlush:
		myScore.straightflush += counter;
		return myScore.straightflush;

	case Combo::Straight:
		myScore.straight += counter;
		return myScore.straight;

	case Combo::RoyalFlush:
		myScore.royal += counter;
		return myScore.royal;

	case Combo::FourKind:
		myScore.four += counter;
		return myScore.four;

	}
}
