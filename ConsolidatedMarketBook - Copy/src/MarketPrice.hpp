#pragma once

class MarketPrice {
    const static int ScalingFactor = 10000;
    static int BlankPrice() { return 0; }
    
public:
    static double ToDoublePrice(int price)
    {
        return (double)price / ScalingFactor;
    }

    static int ToIntegerPrice(double price)
    {
        return (int)(price * ScalingFactor);
    }

    static bool IsBlankPrice(int price)
    {
        return (price == BlankPrice());
    }
};