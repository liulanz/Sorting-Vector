// Modified by Liulan Zheng
// Modifications are stated in the comment begin with "#"


#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>
#include <functional>
using namespace std;

/**
 * Simple insertion sort.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a , Comparator compare )
{
    for( int p = 1; p < a.size( ); ++p )
    {
        Comparable tmp = std::move( a[ p ] );

        int j;
        for( j = p; j > 0 && compare(tmp, a[ j - 1 ]); --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort vector from smallest to largest
 *				or from largest to smallest
 */
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a, int left, int right , Comparator compare )
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j;

        for( j = p; j > left && compare(tmp ,a[ j - 1 ]); --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable>
void shellsort( vector<Comparable> & a )
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); ++i )
        {
            Comparable tmp = std::move( a[ i ] );
            int j = i;

            for( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = std::move( a[ j - gap ] );
            a[ j ] = std::move( tmp );
        }
}



/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort vector from smallest to largest
 *				or from largest to smallest
 */
template <typename Comparable, typename Comparator>
void percDown( vector<Comparable> & a, int i, int n, Comparator compare )
{
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        child = leftChild( i );
        if( child != n - 1 && compare(a[ child ], a[ child + 1 ]) )
            ++child;
        if( compare(tmp ,a[ child ] ))
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}

/**
 * Standard heapsort.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort vector from smallest to largest
 *				or from largest to smallest
 */
template <typename Comparable,typename Comparator>
void heapsort( vector<Comparable> & a, Comparator compare )
{
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size( ), compare);
    for( int j = a.size( ) - 1; j > 0; --j )
    {
        std::swap( a[ 0 ], a[ j ] );       /* deleteMax or deleteMin (delete the root of heap)*/
        percDown( a, 0, j, compare);
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort vector from smallest to largest
 *				or from largest to smallest
 */
template <typename Comparable, typename Comparator>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
            int leftPos, int rightPos, int rightEnd, Comparator compare)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if(compare(a[ leftPos ] , a[ rightPos ]) || a[ leftPos ] == a[ rightPos ])
            tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
        else
            tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    while( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );

    while( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    // Copy tmpArray back
    for( int i = 0; i < numElements; ++i, --rightEnd )
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort vector from smallest to largest
 *				or from largest to smallest
 */
template <typename Comparable, typename Comparator>
void mergeSort( vector<Comparable> & a,
                vector<Comparable> & tmpArray, int left, int right, 
				Comparator compare )
{
    if( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center , compare);
        mergeSort( a, tmpArray, center + 1, right , compare);
        merge( a, tmpArray, left, center + 1, right, compare);
    }
}

/**
 * Mergesort algorithm (driver).
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort vector from smallest to largest
 *				or from largest to smallest
 */
template <typename Comparable, typename Comparator>
void mergeSort( vector<Comparable> & a , Comparator compare)
{
    vector<Comparable> tmpArray( a.size( ) );
    mergeSort( a, tmpArray, 0, a.size( ) - 1, compare);
}

/**
 * #(This function is added)
 * Set the middle element of vector a as new pivot
 * Swap pivot and the last element 
 * @Return pivot
 */
template <typename Comparable>
const Comparable & middle( vector<Comparable> & a, int left, int right)
{
	int center = ( left + right ) / 2;
	std::swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
	
}

/**
 * #(This function is added)
 * Set the first element of vector a as new pivot
 * Swap pivot and the last element 
 * @Return pivot
 */
