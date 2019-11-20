// Part I
// Testing Sorting Algorithms
// Liulan Zheng
/*
	To execute this function:
		/test_sorting_algorithms	<input_type>	<input_size>	<comparison_type>
		input type can be "random" or "sorted_small_to_large"
		comparison_type can be "less" or "greater"
	
	This function will test three type of sorting: heapsort, quicksort, and mergesort
	After each sort, it will print if the sorting is correct, and it will also prints
	how long it took for each method to sort array
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

/*void TestTiming() {
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
		if(compare(input[i+1], input[i])) // or if(!compare(input[i], input[i+1]))
			return false;
	}		
	return true;
}


// Signature for quicksort (heapsort / mergesort similar signatures)*template <typename Comparable, typename Comparator>
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable> &a, Comparator compare) {
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

// Signature for quicksort (heapsort / mergesort similar signatures)
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable> &a, Comparator compare) {
	cout << "Run time: ";
	const auto begin = chrono::high_resolution_clock::now();
	// Time this piece of code.
	mergeSort(a, compare);
	// End of piece of code to time.
	const auto end = chrono::high_resolution_clock::now();    
	cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns";
	cout << " or ";
	cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}



// Signature for quicksort (heapsort / mergesort similar signatures)
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable> &a, Comparator compare) {
	cout << "Run time: ";
	const auto begin = chrono::high_resolution_clock::now();
	// Time this piece of code.
	heapsort(a, compare);
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
  
  
	cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " 
       << comparison_type << endl;
	vector<int> input_vector;
	if (input_type == "random") {
		input_vector = GenerateRandomVector(input_size);
	} else {
	// Generate sorted vector.
		for(int i = 0; i < input_size; i++)
			input_vector.push_back(i);
	}
	cout << "-----------------" << endl;
	if(comparison_type == "greater")
	{
		cout << "[ Heap Sort ]" << endl;
		HeapSort(input_vector, greater<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;

		cout << endl;
		cout << "-----------------" << endl; 
		cout << endl;

		cout << "[ Merge Sort ]" << endl;
		MergeSort(input_vector, greater<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;
		
		cout << endl;
		cout << "-----------------" << endl; 
		cout << endl;

		cout << "[ Quick Sort ]" << endl;
		QuickSort(input_vector, greater<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;
		
		cout << endl;
		cout << "-----------------" << endl; 
		cout << endl;
	}
	else if(comparison_type == "less")
	{
		
		cout << "[ Heap Sort ]" << endl;
		HeapSort(input_vector, less<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

		cout << endl;
		cout << "-----------------" << endl; 
		cout << endl;

		cout << "[ Merge Sort ]" <<endl;
		MergeSort(input_vector, less<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

		cout << endl;
		cout << "-----------------" << endl; 
		cout << endl;

		cout << "[ Quick Sort ]" << endl;
		QuickSort(input_vector, less<int>{});
		cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl;

		cout << endl;
		cout << "-----------------" << endl; 
		cout << endl;	
	}
	return 0;
}
