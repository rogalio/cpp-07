#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// Generic template that works with any function type
// This allows both const and non-const function parameters
template <typename T, typename F>
void iter(T* array, size_t length, F func)
{
	if (array == NULL)
		return;

	for (size_t i = 0; i < length; i++)
	{
		func(array[i]);
	}
}

#endif
