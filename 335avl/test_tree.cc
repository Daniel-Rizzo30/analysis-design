/* 
    Daniel Rizzo
    CSCI 335
    Homework 3 Part 2.2
    Professor Sven Dietrich
    March 12th, 2021
    test_tree.cc
    Main file for Part 2.2 of Homework 3. 
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

// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {

  // 1.) Create Tree

  string db_line; // Create a string to put a line in one at a time
  fstream seq_db; // Create an fstream object
  seq_db.open(dbx_filename, fstream::in); // Set the object to open and read (in) from the given file name
  string an_enz_acro, a_reco_seq;
  while (getline(seq_db, db_line)) { // Read the file line-by-line, insert into db_line 
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

  seq_db.close();

  // 2.) Print Number of Nodes

  cout << "2: " << a_tree.NumberofNodes() << endl;

  // 3.) Print Average Depth / Ratio of Average Depth

  cout << "3a: " << a_tree.AverageDepth() << endl; 
  cout << "3b: " << a_tree.Ratio() << endl;

  // 4.) Find() and Recursive Stats
 
  size_t successes = 0, failures = 0;
  a_tree.resetFindRecursiveCalls();
  seq_db.open(seq_filename, fstream::in);
  while (getline(seq_db, db_line)) { // Read the file line-by-line, insert into db_line 
    if (db_line.find(" ") == db_line.npos) { // Only for lines that do not contain spaces. Skips heading.
      if (a_tree.find(db_line)) { // Find will return true or false, will also update recursive_calls
        successes++;
      }
      else {
        failures++;
      }
    }
  }
  float average_recursive_calls = a_tree.getFindRecursiveCalls() / (successes + failures);
  cout << "4a: " << successes << endl;
  cout << "4b: " << average_recursive_calls << endl; // float
  seq_db.close();

  // 5.) Attempt Removes and Recursive Stats

  seq_db.open(seq_filename, fstream::in);
  a_tree.resetRemoveRecursiveCalls();
  successes = 0;
  failures = 0;
  while (getline(seq_db, db_line)) { // Read the file line-by-line, insert into db_line 
    if (db_line.find(" ") == db_line.npos) { // Only for lines that do not contain spaces. Skips heading.
      SequenceMap x(db_line, "NULL"); 
      if (a_tree.removeSequence(x)) { // Attempt to remove the sequence
        successes++;
      }
      else {
        failures++;
      }
    }
    getline(seq_db, db_line); // Get the line to skip over.
  }
  average_recursive_calls = a_tree.getRemoveRecursiveCalls() / (successes + failures);
  cout << "5a: " << successes << endl;
  cout << "5b: " << average_recursive_calls << endl;
  seq_db.close();

  // 6.) Steps 2 and 3 again

  cout << "6a: " << a_tree.NumberofNodes() << endl;
  cout << "6b: " << a_tree.AverageDepth() << endl; 
  cout << "6c: " << a_tree.Ratio() << endl;

}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;
  AvlTree<SequenceMap> a_tree;
  TestTree(dbx_filename, seq_filename, a_tree);
  return 0;
}
