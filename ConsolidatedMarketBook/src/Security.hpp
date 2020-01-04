#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include "MarketBook.hpp"
#include "MarketFeed.hpp"
using namespace std;

class Security {
    typedef set<Order>::iterator OrderIterator;
    MarketBook book;
public:
    Security()
    {}
    ~Security()
    {}

    void OnOrderUpdate(const MarketFeed& feed)
    {
        SecurityOnExchange k(feed.exchange, feed.args.orderId);
        switch (feed.event)
        {
            case MarketEventType::NEW_ORDER:
                {
                    Order order(feed.args.side, feed.args.price, feed.args.quantity);
                    if (!book.orderExists(k))
                        book.addOrder(k, order); 
                    break;
                }
            case MarketEventType::MODIFY_ORDER:
                {
                    if (book.orderExists(k))
					    book.updateOrder(k, feed.args.quantity);
                    break;
                }
            case MarketEventType::CANCEL_ORDER:
                {
                    if (book.orderExists(k))
					    book.deleteOrder(k);
                    break;
                }
            default:
                break;    
        }
    }

    void OnQuoteUpdate(const MarketFeed& feed)
    {
        Quote q(feed.symbol, feed.exchange, feed.args.bestBidPrice, 
                feed.args.bestBidSize, feed.args.bestOfferPrice, feed.args.bestOfferSize);
        book.addQuote(q);
    }

    list<Quote> getConsolidatedBook(int level)
    {
        list<Quote> levels;
        levels = book.getTopLevels(level);
        return levels;
    }

    set<Order, MaxBid> getBidOrders()
    {
        return book.getBids();
    }

    set<Order, MinOffer> getOfferOrders()
    {
        return book.getOffers();
    }
};