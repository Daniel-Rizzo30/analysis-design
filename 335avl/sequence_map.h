/* 
    Daniel Rizzo
    CSCI 335
    Homework 3 Part 1
    Professor Sven Dietrich
    March 12th, 2021
    sequence_map.h
    Contains the non-template class SequenceMap that an enzyme's recognition sequence, 
    which is some amount of nucluotides, and a vector that is to be filled with any amount
    of that sequence's acronym names.
*/

#ifndef SEQUENCE_MAP_H
#define sEQUENCE_MAP_H

#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
using namespace std;

class SequenceMap {
public:
    // Zero-parameter constructor. 
    SequenceMap() = default;

    // Parameterized constructor
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro) : recognition_sequence_{a_rec_seq} {
        enzyme_acronyms_.push_back(an_enz_acro); // Add element to the private vector. 
    }

    // Accessor Functions
    string getRecognitionSequence() const {
        return recognition_sequence_;
    }
    string getEnzymeAcronym(size_t n) const {
        if (n >= enzyme_acronyms_.size()){
            return "Invalid index";
        }
        return enzyme_acronyms_[n];
    }

    // The Big-5: No dynamic memory usage means these can use defaults.

    // Copy-constructor.
    SequenceMap(const SequenceMap &rhs) = default;

    // Copy-assignment.
    SequenceMap& operator=(const SequenceMap &rhs) = default;

    // Move-constructor.
    SequenceMap(SequenceMap &&rhs) = default;

    // Move-assignment.
    SequenceMap& operator=(SequenceMap &&rhs) = default;

    // Destructor
    ~SequenceMap() = default;

    // End Big-5

    // Comparison operator overload
    // @param rhs: the right hand side SequenceMap that is being compared to.
    // @returns true if this.recognition_sequence_ < rhs.recognition_sequence_, false otherwise.
    bool operator<(const SequenceMap &rhs) const {
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    // Output operator overload
    // @param some_sequencemap: is the object to be displayed.
    // @returns the output of the enzyme_acronyms_ vector for a given recognition_sequence_
    // The output models the output style found in rebase210.txt, included in the start files of the homework
    friend ostream& operator<<(ostream &out, const SequenceMap &some_sequencemap) {
        for (size_t i = 0; i < some_sequencemap.enzyme_acronyms_.size(); i++) {
            out << some_sequencemap.enzyme_acronyms_[i] << ' '; // Output EACH acronym in the vector, separate by slash
        }
        //out << some_sequencemap.recognition_sequence_ << "//" << endl; // End with the recognition sequence, & //
        cout << endl;
        return out;
    }

    // Merge function
    // @param other_sequence: is the object whose vector will be added to the calling SequenceMap's vector
    // @post: the calling SequenceMap's enzyme_acronyms_ will merge with the parameter SequenceMap's enzyme_acronyms_.
    void Merge(const SequenceMap &other_sequence) {
        if (recognition_sequence_ != other_sequence.recognition_sequence_) {
            return; // if the acronyms do not match, then the function should not operate. 
        }
        for (size_t i = 0; i < (other_sequence.enzyme_acronyms_).size(); i++) {
            enzyme_acronyms_.push_back((other_sequence.enzyme_acronyms_)[i]); 
        } // Add element by element to calling SequenceMap's vector, from the other_sequence's vector. 
    }

private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
};

#endif // SEQUENCE_MAP_H