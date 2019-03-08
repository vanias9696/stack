#ifndef STACK_HPP
# define STACK_HPP

#include <exception>
#include <iostream>

template<class T>
class Stack
{
public:
	Stack();
	~Stack();
	Stack(size_t sz);
	Stack(const Stack<T>& data);
	Stack<T>	&operator=(const Stack<T>& data);
	size_t		count()const;
	void		push(const T& data);
	T			pop(void);
private:
	T *top;
	size_t size;
	size_t used;
	T *try_copy(const T* data, size_t wide, size_t use);
};

template<class T>Stack<T>::Stack() : size(0), used(0)
{	
	top = nullptr;
}

template<class T>Stack<T>::~Stack()
{	delete [] top;
	top = nullptr;
	size = 0;
	used = 0;
}

template<class T>Stack<T>::Stack(size_t sz) : size(sz), used(0)
{
	top = new T[sz];
}

template<class T>Stack<T>::Stack(const Stack<T>& data)
{
	top = try_copy(data.top, data.size, data.used);
}

template<class T>
Stack<T>	&Stack<T>::operator=(const Stack<T>& data)
{	
	if (&data == this)
		return *this;
	top = try_copy(data.top, data.size, data.used);
	return *this;
}

template<class T>
size_t		Stack<T>::count()const
{	
	return used;
}

template<class T>
void		Stack<T>::push(const T& data)
{
	if (used + 1 > size)
	{
		T *tmp = new T[size == 0 ? 8 : size * 2];
		try
		{
			for (size_t i = 0; i < used; ++i)
			{	
				tmp[i] = top[i];
			}
			tmp[used++] = data;
			size = size == 0 ? 8 : size * 2;
			delete [] top;
			top = tmp;
		}
		catch(...)
		{
			delete [] tmp;
			throw;
		}
	}
	else
		top[used++] = data;
}

template<class T>
T			Stack<T>::pop(void)
{
	if (used == 0)
		throw std::logic_error("Stack is empty!");
	return(top[--used]);
}

template<class T>
T 			*Stack<T>::try_copy(const T* data, size_t wide, size_t use)
	{	
		T *tmp = new T[wide];
		try
		{	for (size_t i = 0; i < use; ++i)
			{	tmp[i] = data[i];}
			delete [] top;
			top = tmp;
			size = wide;
			used = use;
		}
		catch(...)
		{	
			delete [] tmp;
			throw;
		}
	return tmp;
}

#endif