template <typename Comparable>
const Comparable & first( vector<Comparable> & a, int left, int right)
{
	std::swap( a[ left+1 ], a[ right  ] );
    return a[ right];
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 * #(compare is added)
 */
template <typename Comparable, typename Comparator>
const Comparable & median3( vector<Comparable> & a, int left, int right, Comparator compare)
{
    int center = ( left + right ) / 2;
    
    if( compare(a[ center ] , a[ left ] ))
        std::swap( a[ left ], a[ center ] );
    if( compare(a[ right ] , a[ left ] ))
        std::swap( a[ left ], a[ right ] );
    if( compare(a[ right ] , a[ center ] ))
        std::swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
    std::swap( a[ center ], a[ right -1 ] );
    return a[ right - 1 ];
}

/**
 * #(This function is added (similar to quicksort))
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename Comparable, typename Comparator>
void quicksortFirst( vector<Comparable> & a, int left, int right, Comparator compare)
{
    if( left + 10 <= right )
    {
		const Comparable & pivot = first(a, left, right);
        // Begin partitioning
        int i = left, j = right;
        for( ; ; )
        {
            while( compare(a[ ++i ] , pivot )) { }
            while( compare(pivot , a[ --j ] )) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }
        std::swap( a[ i ], a[ right ] );  // Restore pivot
        quicksortFirst( a, left, i, compare);     // Sort left side of pivot
        quicksortFirst( a, i, right, compare);    // Sort right side of pivot
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, compare);
}

/**
 * #(This function is added (similar to quicksort))
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename Comparable, typename Comparator>
void quicksortMiddle( vector<Comparable> & a, int left, int right, Comparator compare)
{
    if( left + 10 <= right )
    {
		const Comparable & pivot = middle(a, left, right);
        // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( compare(a[ ++i ] , pivot )) { }
            while( compare(pivot , a[ --j ] )) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }
        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

        quicksortMiddle( a, left, i - 1, compare);     // Sort left side of pivot
        quicksortMiddle( a, i + 1, right, compare);    // Sort right side of pivot
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, compare);
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename Comparable, typename Comparator>
void quicksort( vector<Comparable> & a, int left, int right, Comparator compare)
{
	
    if( left + 10 <= right )
    {
		const Comparable & pivot = median3( a, left, right, compare);
            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( compare(a[ ++i ] , pivot )) { }
            while( compare(pivot , a[ --j ] )) { }
            if( i <j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }
        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot
        quicksort( a, left, i - 1, compare);     // Sort left side of pivot
        quicksort( a, i + 1, right, compare);    // Sort right side of pivot
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, compare);
}

/**
 * Quicksort algorithm (driver).
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename Comparable, typename Comparator>
void quicksort( vector<Comparable> & a, Comparator compare)
{
    quicksort( a, 0, a.size( ) - 1, compare);
}

/**
 * #(This function is added)
 * Quicksort algorithm with middle element of vector used as pivot
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename Comparable, typename Comparator>
void quicksortMiddle( vector<Comparable> & a, Comparator compare)
{
    quicksortMiddle( a, 0, a.size( ) - 1, compare);
}

/**
 * #(This function is added)
 * Quicksort algorithm with first element of vector used as pivot
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename Comparable, typename Comparator>
void quicksortFirst( vector<Comparable> & a, Comparator compare)
{
    quicksortFirst( a, 0, a.size( ) - 1, compare);
}

/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int left, int right, int k )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );
            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }
        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot
            // Recurse; only this part changes
        if( k <= i )
            quickSelect( a, left, i - 1, k );
        else if( k > i + 1 )
            quickSelect( a, i + 1, right, k );
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int k )
{
    quickSelect( a, 0, a.size( ) - 1, k );
}


template <typename Comparable>
void SORT( vector<Comparable> & items )
{
    if( items.size( ) > 1 )
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;
        
        auto chosenItem = items[ items.size( ) / 2 ];
        
        for( auto & i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );
            else if( chosenItem < i )
                larger.push_back( std::move( i ) );
            else
                same.push_back( std::move( i ) );
        }
        
        SORT( smaller );     // Recursive call!
        SORT( larger );      // Recursive call!
        
        std::move( begin( smaller ), end( smaller ), begin( items ) );
        std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
        std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );

/*
        items.clear( );
        items.insert( end( items ), begin( smaller ), end( smaller ) );
        items.insert( end( items ), begin( same ), end( same ) );
        items.insert( end( items ), begin( larger ), end( larger ) );
*/
    }
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 * #(compare is added)
 * # @compare: less_than or greater_than, able to sort smallest to largest
 *				or largest to smallest
 */
template <typename RandomIterator, typename Comparator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end,
                    Comparator compare )
{
    if( begin == end )
        return;
        
    RandomIterator j;

    for( RandomIterator p = begin+1; p != end; ++p )
    {
        auto tmp = std::move( *p );
        for( j = p; j != begin && compare( tmp, *( j-1 ) ); --j )
            *j = std::move( *(j-1) );
        *j = std::move( tmp );
    }
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
template <typename RandomIterator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end )
{
    insertionSort( begin, end, less<decltype(*begin )>{ } );
}



#endif
