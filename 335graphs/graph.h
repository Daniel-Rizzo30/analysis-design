/*
    Daniel Rizzo
    CSCI 335
    Homework 6
    Professor Sven Dietrich
    May 11th, 2021
    graph.h
    Graph class implementation as an adjacency list
*/
#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <vector>
#include <list>
using namespace std;

/*
    Graph class

    CONSTRUCTION: with a mandatory number of vertices, defaults to 10 vertices

    ******************PUBLIC OPERATIONS*********************
    void resize(size)          --> Resize the number of vertices to size iff size > vertices_
    size_t size()              --> Return the size of the adjacency list
    bool isEmpty()             --> Returns true if there are no vertices within the graph
    void insertEdge(out, in, c)--> Creates an edge under the adjacency list of 'out'
    double adjacent(out, in)   --> Returns -1 if there is no edge from 'out' to 'in', and returns cost otherwise
    void Dijkstra(start)       --> Performs Dijkstra's Algorithm on this graph
    bool printPathandCost(v) --> Prints the path and cost of v using recursion
    bool printPath(v)        --> For printing the path of v within the call of printPathandCost()
    ***********************STRUCTS**************************
    Edge: stores the vertex the edge goes to and the cost of the path
    Vertex: stores the index / name of the vertex, the outgoing edges, and the cost of getting to that vertex
*/

class Graph {
    public:

    // Constructor
    Graph(int size = 10) : vertices_{size} {
        Adjacency_List_.resize(vertices_); // Set the adjacency list to the correct sizd
        for (size_t i = 0; i < Adjacency_List_.size(); i++) {
            Adjacency_List_[i].index_ = i + 1; // Set each vertex's index
        }

    }

    // Function that resizes the Adjacency_List_ if needed
    void resize(int size) {
        if (size > vertices_) { // Only allows growth so that no vertices can be deleted
            Adjacency_List_.resize(size); // Calls resizd
            vertices_ = size; // Update vertices_
            for (size_t i = 0; i < Adjacency_List_.size(); i++) {
                Adjacency_List_[i].index_ = i + 1; // Set each vertex's index
            }
        }
    }

    // A simple getter function to obtain the number of vertices in the graph
    size_t size() {
        return Adjacency_List_.size();
    }

    // A function to check if there are any vertices in the graph
    bool isEmpty() const { 
        return vertices_ == 0; 
    }

    /**
     * Creates an edge within the outgoing vertex's adjacency list
     * @param out_vertex is the vertex's index in Adjacency_List_ that the edge is coming from
     * @param in_vertex is the vertex's index in Adjacency_List_ that the edge is going to
     * @param c is the cost of the edge when taken
     */
    void insertEdge(int out_vertex, int in_vertex, double c) {
        Edge E(in_vertex, c); // Creates an edge with the parameters
        if (out_vertex - 1 <= Adjacency_List_.size()) { // Checks to see if the vertex is in the graph
            Adjacency_List_[out_vertex - 1].adjacency_.push_back(E); // Add the edge to the proper vertex
        }
        else { // If not in graph, resize to include the vertex
            resize(out_vertex);
            Adjacency_List_[out_vertex - 1].adjacency_.push_back(E); // Add the edge to the proper vertex
        }
        edges_++; // Increment edges_
    }

    /**
     * Checks to see if the two parameters are adjacent
     * @param out_vertex is the vertex's index in Adjacency_List_ that the edge should come from
     * @param in_vertex is the vertex's index in Adjacency_List_ that the edge should go to
     * @return -1.0 if there is no connection, returns the cost if there is a connection.
     */
    double adjacent(int out_vertex, int in_vertex) {
        double adjacent = -1.0; // Set the cost to this sentinal value 
        if (out_vertex == in_vertex) return 0; // If the out and in vertex's are the same, there is always no cost
        if (out_vertex <= Adjacency_List_.size()) { // If the out_vertex is in the Adjacency_List_
            for (std::list<Edge>::iterator it = Adjacency_List_[out_vertex - 1].adjacency_.begin(); 
                    it != Adjacency_List_[out_vertex - 1].adjacency_.end(); ++it) { // Check each edge the vertex has
                if (it->in_vertex_ == in_vertex) { // If there is a matching in_vertex
                    adjacent = it->cost_; // Update the cost
                    break; // Stop looking
                }
            }
        }
        return adjacent; // adjacent is never updated to -1.0 so -1.0 works as a value to signal that there is no edge
    }

