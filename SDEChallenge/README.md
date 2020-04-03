# PaytmLabs SDE Challenge

## Coding Question

Write an interface for a data structure that can provide the moving average of the last N elements added, add elements to the structure and get access to the elements. Provide an efficient implementation of the interface for the data structure.


## It's a C++ project. "Main.cc" file shows the working code. Other 2 files "structure" and "structureImpl" describe below the interface and implementation respectively.

##1. Interface with documentation for the data structure

## "Structure" Interface defines the methods supported by the data structure. C++ supports pure virtual functions. Functions provided are:

	#### virtual void addElement(T ele)=0;
	Adds the element to the structure
	
	#### virtual int size()=0;
	Gets the number of elements

	#### virtual double movingAverage(int n)=0;
	Returns the moving average of last N elements. Time complexity is O(1).

	#### virtual T getElement(int index)=0;
	Returns the element at index. Time complexity is O(1).

	#### virtual Iterator begin()=0;
	Returns the iterator to first element

	#### virtual Iterator end()=0;
	Returns the iterator to last element

### Implementation
   Implemented it using data structures: list, hashmap

	1(b). Traits
	#### "Base" structure defines the basic traits. Extend the base traits to define user element. Functions provided are:
		virtual double getValue()=0;
		For example, SimpleElement is the simplest trait in this case.

##2. Implementation for the interface

### "StructureImpl" class defines the implementation of interface "Structure"

	The data structure is implemented using Linked List and Hash Map. All elements are stored sequentially in the List. HashMap is used to store the sum of all the elements so far at each index. It also stores the pointer to an element in the list. 

	#### "addElement" function always pushes the element into list. It also updates the sum in HashMap, cosidering the latest element. It also keeps the reference to the new element pushed back in the list.

	#### "movingAverage" function returns the average of last n elements. It takes n as a parameter. It takes 3 conditions.
	a. if N <= 0
		It should not consider anything when calculating the average.
	b. if N >= total number of elements
		It should return the average of all the elements
	c. if N is the range between the number of elements in the structure. N > 0 && N < size	
		It should find out the sum before N elements from HashMap. It substracts that sum from total sum to find out the sum of N elements. It returns the average of last N elements.
	
	#### "getElement" function returns the element at given index. It finds the list iterator(element position) from HashMap with the given index. It returns the element from list with position stored in the Map.

	#### "size" returns the number of elements in the data structure
	#### "begin" and "end" returns the pointer to first and last elements.






## Design Question

Design A Google Analytic like Backend System.
We need to provide Google Analytic like services to our customers. Please provide a high level solution design for the backend system. Feel free to choose any open source tools as you want.

### Requirements

1. Handle large write volume: Billions of write events per day.
2. Handle large read/query volume: Millions of merchants wish to gain insight into their business. Read/Query patterns are time-series related metrics.
3. Provide metrics to customers with at most one hour delay.
4. Run with minimum downtime.
5. Have the ability to reprocess historical data in case of bugs in the processing logic.



### Please refer the design pdf for the solution