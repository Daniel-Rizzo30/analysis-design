/*
  Daniel Rizzo
  CSCI 335
  Homework 5
  Professor Sven Dietrich
  April 27th, 2021
  test_sorting_algorithms.cc
  Testing for multiple sorting algorithms
*/

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.
/*
void TestingTiming() {
  cout << "Testing Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();    
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
}
*/

/** 
 * Function to check if a vector already contains the integer x
 * Copies inside of the vector were giving the sorting algorithms trouble
 * @return true if the vector contains x
 */
/*
bool Contains(vector<int>& vec, int x) {
  bool contains = false;
  for (size_t i = 0; i < vec.size(); i++) { // Check every element - very costly in terms of time.
    if (vec[i] == x) {
      contains = true;
    }
  }
  return contains;
} 
*/

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  vector<int> RV;
  for (size_t i = 0; i < size_of_vector; i++) { // Add an element within the given size
    RV.push_back(rand()); // Pushback using rand() function to give a random number. Makes lower numbers slightly more likely
  }
  return RV;
}

// Generate and returns sorted vector of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  vector<int> RV; // Can hold negative values
  /* Implementation for inserting with random values
  int section = (RAND_MAX - 100000) / size_of_vector; // Max value each element can change by on average
  if (smaller_to_larger) { // Smaller to larger route
    for (size_t i = 0; i < size_of_vector; i++) { // for the size of the vector
      if (i == 0) { // Set first value differently
        RV.push_back(rand() % 100000); // Make sure it is small enough so that others have room to grow
      }
      else {
        RV.push_back((rand() % section) + RV[i-1]); // Build off of the previous element to get a new element
      }
    }
  }
  else { // Larger to smaller route
    for (size_t i = 0; i < size_of_vector; i++) { // for the size of the vector
      if (i == 0) { // Set first value differently
        RV.push_back((rand() % 100000) + (RAND_MAX - 100000)); // Make sure it is big enough so others have room to shrink
      }
      else {
        RV.push_back(RV[i-1] - (rand() % section)); // Build off of the previous element to get a new element
      }
    }
  } */
  // Implementation for inserting numbers 1 - size_of_vector into the vector
  if (smaller_to_larger) { // Smaller to larger route
    for (size_t i = 1; i <= size_of_vector; i++) { // for the size of the vector
      RV.push_back(i);
    }
  }
  else { // Larger to smaller route
    for (size_t i = size_of_vector; i > 0; i--) { // for the size of the vector
      RV.push_back(i);
    }
  }
  return RV;
}

// Verifies that a vector is sorted given a comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
  bool order = true;
  for (size_t i = 0; i < input.size() - 1; i++) { // For each pair of adjacent elements in the vector
    if ((!less_than(input[i], input[i + 1])) && input[i] != input[i + 1]) { // If the comparator returns false, and if adjacent elements aren't equal
      order = false; // The order is incorrect
      break; // Already can say that this vector isn't in order - break for loop
    }
  }
  return order; // True if order was never found false, false if order was ever found to be false.

}

// Computes duration given a start time and a stop time in nano seconds
auto ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time) {
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count(); // Computes the difference and converts to ns
}

