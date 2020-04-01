#include <iostream>
#include <list>
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
};

template<typename traits=SimpleElement>
class Structure
{
    public:
        typedef traits T;
        typedef typename list<T>::iterator Iterator;
		
		virtual void addElement(T ele)=0;
	
		virtual int size()=0;
	
		virtual double averageLastMoving()=0;
	
		virtual Iterator begin()=0;
	
		virtual Iterator end()=0;
};

class StructureImpl : public Structure<>
{
	int capacity;
	double sum;
	list<T> elements;
public:
	StructureImpl(int n)
	: capacity(n), sum(0)
	{}
	
	void addElement(T ele)
	{
	    elements.push_back(ele);
	    double val = ele.getValue();
		sum += val;
		
		if(elements.size() > capacity)
		{
			T temp = elements.front();
			sum -= temp.getValue();
			elements.pop_front();
		}
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

	double averageLastMoving()
	{
		return sum/capacity;	
	}
};

int main() {
    int N=4;
    Structure<SimpleElement>* ds = new StructureImpl(N);
    ds->addElement(SimpleElement(1));
    ds->addElement(SimpleElement(2));
    assert(ds->averageLastMoving() == 0.75);
    
    ds->addElement(SimpleElement(100));
    ds->addElement(SimpleElement(200));
    ds->addElement(SimpleElement(300));
    assert(ds->averageLastMoving() == 150.5);

    Structure<SimpleElement>::Iterator it = ds->begin();
    assert(it->getValue() == 2);
    ++it;    
    assert(it->getValue() == 100);
    ++it;    
    assert(it->getValue() == 200);
    ++it;    
    assert(it->getValue() == 300);
    
    it = ds->end(); --it;
    assert(it->getValue() == 300);
	return 0;
}
