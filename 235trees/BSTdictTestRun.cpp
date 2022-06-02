/*
Daniel Rizzo
CSCI 235
12/16/20
Project 6
BSTdict.cpp
Test file
*/

#include "BSTdict.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    BSTdict<string> Alphabet;
    Alphabet.insert("m");
    Alphabet.insert("a");
    Alphabet.insert("z");
    Alphabet.insert("w");
    Alphabet.insert("x");
    Alphabet.insert("p");
    Alphabet.display();

    Alphabet.remove("w");
    Alphabet.display();

    Alphabet.~BSTdict();
    return 0;

    //Run in g++ compiler w/ : g++ BSTdict.cpp BSTdictTestRun.cpp -std=c++17 
    //OR g++ -o BSTdict.cpp to run just implementation
    //Execute with ./a.out
}

