// Part II
// Testing Sorting Algorithms (2nd program)
// Liulan Zheng
/*
	To execute this function in terminal should type
	  ./test_sorting_algorithms	<input_type>	<input_size>	<comparison_type>
	input type can be "random" or "sorted_small_to_large"
	comparison_type can be "less" or "greater"
	This function tests 3 variations of the quicksort algorithm by using different pivots:
		a) Median of three
		b) Middle pivot (always	select	the	middle item in	the	array)
		c) First pivot (always	select	the	first item in	the	array)
	This function prints 1 for verified order if vector is sorted after sorting.
	Also prints how long each sorting method takes to sort the vector
*/

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

namespace {

// Test function that shows how you can time a piece of code.
// Just times a simple loop.
/*void TestTimingQ1() {
  cout << "Test Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();    
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}*/

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
	vector<int> a;
	for (size_t i = 0; i < size_of_vector; ++i)
	a.push_back(rand());
	return a;
}

/**
 * Check if a vector is in order (from smallest to largest or from largest to smallest)
 * @return true if vector is in order, otherwise return false
 */
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator compare) {
	if(input.size() == 0)
		return true;

	for(size_t i = 0; i < input.size()-1; i++)
	{
		if(compare(input[i+1], input[i])) // return false if invalid order is detected
			return false;
	}		
	return true;
}

/**
 * Signature for quicksort (choose median of first, middle, last of vector as pivot)
 * Prints how long it takes to sort a vector
 */
template <typename Comparable, typename Comparator>
void QuickSort1(vector<Comparable> &a, Comparator compare) {
	// pivot is the median of the three
	cout << "[ Median of three ]" << endl;
	
	cout << "Run time: ";
	const auto begin = chrono::high_resolution_clock::now();
	// Time this piece of code.
	quicksort(a, compare);
	// End of piece of code to time.
	const auto end = chrono::high_resolution_clock::now();    
	cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns";
	cout << " or ";
	cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
	
}

/**
 * Signature for quicksort (choose middle element of vector as pivot)
 * Prints how long it takes to sort a vector
 */
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable> &a, Comparator compare) {
	// pivot is the middle element of the array
	cout << "[ Middle ]" << endl;
	
	cout << "Run time: ";
	const auto begin = chrono::high_resolution_clock::now();
	// Time this piece of code.
	quicksortMiddle(a, compare);	
	// End of piece of code to time.
	const auto end = chrono::high_resolution_clock::now();    
	cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns";
	cout << " or ";
	cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
}

/**
 * Signature for quicksort (choose first element of vector as pivot)
 * Prints how long it takes to sort a vector
 */
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable> &a, Comparator compare) {
	// pivot is the first element of the array
	cout << "[ First ]" << endl;
	
	cout << "Run time: ";
	const auto begin = chrono::high_resolution_clock::now();
	// Time this piece of code.
	quicksortFirst(a, compare);
	// End of piece of code to time.
	const auto end = chrono::high_resolution_clock::now();    
	cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns";
	cout << " or ";
	cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
}

}  // namespace


int main(int argc, char **argv) {
	if (argc != 4) {
		cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
		return 0;
	}
	const string input_type = string(argv[1]);
	const int input_size = stoi(string(argv[2]));
	const string comparison_type = string(argv[3]);
	if (input_type != "random" && input_type != "sorted_small_to_large") {
		cout << "Invalid input type" << endl;
		return 0;
	}
	if (input_size <= 0) {
		cout << "Invalid size" << endl;
		return 0;
	}
	if (comparison_type != "less" && comparison_type != "greater") {
		cout << "Invalid comparison type" << endl;
		return 0;
	}
	
	cout << "Testing quicksort: " << input_type << " " << input_size << " numbers " 
		<< comparison_type << endl;
	vector<int> input_vector;
	if (input_type == "random") {
		input_vector = GenerateRandomVector(input_size);
		
	} else {
		for(int i = 0; i < input_size; i++)
			input_vector.push_back(i);
	}
	cout << "-----------------" << endl;
	if(comparison_type == "greater")
	{
		QuickSort1(input_vector, greater<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;
		
		cout << endl;
		cout << "-----------------" << endl;	
		cout << endl;
		
		QuickSort2(input_vector, greater<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;
		
		cout << endl;
		cout << "----------------" << endl;
		cout << endl;
		
		QuickSort3(input_vector, greater<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;
		
		cout << endl;
		cout << "----------------" << endl;
		cout << endl;
	}
	else if(comparison_type == "less")
	{
		QuickSort1(input_vector, less<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;
		
		cout << endl;
		cout << "-----------------" << endl;
		cout << endl;
		
		QuickSort2(input_vector, less<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;
		
		cout << endl;
		cout << "----------------" << endl; 
		cout << endl;
		
		QuickSort3(input_vector, less<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;
		
		cout << endl;
		cout << "----------------" << endl;
		cout << endl;
	}
 
	return 0;
}
