/*
    Daniel Rizzo
    CSCI 335
    Homework 6
    Professor Sven Dietrich
    May 11th, 2021
    FindPaths.cc
    Testing for Dijkstra's Algorithm Implementation
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "graph.h"
using namespace std;

// GetNextNumber is a helper function that inputs the next "number" into a parameter
// @param full_line : is the line that contains the next "number" to grab
// @param new_word : is the string that will contain the next "number" in full_line
// @returns true if a new number was found and put into new_word, false otherwise. 
bool GetNextNumber(string &full_line, string &new_number) {
  if (full_line.find_first_of("1234567890") == full_line.npos) { // If no numbers in the line,  
    return false; // Operation failure
  }
  size_t next_numerical = full_line.find_first_of("1234567890."); // Get first instance of a number
  full_line = full_line.substr(next_numerical, full_line.npos); // Cut out anything from beginning of full_line
  size_t next_non_number = full_line.find_first_not_of("1234567890."); // Find first char that isn't in a number
  new_number = full_line.substr(0, next_non_number); // Give next number to new_number
  if (next_non_number == full_line.npos) { // If next non number is the end of the string
    full_line = ""; // Make the string empty
  }
  else {
    full_line.assign(full_line, next_non_number, full_line.npos); // Otherwise remove this number from the full_line. 
  }
  return true; // New number placed, so operation was successful
}

int findPathDriver(int argc, char **argv) {
    const string graph_filename(argv[1]); // Grab the filenames from their respective places
    const int start_vertex = stoi(argv[2]); // Grab start vertex and convert to integer
    fstream graph_file;
    string next_line, next_number;
    graph_file.open(graph_filename, fstream::in); // Open up the graph file

    // Create Graph
    getline(graph_file, next_line); // Get the number of vertices into next_line
    GetNextNumber(next_line, next_number); // Make sure the line contains just a number
    int vertices = stoi(next_number); // Change the string into an integer
    Graph G(vertices); // Create the graph

    // Enter while loop for creating edges
    while(getline(graph_file, next_line)) { 
      GetNextNumber(next_line, next_number); // Obtain the vertex number from the line
      int out_vertex = stoi(next_number); // Convert to int
      while(GetNextNumber(next_line, next_number)) { // Obtain the vertex to connect to
        int in_vertex = stoi(next_number); // Convert to int
        if (!GetNextNumber(next_line, next_number)) { // Obtain the cost, if it doesn't exist, break
          break; // Break while loop
        }
        double cost = stod(next_number); // Convert to double
        G.insertEdge(out_vertex, in_vertex, cost); // Causing seg fault
      }
    }
    graph_file.close();

    // Test Dijkstra's Algorithm Implementation
    G.Dijkstra(start_vertex); // Call Dijkstra's Algorithm
    for (size_t i = 1; i <= G.size(); i++) {
      G.printPathandCost(i); // Get Path and Cost for each Vertex
    }

    return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    findPathDriver(argc, argv);

    return 0;
}
