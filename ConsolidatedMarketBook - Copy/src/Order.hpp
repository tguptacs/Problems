#pragma once

enum MarketSide{
    Invalid=0,
    Bid,
    Ask
};

struct Order {
    MarketSide side;
    double price;
    mutable int quantity;

    Order(MarketSide s, int p, int q)
    : side(s), price(p), quantity(q)
    {}
};

struct MaxBid{
    bool operator() (const Order& a, const Order& b) const
    {
        return a.price > b.price;
    }
};

struct MinOffer{
    bool operator() (const Order& a, const Order& b) const
    {
        return a.price < b.price;
    }
};
