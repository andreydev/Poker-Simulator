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
#include <unistd.h>

#include "data.hpp"
#include "gamemech.hpp"
#include "generator.hpp"

using namespace std;

const int numberOfCards = 5;
const int maxRandom = 51;

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
    
    cout << "[^] Started with " << numberOfCards << " cards!" << endl << endl;
    
    play();
    
    return 0;
}

void displayResult(){
    while(true){
        usleep(2000000);
        
        vector<Combo> tmpScore = game.getGameResults();
        long long tmpGameCounter = gameCounter;
        
        int nothing = game.vectorSearch(tmpScore, Combo::Nothing, myScore);
        int pairs = game.vectorSearch(tmpScore, Combo::Pair, myScore);
        int twopairs = game.vectorSearch(tmpScore, Combo::TwoPairs, myScore);
        int three = game.vectorSearch(tmpScore, Combo::ThreeKind, myScore);
        int straight = game.vectorSearch(tmpScore, Combo::Straight, myScore);
        int flush = game.vectorSearch(tmpScore, Combo::Flush, myScore);
        int full = game.vectorSearch(tmpScore, Combo::Full, myScore);
        int fourkinds = game.vectorSearch(tmpScore, Combo::FourKind, myScore);
        int straightflush = game.vectorSearch(tmpScore, Combo::StraightFlush, myScore);
        int royalflush = game.vectorSearch(tmpScore, Combo::RoyalFlush, myScore);
        
        cout << "[?] Game #"<< gameCounter << " Done" << endl;
        cout << "[?] Nothing ->"<< nothing << " ->" << nothing/static_cast<float>(tmpGameCounter) * 100 << "%" << endl;
        cout << "[?] Pairs ->"<< pairs << " ->" << pairs/static_cast<float>(tmpGameCounter) * 100 << "%" <<endl;
        cout << "[?] TwoPairs ->"<< twopairs << " ->" << twopairs/static_cast<float>(tmpGameCounter) * 100 << "%" << endl;
        cout << "[?] ThreeKinds ->"<< three << " ->" << three/static_cast<float>(tmpGameCounter) * 100 << "%" << endl;
        cout << "[?] Straights ->"<< straight << " ->" << straight/static_cast<float>(tmpGameCounter) * 100 << "%" << endl;
        cout << "[?] Flushes ->"<< flush << " ->" << flush/static_cast<float>(tmpGameCounter) * 100 << "%" << endl;
        cout << "[?] Fulls ->"<< full << " ->" << full/static_cast<float>(tmpGameCounter) * 100<< "%" << endl;
        cout << "[?] FourKinds ->"<< fourkinds << " ->" << fourkinds/static_cast<float>(tmpGameCounter) * 100 << "%" << endl;
        cout << "[?] StraightFlushes ->"<< straightflush << " ->" << straightflush/static_cast<float>(tmpGameCounter) * 100 << "%" << endl;
        cout << "[?] RoyalFlushes ->"<< royalflush << " ->" << royalflush/static_cast<float>(tmpGameCounter) * 100 << "%" << endl << endl;
        
        while(!done){
            usleep(25);
            continue;
        }
        
        game.clearGameResults();
    }
}

void play(){
    while(true){
        
        usleep(100);
        
        done = false;
        
        gameCounter += 1;
        
        resultCards.clear();
        
        resultCards = generator.rollTable(maxRandom, numberOfCards);
        
        game.verifyResult(resultCards);
        
        done = true;
    }
}
