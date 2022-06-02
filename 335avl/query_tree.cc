/* 
    Daniel Rizzo
    CSCI 335
    Homework 3 Part 2.1
    Professor Sven Dietrich
    March 12th, 2021
    Query_tree.cc
    Main file for Part 2.1 of Homework 3.
*/

#include "avl_tree.h" // Already contains SequenceMap header, so don't include sequence_map.h again. 
//#include "sequence_map.h"
#include <fstream> // For reading from the file, from the name passed in dbx_filename
#include <iostream>
#include <string>
using namespace std;

namespace {

// GetNextWord is a helper function that inputs the next "word" into a parameter
// @param full_line : is the line that contains the next "word" to grab
// @param new_word : is the string that will contain the next "word" in full_line
// @returns true if a new word was found and put into new_word, false otherwise. 
bool GetNextWord(string &full_line, string &new_word) {
  if (full_line.size() <= 1) { // If the line is only one slash, all "words" have already been taken out of it. 
    return false; // Operation failure
  }
  size_t nextslash = full_line.find_first_of('/'); // Get the first instance of a / in the line
  new_word = full_line.substr(0, nextslash); // Set new_word to be the next word, stop at the slash
  full_line.assign(full_line, nextslash + 1, full_line.npos); // Remove this word from the full_line. 
  //cout << full_line << endl;
  //full_line = full_line.substr(nextslash + 1, -1); // Remove this word from the full_line. 
  return true; // New word placed, so operation was successful
}

// @dbx_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) {
  
  // Create Tree

  string db_line; // Create a string to put a line in one at a time
  fstream database; // Create an fstream object
  database.open(dbx_filename, fstream::in); // Set the object to open and read (in) from the given file name
  string an_enz_acro, a_reco_seq;
  while (getline(database, db_line)) { // Read the file line-by-line, insert into db_line 
    if (db_line.find(" ") == db_line.npos) { // Only for lines that do not contain spaces. Skips heading.
      //cout << db_line << endl;
      GetNextWord(db_line, an_enz_acro); // Get the first part of the line using helper function. Delete the word from line
      // - need to take first "word" and insert into an_enz_acro, and delete that word from db_line.
      //cout << an_enz_acro << endl;
      while (GetNextWord(db_line, a_reco_seq)) { // Get next word in the line, returns false if word doesn't exist - "//". 
        //cout << a_reco_seq << endl;
        // Something goes wrong after this.
        if (a_reco_seq.size() > 2) {
          //cout << "Insert: " << endl;
          const SequenceMap new_sequence_map(a_reco_seq, an_enz_acro); // Create another new SequenceMap for inserting.  
          a_tree.insert(new_sequence_map); // Need to change the insert function in the avl_tree.h file
        }
      } // End second while. 
      
    }
  } // End first while.

  database.close();

  // Query Tree 

  string Seq1, Seq2, Seq3; // Obtain user input and assign to variables.
  cout << "Enter first sequence: " << endl;
  cin >> Seq1;
  cout << "Enter second sequence: " << endl;
  cin >> Seq2;
  cout << "Enter third sequence: " << endl;
  cin >> Seq3;
  a_tree.printEnzymeAcronyms(Seq1); // Get acronyms for each, one at a time
  a_tree.printEnzymeAcronyms(Seq2);
  a_tree.printEnzymeAcronyms(Seq3);
  
}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  cout << "Input filename is " << dbx_filename << endl;
  AvlTree<SequenceMap> a_tree;
  QueryTree(dbx_filename, a_tree);
  return 0;
}
