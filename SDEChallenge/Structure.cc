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