#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstddef>

template <typename T>
class Array
{
	private:
		T*				_array;
		unsigned int	_size;

	public:
		// Orthodox Canonical Form
		Array();									// Default constructor
		Array(unsigned int n);						// Parametric constructor
		Array(Array const & src);					// Copy constructor
		Array& operator=(Array const & rhs);		// Assignment operator
		~Array();									// Destructor

		// Subscript operator (two versions: const and non-const)
		T& operator[](unsigned int index);
		T const & operator[](unsigned int index) const;

		// Member function
		unsigned int size() const;

		// Exception class
		class OutOfBoundsException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Error: Index out of bounds";
				}
		};
};

#include "Array.tpp"

#endif
