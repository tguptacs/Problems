#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class StructureImpl : public Structure<>
{
	double sum;
	list<T> elements;
	unordered_map<long, pair<double, Iterator>> averageMap; 
	            //index, <sum, iterator to list element>
public:
	StructureImpl()
	: sum(0)
	{}
	
	void addElement(T ele)
	{
	    elements.push_back(ele);
	    double val = ele.getValue();
		sum += val;

        long newSize = averageMap.size() + 1;
        averageMap[newSize] = make_pair(sum, --elements.end());
	}
	
	int size()
	{
	    return elements.size();    
	}
	
    Iterator begin()
	{
		return elements.begin();
	}

	Iterator end()
	{
		return elements.end();
	}

	double movingAverage(int n)
	{
	    if(n <= 0)
	        return 0;
	    int size = averageMap.size();     
	    if(n >= size)
	    {
	        return sum / size;
	    }
	    int lastIndex = size - n;
    	double nSum = sum - averageMap[lastIndex].first;
	    return nSum / n;
	}
	
	T getElement(int index)
	{
	    if(index > averageMap.size() || index <= 0)
	        return NULL;
	    Iterator it = averageMap[index].second;
	    return *it;
	}
};
