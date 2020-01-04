#pragma once
#include <list>
#include <map>
#include <set>
#include <string>
#include "AggregatedOrderBook.hpp"
#include "Order.hpp"
#include "Quote.hpp"
using namespace std;

struct SecurityOnExchange{
    string exchange;
    int orderId;

    SecurityOnExchange(string ex, int id)
    : exchange(ex), orderId(id)
    {}

    bool operator< (const SecurityOnExchange& s) const
    { 
        if (s.exchange == exchange)
            return s.orderId < orderId;
        return s.exchange < exchange;    
    }
};

class MarketBook {
	map<SecurityOnExchange, Order> bidOrdersMap;
	map<SecurityOnExchange, Order> offerOrdersMap;
    set<Quote, BestMatch> quotes;
    AggregatedOrderBook orderBook;

    const Order& findOrder(const SecurityOnExchange& key)
    {
        auto it = bidOrdersMap.find(key);
        if (it != bidOrdersMap.end())
		{
            return it->second;
		}
        it = offerOrdersMap.find(key);
        if (it != offerOrdersMap.end())
		{
            return it->second;
		}
        static Order invalid(MarketSide::Invalid, -1, -1);
        return invalid;
    }

public:
    MarketBook()
    {}
    ~MarketBook()
    {}

    bool orderExists(const SecurityOnExchange& key)
    {
        MarketSide side = findOrder(key).side;
        return MarketSide::Bid == side || MarketSide::Ask == side;
    }

    void addOrder(const SecurityOnExchange& key, const Order& order)
    {
        pair<SecurityOnExchange, Order> element(key, order);
        if (MarketSide::Bid == order.side)
        {
			bidOrdersMap.insert(element);
        }
        else if (MarketSide::Ask == order.side)
        {
			offerOrdersMap.insert(element);
        }
        orderBook.addOrder(order);
    }
   
    void updateOrder(const SecurityOnExchange& key, const int& q)
    {
        const Order& order = findOrder(key);
        orderBook.cancelOrder(order);
        order.quantity = q;
        orderBook.addOrder(order);
    }

    void deleteOrder(const SecurityOnExchange& key)
    {
        const Order& order = findOrder(key);
        MarketSide side = order.side;
		if (MarketSide::Bid == side)
		{
            bidOrdersMap.erase(key);
		}
        else if (MarketSide::Ask == side)
        {
            offerOrdersMap.erase(key);
        }
        orderBook.cancelOrder(order);
    }

    void addQuote(const Quote& quote)
    {
        quotes.insert(quote);
    }

    list<Quote> getTopLevels(int maxLevel)
    {
        list<Quote> levels;
        int level = 0;
        for (set<Quote>::iterator it = quotes.begin(); level < maxLevel && it != quotes.end(); ++it)
        {
            Quote q(it->symbol, it->exchange, it->bestBidPrice, 
                it->bestBidSize, it->bestOfferPrice, it->bestOfferSize);
            q.bestBidSize = orderBook.getAllBidSize(q.bestBidPrice);
            q.bestOfferSize = orderBook.getAllAskSize(q.bestOfferPrice); 
            if (q.bestBidSize > 0 && q.bestOfferSize > 0)
            {    
                levels.push_back(q);
                level++;
            }
        }
        return levels;
    }

    const set<Order, MaxBid> getBids()
    {
		set<Order, MaxBid> bidOrders;
        for (auto it = bidOrdersMap.begin(); it != bidOrdersMap.end(); ++it)
        {
            bidOrders.insert(it->second);
        }
        return bidOrders;
    }

    const set<Order, MinOffer> getOffers()
    {
        set<Order, MinOffer> offerOrders;
        for (auto it = offerOrdersMap.begin(); it != offerOrdersMap.end(); ++it)
        {
            offerOrders.insert(it->second);
        }
        return offerOrders;
    }
};