// Wrapper function to test the different sorting algorithms
int testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
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
  
  // This block of code to be removed for your final submission.
  //TestingTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " " << comparison_type << endl << endl;
  vector<int> input_vector;
  // Generate the vector.
  if (input_type == "random") {
    // Generate random vector
    input_vector = GenerateRandomVector(input_size);
    srand(time(0)); // Set seed for RNG, use current time so that it's more random.
  } 
  else if (input_type == "sorted_small_to_large") {
    // Generate sorted vector small to big.
    input_vector = GenerateSortedVector(input_size, true);
  }
  else {
    // Generate sorted vector big to small.
    input_vector = GenerateSortedVector(input_size, false);
  }
  vector<int> copy = input_vector;

  // Call quicksort / heapsort / mergesort using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ... with counting start and stop time between calls and computing. And calling verify.

  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...

  if (comparison_type == "less") {
    cout << "HeapSort" << endl << endl; // Heapsort
    const auto beginheap = chrono::high_resolution_clock::now(); // Check time now
    HeapSort(input_vector, less<int>{}); // Sort
    const auto endheap = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginheap, endheap) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl << endl; // Display if correct

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "MergeSort" << endl << endl; // Mergesort
    const auto beginmerge = chrono::high_resolution_clock::now(); // Check time now
    MergeSort(input_vector, less<int>{}); // Sort
    const auto endmerge = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginmerge, endmerge) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl << endl;

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "QuickSort" << endl << endl; // Quicksort
    const auto beginquick = chrono::high_resolution_clock::now(); // Check time now
    QuickSort(input_vector, less<int>{}); // Sort
    const auto endquick = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginquick, endquick) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl << endl; // Display if correct

    cout << "Testing Quicksort Pivot Implementations" << endl << endl;

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "Median of Three" << endl << endl; // Median of Three
    const auto beginmed = chrono::high_resolution_clock::now(); // Check time now
    QuickSort(input_vector, less<int>{}); // Sort
    const auto endmed = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginmed, endmed) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl << endl; // Display if correct

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "Middle" << endl << endl; // Middle
    const auto beginmid = chrono::high_resolution_clock::now(); // Check time now
    QuickSort2(input_vector, less<int>{}); // Sort
    const auto endmid = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginmid, endmid) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl << endl; // Display if correct

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "First" << endl << endl; // First
    const auto beginfirst = chrono::high_resolution_clock::now(); // Check time now
    QuickSort3(input_vector, less<int>{}); // Sort
    const auto endfirst = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginfirst, endfirst) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << endl << endl; // Display if correct
  }
  else { // Greater 
    cout << "HeapSort" << endl << endl; // Heapsort
    const auto beginheap = chrono::high_resolution_clock::now(); // Check time now
    HeapSort(input_vector, greater<int>{}); // Sort
    const auto endheap = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginheap, endheap) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl << endl; // Display if correct

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "MergeSort" << endl << endl; // Mergesort
    const auto beginmerge = chrono::high_resolution_clock::now(); // Check time now
    MergeSort(input_vector, greater<int>{}); // Sort
    const auto endmerge = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginmerge, endmerge) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl << endl;

    input_vector = copy;
    cout << "QuickSort" << endl << endl; // Quicksort
    const auto beginquick = chrono::high_resolution_clock::now(); // Check time now
    QuickSort(input_vector, greater<int>{}); // Sort
    const auto endquick = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginquick, endquick) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl << endl; // Display if correct
    
    cout << "Testing Quicksort Pivot Implementations" << endl << endl;

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "Median of Three" << endl << endl; // Median of Three
    const auto beginmed = chrono::high_resolution_clock::now(); // Check time now
    QuickSort(input_vector, greater<int>{}); // Sort
    const auto endmed = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginmed, endmed) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl << endl; // Display if correct

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "Middle" << endl << endl; // Middle
    const auto beginmid = chrono::high_resolution_clock::now(); // Check time now
    QuickSort2(input_vector, greater<int>{}); // Sort
    const auto endmid = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginmid, endmid) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl << endl; // Display if correct

    input_vector = copy; // Reset vector back to initial state before previous sort
    cout << "First" << endl << endl; // First
    const auto beginfirst = chrono::high_resolution_clock::now(); // Check time now
    QuickSort3(input_vector, greater<int>{}); // Sort
    const auto endfirst = chrono::high_resolution_clock::now(); // Check end time
    cout << "Runtime: " << ComputeDuration(beginfirst, endfirst) << " ns" << endl; // Display run time
    cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl << endl; // Display if correct
  }
}

// Do not change anything below

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  testSortingWrapper(argc, argv);

  return 0;
}
