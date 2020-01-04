#pragma once
#include <iostream>
#include <unordered_map>
#include "Order.hpp"
using namespace std;

struct OrderBookPriceLevel
{
    int quantity;
    int size;
};

class AggregatedOrderBook {
    unordered_map<int, OrderBookPriceLevel> bidPriceMap;
    unordered_map<int, OrderBookPriceLevel> offerPriceMap;

public:
    AggregatedOrderBook()
    {}
    ~AggregatedOrderBook()
    {}

    void addOrder(const Order& order)
    {
        OrderBookPriceLevel priceLevel;
        priceLevel.quantity = order.quantity;
        priceLevel.size = 1;
        switch (order.side)
        {
            case MarketSide::Bid:
            {
                if (bidPriceMap.find(order.price) != bidPriceMap.end())
                {
                    OrderBookPriceLevel& level = bidPriceMap[order.price];
                    level.quantity += priceLevel.quantity;
                    level.size += priceLevel.size;
                }
                else
                {
                    bidPriceMap[order.price] = priceLevel;
                }
                break;
            }
            case MarketSide::Ask:
            {
                if (offerPriceMap.find(order.price) != offerPriceMap.end())
                {
                    OrderBookPriceLevel& level = offerPriceMap[order.price];
                    level.quantity += priceLevel.quantity;
                    level.size += priceLevel.size;
                }
                else
                {
                    offerPriceMap[order.price] = priceLevel;
                }
                break;
            }
            default:
                break;
        }
    }

    void cancelOrder(const Order& order)
    {
        switch (order.side)
        {
            case MarketSide::Bid:
            {
                if (bidPriceMap.find(order.price) != bidPriceMap.end())
                {
                    OrderBookPriceLevel& priceLevel = bidPriceMap[order.price];
                    priceLevel.quantity -= order.quantity;
                    priceLevel.size -= 1;
                }
                break;
            }
            case MarketSide::Ask:
            {
                if (offerPriceMap.find(order.price) != offerPriceMap.end())
                {
                    OrderBookPriceLevel& priceLevel = offerPriceMap[order.price];
                    priceLevel.quantity -= order.quantity;
                    priceLevel.size -= 1;
                }
                break;
            }
            default:
                break;
        }
    }

    int getAllBidSize(const int& price)
    {
        if (bidPriceMap.find(price) != bidPriceMap.end())
        {
            OrderBookPriceLevel& priceLevel = bidPriceMap[price];
            return priceLevel.quantity;
        }
        return 0;
    }

    int getAllAskSize(const int& price)
    {
        if (offerPriceMap.find(price) != offerPriceMap.end())
        {
            OrderBookPriceLevel& priceLevel = offerPriceMap[price];
            return priceLevel.quantity;
        }
        return 0;
    }
};