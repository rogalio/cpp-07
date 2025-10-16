#include <iostream>
#include <string>
#include "iter.hpp"

// ANSI Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// ==================== Template functions ====================

// Template function that takes const reference (read-only)
template <typename T>
void printElement(T const & element)
{
	std::cout << CYAN << element << RESET << " ";
}

// Template function that modifies elements (non-const)
template <typename T>
void incrementElement(T & element)
{
	++element;
}

// Template function that doubles numeric values
template <typename T>
void doubleValue(T & element)
{
	element *= 2;
}

// ==================== Regular functions ====================

// Regular function for const int
void printInt(int const & n)
{
	std::cout << GREEN << "[" << n << "]" << RESET << " ";
}

// Regular function that modifies int
void addTen(int & n)
{
	n += 10;
}

// Regular function for strings
void printString(std::string const & str)
{
	std::cout << BLUE << "\"" << str << "\"" << RESET << " ";
}

// Function to make strings uppercase (modifies)
void toUpperFirst(std::string & str)
{
	if (!str.empty() && str[0] >= 'a' && str[0] <= 'z')
		str[0] = str[0] - 32;
}

// ==================== Custom class ====================

class Number
{
	private:
		int _value;

	public:
		Number(int value = 0) : _value(value) {}

		int getValue() const { return _value; }
		void setValue(int value) { _value = value; }

		Number& operator++()
		{
			_value++;
			return *this;
		}

		Number operator*(int multiplier) const
		{
			return Number(_value * multiplier);
		}

		Number& operator*=(int multiplier)
		{
			_value *= multiplier;
			return *this;
		}
};

std::ostream& operator<<(std::ostream& os, Number const & n)
{
	os << n.getValue();
	return os;
}

void printNumber(Number const & n)
{
	std::cout << MAGENTA << "<" << n.getValue() << ">" << RESET << " ";
}

void multiplyByFive(Number & n)
{
	n *= 5;
}

// ==================== Helper function ====================

template <typename T>
void displayArray(T const * array, size_t size, std::string const & label)
{
	std::cout << label << ": ";
	for (size_t i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

// ==================== MAIN ====================

int main(void)
{
	std::cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << std::endl;
	std::cout << "║        EX01 - TEMPLATE ITER            ║" << std::endl;
	std::cout << "╚════════════════════════════════════════╝" << RESET << std::endl;

	// ========== Test 1: Int array with template function ==========
	std::cout << BOLD << YELLOW << "\n[1] Int array with template functions" << RESET << std::endl;
	{
		int numbers[] = {1, 2, 3, 4, 5};
		size_t size = 5;

		std::cout << "Original: ";
		displayArray(numbers, size, "");

		std::cout << "Print with iter: ";
		::iter(numbers, size, printElement<int>);
		std::cout << std::endl;

		::iter(numbers, size, incrementElement<int>);
		displayArray(numbers, size, "After increment");

		::iter(numbers, size, doubleValue<int>);
		displayArray(numbers, size, "After double");
	}

	// ========== Test 2: Int array with regular functions ==========
	std::cout << BOLD << YELLOW << "\n[2] Int array with regular functions" << RESET << std::endl;
	{
		int numbers[] = {10, 20, 30, 40, 50};
		size_t size = 5;

		displayArray(numbers, size, "Original");

		std::cout << "Print with iter: ";
		::iter(numbers, size, printInt);
		std::cout << std::endl;

		::iter(numbers, size, addTen);
		displayArray(numbers, size, "After adding 10");
	}

	// ========== Test 3: String array ==========
	std::cout << BOLD << YELLOW << "\n[3] String array" << RESET << std::endl;
	{
		std::string words[] = {"hello", "world", "this", "is", "iter"};
		size_t size = 5;

		displayArray(words, size, "Original");

		std::cout << "Print with iter: ";
		::iter(words, size, printString);
		std::cout << std::endl;

		::iter(words, size, toUpperFirst);
		displayArray(words, size, "After capitalizing");
	}

	// ========== Test 4: Float array ==========
	std::cout << BOLD << YELLOW << "\n[4] Float array" << RESET << std::endl;
	{
		float floats[] = {1.1f, 2.2f, 3.3f, 4.4f};
		size_t size = 4;

		displayArray(floats, size, "Original");

		std::cout << "Print with iter: ";
		::iter(floats, size, printElement<float>);
		std::cout << std::endl;

		::iter(floats, size, doubleValue<float>);
		displayArray(floats, size, "After doubling");
	}

	// ========== Test 5: Char array ==========
	std::cout << BOLD << YELLOW << "\n[5] Char array" << RESET << std::endl;
	{
		char letters[] = {'a', 'b', 'c', 'd', 'e'};
		size_t size = 5;

		displayArray(letters, size, "Original");

		std::cout << "Print with iter: ";
		::iter(letters, size, printElement<char>);
		std::cout << std::endl;

		::iter(letters, size, incrementElement<char>);
		displayArray(letters, size, "After increment");
	}

	// ========== Test 6: Custom class ==========
	std::cout << BOLD << YELLOW << "\n[6] Custom class (Number)" << RESET << std::endl;
	{
		Number numbers[] = {Number(10), Number(20), Number(30), Number(40)};
		size_t size = 4;

		displayArray(numbers, size, "Original");

		std::cout << "Print with iter: ";
		::iter(numbers, size, printNumber);
		std::cout << std::endl;

		::iter(numbers, size, multiplyByFive);
		displayArray(numbers, size, "After multiplying by 5");

		::iter(numbers, size, incrementElement<Number>);
		displayArray(numbers, size, "After increment");
	}

	// ========== Test 7: Empty/NULL tests ==========
	std::cout << BOLD << YELLOW << "\n[7] Edge cases (empty and NULL)" << RESET << std::endl;
	{
		int numbers[] = {1, 2, 3};

		std::cout << "Calling iter with length 0: ";
		::iter(numbers, 0, printElement<int>);
		std::cout << GREEN << "(no output - OK)" << RESET << std::endl;

		std::cout << "Calling iter with NULL pointer: ";
		::iter(static_cast<int*>(NULL), 5, printElement<int>);
		std::cout << GREEN << "(no crash - OK)" << RESET << std::endl;
	}

	std::cout << BOLD << GREEN << "\n✓ All iter tests completed!\n" << RESET << std::endl;

	return 0;
}
