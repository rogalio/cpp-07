#include <iostream>
#include <string>
#include "Array.hpp"

// ANSI Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Helper function to print test results
void printTest(std::string const & testName, bool success)
{
	if (success)
		std::cout << GREEN << "✓ " << testName << RESET << std::endl;
	else
		std::cout << RED << "✗ " << testName << RESET << std::endl;
}

// Custom class for testing
class Number
{
	private:
		int _value;

	public:
		Number() : _value(0) {}
		Number(int value) : _value(value) {}

		int getValue() const { return _value; }
		void setValue(int value) { _value = value; }

		Number& operator=(Number const & rhs)
		{
			if (this != &rhs)
				_value = rhs._value;
			return *this;
		}
};

std::ostream& operator<<(std::ostream& os, Number const & n)
{
	os << n.getValue();
	return os;
}

int main(void)
{
	std::cout << BOLD << CYAN << "\n╔════════════════════════════════════════╗" << std::endl;
	std::cout << "║         EX02 - ARRAY CLASS             ║" << std::endl;
	std::cout << "╚════════════════════════════════════════╝" << RESET << std::endl;

	// ========== Test 1: Default constructor ==========
	std::cout << BOLD << YELLOW << "\n[1] Default constructor (empty array)" << RESET << std::endl;
	{
		Array<int> empty;
		std::cout << "Size of empty array: " << CYAN << empty.size() << RESET << std::endl;
		printTest("Empty array has size 0", empty.size() == 0);
	}

	// ========== Test 2: Parametric constructor ==========
	std::cout << BOLD << YELLOW << "\n[2] Parametric constructor with size" << RESET << std::endl;
	{
		Array<int> arr(5);
		std::cout << "Created array with size: " << CYAN << arr.size() << RESET << std::endl;
		printTest("Array size is correct", arr.size() == 5);

		// Check default initialization (tip from subject)
		std::cout << "Default initialized values: ";
		bool allZero = true;
		for (unsigned int i = 0; i < arr.size(); i++)
		{
			std::cout << arr[i] << " ";
			if (arr[i] != 0)
				allZero = false;
		}
		std::cout << std::endl;
		printTest("All elements initialized to 0", allZero);
	}

	// ========== Test 3: Understanding default initialization ==========
	std::cout << BOLD << YELLOW << "\n[3] Default initialization (subject's tip)" << RESET << std::endl;
	{
		std::cout << "Testing: int * a = new int(); then *a:" << std::endl;
		int* a = new int();
		std::cout << "Value of *a: " << MAGENTA << *a << RESET << " (should be 0)" << std::endl;
		printTest("Default-initialized int is 0", *a == 0);
		delete a;

		std::cout << "\nTesting: int * b = new int[5]();" << std::endl;
		int* b = new int[5]();
		std::cout << "Values: ";
		bool allZero = true;
		for (int i = 0; i < 5; i++)
		{
			std::cout << b[i] << " ";
			if (b[i] != 0)
				allZero = false;
		}
		std::cout << std::endl;
		printTest("Array elements initialized to 0", allZero);
		delete[] b;
	}

	// ========== Test 4: Array access and modification ==========
	std::cout << BOLD << YELLOW << "\n[4] Array access and modification" << RESET << std::endl;
	{
		Array<int> arr(5);

		// Fill array
		for (unsigned int i = 0; i < arr.size(); i++)
			arr[i] = i * 10;

		std::cout << "Array after modification: ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << CYAN << arr[i] << RESET << " ";
		std::cout << std::endl;

		printTest("Array modification works", arr[0] == 0 && arr[1] == 10 && arr[4] == 40);
	}

	// ========== Test 5: Copy constructor (deep copy) ==========
	std::cout << BOLD << YELLOW << "\n[5] Copy constructor (deep copy)" << RESET << std::endl;
	{
		Array<int> original(3);
		original[0] = 100;
		original[1] = 200;
		original[2] = 300;

		std::cout << "Original array: ";
		for (unsigned int i = 0; i < original.size(); i++)
			std::cout << GREEN << original[i] << RESET << " ";
		std::cout << std::endl;

		Array<int> copy(original);

		std::cout << "Copied array:   ";
		for (unsigned int i = 0; i < copy.size(); i++)
			std::cout << BLUE << copy[i] << RESET << " ";
		std::cout << std::endl;

		// Modify original
		original[0] = 999;

		std::cout << "After modifying original[0] to 999:" << std::endl;
		std::cout << "Original[0]: " << GREEN << original[0] << RESET << std::endl;
		std::cout << "Copy[0]:     " << BLUE << copy[0] << RESET << std::endl;

		printTest("Deep copy works (copy unaffected)", copy[0] == 100 && original[0] == 999);
	}

	// ========== Test 6: Assignment operator (deep copy) ==========
	std::cout << BOLD << YELLOW << "\n[6] Assignment operator (deep copy)" << RESET << std::endl;
	{
		Array<int> arr1(3);
		arr1[0] = 10;
		arr1[1] = 20;
		arr1[2] = 30;

		Array<int> arr2(5);
		for (unsigned int i = 0; i < arr2.size(); i++)
			arr2[i] = 99;

		std::cout << "Before assignment:" << std::endl;
		std::cout << "arr1 size: " << arr1.size() << ", arr2 size: " << arr2.size() << std::endl;

		arr2 = arr1;

		std::cout << "After arr2 = arr1:" << std::endl;
		std::cout << "arr1 size: " << arr1.size() << ", arr2 size: " << arr2.size() << std::endl;

		// Modify arr1
		arr1[0] = 777;

		std::cout << "After modifying arr1[0] to 777:" << std::endl;
		std::cout << "arr1[0]: " << GREEN << arr1[0] << RESET << std::endl;
		std::cout << "arr2[0]: " << BLUE << arr2[0] << RESET << std::endl;

		printTest("Assignment operator deep copy works", arr2[0] == 10 && arr1[0] == 777);
	}

	// ========== Test 7: Self-assignment ==========
	std::cout << BOLD << YELLOW << "\n[7] Self-assignment protection" << RESET << std::endl;
	{
		Array<int> arr(3);
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;

		// Suppress warning for intentional self-assignment test
		Array<int>& ref = arr;
		arr = ref;

		std::cout << "After self-assignment (arr = arr): ";
		for (unsigned int i = 0; i < arr.size(); i++)
			std::cout << CYAN << arr[i] << RESET << " ";
		std::cout << std::endl;

		printTest("Self-assignment protection works", arr[0] == 1 && arr[1] == 2 && arr[2] == 3);
	}

	// ========== Test 8: Exception handling ==========
	std::cout << BOLD << YELLOW << "\n[8] Out of bounds exception" << RESET << std::endl;
	{
		Array<int> arr(5);
		bool exceptionCaught = false;

		try
		{
			std::cout << "Trying to access arr[10] (size is 5)..." << std::endl;
			int value = arr[10];
			(void)value;
		}
		catch (std::exception const & e)
		{
			exceptionCaught = true;
			std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
		}

		printTest("Exception thrown for out of bounds access", exceptionCaught);

		// Test with empty array
		Array<int> empty;
		exceptionCaught = false;

		try
		{
			std::cout << "Trying to access empty[0]..." << std::endl;
			int value = empty[0];
			(void)value;
		}
		catch (std::exception const & e)
		{
			exceptionCaught = true;
			std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
		}

		printTest("Exception thrown for empty array access", exceptionCaught);
	}

	// ========== Test 9: String array ==========
	std::cout << BOLD << YELLOW << "\n[9] Array of strings" << RESET << std::endl;
	{
		Array<std::string> words(4);
		words[0] = "Hello";
		words[1] = "World";
		words[2] = "from";
		words[3] = "Array";

		std::cout << "String array: ";
		for (unsigned int i = 0; i < words.size(); i++)
			std::cout << MAGENTA << "\"" << words[i] << "\" " << RESET;
		std::cout << std::endl;

		printTest("String array works", words[0] == "Hello" && words[3] == "Array");
	}

	// ========== Test 10: Float array ==========
	std::cout << BOLD << YELLOW << "\n[10] Array of floats" << RESET << std::endl;
	{
		Array<float> floats(4);
		floats[0] = 3.14f;
		floats[1] = 2.71f;
		floats[2] = 1.41f;
		floats[3] = 1.73f;

		std::cout << "Float array: ";
		for (unsigned int i = 0; i < floats.size(); i++)
			std::cout << CYAN << floats[i] << RESET << " ";
		std::cout << std::endl;

		printTest("Float array works", floats[0] > 3.0f && floats[0] < 4.0f);
	}

	// ========== Test 11: Custom class ==========
	std::cout << BOLD << YELLOW << "\n[11] Array of custom class (Number)" << RESET << std::endl;
	{
		Array<Number> numbers(3);
		numbers[0] = Number(100);
		numbers[1] = Number(200);
		numbers[2] = Number(300);

		std::cout << "Number array: ";
		for (unsigned int i = 0; i < numbers.size(); i++)
			std::cout << BLUE << numbers[i] << RESET << " ";
		std::cout << std::endl;

		printTest("Custom class array works", numbers[1].getValue() == 200);
	}

	// ========== Test 12: Const array access ==========
	std::cout << BOLD << YELLOW << "\n[12] Const array access" << RESET << std::endl;
	{
		Array<int> arr(3);
		arr[0] = 10;
		arr[1] = 20;
		arr[2] = 30;

		Array<int> const & constRef = arr;

		std::cout << "Accessing via const reference: ";
		for (unsigned int i = 0; i < constRef.size(); i++)
			std::cout << GREEN << constRef[i] << RESET << " ";
		std::cout << std::endl;

		printTest("Const access works", constRef[1] == 20);
	}

	// ========== Test 13: Large array ==========
	std::cout << BOLD << YELLOW << "\n[13] Large array" << RESET << std::endl;
	{
		Array<int> large(1000);
		large[0] = 1;
		large[999] = 1000;

		std::cout << "Created array of size " << CYAN << large.size() << RESET << std::endl;
		std::cout << "large[0] = " << large[0] << ", large[999] = " << large[999] << std::endl;

		printTest("Large array works", large.size() == 1000 && large[999] == 1000);
	}

	std::cout << BOLD << GREEN << "\n✓ All Array tests completed!\n" << RESET << std::endl;

	return 0;
}
