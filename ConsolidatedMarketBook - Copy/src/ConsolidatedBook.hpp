#pragma once
#include "SecurityManager.hpp"

class ConsolidatedBook {
    const static int MAX_LEVEL = 5;
    SecurityManager mgr;

public:
    ConsolidatedBook()
    : mgr(SecurityManager::getInstance())
    {}
    
    list<Quote> getBestLevels(string symbol, int maxLevel = MAX_LEVEL);
};

list<Quote> ConsolidatedBook::getBestLevels(string symbol, int maxLevel)
{
    return mgr.ConsolidatedBook(symbol, maxLevel);
}