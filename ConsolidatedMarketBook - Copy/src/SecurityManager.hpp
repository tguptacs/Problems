#pragma once
#include <list>
#include <mutex>
#include <set>
#include <unordered_map>
#include "MarketPrice.hpp"
#include "Security.hpp"
using namespace std;

struct ScopedLock{
    __gthread_mutex_t& mutex;

    ScopedLock(__gthread_mutex_t& m)
    : mutex(m)
    {
        __gthread_mutex_trylock(&mutex);
    }

    ~ScopedLock()
    {
        __gthread_mutex_unlock(&mutex);
    }
};

class SecurityManager {
    typedef unordered_map <string, Security>::iterator Iterator;
    unordered_map <string, Security> securityMap; //symbol
    unordered_map <string, __gthread_mutex_t> securityMutex; //symbol
    __gthread_mutex_t mutex;

    SecurityManager()
    {
        __gthread_mutex_init_function(&mutex);
    }

    __gthread_mutex_t& acquireSymbolMutex(string symbol)
    {
        if (securityMutex.find(symbol) != securityMutex.end())
            return securityMutex[symbol];
        ScopedLock lock(mutex);
        __gthread_mutex_t symMutex;
        __gthread_mutex_init_function(&symMutex);
        securityMutex[symbol] = symMutex;
        return securityMutex[symbol];
    }

    bool validateMarketFeed(MarketFeed& feed)
    {
        if(feed.event == MarketEventType::TOP_OF_BOOK)
        {
            feed.args.bestBidPrice = MarketPrice::ToIntegerPrice(feed.args.bestBidPrice);
            feed.args.bestOfferPrice = MarketPrice::ToIntegerPrice(feed.args.bestOfferPrice);
            if (MarketPrice::IsBlankPrice(feed.args.bestBidPrice)
                    || MarketPrice::IsBlankPrice(feed.args.bestOfferPrice))
                return false;
            if (feed.args.bestBidSize <= 0
                    || feed.args.bestOfferSize <= 0)
                return false;
        }
        else if(feed.event == MarketEventType::NEW_ORDER)
        {
            feed.args.price = MarketPrice::ToIntegerPrice(feed.args.price);
            if (MarketPrice::IsBlankPrice(feed.args.price))
                return false;
            if (feed.args.quantity <= 0)
                return false;                
        }
        else if(feed.event == MarketEventType::MODIFY_ORDER)
        {
            if (feed.args.quantity <= 0)
                return false;                
        }
        return true;
    }
public:
    ~SecurityManager()
    {
        __gthread_mutex_destroy(&mutex);
    }

    void OnNotify(MarketFeed feed)
    {
        if (!validateMarketFeed(feed))
        {
            return;
        }
        ScopedLock(acquireSymbolMutex(feed.symbol));
        int feedprice = feed.args.price;
        MarketEventType event = feed.event;
        Security sec;
        Iterator it = securityMap.find(feed.symbol);
        if (it != securityMap.end())
        {
            sec = securityMap[feed.symbol];
        }
        
        switch (event)
        {
            case MarketEventType::NEW_ORDER: 
            case MarketEventType::MODIFY_ORDER:
            case MarketEventType::CANCEL_ORDER:
            {
                sec.OnOrderUpdate(feed);
                break;
            }
            case MarketEventType::TOP_OF_BOOK:
            {
                sec.OnQuoteUpdate(feed);
                break;
            }
            default:
                break;
        }
        securityMap[feed.symbol] = sec;
    }

    static SecurityManager& getInstance()
    {
        static SecurityManager instance;
        return instance;
    }

    set<Order, MaxBid> BidOrders(string symbol)
    {
        ScopedLock(acquireSymbolMutex(symbol));
        Security sec;
        Iterator it = securityMap.find(symbol);
        if (it != securityMap.end())
        {
            return it->second.getBidOrders();
        }
        return set<Order, MaxBid> ();
    }

    set<Order, MinOffer> OfferOrders(string symbol)
    {
        ScopedLock(acquireSymbolMutex(symbol));
        Security sec;
        Iterator it = securityMap.find(symbol);
        if (it != securityMap.end())
        {
            return it->second.getOfferOrders();
        }
        return set<Order, MinOffer> ();
    }

    list<Quote> ConsolidatedBook(string symbol, int maxLevel)
    {
        ScopedLock(acquireSymbolMutex(symbol));
        list<Quote> levels;
        Iterator it = securityMap.find(symbol);
        if (it != securityMap.end())
        {
            levels = it->second.getConsolidatedBook(maxLevel);
            for (auto it = levels.begin(); it != levels.end(); ++it)
            {
                it->bestBidPrice = MarketPrice::ToDoublePrice(it->bestBidPrice);
                it->bestOfferPrice = MarketPrice::ToDoublePrice(it->bestOfferPrice);
            }
        }
        return levels;
    }
};