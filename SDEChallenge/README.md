# PaytmLabs SDE Challenge

## Coding Question

Write an interface for a data structure that can provide the moving average of the last N elements added, add elements to the structure and get access to the elements. Provide an efficient implementation of the interface for the data structure.
### Minimum Requirements



## It's a C++ project.

There are 3 main things.
1. Provide a separate interface (IE `interface`/`trait`) with documentation for the data structure

-- Interface
### "Structure" Interface of the functions supported by the data structure. C++ supports pure virtual functions. Functions provided are:

	virtual double averageLastMoving()=0;
	Get the average of last N elements. Element insertion updates the total sum accordingly.

	virtual void addElement(T ele)=0;

	virtual int size()=0;

	virtual Iterator begin()=0;
	Returns the pointer to first element.

	virtual Iterator end()=0;
	Returns the pointer to last element.

	Implementation
	Implemented it using data structures: list.

LinkedList is suitable for situation that ADD/GET operations usually happens on the first or last positions.


-- Traits

 "Base" structure defines the basic. Extend the base traits to define user element. Functions provided:

	virtual double getValue()=0;

 For example, SimpleElement is the simplest trait in this case.

2. Provide an implementation for the interface

 "StructureImpl" class defines the implementation of interface "Structure"

	- "addElement" function always pushes the element into list of elements. It uses the traits to calculate the sum. It also removes the old elements, when the size of list exceeds the original capacity N(window size)
	- "averageLastMoving" function calculate the average with calculated sum and initial capacity
	- "size" returns the number of elements in the data structure
	- "begin" and "end" returns the pointer to first and last elements.


## Design Question

Design A Google Analytic like Backend System.
We need to provide Google Analytic like services to our customers. Please provide a high level solution design for the backend system. Feel free to choose any open source tools as you want.

### Requirements

1. Handle large write volume: Billions of write events per day.
2. Handle large read/query volume: Millions of merchants wish to gain insight into their business. Read/Query patterns are time-series related metrics.
3. Provide metrics to customers with at most one hour delay.
4. Run with minimum downtime.
5. Have the ability to reprocess historical data in case of bugs in the processing logic.
