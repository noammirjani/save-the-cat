#pragma once
#include <stack>
#include <exception> 
#include <iostream> 

template<class T>
class Stack
{
public:
	//c-tor, d-tor
	Stack() {};
	Stack(const T);
	~Stack() {}

	void freeObj();
	void clear();
	unsigned int size() const;
	T    pop();
	T    top() const;
	void push(const T);
	bool isEmpty()const;

private:
	std::stack<T> m_locations;
};

//-----------------------------------------------------------------------------
template<class T>
void Stack<T>::freeObj() 
{
	auto temp = pop(); 
}


//-----------------------------------------------------------------------------
template<class T>
Stack<T>::Stack(const T location) { m_locations.push(location); }


//-----------------------------------------------------------------------------
template<class T>
void Stack<T>::push(const T location)
{
	m_locations.push(location);
}


//-----------------------------------------------------------------------------
template<class T>
bool Stack<T>::isEmpty() const
{
	return m_locations.empty();
}


//-----------------------------------------------------------------------------
template<class T>
T Stack<T>::pop()
{
	if (!m_locations.empty())
	{
		auto temp = m_locations.top();
		m_locations.pop();
		return temp;
	}
	return{ 5,5 };
}

//-----------------------------------------------------------------------------
template<class T>
T Stack<T>::top() const
{
	if (!m_locations.empty())
	{
		auto temp = m_locations.top();
		return temp;
	}
	return{ 5,5 };
}


//-----------------------------------------------------------------------------
template<class T>
void Stack<T>::clear()
{
	while (!m_locations.empty())
	{
		m_locations.pop();
	}
}


//-----------------------------------------------------------------------------
template<class T>
unsigned int Stack<T>::size() const
{
	auto tempStack = m_locations;
	auto size = 0;
	while (!tempStack.empty())
	{
		tempStack.pop();
		size++;
	}
	return size;

}