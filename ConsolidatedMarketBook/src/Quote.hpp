#pragma once
#include <iostream>
using namespace std;

struct Quote {
    string symbol;
    string exchange;
    double bestBidPrice;
    int bestBidSize;
    double bestOfferPrice;
    int bestOfferSize;
public:
    Quote(string symbol, string ex, int bidPrice, int bidSize, int offerPrice, int offerSize)
    : symbol(symbol), exchange (ex), bestBidPrice(bidPrice), 
      bestBidSize(bidSize), bestOfferPrice(offerPrice), bestOfferSize(offerSize)
    {}
};

struct BestMatch{
    bool operator() (const Quote& a, const Quote& b) const
    {
        int firstCloseMatch = a.bestOfferPrice - a.bestBidPrice;
        int nextCloseMatch = b.bestOfferPrice - b.bestBidPrice;
        
        return firstCloseMatch < nextCloseMatch;
    }
};

