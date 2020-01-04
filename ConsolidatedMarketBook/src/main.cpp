#include <iostream>
#include "ConsolidatedBook.hpp"
#include "Exchange.hpp"

template<typename T>
bool valueEquals(T from, T to)
{
	return from == to;
}
bool valueEquals(double from, double to)
{
    int tick = 1; //checks the price comparison in scale of .0001, if not matched
    int actual = MarketPrice::ToIntegerPrice(from);
    int expected = MarketPrice::ToIntegerPrice(to);
    return actual == expected || (actual-tick) == expected;
}

void addFeedUSExchange(Exchange& usEX)
{
	usEX.addOrder("US-BOND", 9001, 105.1, 140, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9002, 105.2, 130, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9003, 105.3, 120, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9004, 105.4, 110, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9005, 105.5, 100, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9006, 105.6, 90, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9007, 105.7, 80, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9008, 105.8, 70, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9009, 105.85, 60, MarketSide::Bid);
	usEX.addOrder("US-BOND", 9010, 105.9, 50, MarketSide::Bid);
    usEX.addOrder("US-FRN", 9009, 110.85, 60, MarketSide::Bid);
	usEX.addOrder("US-FRN", 9010, 110.9, 50, MarketSide::Bid);

	usEX.addOrder("US-BOND", 8001, 115.95, 140, MarketSide::Ask);
	usEX.addOrder("US-BOND", 8002, 115.75, 150, MarketSide::Ask);
	usEX.addOrder("US-BOND", 8003, 115.65, 151, MarketSide::Ask);
	usEX.addOrder("US-BOND", 8004, 115.55, 152, MarketSide::Ask);
	usEX.addOrder("US-BOND", 8005, 115.50, 156, MarketSide::Ask);
	usEX.addOrder("US-BOND", 8006, 115.48, 161, MarketSide::Ask);
	usEX.addOrder("US-BOND", 8007, 115.46, 170, MarketSide::Ask);
    usEX.addOrder("US-FRN", 8009, 105.9, 60, MarketSide::Ask);
	usEX.addOrder("US-FRN", 8010, 111.85, 50, MarketSide::Ask);

	usEX.publishTopOfBook("US-BOND", 105.9, 50, 115.46, 170);
	usEX.publishTopOfBook("US-BOND", 105.8, 70, 115.48, 161);
	usEX.publishTopOfBook("US-BOND", 105.6, 90, 115.55, 152);
	usEX.publishTopOfBook("US-BOND", 105.4, 110, 115.65, 151);
	usEX.publishTopOfBook("US-BOND", 105.2, 130, 115.75, 150);
	usEX.publishTopOfBook("US-BOND", 105.1, 140, 115.95, 140);
	usEX.publishTopOfBook("US-FRN", 110.9, 50, 105.9, 50);
	usEX.publishTopOfBook("US-FRN", 110.85, 60, 111.85, 60);
}
void addFeedAUSExchange(Exchange& ausEX)
{
	ausEX.addOrder("US-BOND", 9001, 105.09, 160, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9002, 105.2, 170, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9003, 105.31, 180, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9004, 105.4, 190, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9005, 105.49, 100, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9006, 105.6, 110, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9007, 105.71, 120, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9008, 105.8, 130, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9009, 105.84, 140, MarketSide::Bid);
	ausEX.addOrder("US-BOND", 9010, 105.9, 150, MarketSide::Bid);


	ausEX.addOrder("US-BOND", 8001, 115.0, 60, MarketSide::Ask);
	ausEX.addOrder("US-BOND", 8002, 115.75, 50, MarketSide::Ask);
	ausEX.addOrder("US-BOND", 8003, 115.62, 49, MarketSide::Ask);
	ausEX.addOrder("US-BOND", 8004, 115.55, 48, MarketSide::Ask);
	ausEX.addOrder("US-BOND", 8005, 115.49, 44, MarketSide::Ask);
	ausEX.addOrder("US-BOND", 8006, 115.48, 39, MarketSide::Ask);
	ausEX.addOrder("US-BOND", 8007, 112.40, 30, MarketSide::Ask);

	ausEX.publishTopOfBook("US-BOND", 105.09, 160, 112.40, 30);
	ausEX.publishTopOfBook("US-BOND", 105.2, 170, 115.49, 44);
	ausEX.publishTopOfBook("US-BOND", 105.4, 190, 115.62, 49);
	ausEX.publishTopOfBook("US-BOND", 105.6, 110, 115.75, 50);
	ausEX.publishTopOfBook("US-BOND", 105.8, 130, 115.0, 60);
}

