#pragma once
#include <iostream>
#include "SecurityManager.hpp"

using namespace std;

class Exchange {
    string id;
    SecurityManager& mgr;
    void processFeed(MarketFeed& feed)
    {
        mgr.OnNotify(feed);
    }

public:
    Exchange(const string& id)
    : id(id), mgr(SecurityManager::getInstance())
    {}

    void addOrder(string symbol, int orderId, double price, int quantity, MarketSide side)
    {
        MarketFeedBuilder builder;
        MarketFeed feed = builder.symbol(symbol)
                                .exchange(id)
                                .event(MarketEventType::NEW_ORDER)
                                .orderId(orderId)
                                .price(price)
                                .quantity(quantity)
                                .side(side)
                                .build();
        processFeed(feed);                                
    }

    void updateQuantity(string symbol, int orderId, int quantity)
    {
        MarketFeedBuilder builder;
        MarketFeed feed = builder.symbol(symbol)
                                .exchange(id)
                                .event(MarketEventType::MODIFY_ORDER)
                                .orderId(orderId)
                                .quantity(quantity)
                                .build();
        processFeed(feed);                                
    }

    void cancelOrder(string symbol, int orderId)
    {
        MarketFeedBuilder builder;
        MarketFeed feed = builder.symbol(symbol)
                                .exchange(id)
                                .event(MarketEventType::CANCEL_ORDER)
                                .orderId(orderId)
                                .build();
        processFeed(feed);                                
    }

    void publishTopOfBook(string symbol, double bestBidPrice, int bestBidSize, double bestAskPrice, int bestAskSize)
    {
        MarketFeedBuilder builder;
        MarketFeed feed = builder.symbol(symbol)
                                .exchange(id)
                                .event(MarketEventType::TOP_OF_BOOK)
                                .bestBidPrice(bestBidPrice)
                                .bestBidSize(bestBidSize)
                                .bestOfferPrice(bestAskPrice)
                                .bestOfferSize(bestAskSize)
                                .build();
        processFeed(feed);          
  }
};