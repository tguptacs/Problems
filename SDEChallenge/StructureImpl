#include <iostream>
#include <list>
#include <unordered_map>
#include <assert.h>
using namespace std;

struct Base{
	virtual double getValue()=0;
};

struct SimpleElement : public Base{
	double val;
	SimpleElement(double val)
	: val(val)
	{}
	double getValue()
	{
		return val;
	}
	friend ostream& operator<<(ostream& s, SimpleElement& obj)
	{
	    s << obj.val;
	    return s;
	}
};

template<typename traits=SimpleElement>
class Structure
{
    public:
        typedef traits T;
        typedef typename list<T>::iterator Iterator;
		
		virtual void addElement(T ele)=0;
	
		virtual int size()=0;
	
		virtual double movingAverage(int n)=0;

		virtual T getElement(int index)=0;

		virtual Iterator begin()=0;
	
		virtual Iterator end()=0;
};

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

int main() {
    Structure<SimpleElement>* ds = new StructureImpl();
    ds->addElement(SimpleElement(1));
    ds->addElement(SimpleElement(2));
    assert(ds->movingAverage(2) == 1.5);
    
    ds->addElement(SimpleElement(100));
    ds->addElement(SimpleElement(200));
    assert(ds->movingAverage(2) == 150);

    ds->addElement(SimpleElement(300));
    ds->addElement(SimpleElement(700));
    assert(ds->movingAverage(3) == 400);
    
    SimpleElement x = ds->getElement(7);
    assert(x.getValue() == 0);

    x = ds->getElement(6);
    assert(x.getValue() == 700);

    x = ds->getElement(2);
    assert(x.getValue() == 2);
    
    for(Structure<SimpleElement>::Iterator it = ds->begin(); it != ds->end(); ++it)
        cout << *it << "\t";
	return 0;
}
