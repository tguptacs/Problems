#pragma once
#include <iostream>
using namespace std;

enum MarketEventType{
    TOP_OF_BOOK=0,
    NEW_ORDER,
    MODIFY_ORDER,
    CANCEL_ORDER
};

struct MarketFeedArgs{
    double bestBidPrice;
    int bestBidSize;
    double bestOfferPrice;
    int bestOfferSize;
    double price;
    MarketSide side;
    int quantity;
    int orderId;
};

struct MarketFeed{
    MarketEventType event;
    string symbol;
    string exchange;
    MarketFeedArgs args;
};

struct MarketFeedBuilder{
    MarketFeedBuilder symbol(string symbol)
    {
        feed.symbol = symbol;
        return *this;
    }
    MarketFeedBuilder exchange(string exchange)
    {
        feed.exchange = exchange;
        return *this;
    }
    MarketFeedBuilder event(MarketEventType event)
    {
        feed.event = event;
        return *this;
    }
    MarketFeedBuilder orderId(int orderId)
    {
        feed.args.orderId = orderId;
        return *this;
    }
    MarketFeedBuilder quantity(int quantity)
    {
        feed.args.quantity = quantity;
        return *this;
    }
    MarketFeedBuilder side(MarketSide side)
    {
        feed.args.side = side;
        return *this;
    }
    MarketFeedBuilder price(double price)
    {
        feed.args.price = price;
        return *this;
    }
    MarketFeedBuilder bestBidPrice(double bestBidPrice)
    {
        feed.args.bestBidPrice = bestBidPrice;
        return *this;
    }
    MarketFeedBuilder bestBidSize(int bestBidSize)
    {
        feed.args.bestBidSize = bestBidSize;
        return *this;
    }
    MarketFeedBuilder bestOfferPrice(double bestOfferPrice)
    {
        feed.args.bestOfferPrice = bestOfferPrice;
        return *this;
    }
    MarketFeedBuilder bestOfferSize(int bestOfferSize)
    {
        feed.args.bestOfferSize = bestOfferSize;
        return *this;
    }

    MarketFeed build()
    {
        return feed;
    }

private:
    MarketFeed feed;
};