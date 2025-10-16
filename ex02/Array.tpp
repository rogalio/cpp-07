#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"

// ==================== Constructors ====================

// Default constructor: creates an empty array
template <typename T>
Array<T>::Array() : _array(NULL), _size(0)
{
}

// Parametric constructor: creates an array of n elements initialized by default
// Note: new T() ensures default initialization (0 for int, 0.0 for float, etc.)
template <typename T>
Array<T>::Array(unsigned int n) : _array(NULL), _size(n)
{
	if (n > 0)
		_array = new T[n]();
}

// Copy constructor: deep copy
template <typename T>
Array<T>::Array(Array const & src) : _array(NULL), _size(0)
{
	*this = src;
}

// ==================== Destructor ====================

template <typename T>
Array<T>::~Array()
{
	if (_array != NULL)
		delete[] _array;
}

// ==================== Assignment operator ====================

template <typename T>
Array<T>& Array<T>::operator=(Array const & rhs)
{
	// Self-assignment protection
	if (this != &rhs)
	{
		// Delete old array
		if (_array != NULL)
			delete[] _array;

		// Copy size
		_size = rhs._size;

		// Allocate new array
		if (_size > 0)
		{
			_array = new T[_size]();

			// Deep copy elements
			for (unsigned int i = 0; i < _size; i++)
				_array[i] = rhs._array[i];
		}
		else
		{
			_array = NULL;
		}
	}
	return *this;
}

// ==================== Subscript operator ====================

// Non-const version: allows modification
template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _array[index];
}

// Const version: read-only access
template <typename T>
T const & Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _array[index];
}

// ==================== Member function ====================

template <typename T>
unsigned int Array<T>::size() const
{
	return _size;
}

#endif
