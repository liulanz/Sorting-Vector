# Sorting-Vector
This program will sort any unsorted vector using heap sort, merge sort, and 3 variants of quick sort algorithms

To compile type:

 make all

To execute part I:
	./test_sorting_algorithms	<input_type>	<input_size>	<comparison_type>
	<input_type> can be "random" or "sorted_small_to_large"
	<comparison_type> can be "less" or "greater"
	Part I will sort the vector using 3 different sorting method: heap sort, merge sort, and quick sort
	The program will test if the vector is sorted correctly after each of sort method, 
		and it will print how long does it take to sort.
		
To execute part II: 
	./test_qsort_algorithm	<input_type>	<input_size>	<comparison_type>
	<input_type> can be "random" or "sorted_small_to_large"
	<comparison_type> can be "less" or "greater"
	Part II will sort vector with 3 variants of quick sort by using 3 different pivots
		a) Median of three (first, middle, last elements of the vector)
		b) Middle pivot (always	select	the	middle item in the vector)
		c) First pivot (always	select	the	first item in the vector)
	The program will test if the vector is sorted correctly after each of sort method, 
		and it will print how long does it take to sort.
	
To clean object files and executables type:

 make clean

