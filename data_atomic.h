// data_atomic.h -- May 9, 2009
//    by geohot
// part of "The Embedded Disassembler"
//  released under GPLv3, see http://gplv3.fsf.org/
//
// This is the level under data
// Nothing should be included
// These are the lowest level data structures in EDA
// Currently, thats just the changelists

#ifndef EDA_DATAATOMIC_H_
#define EDA_DATAATOMIC_H_

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace eda {

class Address;    // Can't actually call address

// This is a changelist that is "position independent" and "state independent"
// Should be initted as a string
// A StatelessData is now a string
class StatelessChangelist {
public:
  // This adds an assignment of the form
  // if(rhs.first)
  //   (lhs.first)lhs.second = rhs.second;
  // lhs.first is number of bits
  void add_change(const pair<string, int>& lhs, const pair<string, string>& rhs);

  // Returns first change in list
  map<pair<string, int>, pair<string, string> >::iterator get_changes();
private:
  map<pair<string, int>, pair<string, string> > changes_;
};

// This is a set of instructions to modify explicit memory
class Changelist {
public:
  Changelist(int changelist_number, Address* owner) :
    changelist_number_(changelist_number),
    owner_(owner) {};
  // This adds an assignment of the form
  // lhs = rhs;
  void add_change(Address* target, uint8_t data);

  void add_read(Address* source);

  // owner_ accessor
  Address* get_owner();

  // Returns first change in list
  map<Address*, uint8_t>::iterator get_first_change();
  bool get_next_change(map<Address*, uint8_t>::iterator* a);
private:
  // This is every change the changelist makes
  // Addresses are stored in their pointer form so no moving or renaming
  // affects them
  vector<Address*> read_; // Everything this changelist read
  map<Address*, uint8_t> changes_;
  int changelist_number_;
  Address* owner_;
};

// O -- opcode
// o -- subopcode
// F -- flags
// C -- condition
// R -- register
// I -- immed
// P -- PC offset immed
// p -- dereferenced PC offset immed
class ParsedInstruction {
public:
  // Is this valid c++?
  // Should be like printf for strings
  ParsedInstruction();
  void set(const string& format, ...);
private:
// It'd be sweet if this was a string with formatting
  string format_;
  vector<string> args_;
};

}

#endif