bool checkLevel(int level, Quote qt, double bestBidPrice, int bestBidSize, double bestOfferPrice, int bestOfferSize)
{
	cout << "Checking LEVEL# " << level << endl;
	if (!valueEquals(bestBidPrice, qt.bestBidPrice))
    {
        cout << "Failed to match bestBidPrice!" << endl;
        cout << "Actual: " << qt.bestBidPrice << " Expected: " << bestBidPrice << endl;
		return false;
    }
	if (!valueEquals<int>(bestBidSize, qt.bestBidSize))
	{
        cout << "Failed to match bestBidSize!" << endl;
        cout << "Actual: " << qt.bestBidSize << " Expected: " << bestBidSize << endl;
        return false;
    }
	if (!valueEquals(bestOfferPrice, qt.bestOfferPrice))
	{
        cout << "Failed to match bestOfferPrice!" << endl;
        cout << "Actual: " << qt.bestOfferPrice << " Expected: " << bestOfferPrice << endl;
        return false;
    }
	if (!valueEquals<int>(bestOfferSize, qt.bestOfferSize))
	{
        cout << "Failed to match bestOfferSize!" << endl;
        cout << "Actual: " << qt.bestOfferSize << " Expected: " << bestOfferSize << endl;
        return false;
    }
	return true;	
}

bool checkQuotes(list<Quote> q)
{
	if (!valueEquals<int>(q.size(), 5))
    {
        cout << "Failed to match levels!" << endl;
        cout << "Actual size: " << q.size() << " Expected: " << 5 << endl;
		return false;
    }
	auto it = q.begin();
	Quote qt = *it;
	if (!checkLevel(0, qt, 105.09, 160, 112.40, 30))
		return false;
	++it;
	qt = *it;
	if (!checkLevel(1, qt, 105.8, 200, 115.0, 60))
		return false;
	++it;
	qt = *it;
	if (!checkLevel(2, qt, 105.9, 200, 115.46, 170))
		return false;
	++it;
	qt = *it;
	if (!checkLevel(3, qt, 105.8, 200, 115.48, 200))
		return false;
	++it;
	qt = *it;
	if (!checkLevel(4, qt, 105.6, 200, 115.55, 200))
		return false;
	return true;
}
void printQuotes(list<Quote> q)
{
    for (list<Quote>::iterator it = q.begin(); it != q.end(); ++it)
    {
        Quote qt = *it;
        cout << "Symbol: " << qt.symbol << " at " << qt.exchange << endl;
        cout << "---BestBidPrice: " << qt.bestBidPrice << endl;
        cout << "---BestBidSize: " << qt.bestBidSize << endl;
        cout << "---bestOfferPrice: " << qt.bestOfferPrice << endl;
        cout << "---bestOfferSize: " << qt.bestOfferSize << endl;
    }
}
void testBestLevelsforUS_BOND()
{
	Exchange usEX("US-EXC");
	addFeedUSExchange(usEX);

	Exchange ausEX("AUS");
	addFeedAUSExchange(ausEX);

    ConsolidatedBook book;
    list<Quote> q = book.getBestLevels("US-BOND");
    // printQuotes(q);
	bool ret = checkQuotes (q);
	if (ret)
	{
		cout << "Passed!" << endl;
	}
	else
	{
		cout << "Failed!" << endl;
    }
}

int main() {
    std::cout << "Consolidated Book C++ project!" << std::endl;
	testBestLevelsforUS_BOND();
}

