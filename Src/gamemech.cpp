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
	gameResults.clear();
}

vector<Combo> GameMech::getGameResults() {
	return gameResults;
}

// Checking for combinations and saving to gameresults vector
void GameMech::verifyResult(vector<Card> cardResults) {

	vector<int> colors;
	vector<int> cards;

	for (auto i = 0; i < cardResults.size(); i++) {
		colors.push_back(cardResults.at(i).suit);
		cards.push_back(cardResults.at(i).num);
	}

	sort(begin(colors), end(colors));
	sort(begin(cards), end(cards));

	if (search.findRoyalFlush(cards, colors)) {
		gameResults.push_back(Combo::RoyalFlush);
	}

	else if (search.findStraightFlush(cards, colors)) {
		gameResults.push_back(Combo::StraightFlush);
	}

	else if (search.findFourKind(cards)) {
		gameResults.push_back(Combo::FourKind);
	}

	else if (search.findFull(cards)) {
		gameResults.push_back(Combo::Full);
	}

	else if (search.findFlush(colors)) {
		gameResults.push_back(Combo::Flush);
	}

	else if (search.findStraight(cards)) {
		gameResults.push_back(Combo::Straight);
	}

	else if (search.findThree(cards)) {
		gameResults.push_back(Combo::ThreeKind);
	}

	else if (search.findTwoPair(cards)) {
		gameResults.push_back(Combo::TwoPairs);
	}

	else if (search.findPair(cards)) {
		gameResults.push_back(Combo::Pair);
	}

	else {
		gameResults.push_back(Combo::Nothing);
	}
}

// Parsing gameresults and adding to score
void GameMech::vectorSearch(Score& myScore) {

	map <Combo, int> results;

	for (auto i = 0; i < gameResults.size(); i++)
	{
		results[gameResults[i]]++;
	}

	for (auto item : results) {
		switch (item.first) {
		case Combo::Nothing:
			myScore.nothing += item.second;
			break;
		case Combo::Pair:
			myScore.pair += item.second;
			break;
		case Combo::TwoPairs:
			myScore.twopair += item.second;
			break;
		case Combo::ThreeKind:
			myScore.three += item.second;
			break;
		case Combo::Straight:
			myScore.straight += item.second;
			break;
		case Combo::Flush:
			myScore.flush += item.second;
			break;
		case Combo::Full:
			myScore.full += item.second;
			break;
		case Combo::FourKind:
			myScore.four += item.second;
			break;
		case Combo::StraightFlush:
			myScore.straightflush += item.second;
			break;
		case Combo::RoyalFlush:
			myScore.royal += item.second;
			break;
		}
	}
}
