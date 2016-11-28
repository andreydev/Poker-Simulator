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
        
        double nothingPrc = nothing/static_cast<double>(tmpGameCounter) * 100;
        double pairsPrc = pairs/static_cast<double>(tmpGameCounter) * 100;
        double twoPairPrc = twopairs/static_cast<double>(tmpGameCounter) * 100;
        double threePrc = three/static_cast<double>(tmpGameCounter) * 100;
        double straightPrc = straight/static_cast<double>(tmpGameCounter) * 100;
        double flushPrc = flush/static_cast<double>(tmpGameCounter) * 100;
        double fullPrc = full/static_cast<double>(tmpGameCounter) * 100;
        double fourKindsPrc = fourkinds/static_cast<double>(tmpGameCounter) * 100;
        double straightFlushPrc = straightflush/static_cast<double>(tmpGameCounter) * 100;
        double royalFlushPrc = royalflush/static_cast<double>(tmpGameCounter) * 100;
        
        int total = nothingPrc + pairsPrc + twoPairPrc + threePrc + straightPrc + flushPrc + fullPrc + fourKindsPrc + straightPrc + royalFlushPrc;
        
        cout << "[?] Game #"<< gameCounter << " Done \t->" << total << "%" << endl;
        cout << "[?] Nothing ->"<< nothing << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << nothingPrc << "%" << endl;
        cout << "[?] Pairs ->"<< pairs << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << pairsPrc << "%" <<endl;
        cout << "[?] TwoPairs ->"<< twopairs << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << twoPairPrc << "%" << endl;
        cout << "[?] ThreeKinds ->"<< three << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << threePrc << "%" << endl;
        cout << "[?] Straights ->"<< straight << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << straightPrc << "%" << endl;
        cout << "[?] Flushes ->"<< flush << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << flushPrc << "%" << endl;
        cout << "[?] Fulls ->"<< full << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << fullPrc << "%" << endl;
        cout << "[?] FourKinds ->"<< fourkinds << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << fourKindsPrc << "%" << endl;
        cout << "[?] StraightFlushes ->"<< straightflush << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << straightFlushPrc << "%" << endl;
        cout << "[?] RoyalFlushes ->"<< royalflush << " ->" << setiosflags(ios::fixed) << setprecision(precPoint) << royalFlushPrc << "%" << endl << endl;
        
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
