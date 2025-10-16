#include <iostream>
#include <string>
#include "whatever.hpp"

// ANSI Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Custom class for additional testing
class Number
{
	private:
		int _value;

	public:
		Number(int value) : _value(value) {}
		Number() : _value(0) {}

		int getValue() const { return _value; }

		bool operator<(Number const & rhs) const { return _value < rhs._value; }
		bool operator>(Number const & rhs) const { return _value > rhs._value; }
};

std::ostream& operator<<(std::ostream& os, Number const & n)
{
	os << n.getValue();
	return os;
}

int main(void)
{
	std::cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << std::endl;
	std::cout << "║     EX00 - TEMPLATE FUNCTIONS         ║" << std::endl;
	std::cout << "╚════════════════════════════════════════╝" << RESET << std::endl;

	std::cout << BOLD << YELLOW << "\n=== Test from subject ===" << RESET << std::endl;
	{
		int a = 2;
		int b = 3;

		::swap( a, b );
		std::cout << GREEN << "a = " << a << ", b = " << b << RESET << std::endl;
		std::cout << "min( a, b ) = " << BLUE << ::min( a, b ) << RESET << std::endl;
		std::cout << "max( a, b ) = " << MAGENTA << ::max( a, b ) << RESET << std::endl;

		std::string c = "chaine1";
		std::string d = "chaine2";

		::swap(c, d);
		std::cout << GREEN << "c = " << c << ", d = " << d << RESET << std::endl;
		std::cout << "min( c, d ) = " << BLUE << ::min( c, d ) << RESET << std::endl;
		std::cout << "max( c, d ) = " << MAGENTA << ::max( c, d ) << RESET << std::endl;
	}

	std::cout << BOLD << YELLOW << "\n=== Additional tests with float ===" << RESET << std::endl;
	{
		float x = 42.42f;
		float y = 21.21f;

		std::cout << "Before swap: " << RED << "x = " << x << ", y = " << y << RESET << std::endl;
		::swap(x, y);
		std::cout << "After swap:  " << GREEN << "x = " << x << ", y = " << y << RESET << std::endl;
		std::cout << "min( x, y ) = " << BLUE << ::min( x, y ) << RESET << std::endl;
		std::cout << "max( x, y ) = " << MAGENTA << ::max( x, y ) << RESET << std::endl;
	}

	std::cout << BOLD << YELLOW << "\n=== Test with equal values ===" << RESET << std::endl;
	{
		int a = 5;
		int b = 5;

		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "min( a, b ) = " << CYAN << ::min( a, b ) << RESET << " (should return b)" << std::endl;
		std::cout << "max( a, b ) = " << CYAN << ::max( a, b ) << RESET << " (should return b)" << std::endl;

		// Verify it returns the second one by checking address
		std::cout << BLUE << "Address of a: " << &a << RESET << std::endl;
		std::cout << BLUE << "Address of b: " << &b << RESET << std::endl;
		std::cout << GREEN << "Address of min result: " << &::min(a, b) << RESET << std::endl;
		std::cout << GREEN << "Address of max result: " << &::max(a, b) << RESET << std::endl;
	}

	std::cout << BOLD << YELLOW << "\n=== Test with char ===" << RESET << std::endl;
	{
		char c1 = 'a';
		char c2 = 'z';

		std::cout << "Before swap: " << RED << "c1 = " << c1 << ", c2 = " << c2 << RESET << std::endl;
		::swap(c1, c2);
		std::cout << "After swap:  " << GREEN << "c1 = " << c1 << ", c2 = " << c2 << RESET << std::endl;
		std::cout << "min( c1, c2 ) = " << BLUE << ::min( c1, c2 ) << RESET << std::endl;
		std::cout << "max( c1, c2 ) = " << MAGENTA << ::max( c1, c2 ) << RESET << std::endl;
	}

	std::cout << BOLD << YELLOW << "\n=== Test with custom class ===" << RESET << std::endl;
	{
		Number n1(100);
		Number n2(200);

		std::cout << "Before swap: " << RED << "n1 = " << n1 << ", n2 = " << n2 << RESET << std::endl;
		::swap(n1, n2);
		std::cout << "After swap:  " << GREEN << "n1 = " << n1 << ", n2 = " << n2 << RESET << std::endl;
		std::cout << "min( n1, n2 ) = " << BLUE << ::min( n1, n2 ) << RESET << std::endl;
		std::cout << "max( n1, n2 ) = " << MAGENTA << ::max( n1, n2 ) << RESET << std::endl;
	}

	std::cout << BOLD << GREEN << "\n✓ All tests completed!\n" << RESET << std::endl;

	return 0;
}