    /**
     * Implements Dijkstra's Algorithm for finding the shortest path within this graph
     * @param start_vertex is the vertex to start looking for the shortest path at
     */
    void Dijkstra(int start_vertex) {
        Vertex* Start = &Adjacency_List_[start_vertex - 1]; // Use a vertex pointer to track which indexes are used
        for (size_t i = 0; i < Adjacency_List_.size(); i++) { // Reset each vertex's values
            Adjacency_List_[i].previous_in_path_ = infinity_; // infinity_ simulates the nonreal number infinity
            Adjacency_List_[i].cost_ = infinity_;
            Adjacency_List_[i].known_ = false;
        }

        Start->previous_in_path_ = start_vertex; // start_vertex is the only vertex in this vertex's path
        Start->cost_ = 0; // Set the start vertex's values to 0 and true
        Start->known_ = true;

        BinaryHeap<Vertex*> Q1; // Create a heap as specified in the HW6 pdf
        Q1.insert(Start); // Insert the start vertex

        while (!Q1.isEmpty()) { // Only break this while loop if the priority queue is empty
            Vertex* V;
            Q1.deleteMin(V); // Copy the small-cost-vertex into this pointer V
            V->known_ = true; // Set V to true if not already
            for (std::list<Edge>::iterator it = V->adjacency_.begin(); 
                    it != V->adjacency_.end(); ++it) { // For each edge / adjacent vertex for V
                Vertex* W = &Adjacency_List_[it->in_vertex_ - 1]; // Create Vertex* W
                double d = it->cost_; // Copy cost into d
                const double new_dist = V->cost_ + d; // Calculate what would be the new_dist
                if (new_dist < W->cost_) { // Check if the new_dist is better / shorter than what W's is now
                    W->cost_ = new_dist; // If it is, update W 
                    Q1.insert(W); // Insert W into the priority queue
                    W->previous_in_path_ = V->index_; // Set the path of W to V's index
                }
            }
        }
    }

    /**
     * Print path and cost after Dijkstra has run
     * @param vertex is the vertex's index whose path / cost are being calculated
     * @return true if it is connected through Dijkstra's Algorithm
     * @return false if it is not connected to the start vertex used in Dijkstra's Algorithm
     */
    bool printPathandCost(int vertex) {
        cout << vertex << ": "; // Start with printing that this index is the vertex it's calculating
        if (Adjacency_List_[vertex - 1].previous_in_path_ == infinity_) { // If not connected
            cout << "not_possible" << endl; // Print not possible with the _
            return false; // Can't calc path
        }
        else if (Adjacency_List_[vertex - 1].previous_in_path_ != vertex) {  // If the path isn't just the vertex itself
            printPath(Adjacency_List_[vertex - 1].previous_in_path_); // Print the path of the previous vertex
            cout << " "; // Need spacing
        }
        cout << vertex << " cost: " << std::fixed << std::setprecision(1) << Adjacency_List_[vertex - 1].cost_ << endl;
        // Lastly print this vertex's index, and its cost set to always show 1 number after the decimal point
        return true; // Path is possible
    }

    /**
     * Print the path of the vertex, without cost or declaring what vertex this is first, and without using endl
     * Used only as a call within printPathandCost() so that every single vertex's cost is not calculated and printed
     * along the way
     * @param vertex is the vertex whose path is being calculated 
     */
    bool printPath(int vertex) {
        if (Adjacency_List_[vertex - 1].previous_in_path_ == infinity_) { // Pathing is not possible
            cout << "not_possible";
            return false;
        }
        else if (Adjacency_List_[vertex - 1].previous_in_path_ != vertex) { // Pathing is possible
            printPath(Adjacency_List_[vertex - 1].previous_in_path_); // Recursive
            cout << " ";
        }
        cout << vertex;
        return true;
    }


    private: 

    // Data structure to neatly wrap up what needs to be contained within an edge
    struct Edge {

        int in_vertex_; // The vertex this edge goes to
        double cost_; // The cost of taking this edge

        // Constructor
        Edge(int v, double c) 
        : in_vertex_{v}, cost_{c} {}

        // Default Constructor
        Edge() = default;

        /**
         * Operator overload for edge, was needed at one point within the code
         * Still good to have this even though it is not used
         * @returns true if e1's cost is less than e2's 
         */
        friend bool operator<(const Edge& e1, const Edge& e2) {
            if (e1.cost_ < e2.cost_) {
                return true;
            }
            else {
                return false;
            }
        }

        /**
         * Takes a list of edges and inserts into a vector and returns that vector
         * @param a_list is the list to be made into a vector
         * @return vector<Edge> made from the parameter list
         */
        vector<Edge> toVector(list<Edge> a_list) {
            vector<Edge> v;
            for (std::list<Edge>::iterator it = a_list.begin(); it != a_list.end(); ++it) {
                v.push_back(*it); // Add each element from the list
            }
            return v;
        }

    };

    // Data structure to contain all info about a vertex
    struct Vertex {
        int index_; // The index of this vertex within Adjaceny_List_
        list<Edge> adjacency_; // All edges that come from this vertex
        bool known_; // Used for Dijkstra's Algorithm
        double cost_; // To save the cheapest cost of this vertex after Dijkstra's
        int previous_in_path_; // To calculate the path used to get to this vertex

        /**
         * Operator overload for Vertex, used within binary_heap.h to decide what the Min is
         * @returns true if v1's cost is less than v2's, false otherwise
         */
        friend bool operator<(const Vertex& v1, const Vertex& v2) {
            if (v1.cost_ < v2.cost_) {
                return true;
            }
            else {
                return false;
            }
        }
    };

    int vertices_ = 0, edges_ = 0; // Internal data members to track V + E if ever needed
    const double infinity_ = 2147483647; // Create a member variable that is used for comparison to infinity
    vector<Vertex> Adjacency_List_; // The vector that contains all Vertex's of the graph
};

#endif
