#include <iostream>
/*
	Build a cache where you can only have 100 items in it and if you add another it removes the oldest cache. But you must be able to get values in constant time and move positions in the cache in constant time.

	assumptions, by "move positions" it means be able to move a pointer type object to any location in the cache in constant time, and by get values, be able to dereference or access the values at that pointer
	in constant time. And even though 100 is still constant time, thats not what the question means.
	
*/
template <class T>
class cache
{
	public:
		cache(int);
		void add_to_cache(const T&);
		void move_position(int);
		T get_value() const;
	private:
		int _data[100];
		int _position;
		int _insertion;
		int _max;
};

template <class T>
cache<T>::cache(int max) : _data(), _position(0), _insertion(-1), _max(max)
{
}

template <class T>
void cache<T>::add_to_cache(const T& value)
{
	if (_insertion == -1)
	{
		_data[++_insertion] = value;
	}
	else
	{
		_data[_insertion] = value;
		_insertion = (_insertion + 1)%_max;
	}
}

template <class T>
void cache<T>::move_position(int pos)
{
	_position = pos;
}

template <class T>
T cache<T>::get_value() const
{
	return _data[_position];	
}

int main()
{
	cache<int> c(100);
	for (int i = 0; i <= 100; ++i)
	{
		c.add_to_cache(i*2);	
	}
	for (int i = 0; i < 100; ++i)
	{
		c.move_position(i);
		std::cout << i << " = " << c.get_value() << std::endl;
	}
	// replace oldest value.
	c.add_to_cache(100000);
	// go to old oldest value location
	c.move_position(0);
	std::cout << c.get_value() << std::endl;

	return 0;
}
